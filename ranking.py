#!/usr/bin/env python

import sys
from decimal import *

def computeAvg(listname):
	count = len(listname)
	total = 0
	for Eff in listname:
		total = total + Decimal(Eff[-1])
		
	return total/count	
	
def aboveAvg(listname,avg):
	total = len(listname)
	count = 0
	for tup_item in listname:
		if Decimal(tup_item[-1]) >= avg:
			count = count + 1
	
	return Decimal(count)/total
	
def secondVal(tup):
	return tup[-1]
	
def countTop10Percent (listname):
	counter = {}
	counter[0] = 0
	counter[1] = 0
	counter[2] = 0
	counter[3] = 0
	countMax = (int) (0.1 * len(listname))
	count = 0
	
	for i, item in enumerate(listname):
		if count == countMax:
			break
		if item[0] == '0':
			counter[0] = counter[0] + 1
		elif item[0] == '1':
			counter[1] = counter[1] + 1
		elif item[0] == '2':
			counter[2] = counter[2] + 1
		elif item[0] == '3':
			counter[3] = counter[3] + 1
		
		# Giving same rank to two equal numbers
		if i+1 < len(listname):
			getNext = listname[i+1]
			if getNext == item:
				continue
			else:
				count = count + 1
		else:
			count = count + 1
	
	return counter

def countBottom10Percent (listname):
	counter = {}
	counter[0] = 0
	counter[1] = 0
	counter[2] = 0
	counter[3] = 0
	countMax = (int) (0.1 * len(listname))
	count = 0
	
	for i, item in enumerate(listname):
		if count == countMax:
			break
		if item[0] == '0':
			counter[0] = counter[0] + 1
		elif item[0] == '1':
			counter[1] = counter[1] + 1
		elif item[0] == '2':
			counter[2] = counter[2] + 1
		elif item[0] == '3':
			counter[3] = counter[3] + 1
		
		# Giving same rank to two equal numbers
		if i+1 < len(listname):
			getNext = listname[i+1]
			if getNext == item:
				continue
			else:
				count = count + 1
		else:
			count = count + 1
	
	return counter

def findSumRanksForMethod (listname):
	rankSum = {}
	rankSum[0] = 0
	rankSum[1] = 0
	rankSum[2] = 0
	rankSum[3] = 0
	
	numHyper = [0,0,0,0]
	rank = 1
	
	for i,item in enumerate(listname):
		if item[0] == '0':
			rankSum[0] = rankSum[0] + rank
			numHyper[0] = numHyper[0]+1
		elif item[0] == '1':
			rankSum[1] = rankSum[1] + rank
			numHyper[1] = numHyper[1]+1
		elif item[0] == '2':
			rankSum[2] = rankSum[2] + rank
			numHyper[2] = numHyper[2]+1
		elif item[0] == '3':
			rankSum[3] = rankSum[3] + rank
			numHyper[3] = numHyper[3]+1
		
		# Giving same rank to two equal numbers
		if i+1 < len(listname):
			getNext = listname[i+1]
			if getNext == item:
				continue
			else:
				rank = rank + 1
		else:
			rank = rank + 1
	# Dividing by num of hyperplanes in each method to bring all nums
	# between 0 and 1 for comparison
	
	rankSum[0] = Decimal (rankSum[0]) / Decimal (numHyper[0])
	rankSum[1] = Decimal (rankSum[1]) / Decimal (numHyper[1])
	rankSum[2] = Decimal (rankSum[2]) / Decimal (numHyper[2])
	rankSum[3] = Decimal (rankSum[3]) / Decimal (numHyper[3])
	
	return rankSum		
		
	
def main():
	folder = sys.argv[1]
	print ""
	print '--------------------------------'+ folder +'----------------------------------'
	
	f_vsone = open('comparisons/'+ folder +'/final_onevsone.txt','rU')
	f_vsall = open('comparisons/'+ folder +'/final_onevsall.txt','rU')	
	f_dense = open('comparisons/'+ folder +'/final_dense.txt','rU')
	f_sparse = open('comparisons/'+ folder +'/final_sparse.txt','rU')
	
	crossEff_vsone_list = []
	for line in f_vsone:
		string = line[:-1]
		string = string.split(':')
		crossEff_vsone_list.append(('0',string[0],string[-1]))
		
	avgEff_vsone = computeAvg(crossEff_vsone_list)
	print 'Average Cross efficiency for One-vs-One =' , avgEff_vsone	
	print 'Fraction of hyperplanes with cross efficiency greater than or equal to average =', aboveAvg(crossEff_vsone_list,avgEff_vsone),'\n'
	
	crossEff_vsall_list = []
	for line in f_vsall:
		string = line[:-1]
		string = string.split(':')
		crossEff_vsall_list.append(('1',string[0],string[-1]))
		
	avgEff_vsall = computeAvg(crossEff_vsall_list)
	print 'Average Cross efficiency for One-vs-All =' , avgEff_vsall
	print 'Fraction of hyperplanes with cross efficiency greater than or equal to average =',aboveAvg (crossEff_vsall_list,avgEff_vsall),'\n'
	
	crossEff_dense_list = []
	for line in f_dense:
		string = line[:-1]
		string = string.split(':')
		crossEff_dense_list.append(('2',string[0],string[-1]))
		
	avgEff_dense = computeAvg(crossEff_dense_list)
	print 'Average Cross efficiency for Dense =' , avgEff_dense
	print 'Fraction of hyperplanes with cross efficiency greater than or equal to average =',aboveAvg (crossEff_dense_list,avgEff_dense),'\n'
	
	crossEff_sparse_list = []
	for line in f_sparse:
		string = line[:-1]
		string = string.split(':')
		crossEff_sparse_list.append(('3',string[0],string[-1]))
		
	avgEff_sparse = computeAvg(crossEff_sparse_list)
	print 'Average Cross efficiency for Sparse =' , avgEff_sparse
	print 'Fraction of hyperplanes with cross efficiency greater than or equal to average =',aboveAvg (crossEff_sparse_list,avgEff_sparse),'\n'
	

# TODO: 
# Collision of ranks resolve
	
	crossEff_overall_list = crossEff_vsone_list + crossEff_vsall_list + crossEff_dense_list + crossEff_sparse_list
	sorted_crossEff_list_desc = sorted(crossEff_overall_list,key = secondVal,reverse = True)
	sorted_crossEff_list_asc = sorted(crossEff_overall_list,key = secondVal,reverse = False)
	
	counter_desc = {}
	counter_asc = {}
	
	counter_desc = countTop10Percent(sorted_crossEff_list_desc)
	counter_asc = countBottom10Percent(sorted_crossEff_list_asc)
	
	print ""
	print "----------------------------ranking of TOP 10% of all hyperplanes------------------------------------"
	print "The total number of hyperplanes is", len(sorted_crossEff_list_desc)
	print 'Number of hyperplanes from One-vs-One in top 10 % are',counter_desc[0]
	print 'Number of hyperplanes from One-vs-All in top 10 % are',counter_desc[1]
	print 'Number of hyperplanes from Dense in top 10 % are',counter_desc[2]
	print 'Number of hyperplanes from Sparse in top 10 % are',counter_desc[3]
	print ""
	
	print ""
	print "----------------------------ranking of BOTTOM 10% of all hyperplanes------------------------------------"
	print "The total number of hyperplanes is", len(sorted_crossEff_list_asc)
	print 'Number of hyperplanes from One-vs-One in top 10 % are',counter_asc[0]
	print 'Number of hyperplanes from One-vs-All in top 10 % are',counter_asc[1]
	print 'Number of hyperplanes from Dense in top 10 % are',counter_asc[2]
	print 'Number of hyperplanes from Sparse in top 10 % are',counter_asc[3]
	print ""
	
	sumOfRanks = {}
	sumOfRanks = findSumRanksForMethod ( sorted_crossEff_list_desc )
	print ""
	print "--------------------------------average sum of ranks per method-------------------------------------------------"
	print "The sum of ranks in a particular method averaged by the number of hyperplanes in that method is as follows:"
	
	print 'Average Rank of hyperplanes of One-vs-One is', sumOfRanks[0]
	print 'Average Rank of hyperplanes of One-vs-All is', sumOfRanks[1]
	print 'Average Rank of hyperplanes of Dense is', sumOfRanks[2]
	print 'Average Rank of hyperplanes of Sparse is', sumOfRanks[3]
	print ""
	
if __name__ == '__main__':
	main()
