#!/bin/sh

#There'll be 5 folders, one-vs-one, one-vs-all, dense, sparse and overall
#2 more folders called predict and glpk
#1. Run svm-train one-vs-one
#2. Copy all 4 files to both GLPK and predict folders
#3. Add 1st lines to both folder files
#4. Run svm-predict and store values in file
#5. Run glpk and delete all 4 files
#6. Again run svm-train one-vs all and repeat procedure

########################################################################
#IMPORTANT INFO:
# $1 is c value and $2,$3,$4,$5 are gamma values for different methods
########################################################################

#Change these values
trainingFileName='digit'
testingFileName='digit.t'
modelFileNamePrefix='digit.temp.'
outputFileNamePrefix='digit.temp-out.'
scaleRangeFile='../rangeDigit'
folderName='digitTemp'
#changes till here only

fileNameMethod='vsone'
modelFileName=${modelFileNamePrefix}${fileNameMethod}

trainingFilePath='../training/'
testingFilePath='../test/'
modelFilePath='../model/'
outputFilePath='../outputPredict/'
scaledTrainingFileName=${trainingFileName}.scale
scaledTestingFileName=${testingFileName}.scale
cd code
# Scaling both test and training files
#./svm-scale -s ${scaleRangeFile} ${trainingFilePath}${trainingFileName} > ${trainingFilePath}${scaledTrainingFileName}
#./svm-scale -r ${scaleRangeFile} ${testingFilePath}${testingFileName} > ${testingFilePath}${scaledTestingFileName}
#rm $scaleRangeFile
#scaling done

#Running training one-vs-one
./svm-train -i 0 -c $1 -g $2 ${trainingFilePath}${trainingFileName} ${modelFilePath}${modelFileName}
EXIT_STATUS=$?
if [ $EXIT_STATUS != 0 ] ; then
    exit $EXIT_STATUS
fi

#Updating Variables for one-vs-all
fileNameMethod='vsall'
modelFileName=${modelFileNamePrefix}${fileNameMethod}
#Running training one-vs-all
./svm-train -i 1 -c $1 -g $3 ${trainingFilePath}${trainingFileName} ${modelFilePath}${modelFileName}
EXIT_STATUS=$?
if [ $EXIT_STATUS != 0 ] ; then
    exit $EXIT_STATUS
fi

#Updating Variables for dense
fileNameMethod='dense'
modelFileName=${modelFileNamePrefix}${fileNameMethod}
#Running training dense
./svm-train -i 2 -c $1 -g $4 ${trainingFilePath}${trainingFileName} ${modelFilePath}${modelFileName}
EXIT_STATUS=$?
if [ $EXIT_STATUS != 0 ] ; then
    exit $EXIT_STATUS
fi

#Updating Variables for sparse
fileNameMethod='sparse'
modelFileName=${modelFileNamePrefix}${fileNameMethod}
#Running training sparse
./svm-train -i 3 -c $1 -g $5 ${trainingFilePath}${trainingFileName} ${modelFilePath}${modelFileName}
EXIT_STATUS=$?
if [ $EXIT_STATUS != 0 ] ; then
    exit $EXIT_STATUS
fi

#All training for each method complete
#Raw GLPK files for each method made (without adding 1st lines)

#Removing unnecessary files
rm -v kernel_bsv_bsv.txt
rm -v kernel_bsv_sv.txt
rm -v matrix_K_sv.txt
