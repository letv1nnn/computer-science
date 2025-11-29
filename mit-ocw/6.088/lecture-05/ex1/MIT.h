#pragma once

#include <string>
#include <iostream>
#include <vector>

class MITClass {
    std::string class_;
public:
    MITClass(std::string cl);
    
    std::string getName();
};

class MITPerson {
protected:
    int id_;
    std::string name_;
    std::string address_;
public:
    MITPerson(int id, std::string name, std::string address);
    virtual ~MITPerson();

    virtual void displayProfile();
    void changeAddress(std::string newAddress);
};

class Student : public MITPerson {
    int course_;
    int year_;
    std::vector<MITClass *> classesTaken_;
public:
    Student(int id, std::string name, std::string address, int course, int year);
    ~Student();

    void displayProfile();
    void addClassTaken(MITClass *newClass);
    void changeCourse(int newCourse);
};

