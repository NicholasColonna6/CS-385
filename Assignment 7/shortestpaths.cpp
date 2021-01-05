/*******************************************************************************
 * Name        : shortestpath.cpp
 * Author      : Nicholas Colonna
 * Date        : 11/28/18
 * Description : Solve all pairs shortest paths with Floyd's algorithm
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." -ncolonna
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

long **distances;
long **path_lengths;
long **intermediate_vertices;
int num_vertices;
long INF = numeric_limits<long>::max();	   //stackoverflow


//calculates number of digits of value (helper for display_table)
int len(long value) {
    int num_digits = 1;
    while (value > 9) {
        value /= 10;
        num_digits++;
    }
    return num_digits;
}

/**
* Displays the matrix on the screen formatted as a table.
* Code given in assignment
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}

	int max_cell_width = len(max(static_cast<long>(num_vertices), max_val));

	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

vector<char> path(int i, int j){
	if(intermediate_vertices[i][j] != INF){	  //there is an intermediate vertex
		int intermediate = intermediate_vertices[i][j];
		vector<char> begin_to_int = path(i, intermediate);	//recursively calls to get path of begin to intermediate
		vector<char> int_to_end = path(intermediate, j);	//recursively calls to get path of intermediate to end
		int_to_end.insert(int_to_end.end(), 1+begin_to_int.begin(), begin_to_int.end());
		return int_to_end;
	}else{		//no intermediate vertex
		char begin = 65 + i;
		char end = 65 + j;
		vector<char> path;
		path.push_back(end);
		if(begin == end){	//don't add begin if its the same character as end
			return path;
		}else{		//add begin
			path.push_back(begin);
			return path;
		}
	}
}

//Displays the paths in correct format
void display_paths(){
	for(int i = 0; i<num_vertices; i++){
		for(int j = 0; j<num_vertices; j++){
			vector<char> curr_path = path(i, j);	//gets path for current place in matrix
			if(path_lengths[i][j] >= INF){		//output if current place in matrix is INF
				cout << (char)(i + 65) << " -> " << (char)(j + 65) << ", distance: infinity, path: none" << endl;
			}else{		//output for when not infinity (valid path)
				ostringstream oss;
				for(int i = (int)curr_path.size()-1; i >= 0; i--){	//converts vector<char> to string in desired format
					if(i==(int)curr_path.size()-1){
						oss << curr_path[i];
					}else{
						oss << " -> " << curr_path[i];
					}
				}
				string printable_path = oss.str();
				cout << (char)(i + 65) << " -> " << (char)(j + 65) << ", distance: " << path_lengths[i][j] << ", path: " << printable_path << endl;
			}
		}
	}
}

//Helps split the called line into pieces
//Taken from CPPGraphAlgorithm code in class
vector<string> split(const string& s, const string& delim, const bool keep_empty = true) {
    vector<string> result;
    if (delim.empty()) {
        result.push_back(s);
        return result;
    }
    string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}

//Parses through the data on a line to check if there is a correct number of arguments and no illegal values
bool parse_data(vector<string> &parts, const int line_number, const string line, int last_vert) {
	bool all_good = true;
	if (parts.size() != 3){		//if to many or too few arguments, throw error
		cerr << "Error: Invalid edge data '"<< line << "' on line " << line_number << "." << endl;
		return false;
	}
	if (parts[0].length() > 1 || (parts[0][0] < 65 || parts[0][0] > last_vert)){	//if multiple characters or outside of possible vertex range, throw error
		cerr << "Error: Starting vertex '"<< parts[0] << "' on line " << line_number << " is not among valid values A-" << (char)last_vert << "." << endl;
		return false;
	}
	if (parts[1].length() > 1 || (parts[1][0] < 65 || parts[1][0] > last_vert)){	//if multiple characters or outside of possible vertex range, throw error
		cerr << "Error: Ending vertex '"<< parts[1] << "' on line " << line_number << " is not among valid values A-" << (char)last_vert << "." << endl;
		return false;
	}
	return all_good;
}

//Creates a new matrix with INF as all values, and 0 diagonals if distance matrix
long** create_matrix(const bool is_distance){
    long **matrix = new long*[num_vertices];
    for(int i=0; i<num_vertices; i++){
    	matrix[i] = new long[num_vertices];
    	for(int j=0; j<num_vertices; j++){
    		if(j==i && is_distance==true){	//if making distance matrix, set pivots to 0
    			matrix[i][j] = 0;
    		}else{
    			matrix[i][j] = INF;		//initalize all values of matrix to infinity
    		}
    	}
    }
    return matrix;
}

//Utilizes Floyd's algorithm to find all pairs shortest paths; slightly modified to keep track of intermediate vertices
//Based off of pseudo code from textbook
void floyds_algorithm(){
	intermediate_vertices = create_matrix(false);	//create intermediate vertices matrix

	for(int k=1; k<=num_vertices; k++){
		for(int i=1; i<=num_vertices; i++){
			for(int j=1; j<=num_vertices; j++){
				if(path_lengths[i-1][k-1] != INF && path_lengths[k-1][j-1] != INF){
					long right_side = path_lengths[i-1][k-1] + path_lengths[k-1][j-1];
					if(path_lengths[i-1][j-1] > right_side){
						path_lengths[i-1][j-1] = right_side;
						intermediate_vertices[i-1][j-1] = k-1;
					}
				}
			}
		}
	}
}

//deletes a matrix from memory
void delete_matrix(long** matrix){
	for(int i=0; i<num_vertices; i++){
		delete [] matrix[i];
	}
	delete [] matrix;
}

int main(int argc, const char *argv[]) {
    if(argc != 2){		//make sure correct amount of command line arguments
    	cerr << "Usage: ./shortestpaths <filename>" << endl;
    	return 1;
    }

    ifstream input_file(argv[1]);  //create an ifstream object
    if (!input_file) {      //if file does not exist, print an error message.
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    input_file.exceptions(ifstream::badbit);    //add read errors to the list of exceptions the ifstream will handle

    string line;
    getline(input_file, line);
	line.erase(0, line.find_first_not_of(" "));		//trims out spaces on left (from stackoverflow)
	line.erase(line.find_last_not_of(" ") + 1);		//trims out spaces on right (from stackoverflow)
	istringstream temp;
    temp.str(line);
    if(!(temp >> num_vertices) || (num_vertices < 1 || num_vertices > 26)){		//checks that first line is an integer and in required range
    	cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
    	return 1;
    }
    int last_vert = num_vertices + 64;	//integer representation of the last letter allowed based off of # vertices
    distances = create_matrix(true);	//creates distance matrix

    //read in all lines below the first
    try {
        unsigned int line_number = 2;
        while (getline(input_file, line)) {  	//use getline to read in a line
        	line.erase(0, line.find_first_not_of(" "));		//trims out spaces on left (from stackoverflow)
        	line.erase(line.find_last_not_of(" ") + 1);		//trims out spaces on right (from stackoverflow)
        	vector<string> parts = split(line, " ");
        	if(!parse_data(parts, line_number, line, last_vert)){  //if any errors from parsing data, delete and stop
        		delete_matrix(distances);
        		return 1;
        	}

        	int weight;
        	istringstream temp2;
        	temp2.str(parts[2]);
        	if (!(temp2 >> weight) || weight < 1) {		//checks if weight is an integer and greater than 0
        		cerr << "Error: Invalid edge weight '" << parts[2] << "' on line " << line_number << "." << endl;
        		delete_matrix(distances);
        		return 1;
        	}
        	distances[parts[0][0] - 65][parts[1][0] - 65] = weight;  //adds weight to distances
            line_number++;
        }
        input_file.close();   //close file
    } catch (const ifstream::failure &f) {		//catch any errors while reading file
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		delete_matrix(distances);
		return 1;
    }

    //create the path_lengths matrix to be a copy of the distances matrix
	path_lengths = new long*[num_vertices];
	for(int i=0; i<num_vertices; i++){
		path_lengths[i] = new long[num_vertices];
		for(int j=0; j<num_vertices; j++){
			path_lengths[i][j] = distances[i][j];
		}
	}

    //finds all pairs shortest path with Floyd's algorithm
    floyds_algorithm();

    //display tables
    display_table(distances, "Distance matrix:");
    display_table(path_lengths, "Path lengths:");
    display_table(intermediate_vertices, "Intermediate vertices:", true);
    display_paths();


    //delete all matrices from memory
    delete_matrix(distances);
    delete_matrix(path_lengths);
    delete_matrix(intermediate_vertices);

    return 0;
}
