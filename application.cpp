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
    Schedule schd = Schedule();
    string add;
    cout << "Add a course? y/n" << endl;
    cin >> add;

    while (add != "n" && add != "N" && add != "y" && add != "Y") {
        cout << "invalid input. Please try again. Enter y or n. " << endl;
        cin >> add;
    }
    
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

        schd.addCourse(cor);

    cout << "Add a course? y/n" << endl;
    cin >> add;
    }

    // debug code



    // other inputs
    if(add == "n" || add == "N"){
        // retrieve the list of courses entered
        vector<Course> courses = schd.get_courseList();
        int num_of_courses = courses.size();

        // schd.print_info();
        cout << "trying to find a schedule" << endl; 
        vector<Section> selected = schd.scheduler();
        int size = selected.size();
        if(size != 0){
            cout << "found a schedule" << endl;
            // find out which course the sections belong and print out the section info. 
            for(unsigned int i = 0; i < size; i++){
                for(int j = 0; j < num_of_courses; j++){
                    if(courses[j].isInThisCourse(selected[i])){
                        cout << courses[j].get_courseName() << endl;
                    }
                }
                selected[i].print_info();
            }
        }

        else{
            cout << "We haven't found a schedule after 50 trials. " << endl;
        }

        // do one more time
        cout << "Wanna try again? y/n" << endl;
        string answer;
        cin >> answer;

        while(answer == "y"){
            // repeat the code above
            selected = schd.scheduler();
            int size = selected.size();
            if(size != 0){
                cout << "found a schedule" << endl;
                for(unsigned int i = 0; i < size; i++){
                    for(int j = 0; j < num_of_courses; j++){
                        if(courses[j].isInThisCourse(selected[i])){
                            cout << courses[j].get_courseName() << endl;
                        }
                    }
                    selected[i].print_info();
                }
            }

            else{
                cout << "We haven't found a schedule after 100 trials. " << endl;
            }
            cout << "Wanna try again? y/n" << endl;
            cin >> answer;
        }

        cout << "Thanks for using USC Schedule Helper. credit: Xinyang Xu. " << endl;

        return 0;
    }
    return 0;
}