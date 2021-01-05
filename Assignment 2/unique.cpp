/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Nicholas Colonna
 * Date        : 9/23/2018
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." -Nicholas Colonna
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	for(const auto &letter : s){
		if(islower(letter) == 0){	   //islower() found on stackoverflow
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // returns true if all letters in string are unique, that is no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int bitvector = 0;		//bitvector encompasses all letters we have used so far
	unsigned int setter;			//setter is current character we are working with
	for(const auto &letter : s){
		setter = 1 << (letter - 'a');			//assigns binary representation of current letter to setter
		if ((bitvector & setter) == 0){			//if 0, then not a duplicate
			bitvector = (bitvector | setter);	//bitvector changes to include setter character
		}else{
			return false;
		}
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // reads and parses command line arguments.
    // Calls other functions to produce correct output.
    string s;

	if (argc != 2) {		//ensures correct amount of argument given and throws error otherwise
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }

	if(is_all_lowercase(argv[1]) == false){		//ensures all letters are lowercase and throws error otherwise
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}

	if(all_unique_letters(argv[1]) == false){  //ensures all letters are not duplicates and throws error otherwise
		cerr << "Duplicate letters found." << endl;
		return 1;
	}else{
		cout << "All letters are unique." << endl;
	}

	return 1;
}
