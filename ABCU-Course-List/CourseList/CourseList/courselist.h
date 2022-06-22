#pragma once
#ifndef COURSELIST_H
#define COURSELIST_H

#include "courselist.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cstring>

using namespace std;

class courselist {

     private: // no private functions

         
        
     
     public:
         void menuInput(int number);
         void printMenu();
         struct Course;
         vector<Course> loadUp();
         void printCourse(struct Course course);
         void printCourseList(vector<Course> courseList);
         void printCourse2(struct Course course);
         void searchCourseList(vector<Course> courselist);



};
#endif
