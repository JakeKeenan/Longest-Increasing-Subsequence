//Program Author: Jake Keenan
//Program Assignment: HW6 longest increasing subsequence
//Date: 3/5/19

#include <iostream>
#include <string>
#include <sstream> // for std::stringstream
#include <cstdlib> // for exit()

// basic file operations
#include <fstream>

//useful classes
#include <vector>

using namespace std;

//returns number of elements between commas
//in a string...
int getValuesCount(string);

//initializes tables table_v and table_c to be length
//of the int 
void initializeTables(int);

//returns the LIS length that includes arr[i], int* passed
int LIS(int i, int*);

//returns the larger of two integers passed in
int max(int, int);

//array to be populated by file
int* arr;

int* table_v;
//table_v: stores the length of all possible LIS given that 
//for an index i, arr[i] must be the end of the subsequence
//--must be the same length as arr
int* table_c;
//table_c: for each element in arr[i], there is element,
//table_c[i], that indicates the index in arr that is 
//next number down in a LIS that ends with arr[i]
//--must be the same length as arr

int main(int argc, char *argv[]){
	//file parsing:
	if(argc != 2){
		cout<<"Proper Usage: " << argv[0]	<< "<string>Input File Name<string>" << endl;
		exit(1);
	}
	ifstream IFile(argv[1]);//File parser
	if(IFile.is_open()){
		string line;
		getline(IFile, line);
		stringstream lineParser(line);
		
		string parsedValue;
		stringstream converter(line);//set up a stringstream variable
		
		int arrLength = getValuesCount(line);
		initializeTables(arrLength);
		
		arr = new int[arrLength];
		
		int i = 0;
		while(getline(lineParser, parsedValue, ',')){
			converter.clear();
			converter.str(parsedValue);
			int value;
			if(!(converter >> value)){//do conversion
				std::cout<< "conversion for values failed" << std::endl;
				exit(1);
			}
			arr[i] = value;
			i++;
		}
		//File Parsing^
		
		int max = 0;
		LIS(arrLength - 1, &max);
		cout << "Length of the LIS = " << table_v[max] << endl;
		cout << "The LIS is: ";
		vector<int> temp;
		i = max;
		while(table_c[i] != i){
			temp.push_back(arr[i]);
			//cout << arr[i] << " ";
			i = table_c[i];
		}
		//cout << arr[i];
		//cout << endl;
		temp.push_back(arr[i]);
		unsigned int k = temp.size();
		for(unsigned int j = 0; j < k; j++){
			cout << temp.back() << " ";
			temp.pop_back();
		}
		cout << endl;
		IFile.close();
	}
	else{
		cout << "File not found!" << endl;
	}
	return 0;
}

//returns the length of LIS that uses index passed in
int LIS(int i, int* maxRef){
	if(i == 0){//base case
		table_v[i] = 1;
		table_c[i] = i;
		return table_v[i];
	}
	else if(table_v[i] != 0){
		//if table entry exists for a call, return it
		return table_v[i];
	}
	//initialize subsequence length
	table_v[i] = 1;
	//the subsequence only consists of itself
	//so it will reference itself in table_c
	table_c[i] = i;
	for(int j = 1; j <= i; j++){
		//check all elements below the current one
		//and build up a LIS including the current ith element
		if(arr[i]>arr[i-j]){
			//if arr[i-j] can be included in the subsequence
			//update LIS length in table_v for index i
			int temp = 1 + LIS(i-j, maxRef);
			if(temp > table_v[i]){
				//update the reference
				//for table_c when LIs length increases
				table_c[i] = i-j;
			}
			table_v[i] = max(table_v[i], temp);
		}
		else{
			LIS(i-j, maxRef);
		}
	}
	if(table_v[*maxRef] < table_v[i]){
		*maxRef = i;
	}
	return table_v[i];
}

//returns the value of b if it is larger than a, or returns the value of a 
//if it is larger than b. 
int max(int a, int b){
	return (a<b)?b:a;
}

//returns number of elements between commas
//in the passed in string...
//no changes are made to the tables.
int getValuesCount(string line){
	int values = 0;
	stringstream valCounter(line);
	string temp;
	while(getline(valCounter, temp, ',')){
		values++;
	}
	return values;
}

void initializeTables(int arrLength){
	table_v = new int[arrLength];
		for(int j = 0; j < arrLength; j++){
			table_v[j] = 0;
		}
		table_c = new int[arrLength];
		for(int j = 0; j < arrLength; j++){
			table_c[j] = 0;
		}
}


