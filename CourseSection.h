#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Section{

    // Contains:
    // Constructors, Accessors, Operator Overloadings, Mutators
    public:
    // Default constructor and initializing constructors
    Section();
    Section(const string& name, const string& type, int start, int end, const string& dates);

    // Accessors
    string get_sectionName() const; // this is the unique identifier of sections
    string get_type() const;
    void print_dates() const;
    vector<bool> get_dates() const; 
    int get_startTime() const;
    int get_endTime() const;

    // Operator overloading
    // whether it is the same section
    bool operator==(const Section& rhs);

    // print the information of the section
    friend ostream& operator<<(ostream& os, const Section& rhs);

    // Debug function
    // tests whether the Section object has successfully recorded the data. 
    // void print_info() const;

    // Mutator. Change the dates_ member.
    void push_dates(bool date);
    
    private:
    string sectionName_;
    string type_; // didn't consider the condition when some discussions can only correspond to a specific lecture
    vector<bool> dates_; // Mon, Tue, Wed, Thur, Fri
    // in seconds
    int startTime_;
    int endTime_;
};

class Course{
    public:

    // Constructors, initializing constructors
    Course();
    Course(const string& name);

    // accessors
    string get_courseName() const{ return courseName_; }
    vector<Section> get_lectures() const {return lectures_; }
    vector<Section> get_discussions() const {return discussions_; }
    vector<Section> get_quizzes() const {return quizzes_; }

    // mutator
    void addSection(const Section& sectionInfo);
    void add_lectures(const Section& sec){lectures_.push_back(sec); }
    void add_discussions(const Section& sec){discussions_.push_back(sec); }
    void add_quizzes(const Section& sec){quizzes_.push_back(sec); }

    // Operator overloading
    // debug function
    friend ostream& operator<<(ostream& os, const Course& rhs);

    // identify whether a section is in this course
    bool isInThisCourse(Section& sec);

    private:
    string courseName_;
    vector<Section> sections_;
    vector<Section> lectures_;
    vector<Section> discussions_;
    vector<Section> quizzes_;
};

class Schedule {
public:
    // Constructor
    Schedule();

    // return the courseList
    vector<Course> get_courseList() const; 

    // Adds a course to the schedule
    void addCourse(const Course& cor);

    // Prints information about each course in the schedule
    void print_info() const;

    // Schedules sections based on the courses added
    // returns a list of available schedules
    vector< vector<Section> > findSchedule();
    int findScheduleWithLatestStartTime() const; 

private:
    // private data members
    vector<Course> courseList_; // List of courses in the schedule
    vector< vector<Section> > scheduleOptions_; // Options of available course schedules

    // Helper function: determines whether the given schedule of sections meets criteria
    bool isGood(const vector<Section>& sections_to_take) const;

};