#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{

    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;
    // Open a file as a input stream.
    ifstream stfile("./Students.txt");
    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));

                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);


        studentVec.push_back(st);

    }

    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?


    ifstream clfile("./Classes.txt");
    int classFlag = 0;
    bufv.clear();
    while(getline(clfile, line)) {

        if (line.empty()) // It's an empty line.
        {
            classFlag = 1 ;
            continue;
        }
        if (line[0] == '#') // It's a comment line.
        {
            classFlag = 1;
            continue;
        }

        if(classFlag == 1)
        {
            pos1 = 6;
            bufv.push_back(line.substr(pos1, string::npos));
//            cout << line.substr(pos1, string::npos) << endl;
            classFlag ++;
            continue;
        }

        if(classFlag == 2)
        {
            pos1 = 7;
            bufv.push_back(line.substr(pos1, string::npos));
            cl = new Class(bufv[0], stoi(bufv[1]));
//            cout << cl->name <<" " << cl->point <<endl;
            classVec.push_back(cl);
            classFlag ++;
            bufv.clear();
            continue;
        }

        for (vector<Student *>::iterator it = studentVec.begin();
             it != studentVec.end();
             it ++)
        {

            if((*it)->id == line)
            {
                classVec.back()->addStudent(*(*it));
                (*it)->addClass(classVec.back());
            }
        }




    }
    clfile.close();

}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printAvgScore().


    string sbuf;
    Class *cl;

    double studentScore;


    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        while (true){
        cout << "Please input the student id (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;



        try {
            StudentWrapper *st = &(cl->getStudentWrapper(sbuf));
        } catch (...) {
            cout << "No match student!" << endl;
            continue;
        }

        for (vector<Student *>::iterator it = studentVec.begin();
             it != studentVec.end();
             it ++)
        {
            if((*it)->id == sbuf)
            cout << (*it)->toString();
        }

        string subv;
        cout << "Please input the score: ";
        cin >> subv;
        if (subv == "q")
            continue;

        try {
            studentScore = stof(subv);
        } catch (...) {
            cout << "Wrong score!" << endl;
            continue;
        }


        if (studentScore > 100 || studentScore < 0)
            { cout << "Wrong score!" << endl;
               continue;
            }

        cl->getStudentWrapper(sbuf).setScore(studentScore);

        }
    }

}

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        cout << "The average score is: ";
        printf("%.2f\n", avg);
    }
}

void AppX::printGpa()
{
    // TODO: implement printGpa.
    // Hint: Take a look at printAvgScore().
    string id;
    Student *student;
    double gpa;

    while (true) {
        cout << "Please input the student id (or input q to quit):";
        cin >> id;
        if (id == "q")
            break;

        student = nullptr;
        for (vector<Student *>::iterator it = studentVec.begin();
             it != studentVec.end();
             ++it) {
            if ((*it)->id == id) {
                student = *it;
                break;
            }
        }
        if (student == nullptr) {
            cout << "No match student!" << endl;
            continue;
        }

        gpa = student->getGrade();
        cout << student->toString();

        printf("GPA = %.2f\n", gpa);
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
