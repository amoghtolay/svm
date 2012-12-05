#!/usr/bin/env python

import csv
from collections import defaultdict
import subprocess
import math
import time

start = time.time()

################################################################
# IMPORTANT NOTICE:
# IF YOU NEED TO TEST THE DATA AND THEN MAKE THE FILES, (USUALLY THE CASE), THEN WHILE
# CALLING THE PROCESS, CALL runWithTest.sh, ELSE (ESPECIALLY IN THE CASE OF IRIS, RUN
# runWithoutTest.sh
####################################################################

		#########################################################################
		# TODO:
		# Also, call final run.sh with appropriate command line parameters after appropriate cleanup
		# And ensure that the ranges and values of C and g are matching with paper
		# Test manually
		###########################################################################


#################################
#Change the grid parameters here
#################################
beginC = math.pow(2,9)
# ^change back to math.pow(2,12)			
endC = math.pow(2,-2)
intervalC = 2 # Divide by 2

beginGamma = math.pow(2,4)
# ^change back to math.pow(2,4)			
endGamma = math.pow(2,-7)
intervalGamma = 2 # Divide by 2

C_count = math.log(beginC/endC) / math.log(intervalC) + 1
Gamma_count = math.log(beginGamma/endGamma) / math.log(intervalGamma) + 1
###################################

presentC = beginC
presentGamma = beginGamma
sumCrossEff = 0

maxCrossEff_vsOne = 0
maxCrossEff_vsAll = 0
maxCrossEff_dense = 0
maxCrossEff_sparse = 0

bestC_vsOne = presentC
bestC_vsAll = presentC
bestC_dense = presentC
bestC_sparse = presentC

bestGamma_vsOne = presentGamma
bestGamma_vsAll = presentGamma
bestGamma_dense = presentGamma
bestGamma_sparse = presentGamma

counter = 0
CGammaList = []

# TEMPORARY FILES FOR DEBUGGING
fpDebugVsOne = open("./Debugging/debug_vsone.txt", "wb")
fpDebugVsAll = open("./Debugging/debug_vsall.txt", "wb")
fpDebugDense = open("./Debugging/debug_dense.txt", "wb")
fpDebugSparse = open("./Debugging/debug_sparse.txt", "wb")

while (presentC >= endC):
	presentGamma = beginGamma
	while (presentGamma >= endGamma):
		counter = counter + 1
		#########################################################################
		# TODO:
		# Call gridSearchAux.sh from here with the two command line parameters
		# Also, call final run.sh with appropriate command line parameters after appropriate cleanup
		# And ensure that the ranges and values of C and g are matching with paper
		# Test manually
		###########################################################################

		process = subprocess.Popen(['./gridSearchAux0.sh', str(presentC), str(presentGamma), str(presentGamma), str(presentGamma), str(presentGamma)])
		error = process.wait();
		if error == 24:
			print "It returned error code ", error
			# Temporarily
			#exit(24)
			# Now continue and skip this loop, make a note that this value was skipped
			# TODO HERE
			presentGamma = presentGamma/intervalGamma
			continue
			
		elif error != 0:
			print "There was some error, returned error ", error
		########################
		
		CGammaList.append((presentC,presentGamma))
		print "#########################################################"
		print "COUNTER IS : ", counter
		print "#########################################################"
		presentGamma = presentGamma/intervalGamma
	presentC = presentC/intervalC

presentC = beginC
presentGamma = beginGamma

counter = 0

process = subprocess.Popen(['./gridSearchAux1.sh'])
if process.wait() != 0:
	print "There were some errors"



# Opening and evaluating sum of one-vs-one cross effeciency
sumCrossEff = 0
fpVsOne = open("./GLPK_Files/one-vs-one/crossEfficiency_glpk.txt", "rb")

num_lines = 0

for line in fpVsOne:
	num_lines = num_lines + 1

fpVsOne.seek(0)
num_hyper = num_lines/len(CGammaList)
hypercounter = 0
#max_hyper = 0

csvCrossEff = csv.reader(fpVsOne, delimiter=':')
for row in csvCrossEff:
	hypercounter = hypercounter + 1
	sumCrossEff += float(row[1])
	if hypercounter%num_hyper == 0:
		if math.isnan(sumCrossEff) is False:
			if (sumCrossEff > maxCrossEff_vsOne):
				(bestC_vsOne,bestGamma_vsOne) = CGammaList[(hypercounter/num_hyper) - 1]
				maxCrossEff_vsOne = sumCrossEff
		# For DEBUGGING:
		fpDebugVsOne.write(str(sumCrossEff))
		fpDebugVsOne.write('\n')
		sumCrossEff = 0 
fpVsOne.close()
		
		
#bestC_vsOne = beginC/pow(2,math.floor(max_hyper/(num_hyper*C_count)))
#bestGamma_vsOne = beginGamma/pow(2,(max_hyper/num_hyper)%Gamma_count)
			
# Opening and evaluating sum of one-vs-all cross effeciency
sumCrossEff = 0
fpVsAll = open("./GLPK_Files/one-vs-all/crossEfficiency_glpk.txt", "rb")
num_lines = 0

for line in fpVsAll:
	num_lines = num_lines + 1

fpVsAll.seek(0)
num_hyper = num_lines/len(CGammaList)
hypercounter = 0
#max_hyper = 0

csvCrossEff = csv.reader(fpVsAll, delimiter=':')
for row in csvCrossEff:
	hypercounter = hypercounter + 1
	sumCrossEff += float(row[1])
	if hypercounter%num_hyper == 0:
		if math.isnan(sumCrossEff) is False:
			if (sumCrossEff > maxCrossEff_vsAll):
				(bestC_vsAll,bestGamma_vsAll) = CGammaList[(hypercounter/num_hyper) - 1]
				maxCrossEff_vsAll = sumCrossEff
		# FOR DEBUGGING:
		fpDebugVsAll.write(str(sumCrossEff))
		fpDebugVsAll.write('\n')
		sumCrossEff = 0 
fpVsAll.close()
		
# FOR DEBUGGING:
fpDebugVsAll.write(str(sumCrossEff))
fpDebugVsAll.write('\n')

		
#bestC_vsAll = beginC/pow(2,math.floor(max_hyper/(num_hyper*C_count)))
#bestGamma_vsAll = beginGamma/pow(2,(max_hyper/num_hyper)%Gamma_count)
			
# Opening and evaluating sum of dense cross effeciency
sumCrossEff = 0
fpDense = open("./GLPK_Files/dense/crossEfficiency_glpk.txt", "rb")
csvCrossEff = csv.reader(fpDense, delimiter=':')
num_lines = 0

for line in fpDense:
	num_lines = num_lines + 1

fpDense.seek(0)
num_hyper = num_lines/len(CGammaList)
hypercounter = 0
#max_hyper = 0

csvCrossEff = csv.reader(fpDense, delimiter=':')
for row in csvCrossEff:
	hypercounter = hypercounter + 1
	sumCrossEff += float(row[1])
	if hypercounter%num_hyper == 0:
		if math.isnan(sumCrossEff) is False:
			if (sumCrossEff > maxCrossEff_dense):
				(bestC_dense,bestGamma_dense) = CGammaList[(hypercounter/num_hyper) - 1]
				maxCrossEff_dense = sumCrossEff
		# FOR DEBUGGING:
		fpDebugDense.write(str(sumCrossEff))
		fpDebugDense.write('\n')
		sumCrossEff = 0 
fpDense.close()
		
#bestC_dense = beginC/pow(2,math.floor(max_hyper/(num_hyper*C_count)))
#bestGamma_dense = beginGamma/pow(2,(max_hyper/num_hyper)%Gamma_count)
		
# Opening and evaluating sum of sparse cross effeciency
sumCrossEff = 0
fpSparse = open("./GLPK_Files/sparse/crossEfficiency_glpk.txt", "rb")
csvCrossEff = csv.reader(fpSparse, delimiter=':')
num_lines = 0

for line in fpSparse:
	num_lines = num_lines + 1

fpSparse.seek(0)
num_hyper = num_lines/len(CGammaList)
hypercounter = 0
#max_hyper = 0

csvCrossEff = csv.reader(fpSparse, delimiter=':')
for row in csvCrossEff:
	hypercounter = hypercounter + 1
	sumCrossEff += float(row[1])
	if hypercounter%num_hyper == 0:
		if math.isnan(sumCrossEff) is False:
			if (sumCrossEff > maxCrossEff_sparse):
				(bestC_sparse,bestGamma_sparse) = CGammaList[(hypercounter/num_hyper) - 1]
				maxCrossEff_sparse = sumCrossEff
		# FOR DEBUGGING:
		fpDebugSparse.write(str(sumCrossEff))
		fpDebugSparse.write('\n')
		sumCrossEff = 0 
fpSparse.close()
		
		
#bestC_sparse = beginC/pow(2,math.floor(max_hyper/(num_hyper*C_count)))
#bestGamma_sparse = beginGamma/pow(2,(max_hyper/num_hyper)%Gamma_count)
	
	# FOR DEBUGGING:
#	fpDebugVsOne.write('\n')
# fpDebugVsAll.write('\n')
#	fpDebugDense.write('\n')
#	fpDebugSparse.write('\n')
	
fpDebugVsOne.close()
fpDebugVsAll.close()
fpDebugDense.close()
fpDebugSparse.close()

# IF TESTING REQUIRED, USE runWithTest.sh, else run with 'runWithoutTest.sh'
# processRun = subprocess.Popen(['./runWithTest.sh', str(bestC_vsOne), str(bestGamma_vsOne), str(bestC_vsAll), str(bestGamma_vsAll), str(bestC_dense), str(bestGamma_dense), str(bestC_sparse), str(bestGamma_sparse)])
processRun = subprocess.Popen(['./runWithoutTest.sh', str(bestC_vsOne), str(bestGamma_vsOne), str(bestC_vsAll), str(bestGamma_vsAll), str(bestC_dense), str(bestGamma_dense), str(bestC_sparse), str(bestGamma_sparse)])
if processRun.wait() != 0:
	print "There were some errors in run.sh process opening"

#NOW BEST C AND GAMMA HAVE BEEN OBTAINED AS FOLLOWS

print ""
print "The final obtained values after grid-search on c and gamma are as follows:"
print "For one-vs-one: C=", bestC_vsOne, " Gamma = ", bestGamma_vsOne, "with max Cross efficiency = ", maxCrossEff_vsOne
print "For one-vs-all: C=", bestC_vsAll, " Gamma = ", bestGamma_vsAll, "with max Cross efficiency = ", maxCrossEff_vsAll
print "For dense: C=", bestC_dense, " Gamma = ", bestGamma_dense, "with max Cross efficiency = ", maxCrossEff_dense
print "For sparse: C=", bestC_sparse, " Gamma = ", bestGamma_sparse, "with max Cross efficiency = ", maxCrossEff_sparse
print ""
print "it took", time.time() - start, "seconds to execute entire script"
print ""
