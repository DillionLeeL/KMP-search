#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

#include "KMP.h"

using namespace std;

int main(int argc, char* argv[]) {

	ifstream inputFile;
	string fileName= "";
	bool all;
	string sequence;
	string toFind = "";
	vector<int> results;

	// File name and option for all occurences
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-a"))
			all = true;
		if (string(argv[i]).find(".txt")!= string::npos)
			fileName = argv[i];
	}

	// File operation
	if (fileName != "")
		inputFile.open(fileName);
	else {
		cout << "Please enter file name: ";
		cin >> fileName;
		inputFile.open(fileName);
	}
	if (!inputFile.is_open()) {
		cout << "Error: unable to open input file." << endl;
		exit(1);
	}
	/*
	if (toFind == "") {
		cout << endl << "Please enter search term: ";
		cin >> toFind;
	} 
	*/

	while (inputFile >> sequence && inputFile >> toFind) {

		cout << sequence << " " << toFind << endl;

		results = KMPSearch(sequence, toFind, all);
		cout << results[0] << endl;
		if (all) {
			for (int i = 1; i < results.size(); i++) {
				cout << results[i] << endl;
			}
		}

	}

	inputFile.close();
	return 0;
}