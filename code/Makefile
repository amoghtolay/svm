CXXC = g++
CFLAGS = -Wall -O3 -g

###########################################################
# IMPORTANT NOTE:
# Read or else make will fail
# Please ensure appropriate Matlab environment variables are set as described below
###########################################################

all: svm-train svm-predict svm-scale efficiency span-calc test-script cleanGLPK
	chmod +x ../gridSearchAux0.sh
	chmod +x ../gridSearchAux1.sh
	chmod +x ../removeFiles.sh
svm-predict: svm-predict.c svm.o
	$(CXXC) $(CFLAGS) svm-predict.c svm.o -o svm-predict -lm
svm-train: svm-train.c svm.o
	$(CXXC) $(CFLAGS) svm-train.c svm.o -o svm-train -lm
svm-scale: svm-scale.c
	$(CXXC) $(CFLAGS) svm-scale.c -o svm-scale
svm.o: svm.cpp svm.h
	$(CXXC) $(CFLAGS) -c svm.cpp
# This is the span calculate function written by Amogh at home that uses
# Matlab engine (so that matlab can run parallely in another process)
#
# Please ensure matlab is installed and run the following commands on a new system:
# export PATH=$PATH:/usr/local/MATLAB/R2011a/bin
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/MATLAB/R2011a/bin/glnxa64:/usr/local/MATLAB/R2011a/sys/os/glnxa64
# Or add these env var to /etc/bash.bashrc
span-calc:
	mex -f /usr/local/MATLAB/R2011a/bin/engopts.sh ./computeSpanMatlabEng.cpp
efficiency:
	g++-4.4 -g -lglpk glpk_4params.cpp -o glpk_efficiency
	g++ -g compute_average_vsone.cpp -o compute-average
test-script:
	chmod +x ../runWithTest.sh
	chmod +x ../runWithoutTest.sh
clean:
	rm -f *~ svm.o svm-train svm-predict svm-scale compute-average computeSpanMatlabEng glpk_efficiency
	rm -vf kernel_bsv_bsv.txt kernel_bsv_sv.txt matrix_K_sv.txt spans_out.txt svmPipe matlabPipe
cleanGLPK:
	rm -vf ../GLPK_Files/dense/* ../GLPK_Files/one-vs-all/* ../GLPK_Files/one-vs-one/* ../GLPK_Files/sparse/* ../GLPK_Files/overall/*
	rm -vf ../Debugging/*
