/*
 *
 *	This is a simple program that tries to invert matrices repeatedly 
 *  using MATLAB Engine functions from a C++ program.
 *
 * Copyright Amogh Tolay
 * All rights reserved
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/usr/local/MATLAB/R2011a/extern/include/engine.h"
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define  BUFSIZE 256

int main()

{
	Engine *ep;
	mxArray *result = NULL;
	double resultOfCPP[1];
	
	if (!(ep = engOpen("matlab -nodisplay"))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}
	engSetVisible(ep,0);
	bool vis;
	engGetVisible(ep, &vis);
	printf("The visibility is %d", vis);
	/*
	 * Below is code for concurrent processes
	 */
	// Naming as follows:
	// matlabFd is a pipe TO MATLAB. So, Matlab reads from it and SVM writes to it
	// svmFd is a pipe TO SVM. So, SVM reads from it and Matlab writes to it
	int matlabFd, svmFd;

	
	// Create 2 pipes - one for writing to and one for reading from
	char matlabPipe[] = "matlabPipe";  // Use to read from the SVM
	char svmPipe[] = "svmPipe";        // Use to write to the SVM

	while (1) {
		// Wait in a loop for request, process it, and write back the inverted matrix as result
		
		matlabFd = open(matlabPipe, O_RDONLY); // Blocks till something is written to it by the SVM
		// Something written by parent	
		if (matlabFd == -1) {
			printf("Pipe to read from SVM could not be opened\n");
			return EXIT_FAILURE;
		}
		char buff[10];
		memset(buff, '\0', 10); // Sets all bytes of the buffer to the null char. Important as buffer needs to be reset.
		read(matlabFd, buff, 10);
		close(matlabFd);
		printf("Received %s from SVM\n", buff);
		
		if (strcmp(buff, "quit") == 0) {
			// Time to QUIT after winding up
			break;
		}

		/*
		 * Do stuff here
		*/
		// All commands are given here (using evalString)

		engEvalString(ep, "km = load('matrix_K_sv.txt');");
		engEvalString(ep, "K_sv_inverse = pinv(km);");
		engEvalString(ep, "span1 = max( 1.0 ./ diag(K_sv_inverse));");
		engEvalString(ep, "span2 = 0.0;");
		engEvalString(ep, "bsv_bsv_km = load('kernel_bsv_bsv.txt');");
		engEvalString(ep, "[bsv_row, bsv_col] = size(bsv_bsv_km);");
		engEvalString(ep, "if( bsv_row > 0 ) bsv_sv_km = load('kernel_bsv_sv.txt'); span2 = max(diag(bsv_bsv_km) - diag(bsv_sv_km' * K_sv_inverse * bsv_sv_km)); end;");
		engEvalString(ep, "span = max(span1, span2);");

		if ((result = engGetVariable(ep,"span")) == NULL)
			printf("Couldn't copy the answer into CPP Code\n\n");
		else
			memcpy((void *)resultOfCPP, (void *)mxGetPr(result), sizeof(resultOfCPP));

		FILE *fp;
		fp = fopen("spans_out.txt", "a");
		if (fp == NULL)
		{
			printf("\nError in opening spans_out file\n\n");
			exit(EXIT_FAILURE);
		}
		fprintf(fp, "%f\n", *resultOfCPP);
		fclose(fp);
			
		// Commands end here
		
		// Ready with the inverse!!
		svmFd = open(svmPipe, O_WRONLY);
		if (svmFd == -1) {
			printf("Pipe to write to SVM could not be opened\n");
			return EXIT_FAILURE;
		}
		write(svmFd, "done", sizeof("done"));
		close(svmFd);
	}

	/*
	 * Engine closes here, finish everything till here
	*/
	engClose(ep);
	
	// Then send a over signal to the SVM process
	svmFd = open(svmPipe, O_WRONLY);
	if (svmFd == -1) {
		printf("Pipe to write to SVM could not be opened\n");
		return EXIT_FAILURE;
	}
	write(svmFd, "over", sizeof("over"));
	close(svmFd);

	printf("Now, exiting child (MATLAB) process....\n");
	
	return EXIT_SUCCESS;
}
