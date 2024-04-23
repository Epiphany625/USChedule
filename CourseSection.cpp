#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "CourseSection.h"

using namespace std;

// Constructors, initializing constructors
Course::Course(){
    courseName_ = ""; 

}

Course::Course(string name){
    courseName_ = name;
}

// accessors
string Course::get_courseName() const{
    return courseName_;
}

// mutator
void Course::addSection(const Section& sectionInfo){
    sections_.push_back(sectionInfo);
}

Section::Section(){
    sectionName_ = "";
    type_ = "";
    startTime_ = 0;
    endTime_ = 0;
}

Section::Section(string name, string type, int start, int end, string dates){
    sectionName_ = name;
    type_ = type;
    startTime_ = start;
    endTime_ = end;
    dates_.resize(5);

    int size = dates.size();

    // deal with the dates vector
    // already checked with compiler
    for(unsigned int i = 0; i < size - 1; i++){
        if(dates[i] == 'M') dates_[0] = true;
        if(dates[i] == 'T' && dates[i+1] != 'h') dates_[1] = true;
        if(dates[i] == 'W') dates_[2] = true;
        if(dates[i] == 'T' && dates[i+1] == 'h') dates_[3] = true;
        if(dates[i] == 'F') dates_[4] = true;
    }

    if(dates[size - 1] == 'M') dates_[0] = true;
    if(dates[size - 1] == 'T') dates_[1] = true;
    if(dates[size - 1] == 'W') dates_[2] = true;
    if(dates[size - 1] == 'F') dates_[4] = true;
}


void Section::print_dates() const{
    string date = "12345";
    for(unsigned int i = 0; i < dates_.size(); i++){
        if(dates_[i] == true) cout << date[i];
    }

    cout << endl;
}

vector<bool> Section::get_dates() const {
    return dates_;
}

string Section::get_sectionName() const {
    return sectionName_;
}

string Section::get_type() const {
    return type_;
}

int Section::get_startTime() const {
    return startTime_;
    }

int Section::get_endTime() const {
    return endTime_;
}

bool Course::isInThisCourse(Section& sec){
    int size = sections_.size();
    for(int i = 0; i < size; i++){
        if(sec.get_sectionName() == sections_[i].get_sectionName()) return true;
    }
    return false; 
}

// Debug function
// tests whether the notes are taken down appropriately, the accessors, and the print function. 
void Section::print_info() const {
    cout << "Section name: " << sectionName_ << "    ";
    cout << "Section type: " << type_ << endl;
    cout << "Start time: " << startTime_ / 60 << ":" << startTime_ % 60 << "         ";
    cout << "End time: " << endTime_ / 60 << ":" << endTime_ % 60 << endl;
    cout << "Dates: ";
    print_dates();
    cout << "------------------------------" << endl;
}

// Debug function
void Course::print_info() const {
    cout << "Course name: " << get_courseName() << endl;
    cout << "Sections: " << endl;
    for(unsigned int i = 0; i < sections_.size(); i++){
        sections_[i].print_info();
    }
    cout << "Number of Lectures: " << lectures_.size() << endl;
    cout << "Number of Discussions: " << discussions_.size() << endl;
    cout << "Number of Quizzes: " << quizzes_.size() << endl;
    cout << endl;
    cout << endl;
}


void Section::push_dates(bool date){
    dates_.push_back(date);
}

// Constructor definition
Schedule::Schedule() {}

// Adds a course to the schedule
void Schedule::addCourse(const Course& cor) {
    courseList_.push_back(cor);
}

// Prints information about each course in the schedule
void Schedule::print_info() const {
    for (unsigned int i = 0; i < courseList_.size(); i++) {
        courseList_[i].print_info();
    }
}

vector<Course> Schedule::get_courseList() const {
    return courseList_;
}

bool Schedule::isGood(const vector<Section>& sections_to_take) const{

    // take note of everyday's start time and end time
    int size = sections_to_take.size();
    vector< vector<int> > week(5);

    // Attention. This is the core of all the codes. Determine whether the selected fits the schedule. 
    // Attention. Take extra care of index exception. 
    // this nested for loop mainly deals with populating the week vector
    // in the format of start, end, start, end, ...
    // the index of the week represents the day of the week
    for(int i = 0; i < size; i++){
        // take notes of the start and end time
        int start = sections_to_take[i].get_startTime();
        int end = sections_to_take[i].get_endTime();

        // update the values of of "week"
        for(int j = 0; j < 5; j++){    
            if(sections_to_take[i].get_dates()[j]) {    
                week[j].push_back(start);
                week[j].push_back(end);
            }       
        }
    }

    for(int i = 0; i < 5; i++){
        int weekDaySize = week[i].size();
        for(int j = 0; j < weekDaySize; j+=2){
            for(int k = j; k < weekDaySize; k+=2){
                if(k != j && ((week[i][k] >= week[i][j] && week[i][k] <= week[i][j+1])||(week[i][k+1] >= week[i][j] && week[i][k+1] <= week[i][j+1]))){
                    if((week[i][k] <= week[i][j] && week[i][k+1] >= week[i][j+1])||(week[i][k] >= week[i][j] && week[i][k+1] <= week[i][j+1])){
                        return false;
                    }
                }                
            }
        }
    }

    // the part above is hard to understand, and it means something below. Making Mondey as an example. 

    // // Monday
    // for(int i = 0; i < monSize; i += 2){
    //     for(int j = i; j < monSize; j+= 2){
    //         // four possibilities of failing to become a good schedule. 
    //         if(j != i && ((monday[j] >= monday[i] && monday[j] <= monday[i+1])||(monday[j+1] >= monday[i] && monday[j+1] <= monday[i+1]))){
    //             if((monday[j] <= monday[i] && monday[j+1] >= monday[i+1])||(monday[j] >= monday[i] && monday[j+1] <= monday[i+1])){
    //                 return false;
    //             }
    //         }
    //     }
    // }

    // debug code
    // cout << "Wednesday" << endl;
    // for(unsigned int i = 0; i < week[2].size(); i++){
    //     cout << week[2][i] << " " << endl; 
    // }
    return true; 
}

vector<Section> Schedule::scheduler() const {
    cout << "entered the scheduler function" << endl;
    int num_of_courses = courseList_.size();
    // repeat the process 100 times
    vector<Section> selected;

    for(int i = 0; i < 100; i++){     
        for(int j = 0; j < num_of_courses; j++){
            // select lectures, discussions, and quizzes at random
            // take notes of the size

            // cout << "starting selecting lectures, discussions, and quizzes" << endl;
            vector<Section> lectures = courseList_[j].get_lectures();
            int num_of_lectures = lectures.size();
            vector<Section> discussions = courseList_[j].get_discussions();
            int num_of_discussions = discussions.size();
            vector<Section> quizzes = courseList_[j].get_quizzes();
            int num_of_quizzes = quizzes.size();

            
            // select at random
            if(num_of_lectures > 0){
                selected.push_back(lectures[rand() % num_of_lectures]);
            }

            if(num_of_discussions > 0){
                selected.push_back(discussions[rand() % num_of_discussions]);
            }

            if(num_of_quizzes > 0){
                selected.push_back(quizzes[rand() % num_of_quizzes]);
            }
            // cout << "finished selecting" << endl;
        }
        // cout << "finished the loop" << endl;
        if(isGood(selected)) return selected; 
        else {
            selected.clear();
            // cout << "Oops" << endl;
        }
    }

    return selected; 
}
