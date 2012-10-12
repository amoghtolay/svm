#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>

using namespace std;

//Function declarations
void addTable(string tempLine, vector<vector<float> > *avgTable);
int lookTable( vector<vector<float> > *avgTable, float classLabel );
void populateTable( vector<vector<float> > *avgTable );

//Functions start here
/*
 * The function addTable parses the tempLine read from file, and gets the corresponding two classes
 * If the classes haven't been read (checked using tableLook() ) then add a row corresponding to it
*/
void addTable(string tempLine, vector<vector<float> > *avgTable)
{
	string strClass1, strClass2;
	int pos1 = tempLine.find("_");
	strClass1 = tempLine.substr(0 , pos1);	
	int pos2 = tempLine.find(":");
	strClass2 = tempLine.substr(pos1+1,pos2-2);
	
	float class1 = atof(strClass1.c_str());
	float class2 = atof(strClass2.c_str());
	
	if(lookTable( avgTable, class1 ) == -1 )
	{	
		vector<float> row; // Create an empty row

		//Generating temp row to be pushed back into main vector
		row.push_back(class1); // Add an element (column) to the row
		row.push_back(0); // Add 2nd column as 0
		
		(*avgTable).push_back(row); // Add the row to the main vector
	}
	if(lookTable( avgTable, class2 ) == -1 )
	{
		vector<float> row; // Create an empty row
	
		//Generating temp row to be pushed back into main vector
		row.push_back(class2); // Add an element (column) to the row
		row.push_back(0); // Add 2nd column as 0
		
		(*avgTable).push_back(row); // Add the row to the main vector
	}
}

int lookTable( vector<vector<float> > *avgTable, float classLabel )
{
	for( int i=0; i<(*avgTable).size(); i++)
	{
		if ((int)(*avgTable)[i][0] == (int)classLabel )
			return i;
	}
	return (-1);
}

void populateTable( vector<vector<float> > *avgTable )
{
	ifstream fpEff;
	fpEff.open("../GLPK_Files/one-vs-one/output_efficiencies.vsone.txt");
	string tempLine;
	
	if(fpEff.good())
		getline(fpEff, tempLine); 
	while (fpEff.good())
	{
		string strClass1, strClass2, strEff;
		int pos1 = tempLine.find("_");
		strClass1 = tempLine.substr(0 , pos1);	
		int pos2 = tempLine.find(":");
		strClass2 = tempLine.substr(pos1+1,pos2-2);
		
		/*
		 * Now obtaining efficiency
		 * starting from Z = 
		 * and ending at ; -9
		 * +4 is done as "Z = " has length 4
		 * -9 is done to obtain semicolon (obtained by trial and error)
		*/
		int pos3 = tempLine.find("Z = ");    // position of "Z = "
		int pos4 = tempLine.find(";\t");
		strEff = tempLine.substr(pos3+4, pos4-9);
		
		float class1 = atof(strClass1.c_str());
		float class2 = atof(strClass2.c_str());
		float eff = atof(strEff.c_str());
		
		getline(fpEff, tempLine); 
		//Now, I have eff, class1 and class2
		//Look up each class and write at position returned by lookTable()
		(*avgTable)[lookTable(avgTable, class1)][1] += eff;
		(*avgTable)[lookTable(avgTable, class2)][1] += eff;
	}
	fpEff.close();
}

int main()
{
	//While new labels are found, add row in vector for first pass
	ifstream fpEff;
	fpEff.open("../GLPK_Files/one-vs-one/output_efficiencies.vsone.txt");
	ofstream fpOutAvg;
	fpOutAvg.open("../GLPK_Files/one-vs-one/avg_efficiencies.vsone.txt");
	
	if(!fpEff || !fpOutAvg)
	{
		cout<<"ERROR: Files could not be opened";
		exit(EXIT_FAILURE);
	}
	
	string tempLine;
	vector<vector<float> > avgTable;
	if(fpEff.good())
		getline(fpEff, tempLine); 
	else
		cout<<"The one-vs-one efficiency file could not be read";
	
	while (fpEff.good())
	{
		addTable(tempLine, &avgTable);
		getline(fpEff, tempLine); 
	}
	fpEff.close();

	//Now populate table with sums
	populateTable(&avgTable);

	
	for( int i=0; i < avgTable.size(); i++)
		fpOutAvg<<avgTable[i][0]<<": "<<"Z = "<<avgTable[i][1]/(avgTable.size()-1)<<";\n";
	
	fpOutAvg.close();
	return (0);
}
