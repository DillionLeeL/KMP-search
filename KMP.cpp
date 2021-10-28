#include "KMP.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

vector<int> buildTable(string x) {
	int m = x.size();
	int i = 0, j = 1;

	// Initialize KMP array to zeros
	vector<int> dupe(m, 0);

	while (j < m) {
		// First character repeats
		if (x[i] == x[j]) {
			i++;
			dupe[j] = i;
			j++;
		}
		// first character does not repeat
		else if (i == 0) {
			j++;
		}
		// Current character does not repeat after finding matches
		else {
			i = dupe[i - 1];
		}
	}
	return dupe;
}

vector<int> KMPSearch(string sequence, string toFind, bool all) {

	vector<int> indexes;

	if (toFind == "") {
		indexes.push_back(0);
		return indexes;
	}
	if (sequence == "" || toFind.size() > sequence.size()) {
		indexes.push_back(-1);
		return indexes;
	}

	vector<int> arr = buildTable(toFind);
	// sequence pointer and find pointer
	int sp = 0;
	int fp = 0;
	int m = sequence.size();
	int n = toFind.size();
	bool multiple = all;

	while (sp < m && fp < n) {

		// last character matches 
		if (sequence[sp] == toFind[fp] && fp == n - 1) {
			//cout << "inside function index: " << sp - fp << endl;
			indexes.push_back(sp - fp);
			if (!multiple)
				return indexes;
			else {
				sp++;
				fp = 0;
			}
		}
		// Not last character but does match
		else if (sequence[sp] == toFind[fp]) {
			sp++;
			fp++;
		}
		// Current character does not match
		else {
			// find pointer does not need to move, go forward in sequence
			if (fp == 0)
				sp++;
			// move find pointer to correct location in table
			else
				fp = arr[fp - 1];
		}
	}
	// substring not found
	if (indexes.empty()) {
		//cout << "EMPTY" << endl;
		indexes.push_back(-1);
	}
	return indexes;
}