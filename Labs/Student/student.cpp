/*
 * student.cpp
 *
 *  Created on: Sep 7, 2018
 *      Author: Nicholas Colonna
 *      Pledge: "I pledge my honor that I have abided by the Stevens Honor System." ncolonna
 */
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student {

public:
	//Constructor
	Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} { }

	//Methods
	string full_name() const {
		return first_ + " " + last_;
	}

	int id() const {
		return id_;
	}

	float gpa() const {
		return gpa_;
	}

	void print_info() const {
		cout << first_ << " " << last_ << ", GPA: " << fixed << setprecision(2) << gpa_
				<< ", ID: " << id_ << endl;
		//formatting to 2 decimals from StackOverflow
	}

private:
	//Member Variables
	string first_;
	string last_;
	float gpa_;
	int id_;
};

/**
 * Takes a vector of Student objects, and returns a new vector with all Students whose GPA is < 1.0
 */
vector<Student> find_failing_students(const vector<Student> &students) {
	//Iterates through the students vector, appending each student whose gpa is less than 1.0 to the failing_students vector
	vector<Student> failing_students;
	for(auto it = students.cbegin(); it != students.cend(); ++it){
		if(it->gpa() < 1.0){
			failing_students.push_back(*it);
		}
	}
	return failing_students;
}

/**
 * Takes a vector of Student objects and prints them to the screen
 */
void print_students(const vector<Student> &students) {
	//Iterates through the students vector, calling print_info() for each student
	for(auto it = students.cbegin(); it != students.cend(); ++it){
		it->print_info();
	}
}

/** 
 * Allows the user to enter information for multiple students, then
 * find those students whose GPA is below 1.0 and prints them to the
 * screen.   
 */
int main() {
	 string first_name, last_name;
	 float gpa;
	 int id;
	 char repeat;
	 vector<Student> students;

	 do {
		 cout << "Enter student's first name: ";
		 cin >> first_name;
		 cout << "Enter student's last name: ";
		 cin >> last_name;
		 gpa = -1;
		 while(gpa < 0 || gpa > 4){
			 cout << "Enter student's GPA (0.0-4.0): ";
			 cin >> gpa;
		 }
		 cout << "Enter student's ID: ";
		 cin >> id;
		 students.push_back(Student(first_name, last_name, gpa, id));
		 cout << "Add another student to database (Y/N)? ";
		 cin >> repeat;
	 } while(repeat == 'Y' || repeat == 'y');

	 cout << endl << "All students:" << endl;
	 print_students(students);

	 cout << endl << "Failing students:";
	 vector<Student> failing_students = find_failing_students(students); //make vector of failing students
	 if(failing_students.empty() == true){
		 cout << " None" << endl;		//print space and "None" if no students failing
	 } else {
		 cout << endl;
		 print_students(failing_students);  //otherwise print each failing student on separate line
	 }

	 return 0;
 }
