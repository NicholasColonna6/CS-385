/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Nicholas Colonna
 * Date        : September 10, 2018
 * Description : Sieve of Eratosthenes
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." -ncolonna
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
    	fill_n(is_prime_, limit_+1, true);  //from StackOverflow (fill an array with same value)

    	sieve();

    	num_primes_ = count_num_primes();
    	for(int i=limit_; i > 0; i--){		//loop through array backwards until first true
        	if(is_prime_[i] == true){		//this will give us our highest prime number
        		max_prime_ = i;
        		break;
        	}
        }
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
        // Write code to display the primes in the format specified in the
        // requirements document.
    	const int max_prime_width = num_digits(max_prime_);
    	const int primes_per_row = 80 / (max_prime_width + 1);
    	int rnum_printed = 0;		//counter for primes printed in current row
    	int num_printed = 0;		//used to keep track of how many primes have been printed
    	if(num_primes_ >= primes_per_row){		//checks if we have more primes than can fit on one row
    		for(int i=2; i<=limit_; i++){		//loops through all integers from 2 to limit
    			if(rnum_printed < primes_per_row){		//checks that row isn't filled
    				if(is_prime_[i] == true){	//checks if current number is prime
    					cout << setw(max_prime_width) << i;	//print prime number with specified width
    					rnum_printed++;			//increase count of numbers on a given line
    					num_printed++;		//increase total number printed counter
    					if(num_printed + 1 <= num_primes_ && rnum_printed != primes_per_row){  //prints space if current number isn't the last number in row and total
    						cout << " ";
    					}
    				}
    			}else{		//if row was filled, end line and reset primes per row count
    				cout << endl;
    				rnum_printed = 0;
    			}
    		}
    	}else{			//if all primes can fit on one line, we don't need to specify print width
    		for(int i=2; i<=limit_; i++){		//loop from 2 to limit
    			if(is_prime_[i] == true){		//checks if current number is prime
    				cout << i;			//prints current prime number
    				num_printed++;		//increase total number printed counter
    				if(num_printed + 1 <= num_primes_){  //if current number isn't the last, print a space
    					cout << " ";
    				}
    			}
    		}
    	}
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const {
        // Write code to count the number of primes found
    	// Loops through integers 2 through limit and increments num every time it encounters a 'true' for prime
    	int num = 0;
    	for(int i=2; i <= limit_; i++){
    		if(is_prime_[i] == true){
    			num++;
    		}
    	}
    	return num;
    }

    int num_digits(int num) const {
        // Write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
    	// Divides num by 10 every time it loops and increments count to keep track of total digits
    	int digits = 0;
    	while(num >= 1){
    		num = num / 10;
    		digits++;
    	}
    	return digits;
    }

    void sieve() {
        // Write sieve algorithm
    	// Interpreted from psuedo-code on assignment instructions
    	for(int i = 2; i <= sqrt(limit_); i++){
    		if(is_prime_[i] == true){
    			for(int j = i*i; j <= limit_; j+=i){
    				is_prime_[j] = false;
    			}
    		}
    	}
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // Write code that uses your class to produce the desired output.
    PrimesSieve ps(limit);
    cout << endl;
    cout << "Number of primes found: " << ps.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    ps.display_primes();

    return 0;
}
