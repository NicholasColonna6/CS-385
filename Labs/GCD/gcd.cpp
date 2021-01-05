/*
 * gcd.cpp
 *
 *  Created on: Aug 31, 2018
 *      Author: Nicholas Colonna
 *      "I pledge my honor that I have abided by the Stevens Honor System." ncolonna
 */
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int gcd_iterative(int m, int n){
	if(m == n){
		return abs(m);
	}else if(m > n){
		while(n != 0){
			int temp = m % n;
			m = n;
			n = temp;
		}
		return abs(m);
	}else{
		while(m != 0){
			int temp = n % m;
			n = m;
			m = temp;
		}
		return abs(n);
	}
}

int gcd_recursive(int m, int n){
	if(n > m){  //ensure the larger number is the first parameter
		return gcd_recursive(n, m);
	}else if(m % n == 0){  //base case, m is divisible by n
		return abs(n);
	}else{  //recurse with n and remainder of m/n
		return gcd_recursive(n, m%n);
	}
}

int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer." << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer." << endl;
        return 1;
    }

    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m,n) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_iterative(m,n) << endl;
    return 0;
}
