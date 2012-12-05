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
trainingFileName='digit'
testingFileName='digit.t'
modelFileNamePrefix='digit.temp.'
outputFileNamePrefix='digit.temp-out.'
scaleRangeFile='../rangeDigit'
folderName='digitTemp'
#changes till here only


rm -v GLPK_Files/one-vs-one/hyperplaneClass_glpk
rm -v GLPK_Files/one-vs-one/accuracy_glpk
rm -v GLPK_Files/one-vs-one/margin_glpk
rm -v GLPK_Files/one-vs-one/spans_glpk
rm -v GLPK_Files/one-vs-one/nSV_glpk
mv -v GLPK_Files/one-vs-one/crossEfficiency_glpk.txt GLPK_Files/one-vs-one/crossEfficiency_glpk.allhyper.txt
rm -v GLPK_Files/one-vs-one/output_efficiencies.vsone.txt
rm -v GLPK_Files/one-vs-one/avg_efficiencies.vsone.txt

rm -v GLPK_Files/one-vs-all/hyperplaneClass_glpk
rm -v GLPK_Files/one-vs-all/accuracy_glpk
rm -v GLPK_Files/one-vs-all/margin_glpk
rm -v GLPK_Files/one-vs-all/spans_glpk
rm -v GLPK_Files/one-vs-all/nSV_glpk
mv -v GLPK_Files/one-vs-all/crossEfficiency_glpk.txt GLPK_Files/one-vs-all/crossEfficiency_glpk.allhyper.txt
rm -v GLPK_Files/one-vs-all/output_efficiencies.vsall.txt

rm -v GLPK_Files/dense/hyperplaneClass_glpk
rm -v GLPK_Files/dense/accuracy_glpk
rm -v GLPK_Files/dense/margin_glpk
rm -v GLPK_Files/dense/spans_glpk
rm -v GLPK_Files/dense/nSV_glpk
mv -v GLPK_Files/dense/crossEfficiency_glpk.txt GLPK_Files/dense/crossEfficiency_glpk.allhyper.txt
rm -v GLPK_Files/dense/output_efficiencies.dense.txt

rm -v GLPK_Files/sparse/hyperplaneClass_glpk
rm -v GLPK_Files/sparse/accuracy_glpk
rm -v GLPK_Files/sparse/margin_glpk
rm -v GLPK_Files/sparse/spans_glpk
rm -v GLPK_Files/sparse/nSV_glpk
mv -v GLPK_Files/sparse/crossEfficiency_glpk.txt GLPK_Files/sparse/crossEfficiency_glpk.allhyper.txt
rm -v GLPK_Files/sparse/output_efficiencies.sparse.txt

#########################################
# IMPORTANT INFO:
# $1 is c value and $2 is gamma value for one-vs-one
# $3 is c value and $4 is gamma value for one-vs-all
# $5 is c value and $6 is gamma value for dense
# $7 is c value and $8 is gamma value for sparse
#########################################
fileNameMethod='vsone'
modelFileName=${modelFileNamePrefix}${fileNameMethod}

trainingFilePath='../training/'
#testingFilePath='../test/'
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
#Moving all GLPK files to one-vs-one folder
#mv -v accuracy_glpk ../GLPK_Files/one-vs-one/accuracy_glpk
#mv -v margin_glpk ../GLPK_Files/one-vs-one/margin_glpk
#mv -v spans_glpk ../GLPK_Files/one-vs-one/spans_glpk
#mv -v nSV_glpk ../GLPK_Files/one-vs-one/nSV_glpk
#mv -v hyperplaneClass_glpk ../GLPK_Files/one-vs-one/hyperplaneClass_glpk

#Updating Variables for one-vs-all
fileNameMethod='vsall'
modelFileName=${modelFileNamePrefix}${fileNameMethod}
#Running training one-vs-all
./svm-train -i 1 -c $3 -g $4 ${trainingFilePath}${trainingFileName} ${modelFilePath}${modelFileName}
#Moving all GLPK files to one-vs-one folder
#mv -v accuracy_glpk ../GLPK_Files/one-vs-all/accuracy_glpk
#mv -v margin_glpk ../GLPK_Files/one-vs-all/margin_glpk
#mv -v spans_glpk ../GLPK_Files/one-vs-all/spans_glpk
#mv -v nSV_glpk ../GLPK_Files/one-vs-all/nSV_glpk
#mv -v hyperplaneClass_glpk ../GLPK_Files/one-vs-all/hyperplaneClass_glpk

#Updating Variables for dense
fileNameMethod='dense'
modelFileName=${modelFileNamePrefix}${fileNameMethod}
#Running training dense
./svm-train -i 2 -c $5 -g $6 ${trainingFilePath}${trainingFileName} ${modelFilePath}${modelFileName}
#Moving all GLPK files to one-vs-one folder
#mv -v accuracy_glpk ../GLPK_Files/dense/accuracy_glpk
#mv -v margin_glpk ../GLPK_Files/dense/margin_glpk
#mv -v spans_glpk ../GLPK_Files/dense/spans_glpk
#mv -v nSV_glpk ../GLPK_Files/dense/nSV_glpk
#mv -v hyperplaneClass_glpk ../GLPK_Files/dense/hyperplaneClass_glpk

#Updating Variables for sparse
fileNameMethod='sparse'
modelFileName=${modelFileNamePrefix}${fileNameMethod}
#Running training dense
./svm-train -i 3 -c $7 -g $8 ${trainingFilePath}${trainingFileName} ${modelFilePath}${modelFileName}
#Moving all GLPK files to one-vs-one folder
#mv -v accuracy_glpk ../GLPK_Files/sparse/accuracy_glpk
#mv -v margin_glpk ../GLPK_Files/sparse/margin_glpk
#mv -v spans_glpk ../GLPK_Files/sparse/spans_glpk
#mv -v nSV_glpk ../GLPK_Files/sparse/nSV_glpk
#mv -v hyperplaneClass_glpk ../GLPK_Files/sparse/hyperplaneClass_glpk

#All training for each method complete
#Raw GLPK files for each method made (without adding 1st lines)

#Removing unnecessary files
rm -v kernel_bsv_bsv.txt
rm -v kernel_bsv_sv.txt
rm -v matrix_K_sv.txt

#concatenate each GLPK file to form one for overall
cd ../GLPK_Files/
cat one-vs-one/accuracy_glpk one-vs-all/accuracy_glpk dense/accuracy_glpk sparse/accuracy_glpk > overall/accuracy_glpk
cat one-vs-one/margin_glpk one-vs-all/margin_glpk dense/margin_glpk sparse/margin_glpk > overall/margin_glpk
cat one-vs-one/nSV_glpk one-vs-all/nSV_glpk dense/nSV_glpk sparse/nSV_glpk > overall/nSV_glpk
cat one-vs-one/spans_glpk one-vs-all/spans_glpk dense/spans_glpk sparse/spans_glpk > overall/spans_glpk
cat one-vs-one/hyperplaneClass_glpk one-vs-all/hyperplaneClass_glpk dense/hyperplaneClass_glpk sparse/hyperplaneClass_glpk > overall/hyperplaneClass_glpk

#REPEAT PROCEDURE FOR OTHERS TOO FROM HERE
###########################################
#Adding First line to each file individually and moving them back
cd one-vs-one
for file in *_glpk ; do
	lineCount=`cat $file | wc -l`
	sed "1 i\
$lineCount" $file > ${file}.new
mv -vf ${file}.new $file
done

#Now run svm-predict for one-vs-one
#fileNameMethod='vsone'
#outputFileName=${outputFileNamePrefix}${fileNameMethod}
cd ../../code/
#./svm-predict ${testingFilePath}${testingFileName} ${modelFilePath}${modelFileName} ${outputFilePath}${outputFileName}
#mv -v test_accuracyHyperplane.txt ../GLPK_Files/one-vs-one/testAccuracy.txt
#Now run glpk for one-vs-one
./glpk_efficiency 0
#Removing all GLPK Input files
#rm -v hyperplaneClass_glpk
#moving output GLPK files to appropriate locations
#mv -v output_efficiencies.vsone.txt ../GLPK_Files/one-vs-one/output_efficiencies.vsone.txt
#mv -v crossEfficiency_glpk.txt ../GLPK_Files/one-vs-one/crossEfficiency_glpk.txt
#mv -v avg_efficiencies.vsone.txt ../GLPK_Files/one-vs-one/avg_efficiencies.vsone.txt
##################################################
#Repeat till here

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
#Removing all GLPK Input files
#rm -v hyperplaneClass_glpk
#moving output GLPK files to appropriate locations
#mv -v output_efficiencies.vsall.txt ../GLPK_Files/one-vs-all/output_efficiencies.vsall.txt
#mv -v crossEfficiency_glpk.txt ../GLPK_Files/one-vs-all/crossEfficiency_glpk.txt
##################################################

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
#Removing all GLPK Input files
#rm -v hyperplaneClass_glpk
#moving output GLPK files to appropriate locations
#mv -v output_efficiencies.dense.txt ../GLPK_Files/dense/output_efficiencies.dense.txt
#mv -v crossEfficiency_glpk.txt ../GLPK_Files/dense/crossEfficiency_glpk.txt
##################################################

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
#Removing all GLPK Input files
#rm -v hyperplaneClass_glpk
#moving output GLPK files to appropriate locations
#mv -v output_efficiencies.sparse.txt ../GLPK_Files/sparse/output_efficiencies.sparse.txt
#mv -v crossEfficiency_glpk.txt ../GLPK_Files/sparse/crossEfficiency_glpk.txt
##################################################

###########################################
#Adding First line to each file individually and moving them back
cd ../GLPK_Files/overall
for file in *_glpk ; do
	lineCount=`cat $file | wc -l`
	sed "1 i\
$lineCount" $file > ${file}.new
mv -vf ${file}.new $file
done

#Now run svm-predict for overall
#fileNameMethod='overall'
#outputFileName=${outputFileNamePrefix}${fileNameMethod}
cd ../../code/
#Now run glpk for overall
./glpk_efficiency 4
#Removing all GLPK Input files
#rm -v hyperplaneClass_glpk
#moving output GLPK files to appropriate locations
#mv -v output_efficiencies.vsall.txt ../GLPK_Files/overall/output_efficiencies.overall.txt
#mv -v crossEfficiency_glpk.txt ../GLPK_Files/overall/crossEfficiency_glpk.txt
##################################################

#Now all the running of codes is done
#Just need to populate the CSV files by joining them together
#All required files are now in GLPK_Files/appropriate folder name

#For one-vs-one
cd ../GLPK_Files/one-vs-one/
if [ ! -d "../../comparisons/${folderName}/one-vs-one" ]; then
    # Control will enter here if DIRECTORY doesn't exist.
    mkdir -p ../../comparisons/${folderName}/one-vs-one
fi
paste -d : output_efficiencies.vsone.txt crossEfficiency_glpk.txt > ../../comparisons/${folderName}/one-vs-one/finalData-one-vs-one.txt

#For one-vs-all
cd ../one-vs-all
if [ ! -d "../../comparisons/${folderName}/one-vs-all" ]; then
	# Control will enter here if DIRECTORY doesn't exist.
	mkdir ../../comparisons/${folderName}/one-vs-all
fi
paste -d : output_efficiencies.vsall.txt crossEfficiency_glpk.txt > ../../comparisons/${folderName}/one-vs-all/finalData-one-vs-all.txt

#For dense
cd ../dense
if [ ! -d "../../comparisons/${folderName}/dense" ]; then
	# Control will enter here if DIRECTORY doesn't exist.
	mkdir ../../comparisons/${folderName}/dense
fi
paste -d : output_efficiencies.dense.txt crossEfficiency_glpk.txt > ../../comparisons/${folderName}/dense/finalData-dense.txt

#For sparse
cd ../sparse
if [ ! -d "../../comparisons/${folderName}/sparse" ]; then
	# Control will enter here if DIRECTORY doesn't exist.
	mkdir ../../comparisons/${folderName}/sparse
fi
paste -d : output_efficiencies.sparse.txt crossEfficiency_glpk.txt > ../../comparisons/${folderName}/sparse/finalData-sparse.txt

#For overall
cd ../overall
if [ ! -d "../../comparisons/${folderName}/overall" ]; then
	# Control will enter here if DIRECTORY doesn't exist.
	mkdir ../../comparisons/${folderName}/overall
fi
paste -d : output_efficiencies.overall.txt crossEfficiency_glpk.txt > ../../comparisons/${folderName}/overall/finalData-overall.txt

#FINAL FILE CREATION:
#FORMAT: 
# individualEff:individualCrossEff:TestAccuracy:overallEff:overallCrossEff
cd ../../comparisons/${folderName}/
pwd
cat ./one-vs-one/finalData-one-vs-one.txt ./one-vs-all/finalData-one-vs-all.txt ./dense/finalData-dense.txt ./sparse/finalData-sparse.txt > tempCatFile.txt
paste -d : tempCatFile.txt ./overall/finalData-overall.txt > finalEverything.txt
rm tempCatFile.txt
