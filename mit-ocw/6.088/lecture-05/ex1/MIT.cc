#include "MIT.h"

MITClass::MITClass(std::string cl)
    : class_(cl) {}

std::string MITClass::getName() {
    return class_;
}

MITPerson::MITPerson(int id, std::string name, std::string address)
    : id_(id), name_(name), address_(address) {}

MITPerson::~MITPerson() {}

void MITPerson::displayProfile() {
    std::cout << "Name: " << name_ << ", ID: " << id_ << ", Address: " << address_ << '\n';
}

void MITPerson::changeAddress(std::string newAddress) {
    address_ = newAddress;
}

Student::Student(int id, std::string name, std::string address, int course, int year)
    : MITPerson(id, name, address), course_(course), year_(year) {}

Student::~Student() {
    for(int i = 0; i < classesTaken_.size(); ++i) {
        delete classesTaken_[i];
    }
}

void Student::displayProfile() {
    std::cout << "Name: " << name_ << ", ID: " << id_ << ", Address: " << address_ << '\n';
    std::cout << "Course: " << course_ << '\n';
    std::vector<MITClass *>::iterator it;
    std::cout << "Classes taken:\n";
    for (it = classesTaken_.begin(); it != classesTaken_.end(); it++) {
        MITClass *c = *it;
        std::cout << c->getName() << '\n';
    }
}

void Student::addClassTaken(MITClass *newClass) {
    classesTaken_.push_back(newClass);
}

void Student::changeCourse(int newCourse) {
    course_ = newCourse;
}

