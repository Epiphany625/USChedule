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
    vector<int> monday;
    vector<int> tuesday;
    vector<int> wednesday;
    vector<int> thursday;
    vector<int> friday;

    for(int i = 0; i < size; i++){
        // take notes of the start and end time
        int start = sections_to_take[i].get_startTime();
        int end = sections_to_take[i].get_startTime();

        // determine when the section will take place, and push to corresponding vectors
        if(sections_to_take[i].get_dates()[0]) {monday.push_back(start); monday.push_back(end); }
        if(sections_to_take[i].get_dates()[1]) {tuesday.push_back(start); tuesday.push_back(end); }
        if(sections_to_take[i].get_dates()[2]) {wednesday.push_back(start); wednesday.push_back(end); }
        if(sections_to_take[i].get_dates()[3]) {thursday.push_back(start); thursday.push_back(end); }
        if(sections_to_take[i].get_dates()[4]) {friday.push_back(start); friday.push_back(end); }       
    }

    int monSize = monday.size();
    int tueSize = tuesday.size();
    int wedSize = wednesday.size();
    int thurSize = thursday.size();
    int friSize = friday.size();

    // Attention. This is the core of all the codes. Determine whether the selected fits the schedule. 
    // Attention. Take extra care of index exception. 

    // Monday
    for(int i = 0; i < monSize; i += 2){
        for(int j = i; j < monSize; j+= 2){
            // four possibilities of failing to become a good schedule. 
            if(j != i && ((monday[j] >= monday[i] && monday[j] <= monday[i+1])||(monday[j+1] >= monday[i] && monday[j+1] <= monday[i+1]))){
                if((monday[j] <= monday[i] && monday[j+1] >= monday[i+1])||(monday[j] >= monday[i] && monday[j+1] <= monday[i+1])){
                    return false;
                }
            }
        }
    }
    // Tuesday
    for(int i = 0; i < tueSize; i += 2){
        for(int j = i; j < tueSize; j+= 2){
            // four possibilities of failing to become a good schedule. 
            if(j != i && ((tuesday[j] >= tuesday[i] && tuesday[j] <= tuesday[i+1])||(tuesday[j+1] >= tuesday[i] && tuesday[j+1] <= tuesday[i+1]))){
                if((tuesday[j] <= tuesday[i] && tuesday[j+1] >= tuesday[i+1])||(tuesday[j] >= tuesday[i] && tuesday[j+1] <= tuesday[i+1])){
                    return false;
                }
            }
        }
    }
    // Wednesday
    for(int i = 0; i < wedSize; i += 2){
        for(int j = i; j < wedSize; j+= 2){
            // four possibilities of failing to become a good schedule. 
            if(j != i && ((wednesday[j] >= wednesday[i] && wednesday[j] <= wednesday[i+1])||(wednesday[j+1] >= wednesday[i] && wednesday[j+1] <= wednesday[i+1]))){
                if((wednesday[j] <= wednesday[i] && wednesday[j+1] >= wednesday[i+1])||(wednesday[j] >= wednesday[i] && wednesday[j+1] <= wednesday[i+1])){
                    return false;
                }
            }
        }
    }
    // Thursday
    for(int i = 0; i < thurSize; i += 2){
        for(int j = i; j < thurSize; j+= 2){
            // four possibilities of failing to become a good schedule. 
            if(j != i && ((thursday[j] >= thursday[i] && thursday[j] <= thursday[i+1])||(thursday[j+1] >= thursday[i] && thursday[j+1] <= thursday[i+1]))){
                if((thursday[j] <= thursday[i] && thursday[j+1] >= thursday[i+1])||(thursday[j] >= thursday[i] && thursday[j+1] <= thursday[i+1])){
                    return false;
                }
            }
        }
    }
    // Friday
    for(int i = 0; i < friSize; i += 2){
        for(int j = i; j < friSize; j+= 2){
            // four possibilities of failing to become a good schedule. 
            if(j != i && ((friday[j] >= friday[i] && friday[j] <= friday[i+1])||(friday[j+1] >= friday[i] && friday[j+1] <= friday[i+1]))){
                if((friday[j] <= friday[i] && friday[j+1] >= friday[i+1])||(friday[j] >= friday[i] && friday[j+1] <= friday[i+1])){
                    return false;
                }
            }
        }
    }

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

