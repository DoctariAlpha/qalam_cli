#include "session.h"
#include "get_courses.h"
#include "get_pass.h"
#include <string>
#include <vector>
#include "select.h"
#include "get_grades.h"
#include <iostream>


struct SessionData{ // stores current session data // 
        bool fetched_courses = false;
        std::string c_base_url = "https://qalam.nust.edu.pk/student";
        std::vector<std::vector<std::string>> courses;
        std::unordered_map<std::string,std::vector<std::vector<std::string>>> grades;
        //std::unordered_map<std::string,std::string> course_names;
};

void session(){
    SessionData current_session;
    cpr::Session session; // the current session
    cpr::Header header{
        {"Host", "qalam.nust.edu.pk"},
        {"User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:149.0) Gecko/20100101 Firefox/149.0"},
        {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"},
        {"Accept-Language", "en-US,en;q=0.9"}   
     };

    session.SetHeader(header);
    // std::string username_def = ""; // for now // remove this !!!!
    std::string password_def = "Student@123"; 
    std::string username{""}, password{""};
    std::cin.ignore();
    std::cout << "username:";
    std::getline(std::cin,username);
    std::cout << "password: ";
    password = getPassword(); // defined in get_pass.cpp

    //if (username == "") username = username_def; // remove this.
    if (password == "") password = password_def;

    int l = login(session,username,password); // checking if has logged in correctly

    if (l){
    	std::cout << "Successfully logged in! \n";
    	bool done = false;
    	std::string command{""};
    	while (!done){
    		std::cout << "--$ ";
    		std::cin >> command; 
                //cin.ignore;//?
    		if (command == "get_grades"){ // get_grades
                        if (!current_session.fetched_courses){
                                std::cout << "Courses not fetched. Fetching NOw.\n";
                                current_session.courses = get_courses(session);
                                current_session.fetched_courses = true;
                        }
                        int s = select(current_session.courses);
                        std::string c_id = current_session.courses.at(s).at(0);
                        printA(current_session.courses.at(s),"  ");
                        std::cout << '\n';
                        if (!current_session.grades.contains(c_id)){
                                std::cout << "Getting grades\n";
                                current_session.grades[c_id] = get_grades(c_id,session);
                        } printA(current_session.grades[c_id], "   ", 0);
                }

    		if (command == "get_courses") { // get the courses
                        if (!current_session.fetched_courses){
                                std::cout<< "Fetching courses\n";
                                current_session.courses = get_courses(session);
                                current_session.fetched_courses = true;
                        }
                        printA(current_session.courses);
    		}
                if (command == "get_all_grades") {
                        if (!current_session.fetched_courses){
                                std::cout << "Courses not fetched. Fetching Now.\n";
                                current_session.courses = get_courses(session);
                                current_session.fetched_courses = true;
                        }
                        
                        for (int i =0; i< current_session.courses.size(); i++){
                                std::cout << "\n";
                                std::string c_id = current_session.courses.at(i).at(0);
                                printA(current_session.courses.at(i),"  ");
                                std::cout << '\n';
                                if (!current_session.grades.contains(c_id)){
                                        std::cout << "Getting grades\n";
                                        current_session.grades[c_id] = get_grades(c_id,session);
                                } printA(current_session.grades[c_id],"   ",0);
                        }
                }

                if (command == "clear"){
                        std::cout << "\033[2J\033[H";
                }
    		if (command == "logout") done=true;
                if (command == "help") {
                        std::cout <<  "Commands:\n get_grades\n get_all_grades \n get_courses \n clear \n logout\n";

                }
    	   }
    	std::cout << "Logged out" << std::endl;
    }
    else{
    	std::cout << "Failed to login \n";
    }
}
