#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "CourseSection.h"

using namespace std;

// Default Constructor of Course object
Course::Course() : courseName_("") { }

// Initializing Constructor of Course object
Course::Course(const string& name) : courseName_(name) { } 

// Add a section to a course
void Course::addSection(const Section& sectionInfo){
    sections_.push_back(sectionInfo);
}

// Default Constructor of Section object
Section::Section(){
    sectionName_ = "";
    type_ = "";
    startTime_ = 0;
    endTime_ = 0;
}

// Initializing Constructor of Section object
// Parse the dates
Section::Section(const string& name, const string& type, int start, int end, const string& dates) : 
sectionName_(name), type_(type), dates_(5) , startTime_(start), endTime_(end) {

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

// Various Accessors of Section object
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

bool Section::operator==(const Section& rhs){
    return (sectionName_ == rhs.get_sectionName());
}

bool Course::isInThisCourse(Section& sec){
    int size = sections_.size();
    for(int i = 0; i < size; i++){
        if(sec == sections_[i]) return true;
    }
    return false; 
}

ostream& operator<<(ostream& os, const Section& rhs){
    os << "------------------------------------------------" << endl;    
    os << "Section name: " << rhs.sectionName_ << "    ";
    os << "Section type: " << rhs.type_ << endl;
    os << "Start time: " << rhs.startTime_ / 60 << ":" << rhs.startTime_ % 60 << "         ";
    os << "End time: " << rhs.endTime_ / 60 << ":" << rhs.endTime_ % 60 << endl;
    os << "Dates: ";
    rhs.print_dates();
    os << "------------------------------------------------" << endl;    
    return os;
}

// Debug function: print out the course info
ostream& operator<<(ostream& os, const Course& rhs){
    os << "Course name: " << rhs.get_courseName() << endl;
    os << "Sections: " << endl;
    for(unsigned int i = 0; i < rhs.sections_.size(); i++){
        os << rhs.sections_[i];
    }
    os << "Number of Lectures: " << rhs.lectures_.size() << endl;
    os << "Number of Discussions: " << rhs.discussions_.size() << endl;
    os << "Number of Quizzes: " << rhs.quizzes_.size() << endl;
    os << endl;
    os << endl;
    return os;    
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
        cout << courseList_[i];
    }
}

vector<Course> Schedule::get_courseList() const {
    return courseList_;
}

// check whether this is a good schedule
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

        // update the values of of "week" with the order of start time(2n) and end time(2n+1)
        for(int j = 0; j < 5; j++){    
            if(sections_to_take[i].get_dates()[j]) {    
                week[j].push_back(start);
                week[j].push_back(end);
            }       
        }
    }

    // start to determine whether the schedule is good or not
    for(int i = 0; i < 5; i++){
        int weekDaySize = week[i].size();
        // find every possible combination that can result in a conflict of time
        // resembles the algorithm for bubble sort
        for(int j = 0; j < weekDaySize; j+=2){
            for(int k = j; k < weekDaySize; k+=2){
                if(k != j && ((week[i][k] >= week[i][j] && week[i][k] <= week[i][j+1])||(week[i][k+1] >= week[i][j] && week[i][k+1] <= week[i][j+1]))){
                    return false; 
                }
                if(k != j && ((week[i][k] <= week[i][j] && week[i][k+1] >= week[i][j+1])||(week[i][k] >= week[i][j] && week[i][k+1] <= week[i][j+1]))){
                    return false; 
                }                
            }
        }
    }

    // debug code
    // cout << "Wednesday" << endl;
    // for(unsigned int i = 0; i < week[2].size(); i++){
    //     cout << week[2][i] << " " << endl; 
    // }
    return true; 
}

// not a const function, because it initializes another data member
vector< vector<Section> > Schedule::findSchedule() {
    cout << "entered the scheduler function" << endl;
    int num_of_courses = courseList_.size();
    
    vector< vector<Section> > selected;
    // repeat the process 1000 times

    // now, we are going to find the repetition time. 
    int repetition = 4;
    for(unsigned int i = 0; i < courseList_.size(); i++){
        unsigned char num_of_lectures = courseList_[i].get_lectures().size();
        unsigned char num_of_discussions = courseList_[i].get_discussions().size();
        unsigned char num_of_quizzes = courseList_[i].get_quizzes().size();
        // multiply the numbers to find the required time for repetition. 
        if(num_of_lectures != 0){
            repetition *= num_of_lectures;
        }
        if(num_of_discussions != 0){
            repetition *= num_of_discussions;
        }
        if(num_of_quizzes != 0){
            repetition *= num_of_quizzes;
        }        
    }
    // End of finding the number of repetition

    for(int i = 0; i < repetition; i++){ 

        // come up with a possible combination
        vector<Section> possibleCombination;    

        for(int j = 0; j < num_of_courses; j++){

            // select lectures, discussions, and quizzes at random
            // take notes of the size

            // cout << "starting selecting lectures, discussions, and quizzes" << endl;
            vector<Section> lectures = courseList_[j].get_lectures();
            unsigned char num_of_lectures = lectures.size();
            vector<Section> discussions = courseList_[j].get_discussions();
            unsigned char num_of_discussions = discussions.size();
            vector<Section> quizzes = courseList_[j].get_quizzes();
            unsigned char num_of_quizzes = quizzes.size();

            
            // select random lectures, discussions(labs), and quizzes
            
            if(num_of_lectures > 0){
                possibleCombination.push_back(lectures[rand() % num_of_lectures]);
            }
            if(num_of_discussions > 0){
                possibleCombination.push_back(discussions[rand() % num_of_discussions]);
            }
            if(num_of_quizzes > 0){
                possibleCombination.push_back(quizzes[rand() % num_of_quizzes]);
            }
            // cout << "finished selecting" << endl;
        }

        // cout << "finished the loop" << endl;

        // if the combination doesn't have time conflicts, we push back the selection
        if(isGood(possibleCombination)) {
            selected.push_back(possibleCombination);
            // cout << "there is a schedule" << endl; 
        }

        // this schedule is not good. we have to clear the selected sections and do again.
        else {           
            possibleCombination.clear();
            // cout << "Oops" << endl;
        }
    }

    
    cout << "number of repetition: " << repetition << endl;

    scheduleOptions_ = selected; 
    return selected; 
}

int Schedule::findScheduleWithLatestStartTime() const{
    // it is possible to better the code a little bit here

    int index = 0; // the index of the schedule with the latest start time
    int size = scheduleOptions_.size(); // the number of possible schedules (combination of sections)
    cout << "Size of schedule Options" << size << endl; 
    int sectionCount = scheduleOptions_[0].size(); // the number of sections to take each week

    int largestSum = 0;

    for(int i = 0; i < size; i++){
        // Step 1: take note of everyday's start time and end time, store them in a vector.
        vector< vector<int> > week(5);
        for(int j = 0; j < sectionCount; j++){
            // take notes of the start and end time
            int start = scheduleOptions_[i][j].get_startTime();
            int end = scheduleOptions_[i][j].get_endTime();

            // update the values of of "week" with the order of start time(2n) and end time(2n+1)
            for(int k = 0; k < 5; k++){    
                if(scheduleOptions_[i][j].get_dates()[k]) {    
                    week[k].push_back(start);
                    week[k].push_back(end);
                }       
            }
        }
        // Step 1 End

        // Step 2 Start
        // now, we need to sum up the earliest start time every day
        // we also need to take care of the days when there is actually no class
        // we just assume that these kinds of days has a start time at 14:00

        int sum = 0; // the sum of the earliest start times. 

        for(int weekday = 0; weekday < 5; weekday++){
            int start = 1440;

            // deal with the case when there exists a day that doesn't have a class
            if(week[weekday].size() == 0){
                sum += 840;
            }

            // find the earliest start time for each day
            for(unsigned int j = 0; j < week[weekday].size(); j++){
                if(week[weekday][j] < start){
                    start = week[weekday][j];
                }
            }

            sum += start; 
        }

        // find the largest sum. This means that we are finding the schedule witht the latest wake up time. 

        if(sum > largestSum){
            largestSum = sum;
            index = i;
        }
    }

    return index; 
}