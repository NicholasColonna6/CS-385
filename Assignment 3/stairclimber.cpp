/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Nicholas Colonna
 * Date        : 9/26/2018
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." -Nicholas Colonna
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int>> get_ways(int num_stairs) {
    //Return a vector of vectors of ints representing the different combinations of
	//ways to climb num_stairs stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways;
	vector<vector<int>> result;
	if(num_stairs <= 0){
		ways.push_back(vector<int>());		//add empty vector if can't add anymore stairs
	}else{
		for(int i = 1; i<=3; i++){		//loop for each move type -- 1, 2, or 3 stairs
			if(num_stairs >= i){		//if its possible to move i stairs, do it
				result = get_ways(num_stairs - i);		//recurse after making the move
				for(auto it = result.begin(); it != result.end(); ++it){
					it->insert(it->begin(), i);			//i to the solutions found
				}
				ways.reserve(ways.size() + result.size());			//reserve & insert found on stackoverflow
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}
	return ways;
}

int num_digits(int num) {
    // Helper Function: Determines how many digits are in an integer
	// Divides num by 10 every time it loops and increments count to keep track of total digits
 	int digits = 0;
 	while(num >= 1){
 		num = num / 10;
 		digits++;
 	}
 	return digits;
}

void display_ways(const vector<vector<int>> &ways) {
    // Display the ways to climb stairs by iterating over the vector of vectors and printing each combination.
	if((int)ways.size() < 10){		//if less than 10 ways, we want to left align
		for(int i=1; i<=(int)ways.size(); i++){		//loops through ways array
			cout << i << ". [";
			for(int j=1; j<=(int)ways[i-1].size(); j++){	//loops through individual ways
				cout << ways[i-1][j-1];
				if(j != (int)ways[i-1].size()){
					cout << ", ";
				}else{
					cout << "]" << endl;
				}
			}
		}
	}else{		//if 10 or greater ways, align right to widest number
		int max_width = num_digits((int)ways.size());
		for(int i=1; i<=(int)ways.size(); i++){			//loops through ways array
			cout << setw(max_width) << i << ". [";
			for(int j=1; j<=(int)ways[i-1].size(); j++){	//loops through individual ways
				cout << ways[i-1][j-1];
				if(j != (int)ways[i-1].size()){
					cout << ", ";
				}else{
					cout << "]" << endl;
				}
			}
		}
	}
}

int main(int argc, char * const argv[]) {
	if(argc != 2){		//error if no input or too many input arguments are given
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	if(atoi(argv[1]) != (int)atoi(argv[1]) || atoi(argv[1]) <= 0){		//error if non-integer, zero or negative integer is given
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	int num_stairs = atoi(argv[1]);		//atoi() conversion of character to int found on stackoverflow
	vector<vector<int>> ways = get_ways(num_stairs);

	if(num_stairs == 1){	//appropriate grammar if only 1 stair
		cout << ways.size() <<" way to climb " << num_stairs << " stair." << endl;
		display_ways(ways);
	}else{					//all other stair numbers
		cout << ways.size() << " ways to climb " << num_stairs << " stairs." << endl;
		display_ways(ways);
	}

	return 0;
}
