// Nick Boodoo

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define Course object
class Course {

private:
    string courseNumber;
    string courseName;
    vector<string> preReqs;

    // Using setters and getters to access the Course object
public:
    void setName(string name) {
        courseName = name;
    }

    string getName() {
        return courseName;
    }

    void setNumber(string number) {
        courseNumber = number;
    }

    string getNumber() {
        return courseNumber;
    }

    void addpreReq(string courseNum) {
        this->preReqs.push_back(courseNum);
    }

    vector<string> getpreReqs() {
        return preReqs;
    }

    // Defining constructor for Course object
    Course(string number, string name) {
        this->courseName = name;
        this->courseNumber = number;
    }

};

// Selection sort to sort courses by course number alphanumerically
vector<Course> mySort(vector<Course> courses) {
    for (int spot = 0; spot < courses.size(); spot++) {
        int current_min = spot;
        for (int look = spot; look < courses.size(); look++) {
            if (courses[look].getNumber() < courses[current_min].getNumber()) {
                current_min = look;
            }
        }
        // Swap spot and current_min
        Course temp = courses[spot];
        courses[spot] = courses[current_min];
        courses[current_min] = temp;
    }
    return courses;
}

// Read input file and create Course objects
vector<Course> loadDataStructure() {

    // Initialize a vector to store contents of the course file
    vector<string> lines;

    ifstream file;

    string textFileName;

    cout << "Enter the name of the file which you would like to import." << endl;
    cin >> textFileName;

    file.open(textFileName);

    // Incorrect filename or file is not in correct place
    if (!file.is_open())
    {
        cout << "Unable to open the file." << endl;
    }

    string line = "";


    // Appends vector with lines "data" from file
    while (getline(file, line)) {

        lines.push_back(line);
    }

    vector<Course> courses = {};

    // Outputs each line of the lines vector
    for (int i = 0; i < lines.size(); i++) {

        // Intitialize vector for tokenized courses
        vector<string> dataFields;

        stringstream stream(lines.at(i));

        // Create temporary variable to hold tokenized courses
        string temp;

        // Appends vector with courses
        while (getline(stream, temp, ',')) {
            dataFields.push_back(temp);
        }

        // Protects against courses not having a course name or number
        if (dataFields.size() < 2) {
            continue;
        }

       
        Course currentCourse(dataFields[0], dataFields[1]);

        // Covers the case where we have no preReqs, 1 preReqs or more preReqs
        for (int i = 2; i < dataFields.size(); i++) {
            currentCourse.addpreReq(dataFields[i]);
        }

        courses.push_back(currentCourse);
        cout << "Course has been successfully loaded: " << currentCourse.getName() << endl;
    }

    file.close();

    courses = mySort(courses);

    // Returning the vector that contains our Course objects
    return courses;

}

void printCourses(vector<Course> courses) {
    for (int i = 0; i < courses.size(); i++) {
        cout << courses[i].getNumber() << ", " << courses[i].getName() << endl;
    }
        
}

// Finds matching course number and prints out course data, otherwise will print out an error message
void printSingleCourse(vector<Course> courses) {

    cout << "What course do you want to know about?" << endl;
    string response;
    cin >> response;
    for (int i = 0; i < response.size(); i++) {
        response[i] = toupper(response[i]);
    }
    for (int i = 0; i < courses.size(); i++) {
        if (response == courses[i].getNumber()) {
            cout << courses[i].getNumber() << ", " << courses[i].getName() << endl;
            vector<string> preReqs = {};
            preReqs = courses[i].getpreReqs();
            if (preReqs.size() > 0) {
                cout << "Prerequisites: ";
            }
            
            for (int j = 0; j < preReqs.size(); j++) {
                cout << preReqs[j];
                if (j < preReqs.size() - 1) {
                    cout << ", ";
                }
                else {
                    cout << endl;
                }
            }
            return;
        }
    }
    cout << "Invalid course number" << endl;
}

// Prints menu options until user exits the program
void Menu() {

    cout << "Welcome to the Course Planner" << endl;

    // Created empty vector
    vector<Course> courseList = {};

    while (true) {

        int selection = 0;
        string selectionB;

        cout << "\t 1. Load Data Structure." << endl;
        cout << "\t 2. Print Course List." << endl;
        cout << "\t 3. Print Course." << endl;
        cout << "\t 9. Exit" << endl;
        cout << "What would you like to do?" << endl;

        cin >> selection;

        if (selection == 9) {
            break;
        }
        else if (selection == 1) {
            courseList = loadDataStructure();
        }
        else if (selection == 2) {
            printCourses(courseList);
        }
        else if (selection == 3) {
            printSingleCourse(courseList);
        }
        else {
            cout << selection << " is not a valid option." << endl;
        }

    }
};

int main() {

    Menu();
    
    return 0;

}

