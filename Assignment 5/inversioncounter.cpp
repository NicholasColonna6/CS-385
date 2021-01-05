/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Nicholas Colonna
 * Version     : 1.0
 * Date        : 11/4/18
 * Description : Counts the number of inversions in an array.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." -ncolonna
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count_inversions = 0;
	for(int i = 0; i<length; i++){	//loops through array starting at i
    	for(int j=i+1; j<length; j++){	//loops through array starting at i+1
    		if(array[j] < array[i]){
    			count_inversions++;		//count inversion if value at index j (to the right) is greater than i
    		}
    	}
    }
	return count_inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	int* scratch = new int[length];  //creates scratch array for merge sort of correct length
    long count_inversions = 0;

    count_inversions = mergesort(array, &scratch[0], 0, length-1);	//number of inversions is counted in mergesort algorithm

    delete[] scratch;	//clears memory
    return count_inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
	long count_inversions = 0;

	//mergesort constructed based on canvas pseudo-code
	if(low < high){
		int mid = low + (high - low) / 2;
		count_inversions = mergesort(array, scratch, low, mid);		//assigns all inversions from left half
		count_inversions = count_inversions + mergesort(array, scratch, mid+1, high);  //adds all inversions from right half to left
		int L = low;
		int H = mid + 1;
		for(int i = low; i <= high; i++){
			if((L <= mid) && ((H > high) || array[L] <= array[H])){
				scratch[i] = array[L];
				L++;
			}else{
				scratch[i] = array[H];
				count_inversions = count_inversions + (mid - L + 1); //adds to count how far the value at index i had to move to be in correct spot
				H++;
			}
		}
		for(int i = low; i<=high; i++){		//rebuilds array using scratch
			array[i] = scratch[i];
		}
	}

	return count_inversions;
}

int main(int argc, char *argv[]) {
    //parse command-line argument
    if(argc > 2){		//throw error if more arguments than possible (only 1 or 2 allowed)
    	cerr << "Usage: ./inversioncounter [slow]" << endl;
    	return 1;
    }else if(argc==2){  	//throws error if second argument is given and it is not equal to "slow"
    	if(strcmp(argv[1], "slow") != 0){		//strcmp compares argv[1] and string literal (from stackoverflow)
    		cerr << "Error: Unrecognized option '"<< argv[1] << "'." << endl;
    		return 1;
    	}
    }

    //given code to parse integer inputs
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }


    if(values.size() == 0){		//throw error if nothing was inputted or if they were all spaces
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }

    if(argc == 1){		//if argc is 1, then we run fast function
    	cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }else{		//if argc isn't 2, we are running the slow function
    	cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    }

    return 0;
}
