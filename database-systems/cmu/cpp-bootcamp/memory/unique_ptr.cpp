// std::unique_ptr is a type of smart pointer that retains sole ownership of an
// object. This means that no two instances of std::unique_ptr can manage the
// same object.

#include <cstdint>
#include <cstdio>
#include <memory>

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

void set_x_to_445(std::unique_ptr<Point> &ptr) { ptr->set_x(445); }

int main(int argc, char **argv) {
    // initialization of an empty unique pointer of type
    std::unique_ptr<Point> pp_empty;
    // initialization of a unique pointer with different constructors
    std::unique_ptr<Point> ppc1 = std::make_unique<Point>(13, -73);
    std::unique_ptr<Point> ppc2 = std::make_unique<Point>();

    if (pp_empty) pp_empty->print();
    if (ppc1) ppc1->print();

    std::unique_ptr<Point> moved_ppc1 = std::move(ppc1);

    set_x_to_445(moved_ppc1);
    if (moved_ppc1) moved_ppc1->print();

    return 0;
}
