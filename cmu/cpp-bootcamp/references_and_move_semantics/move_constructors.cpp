#include <iostream>
#include <utility>
#include <string>
#include <cstdint>
#include <vector>

class Person {
private:
    uint8_t age_;
    std::vector<std::string> nicknames_;
    bool valid_;
public:
    Person() : age_(uint8_t{}), nicknames_({}), valid_(true) {}
    // takes rvalue reference to not copy the whole vector
    Person(uint8_t age, std::vector<std::string> &&nicknames)
        : age_{age}, nicknames_(std::move(nicknames)), valid_(true) {}
    Person(Person &&other) : age_(other.age_), nicknames_(std::move(other.nicknames_)), valid_(true) {
        std::cout << "Calling the move cpnstructor for class Person.\n";
        other.valid_ = false;
    }
    // move  assignment operator for class Person
    Person &operator=(Person &&other) {
        age_ = other.age_;
        nicknames_ = std::move(other.nicknames_);
        valid_ = true;
        other.valid_ = false;
        return *this;
    }
    // we delete the copy constructor and the copy assignment operator,
    // so this class cannot be copy-constructed
    Person(const Person &) = delete;
    Person &operator=(const Person &) = delete;

    uint8_t get_age() { return age_; }
    const uint8_t get_age() const { return age_; }

    std::string get_nickname_at(const size_t idx) { return nicknames_[idx]; }
    const std::string get_nickname_at(const size_t idx) const { return nicknames_[idx]; }

    void print_is_valid() {
        if (valid_) std::cout << "object is valid.\n";
        else std::cout << "object is not valid!\n";
    }
};

int main(int argc, char **argv) {

    Person andy(18, {"andy", "pavlo"});
    std::cout << "Andy's validity: "; andy.print_is_valid();

    Person andy1(std::move(andy));
    std::cout << "Andy1's validity: "; andy1.print_is_valid();
    std::cout << "Andy's validity: "; andy.print_is_valid();

    return 0;
}

