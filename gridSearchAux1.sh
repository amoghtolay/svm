#!/bin/sh

#There'll be 5 folders, one-vs-one, one-vs-all, dense, sparse and overall
#2 more folders called predict and glpk
#1. Run svm-train one-vs-one
#2. Copy all 4 files to both GLPK and predict folders
#3. Add 1st lines to both folder files
#4. Run svm-predict and store values in file
#5. Run glpk and delete all 4 files
#6. Again run svm-train one-vs all and repeat procedure

#Change these values
trainingFileName='dna.scale'
testingFileName='dna.scale.t'
modelFileNamePrefix='dna.scale.model.'
outputFileNamePrefix='dna.scale-out.'
scaleRangeFile='../rangeDNA'
folderName='dna'
#changes till here only


fileNameMethod='vsone'
modelFileName=${modelFileNamePrefix}${fileNameMethod}

trainingFilePath='../training/'
testingFilePath='../test/'
modelFilePath='../model/'
outputFilePath='../outputPredict/'
scaledTrainingFileName=${trainingFileName}.scale
scaledTestingFileName=${testingFileName}.scale

#REPEAT PROCEDURE FOR OTHERS TOO FROM HERE
###########################################
#Adding First line to each file individually and moving them back
cd GLPK_Files/one-vs-one
for file in *_glpk ; do
	lineCount=`cat $file | wc -l`
	sed "1 i\
$lineCount" $file > ${file}.new
mv -vf ${file}.new $file
done

#Don't need to run svm-predict for grid searching of parameters
#Now run svm-predict for one-vs-one
#fileNameMethod='vsone'
#outputFileName=${outputFileNamePrefix}${fileNameMethod}
cd ../../code/
#./svm-predict ${testingFilePath}${testingFileName} ${modelFilePath}${modelFileName} ${outputFilePath}${outputFileName}
#mv -v test_accuracyHyperplane.txt ../GLPK_Files/one-vs-one/testAccuracy.txt
#Now run glpk for one-vs-one
./glpk_efficiency 0

###########################################
#Adding First line to each file individually and moving them back
cd ../GLPK_Files/one-vs-all
for file in *_glpk ; do
	lineCount=`cat $file | wc -l`
	sed "1 i\
$lineCount" $file > ${file}.new
mv -vf ${file}.new $file
done

#Now run svm-predict for one-vs-all
#fileNameMethod='vsall'
#outputFileName=${outputFileNamePrefix}${fileNameMethod}
cd ../../code/
#./svm-predict ${testingFilePath}${testingFileName} ${modelFilePath}${modelFileName} ${outputFilePath}${outputFileName}
#mv -v test_accuracyHyperplane.txt ../GLPK_Files/one-vs-all/testAccuracy.txt
#Now run glpk for one-vs-all
./glpk_efficiency 1

###########################################
#Adding First line to each file individually and moving them back
cd ../GLPK_Files/dense
for file in *_glpk ; do
	lineCount=`cat $file | wc -l`
	sed "1 i\
$lineCount" $file > ${file}.new
mv -vf ${file}.new $file
done

#Now run svm-predict for dense
#fileNameMethod='dense'
#outputFileName=${outputFileNamePrefix}${fileNameMethod}
cd ../../code/
#./svm-predict ${testingFilePath}${testingFileName} ${modelFilePath}${modelFileName} ${outputFilePath}${outputFileName}
#mv -v test_accuracyHyperplane.txt ../GLPK_Files/dense/testAccuracy.txt
#Now run glpk for dense
./glpk_efficiency 2

###########################################
#Adding First line to each file individually and moving them back
cd ../GLPK_Files/sparse
for file in *_glpk ; do
	lineCount=`cat $file | wc -l`
	sed "1 i\
$lineCount" $file > ${file}.new
mv -vf ${file}.new $file
done

#Now run svm-predict for sparse
#fileNameMethod='sparse'
#outputFileName=${outputFileNamePrefix}${fileNameMethod}
cd ../../code/
#./svm-predict ${testingFilePath}${testingFileName} ${modelFilePath}${modelFileName} ${outputFilePath}${outputFileName}
#mv -v test_accuracyHyperplane.txt ../GLPK_Files/sparse/testAccuracy.txt
#Now run glpk for sparse
./glpk_efficiency 3
