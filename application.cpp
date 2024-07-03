#include <iostream>
#include <string>
#include <vector>
#include "CourseSection.cpp"

using namespace std;

// global helper function
int to_second(int hour, int minute){
    return hour*60 + minute;
}

int main(){
    // Initialize the Schedule object, which contains information for the courses the user
    // is willing to take
    Schedule schd = Schedule();

    // whether the user is going to add a course
    string add;
    cout << "Add a course? y/n" << endl;
    cin >> add;

    // check the validity of user input
    while (add != "n" && add != "N" && add != "y" && add != "Y") {
        cout << "invalid input. Please try again. Enter y or n. " << endl;
        cin >> add;
    }
    
    // the main segment. perform the course and section input. 
    while(add == "y" || add == "Y"){
        // read the course name
        string courseName;
        cout << "Course Name: " << endl;
        cin >> courseName;
        if(cin.fail()){
            cout << "Error reading course name" << endl;
            return 1;
        }
        
        // initialize the course variable
        // Caution: do i need to dynamically allocate the variables?
        Course cor = Course(courseName); 

        // read the section info
        cout << "Please enter: section name; string type; startHour, startMinute, endHour, endMinute, dates " << endl;
        cout << "Enter 'end' to stop" << endl;
        while(true){
            string name, type, dates; int startHour, startMinute, endHour, endMinute; 
            cin >> name;
            if(name == "end" || name == "End") break;
            cin >> type >> startHour >> startMinute >> endHour >> endMinute >> dates;
            if(cin.fail()){
                cout << "Invalid input" << endl;
                return 1;
            }
            int start = to_second(startHour, startMinute);
            int end = to_second(endHour, endMinute);

            Section sec = Section(name, type, start, end, dates);
            cor.addSection(sec);

            // add to corresponding section types
            if(type == "Lecture") cor.add_lectures(sec);
            if(type == "Discussion" || type == "Lab") cor.add_discussions(sec);
            if(type == "Quiz") cor.add_quizzes(sec);
        }

        // already entered a complete course. add the course to the schedule 
        schd.addCourse(cor);
    
    // whether to add another course. 
    cout << "Add a course? y/n" << endl;
    cin >> add;
    }

    // debug code



    // If the user enters no, then we start to schedule the courses based on the user input. 
    if(add == "n" || add == "N"){
        // retrieve the list of courses entered
        vector<Course> courses = schd.get_courseList();
        int num_of_courses = courses.size();

        // schd.print_info();
        cout << "trying to find a schedule" << endl; 
        vector< vector<Section> > selected = schd.findSchedule();
        int size = selected.size(); // the number of possible combinations

        if(size != 0){
            cout << "found a schedule" << endl;

            cout << "Please choose the option that matches your needs" << endl;
            cout << "A: latest start time, on average" << endl;
            cout << "B: give me a random schedule" << endl;
            char option;
            cin >> option;
            if(cin.fail() || (option != 'A' && option != 'a' && option != 'B' && option != 'b')){
                cout << "invalid selection" << endl; 
                cout << "Please choose the option that matches your needs" << endl;
                cin >> option;
            }

            else if(option == 'A'|| option == 'a'){
                // find a schedule with the latest start time, on average
                int index = schd.findScheduleWithLatestStartTime();

                // In this nested for loop, we are trying to find out which
                // course the sections belong and print out the section info. 
                for(unsigned int i = 0; i < selected[index].size(); i++){
                    for(int j = 0; j < num_of_courses; j++){
                        if(courses[j].isInThisCourse(selected[index][i])){
                            cout << courses[j].get_courseName() << endl;
                        }
                    }

                    cout << selected[index][i];
                }

            }

            else if(option != 'B' || option != 'b'){
                // choose the first found schedule, and check the corresponding course
                for(unsigned int i = 0; i < selected[0].size(); i++){
                    for(int j = 0; j < num_of_courses; j++){
                        if(courses[j].isInThisCourse(selected[0][i])){
                            cout << courses[j].get_courseName() << endl;
                        }
                    }

                    cout << selected[0][i];
                }                
            }
        }

        else{
            cout << "We haven't found a schedule after 1000 trials. " << endl;
        }

        cout << "Thanks for using USChedule. credit: Xinyang Xu. " << endl;

        return 0;
    }

    return 0;
}