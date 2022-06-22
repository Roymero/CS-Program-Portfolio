#include "courselist.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include<iomanip>
#include <sstream>
#include <string.h>
#include <cstring>

using namespace std;

struct courselist::Course // using a struct to properly segment data from text file
{
	string courseNumber; // first part of struct will be the course number
	string courseName;  // second will be the name
	vector<string> prereqs; // last will be a string vector of prereqs of the course

};

 vector<courselist::Course> courselist::loadUp() {

	 ifstream file1("list.txt");
	 vector<Course> myCourses;
	 string line;

	 while (getline(file1, line)) {
		 
		 Course course;
		 int beginning = 0;
		 int end = line.find(",");
		 vector <string> courseInfo;

		 while (end != -1) { // This while loop will separate the segments of each line by a comma and appropriate them 
			                 // to each value of the course struct appropriately

			 courseInfo.push_back(line.substr(beginning, (end - beginning)));
			 beginning = end + 1;
			 end = line.find(",", beginning);

		 }

		 courseInfo.push_back(line.substr(beginning, (end - beginning)));


		 course.courseNumber = courseInfo[0]; // Making the first segment of each line the course Number 
		 course.courseName = courseInfo[1];  // Second segment will be course name

		 for (int i = 2; i < courseInfo.size(); i++) {

			 course.prereqs.push_back(courseInfo[i]);  // Every segment after the second segment will be added to prereqs vector
		 }
		 
		 myCourses.push_back(course);



	 }

	 return myCourses;


}

 
 


void courselist::printMenu() {
	cout << "Welcome to the Course Planner" << endl;
	cout << endl;
	cout << "1. Load Data Structure" << endl;
	cout << "2. Print Course List" << endl;
	cout << "3. Print Course"<< endl;
	cout << "4. Exit"<<endl;
}



void courselist::printCourseList(vector<courselist::Course> courseList) {

	int vectorSize = courseList.size();
	
	//Going to use bubble sort to sort list

	for (int i = 0; i < vectorSize - 1; i++) {
		for (int j = 0; j < (vectorSize - 1) - i; j++) {

			if (courseList[j].courseNumber > courseList[j + 1].courseNumber) {
				swap(courseList[j + 1], courseList[j]);

			}

		}

	}

	// Printing out all courses.

	cout << "\nHere is a sample schedule: \n\n";
	for (int i = 0; i < vectorSize; i++) {
		printCourse2(courseList[i]);
	}
   
	cout << "\n";
}



void courselist::printCourse2(courselist::Course course) { // going to use this function to print out schedule with no prereqs

	// Assigning function variables

	string courseNumber = course.courseNumber;
	string courseName = course.courseName;
	vector <string> prereqs = course.prereqs;

	cout << courseNumber << ", " << courseName << endl;
}




void courselist::printCourse(courselist::Course course) {

	// Assigning function variables

	string courseNumber = course.courseNumber;
	string courseName = course.courseName;
	vector <string> prereqs = course.prereqs; 

	cout << courseNumber << ", " << courseName << endl;
	cout << "Prerequisites: ";
	

	// Printing out prereqs and removing coma at the end of the list
	for (int i = 0; i < prereqs.size(); i++) {
		if (i < prereqs.size() - 1) {
			cout << prereqs[i] << ", ";
		}
		else if (i == prereqs.size() - 1) {
			cout << prereqs[i];
		}
	}

	cout << "\n";



}


void courselist::searchCourseList(vector<courselist::Course> courseList) { // This function will search for courses

	int vectorSize = courseList.size();
	string course;
	string course1;
	int validation = 2;
	cout << "What course would you like to know more about? ";
	cin >> course;

	for (int i = 0; i < vectorSize; i++) {
		
		course1 = courseList[i].courseNumber;

		for (int j = 0; j < 4; j++) {

			course1[j] = tolower(course1[j]);
			course[j] = tolower(course[j]);

		}

		validation = course1.compare(course);

		if (validation == 0) {
			cout << "\n";
			printCourse(courseList[i]);
			return;
		}


	}

	// If course not found this will be the statement printed out.
	if (validation != 0) {
		cout << "\nCourse not found." << endl;
		
	}


}



void courselist::menuInput(int number) {

	static vector<Course> studentCourses;

	if (number == 1) { // Loading up courses from text file

		studentCourses = loadUp();
		
	}
	else if (number == 2) { // printing out course schedule

		
		printCourseList(studentCourses);
		
	}
	else if (number == 3) { // searching for course


		searchCourseList(studentCourses);

	}
	else if (number == 4) { // Simple termination function
		cout << "\nThank you for using the Roymero Inc. Automated Course List, Have a great day.\n";
		exit(EXIT_SUCCESS);
	}

	//using this while loop to catch any numbers greater than 5 and less than 1 as inputs
	while (number > 4 || number < 1) {
		cout << "\nError, please enter proper input: ";
		cin.clear();
		cin.ignore(123, '\n');
		cin >> number;
		menuInput(number);

	}



}





