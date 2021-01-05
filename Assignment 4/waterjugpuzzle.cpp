/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Nicholas Colonna
 * Date        : 10/19/2018
 * Description : Solves the water jug problem
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." -Nicholas Colonna
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

int a_cap, b_cap, c_cap;
bool goal_reached = false;
int goal_state [3];

// Struct to represent state of water in the jugs.
struct State {
	private:
		int a_lvl, b_lvl, c_lvl;
		vector<string> steps;

    public:
    	State(int _a, int _b, int _c, vector<string> pastSteps) : a_lvl(_a), b_lvl(_b), c_lvl(_c) {
    		steps = pastSteps;
    	}

    	//getter for jug a
    	int getA(){
    		return a_lvl;
    	}

    	//getter for jug b
    	int getB(){
    		return b_lvl;
    	}

    	//getter for jug c
    	int getC(){
    		return c_lvl;
    	}

    	//getter for steps
    	vector<string> getSteps(){
    		return steps;
    	}

    	//prints out all pours made
    	void printSteps(){
    		for(unsigned int i=0; i<steps.size(); i++){
    			cout << steps[i] << endl;
    		}
    	}
};

vector<string> buildSteps(int a, int b, int c){
	vector<string> steps;
	stringstream ss;
	ss << "Initial state. (" << a << ", " << b << ", " << c << ")";
	steps.push_back(ss.str());
	return steps;
}

string formatState(int a, int b, int c){
	stringstream ss;
	ss << "(" << a << ", " << b << ", " << c << ")";
	return ss.str();
}

bool isGoalReached(int a, int b, int c){
	if(goal_state[0]==a && goal_state[1]==b && goal_state[2]==c){
		return true;
	}
	return false;
}

queue<State> q;

//Utilize breadth-first search to go through combinations of pours to determine the best possible way to reach the target goal
void bfs(int a_lvl, int b_lvl, int c_lvl){
	//create 2D array that stores booleans of whether a state was visited
	bool **visited = new bool* [a_cap+1];
	for(int i=0; i<=a_cap; i++){
		visited[i] = new bool [b_cap+1];
		fill_n(visited[i], b_cap+1, false);
	}

	//create state for starting situation and at to queue
	State initialState(a_lvl, b_lvl, c_lvl, buildSteps(a_lvl, b_lvl, c_lvl));
	q.push(initialState);

	//loops through combinations until it finds a solution or determines there are no possible solutions
	while(!(q.empty())){
		//assigns values for jug levels from front of queue
		a_lvl = q.front().getA();
		b_lvl = q.front().getB();
		c_lvl = q.front().getC();

		int a, b, c;		//a, b, c are helpers when making pours
		int amount_poured;	//stores amount poured for help building steps
		string line;		//stores a step before its added to total steps

		//check if goal was reached
		if(isGoalReached(a_lvl, b_lvl, c_lvl) == true){
			goal_reached = true;
			q.front().printSteps();
			break;
		}

		State curr = q.front();
		q.pop();

		visited[a_lvl][b_lvl] = true;		//set current state to visited

		if(a_lvl < a_cap){   //C to A
			if(c_lvl > 0){		//only pours if the pouring jug has liquid in it
				a = a_lvl + c_lvl;
				b = b_lvl;

				if(a_cap < a){		//if after pour, receiving jug exceeds capacity, set receiving jug to its capacity
					a = a_cap;
				}
				amount_poured = a - a_lvl;
				c = c_lvl - amount_poured;

				//builds string for move
				stringstream ss;
				ss << amount_poured;
				string num = ss.str();
				if(amount_poured == 1){
					line = "Pour " + num + " gallon from C to A. ";
				}else{
					line = "Pour " + num + " gallons from C to A. ";
				}

				//checks if been visited and finishes string for move
				if(visited[a][b] == false){
					vector<string> allSteps = curr.getSteps();
					allSteps.push_back(line + formatState(a, b, c));
					State CtoA(a, b, c, allSteps);
					q.push(CtoA);
				}
			}
		}

		if(a_lvl < a_cap){		//B to A
			if(b_lvl > 0){		//only pours if the pouring jug has liquid in it
				a = a_lvl + b_lvl;
				c = c_lvl;

				if(a_cap < a){		//if after pour, receiving jug exceeds capacity, set receiving jug to its capacity
					a = a_cap;
				}
				amount_poured = a - a_lvl;
				b = b_lvl - amount_poured;

				//builds string for move
				stringstream ss;
				ss << amount_poured;
				string num = ss.str();
				if(amount_poured == 1){
					line = "Pour " + num + " gallon from B to A. ";
				}else{
					line = "Pour " + num + " gallons from B to A. ";
				}

				//checks if been visited and finishes string for move
				if(visited[a][b] == false){
					vector<string> allSteps = curr.getSteps();
					allSteps.push_back(line + formatState(a, b, c));
					State BtoA(a, b, c, allSteps);
					q.push(BtoA);
				}
			}
		}

		if(b_lvl < b_cap){		//C to B
			if(c_lvl > 0){		//only pours if the pouring jug has liquid in it
				b = b_lvl + c_lvl;
				a = a_lvl;

				if(b_cap < b){		//if after pour, receiving jug exceeds capacity, set receiving jug to its capacity
					b = b_cap;
				}
				amount_poured = b - b_lvl;
				c = c_lvl - amount_poured;

				//builds string for move
				stringstream ss;
				ss << amount_poured;
				string num = ss.str();
				if(amount_poured == 1){
					line = "Pour " + num + " gallon from C to B. ";
				}else{
					line = "Pour " + num + " gallons from C to B. ";
				}

				//checks if been visited and finishes string for move
				if(visited[a][b] == false){
					vector<string> allSteps = curr.getSteps();
					allSteps.push_back(line + formatState(a, b, c));
					State CtoB(a, b, c, allSteps);
					q.push(CtoB);
				}
			}
		}

		if(b_lvl < b_cap){		//A to B
			if(a_lvl > 0){		//only pours if the pouring jug has liquid in it
				b = b_lvl + a_lvl;
				c = c_lvl;

				if(b_cap < b){		//if after pour, receiving jug exceeds capacity, set receiving jug to its capacity
					b = b_cap;
				}
				amount_poured = b - b_lvl;
				a = a_lvl - amount_poured;

				//builds string for move
				stringstream ss;
				ss << amount_poured;
				string num = ss.str();
				if(amount_poured == 1){
					line = "Pour " + num + " gallon from A to B. ";
				}else{
					line = "Pour " + num + " gallons from A to B. ";
				}

				//checks if been visited and finishes string for move
				if(visited[a][b] == false){
					vector<string> allSteps = curr.getSteps();
					allSteps.push_back(line + formatState(a, b, c));
					State AtoB(a, b, c, allSteps);
					q.push(AtoB);
				}
			}
		}

		if(c_lvl < c_cap){		//B to C
			if(b_lvl > 0){		//only pours if the pouring jug has liquid in it
				c = c_lvl + b_lvl;
				a = a_lvl;

				if(c_cap < c){		//if after pour, receiving jug exceeds capacity, set receiving jug to its capacity
					c = c_cap;
				}
				amount_poured = c - c_lvl;
				b = b_lvl - amount_poured;

				//builds string for move
				stringstream ss;
				ss << amount_poured;
				string num = ss.str();
				if(amount_poured == 1){
					line = "Pour " + num + " gallon from B to C. ";
				}else{
					line = "Pour " + num + " gallons from B to C. ";
				}

				//checks if been visited and finishes string for move
				if(visited[a][b] == false){
					vector<string> allSteps = curr.getSteps();
					allSteps.push_back(line + formatState(a, b, c));
					State BtoC(a, b, c, allSteps);
					q.push(BtoC);
				}
			}
		}

		if(c_lvl < c_cap){		//A to C
			if(a_lvl > 0){		//only pours if the pouring jug has liquid in it
				c = c_lvl + a_lvl;
				b = b_lvl;

				if(c_cap < c){		//if after pour, receiving jug exceeds capacity, set receiving jug to its capacity
					c = c_cap;
				}
				amount_poured = c - c_lvl;
				a = a_lvl - amount_poured;

				//builds string for move
				stringstream ss;
				ss << amount_poured;
				string num = ss.str();
				if(amount_poured == 1){
					line = "Pour " + num + " gallon from A to C. ";
				}else{
					line = "Pour " + num + " gallons from A to C. ";
				}

				//checks if been visited and finishes string for move
				if(visited[a][b] == false){
					vector<string> allSteps = curr.getSteps();
					allSteps.push_back(line + formatState(a, b, c));
					State AtoC(a, b, c, allSteps);
					q.push(AtoC);
				}
			}
		}
	}

	//print statement when no solution was found
	if(goal_reached == false){
		cout << "No solution." << endl;
	}

	//clean memory (method from from stackoverflow)
	//https://stackoverflow.com/questions/30720594/deleting-a-dynamically-allocated-2d-array
	for(int i=0; i<=b_cap; i++){
		delete[] visited[i];
	}
	delete[] visited;
}


int main(int argc, char * const argv[]) {
	//error checks right amount of arguments
	if(argc != 7){		//throw error if less than or more than 7 arguments are given
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}

	//error checking inputs
	int args [6] = {};
	for(int i=1; i<7; i++){
		int help;
		istringstream iss(argv[i]);
		if(!(iss >> help) || help < 0){		//if capacity or goal is not an integer or is negative, throw error
			if(i <= 3){
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char)(i+64) << "." << endl;
				return 1;
			}else{
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << (char)(i-3+64) << "." << endl;
				return 1;
			}
		}
		if(i==3 && help==0){	//if C is initially empty, throw error
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char)(i+64) << "." << endl;
			return 1;
		}

		args[i-1] = help;  //store argv[i] values for testing and less stringstream use
	}

	//error checking capacity with goals
	int sum = 0;
	for(int i=0; i<3; i++){
		int j = i+3;
		if(args[i] < args[j]){		//if capacity is less than goal for a jug, throw error
			cerr << "Error: Goal cannot exceed capacity of jug " << (char)(i+65) << "." << endl;
			return 1;
		}
		sum += args[j];
	}
	//error checking goal state total
	if(args[2] != sum){		//if sum of water in goal state is not equal to starting amount in jug c, throw error
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}


	//assigns inputed goals to global goal array
	for(int i=3; i<6; i++){
		goal_state[i-3] = args[i];
	}
	//assign capacity inputs to global capacity variables
	a_cap = args[0];
	b_cap = args[1];
	c_cap = args[2];

	bfs(0,0, c_cap);	//calls breadth-first search function that checks all paths for solution

	return 0;
}
