#include <stdio.h>
#include <stdlib.h>
#include "glpk.h"   
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

void formulate_prob(int* ia, int* ja, double* ar, char* argv[])
{
	//Openining all four file pointers here AGAIN!!
	FILE* fp_margin_table = NULL;
	FILE* fp_accuracy_table = NULL;
	FILE* fp_spans_table = NULL;
	FILE* fp_nSV_table = NULL;
	if (argv[1][0] == '0')
	{
		fp_margin_table = fopen("../GLPK_Files/one-vs-one/margin_glpk", "r");
		fp_accuracy_table = fopen("../GLPK_Files/one-vs-one/accuracy_glpk", "r");
		fp_spans_table = fopen("../GLPK_Files/one-vs-one/spans_glpk", "r");
		fp_nSV_table = fopen("../GLPK_Files/one-vs-one/nSV_glpk", "r");
	}
	
	else if (argv[1][0] == '1')
	{
		fp_margin_table = fopen("../GLPK_Files/one-vs-all/margin_glpk", "r");
		fp_accuracy_table = fopen("../GLPK_Files/one-vs-all/accuracy_glpk", "r");
		fp_spans_table = fopen("../GLPK_Files/one-vs-all/spans_glpk", "r");
		fp_nSV_table = fopen("../GLPK_Files/one-vs-all/nSV_glpk", "r");
	}
	
	else if (argv[1][0] == '2')
	{
		fp_margin_table = fopen("../GLPK_Files/dense/margin_glpk", "r");
		fp_accuracy_table = fopen("../GLPK_Files/dense/accuracy_glpk", "r");
		fp_spans_table = fopen("../GLPK_Files/dense/spans_glpk", "r");
		fp_nSV_table = fopen("../GLPK_Files/dense/nSV_glpk", "r");
	}
	
	else if (argv[1][0] == '3')
	{
		fp_margin_table = fopen("../GLPK_Files/sparse/margin_glpk", "r");
		fp_accuracy_table = fopen("../GLPK_Files/sparse/accuracy_glpk", "r");
		fp_spans_table = fopen("../GLPK_Files/sparse/spans_glpk", "r");
		fp_nSV_table = fopen("../GLPK_Files/sparse/nSV_glpk", "r");
	}
	
	else if (argv[1][0] == '4')
	{
		fp_margin_table = fopen("../GLPK_Files/overall/margin_glpk", "r");
		fp_accuracy_table = fopen("../GLPK_Files/overall/accuracy_glpk", "r");
		fp_spans_table = fopen("../GLPK_Files/overall/spans_glpk", "r");
		fp_nSV_table = fopen("../GLPK_Files/overall/nSV_glpk", "r");
	}
	
	if( fp_margin_table == NULL || fp_accuracy_table == NULL || fp_spans_table == NULL || fp_nSV_table == NULL)
	{
		printf("One of the *_glpk files could not be opened for formulating the table\n");
		exit(3);
	}
	//All file pointers successfully opened
	//no_hyper stored from 1st line of file
	int no_hyper=0;
	fscanf(fp_margin_table, "%d", &no_hyper);
	fscanf(fp_accuracy_table, "%d", &no_hyper);
	fscanf(fp_spans_table, "%d", &no_hyper);
	fscanf(fp_nSV_table, "%d", &no_hyper);
	
	for(int i=5, val=2; i<=((no_hyper+1)*4); i=i+4, val++)
	{
		//Reading all values from the same line from al four files
		double margin, accuracy, spans, nSV;
		fscanf(fp_margin_table, "%lf", &margin);
		fscanf(fp_accuracy_table, "%lf", &accuracy);
		fscanf(fp_spans_table, "%lf", &spans);
		fscanf(fp_nSV_table, "%lf", &nSV);

		//Formulating the table
		ia[i]   = val; ja[i]   = 1; ar[i] = -(spans); 
		ia[i+1] = val; ja[i+1] = 2; ar[i+1] = -(nSV); 
		ia[i+2] = val; ja[i+2] = 3; ar[i+2] = margin; 
		ia[i+3] = val; ja[i+3] = 4; ar[i+3] = accuracy;		
		
		//cout<<"ar["<<i<<"] = "<<ar[i]<<"\tar["<<i+1<<"] = "<<ar[i+1]<<"\tar["<<i+2<<"] = "<<ar[i+2]<<"\tar["<<i+3<<"] = "<<ar[i+3]<<"\n";		

	}
	fclose(fp_margin_table);
	fclose(fp_accuracy_table);
	fclose(fp_spans_table);
	fclose(fp_nSV_table);
}

void exitHelp()
{
	cout<<"Please give 1 parameter to this file.\nWrite \n0 if One-vs-One\n1 if One-vs-all\n2 if Dense\n3 if Sparse\n";
	exit(1);
}
//Function to compute cross effeciencies (eff with wts of others)
void crossEff(double* wtSpan, double* wtMargin, double* wtAccuracy, double* wtnSV, char* argv[])
{
	//Openining all four file pointers here
	FILE* fp_margin=NULL;
	FILE* fp_accuracy=NULL;
	FILE* fp_spans=NULL;
	FILE* fp_nSV=NULL;
	ifstream fp_hyperplaneClass;
	ofstream fp_outCrossEff;
	if (argv[1][0] == '0')
	{
		fp_margin = fopen("../GLPK_Files/one-vs-one/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/one-vs-one/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/one-vs-one/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/one-vs-one/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/one-vs-one/hyperplaneClass_glpk");
		fp_outCrossEff.open("../GLPK_Files/one-vs-one/crossEfficiency_glpk.txt");
	}
	
	else if (argv[1][0] == '1')
	{
		fp_margin = fopen("../GLPK_Files/one-vs-all/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/one-vs-all/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/one-vs-all/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/one-vs-all/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/one-vs-all/hyperplaneClass_glpk");
		fp_outCrossEff.open("../GLPK_Files/one-vs-all/crossEfficiency_glpk.txt");
	}
	
	else if (argv[1][0] == '2')
	{
		fp_margin = fopen("../GLPK_Files/dense/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/dense/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/dense/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/dense/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/dense/hyperplaneClass_glpk");
		fp_outCrossEff.open("../GLPK_Files/dense/crossEfficiency_glpk.txt");
	}
	
	else if (argv[1][0] == '3')
	{
		fp_margin = fopen("../GLPK_Files/sparse/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/sparse/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/sparse/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/sparse/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/sparse/hyperplaneClass_glpk");
		fp_outCrossEff.open("../GLPK_Files/sparse/crossEfficiency_glpk.txt");
	}
	
	else if (argv[1][0] == '4')
	{
		fp_margin = fopen("../GLPK_Files/overall/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/overall/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/overall/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/overall/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/overall/hyperplaneClass_glpk");
		fp_outCrossEff.open("../GLPK_Files/overall/crossEfficiency_glpk.txt");
	}
	
	if( fp_margin == NULL || fp_accuracy == NULL || fp_spans == NULL || fp_nSV == NULL || fp_hyperplaneClass == NULL || fp_outCrossEff == NULL)
	{
		printf("One of the *_glpk files could not be opened\n");
		exit(2);
	}
	//All file pointers successfully opened
	
	//Now, reading no. of hyperplanes to get no of rows
	int no_hyper[5];
	fscanf(fp_margin, "%d", &no_hyper[0]);
	fscanf(fp_accuracy, "%d", &no_hyper[1]);
	fscanf(fp_spans, "%d", &no_hyper[2]);
	fscanf(fp_nSV, "%d", &no_hyper[3]);
	fp_hyperplaneClass>>no_hyper[4];
	
	for (int i=0; i<4; i++)
		if(no_hyper[i] != no_hyper[i+1])
		{
			cout<<"1st lines of four files do not match";
			exit(3);
		}
	//Done Reading no of hyper_planes available in any element of this array
	double margin;
	while(fscanf(fp_margin, "%lf", &margin) !=EOF) 
	{
		double accuracy, spans, nSV, effSum = 0;
		string hypClassLabel;
		fscanf(fp_accuracy, "%lf", &accuracy);
		fscanf(fp_spans, "%lf", &spans);
		fscanf(fp_nSV, "%lf", &nSV);
		fp_hyperplaneClass>>hypClassLabel;
		
		fp_outCrossEff<<hypClassLabel<<":";
		for(int i=0;i<no_hyper[0];i++)
			effSum += (wtAccuracy[i] * accuracy + wtMargin[i] * margin) / (wtSpan[i] * spans + wtnSV[i] * nSV);
		
		fp_outCrossEff<<effSum/no_hyper[0]<<"\n";
	}
	fclose(fp_margin);
	fclose(fp_accuracy);
	fclose(fp_spans);
	fclose(fp_nSV);
	fp_outCrossEff.close();
	fp_hyperplaneClass.close();
}

int main(int argc, char *argv[] )
{
	string fileName;
	ofstream fp_output;

	if( argc != 2 )
		exitHelp();
	cout<<"\n"<<argc;
	
	if (argv[1][0]=='0')
		fp_output.open("../GLPK_Files/one-vs-one/output_efficiencies.vsone.txt");
	else if (argv[1][0]=='1')
			fp_output.open("../GLPK_Files/one-vs-all/output_efficiencies.vsall.txt");
	else if (argv[1][0] == '2')
		fp_output.open("../GLPK_Files/dense/output_efficiencies.dense.txt");
	else if (argv[1][0] == '3')
		fp_output.open("../GLPK_Files/sparse/output_efficiencies.sparse.txt");
	else if (argv[1][0]=='4')
			fp_output.open("../GLPK_Files/overall/output_efficiencies.overall.txt");
	else 
		exitHelp();
	
	//Definition of problem and defining vars
	
	 
    glp_prob *lp;
    //int ia[1+8000], ja[1+8000];
	int *ia, *ja;
	double* ar;
	double Z, u1,u2,v1,v2;
	//Declared for cross-effeciency
	//Holds the sum of the corr weights
	double *wtSpan, *wtMargin, *wtAccuracy, *wtnSV;
	int counter = 0;
	
	if( fp_output == NULL )
	{
		printf("output_efficiencies file could not be created\n");
		exit(1);
	}		
			
	lp = glp_create_prob();
	
	glp_set_prob_name(lp, "best_hyperplane");
	
	//Openining all four file pointers here
	FILE* fp_margin=NULL;
	FILE* fp_accuracy=NULL;
	FILE* fp_spans=NULL;
	FILE* fp_nSV=NULL;
	ifstream fp_hyperplaneClass;
	if (argv[1][0] == '0')
	{
		fp_margin = fopen("../GLPK_Files/one-vs-one/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/one-vs-one/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/one-vs-one/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/one-vs-one/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/one-vs-one/hyperplaneClass_glpk");
	}
	
	else if (argv[1][0] == '1')
	{
		fp_margin = fopen("../GLPK_Files/one-vs-all/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/one-vs-all/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/one-vs-all/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/one-vs-all/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/one-vs-all/hyperplaneClass_glpk");
	}
	
	else if (argv[1][0] == '2')
	{
		fp_margin = fopen("../GLPK_Files/dense/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/dense/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/dense/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/dense/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/dense/hyperplaneClass_glpk");
	}
	
	else if (argv[1][0] == '3')
	{
		fp_margin = fopen("../GLPK_Files/sparse/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/sparse/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/sparse/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/sparse/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/sparse/hyperplaneClass_glpk");
	}
	
	else if (argv[1][0] == '4')
	{
		fp_margin = fopen("../GLPK_Files/overall/margin_glpk", "r");
		fp_accuracy = fopen("../GLPK_Files/overall/accuracy_glpk", "r");
		fp_spans = fopen("../GLPK_Files/overall/spans_glpk", "r");
		fp_nSV = fopen("../GLPK_Files/overall/nSV_glpk", "r");
		fp_hyperplaneClass.open("../GLPK_Files/overall/hyperplaneClass_glpk");
	}
	
	if( fp_margin == NULL || fp_accuracy == NULL || fp_spans == NULL || fp_nSV == NULL || fp_hyperplaneClass == NULL)
	{
		printf("One of the *_glpk files could not be opened\n");
		exit(2);
	}
	//All file pointers successfully opened
	
	//Now, reading no. of hyperplanes to get no of rows
	int no_hyper[5];
	fscanf(fp_margin, "%d", &no_hyper[0]);
	fscanf(fp_accuracy, "%d", &no_hyper[1]);
	fscanf(fp_spans, "%d", &no_hyper[2]);
	fscanf(fp_nSV, "%d", &no_hyper[3]);
	fp_hyperplaneClass>>no_hyper[4];
	
	for (int i=0; i<4; i++)
	{
		if(no_hyper[i] != no_hyper[i+1])
		{
			cout<<"1st lines of four files do not match";
			exit(3);
		}
	}
	//Done Reading no of hyper_planes available in any element of this array
	ia = new int[(no_hyper[0]+1)*4 + 1];
	ja = new int[(no_hyper[0]+1)*4 + 1];
	ar = new double[(no_hyper[0]+1)*4 + 1];
	
	//Alotting memory for weights for cross efficiency
	wtSpan = new double[no_hyper[0]];
	wtAccuracy = new double[no_hyper[0]];
	wtMargin = new double[no_hyper[0]];
	wtnSV = new double[no_hyper[0]];
		
	glp_set_obj_dir(lp, GLP_MAX);
	glp_add_rows(lp,(no_hyper[0]+1));
	
	glp_set_row_bnds(lp, 1, GLP_FX, 1.0, 1.0);
	for(int i=2; i<=(no_hyper[0]+1); i++)
		glp_set_row_bnds(lp, i, GLP_UP, 0.0, 0.0);
		
	//Adding Rows ends
	double margin=0, accuracy=0, spans=0, nSV=0;
	string hypClassLabel;
	glp_add_cols(lp, 4);
	
	while(fscanf(fp_margin, "%lf", &margin) !=EOF) 
	{
		fscanf(fp_accuracy, "%lf", &accuracy);
		fscanf(fp_spans, "%lf", &spans);
		fscanf(fp_nSV, "%lf", &nSV);
		fp_hyperplaneClass>>hypClassLabel;
		
		/*
		Setting the objective of the LP, ie. Maximize (v1*margin + v2*accuracy)
		That is, maximize the numerator(output's linear combination)
		*/
		glp_set_col_name(lp, 1, "u1");
		glp_set_col_bnds(lp, 1, GLP_LO, 0.00001, 0.0);
		glp_set_obj_coef(lp, 1, 0.0);
	
		glp_set_col_name(lp, 2, "u2");
		glp_set_col_bnds(lp, 2, GLP_LO, 0.00001, 0.0);
		glp_set_obj_coef(lp, 2, 0.0);
						
		glp_set_col_name(lp, 3, "v1");
		glp_set_col_bnds(lp, 3, GLP_LO, 0.00001, 0.0);
		glp_set_obj_coef(lp, 3, margin);
		
		glp_set_col_name(lp, 4, "v2");
		glp_set_col_bnds(lp, 4, GLP_LO, 0.00001, 0.0);
		glp_set_obj_coef(lp, 4, accuracy);
		//Columns all set!
		
		//Assigning the 1st row, ie lin. combination of inputs=1
		//Now inserting 1st row in table
		ia[1] = 1; ja[1] = 1; ar[1] = spans; /* a[1,1]=spans*/
		ia[2] = 1; ja[2] = 2; ar[2] = nSV; /* a[1,2] = nSV*/
		ia[3] = 1; ja[3] = 3; ar[3] = 0.0; /* a[1,3] = 0 (v1) */
		ia[4] = 1; ja[4] = 4; ar[4] = 0.0; /* a[1,4] = 0 (v2) */
		
		//Call function to formulate the rest of the rows
		//cout<<"\nar[1] = "<<ar[1]<<"\tar[2] = "<<ar[2]<<"\tar[3] = "<<ar[3]<<"\tar[4] = "<<ar[4]<<"\n";
		formulate_prob(ia, ja, ar,argv);
		//Now, we have the table also
		
		//Load Matrix of LP and solve LP+write the file
		/*
		 * Code corrected here on 14th March.
		 * Efficiency greater than 1 problem corrected
		 * by changing the 2nd parameter of functionn call glp_load_matrix
		 * to present value (adding 1)
		 */ 
		glp_load_matrix(lp, ((no_hyper[0]+1)*4), ia, ja, ar);
		glp_simplex(lp, NULL);
		Z = glp_get_obj_val(lp);
		
		u1 = glp_get_col_prim(lp, 1);
		u2 = glp_get_col_prim(lp, 2);
		v1 = glp_get_col_prim(lp, 3);
		v2 = glp_get_col_prim(lp, 4);
		
		wtSpan[counter] = u1; 
		wtnSV[counter] = u2;
		wtMargin[counter] = v1;
		wtAccuracy[counter] = v2;
		counter++;
		
		cout.precision(16);
		fp_output<<hypClassLabel<<":"<<Z<<"\n";
		//fp_output<<hypClassLabel<<": Z = "<<Z<<";\tu1(spans) = "<<u1<<";\tu2(nSV) = "<<u2<<";\tv1(margin) = "<<v1<<";\tv2(accuracy) = "<<v2<<";\n";
		printf("\nZ = %g; u1 = %g; u2 = %g; v1 = %g; v2 = %g;\n\n", Z, u1, u2, v1, v2);
	}
	fclose(fp_margin);
	fclose(fp_accuracy);
	fclose(fp_spans);
	fclose(fp_nSV);
	fp_output.close();
	fp_hyperplaneClass.close();
    //Adding columns ends here
	
	
	//computing cross efficiency code
	crossEff(wtSpan,wtMargin,wtAccuracy,wtnSV,argv);
	
	//Table ends here
	//Deleting all GLPK files as they are no longer needed
	//system("rm accuracy_glpk");
	//system("rm margin_glpk");
	//system("rm spans_glpk");
	//system("rm nSV_glpk");
	//system("rm hyperplaneClass_glpk");
	
	if (argv[1][0] == '0')
		system("./compute-average");
	
	glp_delete_prob(lp);
	return 0;
}

