// std::shared_ptr is a type of smart pointer that retains shared ownership of
// an object through a pointer. This means that multiple shared pointers can
// own the same object, and shared pointers can be copied.

#include <cstdint>
#include <cstdio>
#include <memory>
#include <iostream>

class Point {
private:
    int64_t x_, y_;
public:
    Point() : x_{}, y_{} {}; 
    Point(int64_t x, int64_t y) : x_(x), y_(y) {}
    Point(const Point &point) : x_(point.x_), y_(point.y_) {}
    Point &operator=(const Point &point) { 
        x_ = point.x_; y_ = point.y_; 
        return *this;
    }
public:
    inline const int x() const { return x_; }
    inline const int y() const { return y_; } 
    inline void set_x(int64_t x) { x_ = x; }
    inline void set_y(int64_t y) { y_ = y; }
    inline void print() { std::printf("Point { x: %d, y: %d }\n", (int)x_, (int)y_); }
};

void modify_ptr_via_ref(std::shared_ptr<Point> &point) { point->set_x(77); }
void modify_ptr_via_rvalue_ref(std::shared_ptr<Point> &&point) { point->set_y(33); }
void copy_shared_ptr_in_function(std::shared_ptr<Point> point) { std::cout << "Reference count: " << point.use_count() << '\n'; }

int main(int argc, char **argv) {
    // empty pointer
    std::shared_ptr<Point> ep;
    // with constructor
    std::shared_ptr<Point> spp1 = std::make_shared<Point>();
    std::shared_ptr<Point> spp2 = std::make_shared<Point>(1, 1);

    std::cout << "spp1 " << (spp1 ? "not empty" : "empty") << '\n';
    std::cout << "spp2 reference count: " << spp2.use_count() << '\n';
    {
        std::shared_ptr<Point> spp3 = spp2;
        std::cout << "spp2 reference count: " << spp2.use_count() << '\n';
    }
    std::cout << "spp2 reference count: " << spp2.use_count() << '\n';

    std::shared_ptr<Point> spp4 = std::move(spp2);
    std::cout << "spp2 reference count: " << spp4.use_count() << '\n';
    
    // applying defined functions on shared pointers
    modify_ptr_via_ref(spp4);
    std::cout << "spp4 reference count: " << spp4.use_count() << '\n';

    modify_ptr_via_rvalue_ref(std::move(spp4));
    std::cout << "spp4 reference count: " << spp4.use_count() << '\n';

    copy_shared_ptr_in_function(spp4);
    std::cout << "spp4 reference count: " << spp4.use_count() << '\n';

    return 0;
}
