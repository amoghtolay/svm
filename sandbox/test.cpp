#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
	int exitCode = 0;
	cout<<"Type exit code to return:";
	cin>>exitCode;
	exit(exitCode);
	return 0;
}
