// C++ foundational course, MIPT, 2021-2022

#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class Point2D {
    T x_, y_;
public:
    Point2D(T x = NAN, T y = NAN) : x_(x), y_(y) {}
    bool valid() const { return (std::isnan(x_) || std::isnan(y_)) == 0; }
    const T x() const { return x_; }
    const T y() const { return y_; }
    void print() const { std::cout << "X: " << x_ << " Y: " << y_; }

    friend std::istream& operator>>(std::istream& in, Point2D& p) {
        return in >> p.x_ >> p.y_;
    }
};

template <typename T, typename C, typename K>
class Triangle2D {
    Point2D<T> p1_;
    Point2D<C> p2_;
    Point2D<K> p3_;
public:
    Triangle2D(Point2D<T> p1, Point2D<C> p2, Point2D<K> p3) : p1_(p1), p2_(p2), p3_(p3) {}
    
    Point2D<T> p1() const { return p1_; }
    Point2D<C> p2() const { return p2_; }
    Point2D<K> p3() const { return p3_; }

    static std::vector<Triangle2D<T, C, K>> get_input(int argc, char **argv) {
        if (argc < 1) {
            std::cerr << "Not enough arguments!\nUsage: <binary> <number of triangles> <points>";
        }
        std::size_t size = atoi(argv[1]);
        std::vector<Triangle2D<T, C, K>> triangles(size);
        for (int i{}; i < size; ++i) {
            Point2D<T> p1(atoi(argv[i * 3 + i + 1]));
            Point2D<C> p2(atoi(argv[i * 3 + i + 2]));
            Point2D<K> p3(atoi(argv[i * 3 + i + 3]));
            triangles[i] = Triangle2D<Point2D<T>, Point2D<C>, Point2D<K>>(p1, p2, p3);
        }
        return triangles;
    }
    static std::vector<Triangle2D<T, C, K>> get_input() {
        std::size_t size;
        std::cout << "Enter the number of triangles: ";
        std::cin >> size;

        std::vector<Triangle2D> triangles;
        triangles.reserve(size);

        for (std::size_t i = 0; i < size; ++i) {
            std::cout << "Enter 3 points (x y):\n";
            Point2D<T> p1;
            Point2D<C> p2;
            Point2D<K> p3;

            std::cin >> p1 >> p2 >> p3;
            triangles.emplace_back(p1, p2, p3);
        }
        return triangles;
    }
    const void print() const {
        std::cout << "Triangle ("; p1_.print();
        std::cout << ", "; p2_.print();
        std::cout << ", "; p3_.print();
        std::cout << ").\n";
    }
    static bool collission(const Triangle2D<T, C, K>& t1, const Triangle2D<T, C, K>& t2) {
        if (!t1.p1().valid() || !t1.p2().valid() || !t1.p3().valid() ||
            !t2.p1().valid() || !t2.p2().valid() || !t2.p3().valid()) {
            std::cerr << "Points are not valid!\n";
            return false;
        } 
        return false;
    }
};

int main(int argc, char **argv) {
    auto triangles = Triangle2D<int, int, int>::get_input();
#ifdef DEBUG
    for (int i{}; i < triangles.size(); ++i)
       triangles[i].print(); 
#endif
    
    return 0;
}
