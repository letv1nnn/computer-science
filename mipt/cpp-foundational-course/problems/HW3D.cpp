// C++ foundational course, MIPT, 2021-2022
/*
                        TASK HW3D
    You are given a set of points in three-dimensional space.
    Each three consecutive points define a triangle.
    Determine how many pairs of triangles intersect.
    
    compiling: g++ -DTEST_MODE -O2 HW3D.cpp -lgtest -lgtest_main -pthread
*/

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

template<typename T>
class Point {
private:
    T x_ = NAN, y_ = NAN, z_ = NAN;
public:
    Point() = default;
    Point(T x, T y, T z) : x_(x), y_(y), z_(z) {}
    ~Point() = default;

    const T x() const { return x_; }
    const T y() const { return y_; }
    const T z() const { return z_; }

    void print() const { std::cout << "X: " << x_ << ", Y: " << y_ << ", Z: " << z_; }
    bool valid() { return (std::isnan(x_) || std::isnan(y_) || std::isnan(z_)) == false; }

    Point<T> operator+(const Point<T> other) const { return {x_ + other.x_, y_ + other.y_, z_ + other.z_}; }
    Point<T> operator-(const Point<T> other) const { return {x_ - other.x_, y_ - other.y_, z_ - other.z_}; }

    // calculating dot product, given two points.
    static double inner_product(const Point<T>& pa, const Point<T>& pb) { return pa.x_ * pb.x_ + pa.y_ * pb.y_ + pa.z_ * pb.z_; }
    // calculating normal to the plane. n = (B - A) * (C - A)
    static Point<T> cross(const Point<T>& pa, const Point<T>& pb) { return {pa.y_ * pb.z_ - pa.z_ * pb.y_, pa.z_ * pb.x_ - pa.x_ * pb.z_, pa.x_ * pb.y_ - pa.y_ * pb.x_}; }
};

template<typename T>
class Triangle {
private:
    Point<T>& a_, b_, c_;
public:
    Triangle() = default;
    Triangle(Point<T>& a, Point<T>& b, Point<T>& c) : a_(a), b_(b), c_(c) {}
    ~Triangle() = default;

    void print() const {
        std::cout << "A - ("; a_.print();
        std::cout << "), B - ("; b_.print();
        std::cout << "), C - ("; c_.print();
        std::cout << ")\n";
    }
    bool valid() const { return a_.valid() && b_.valid() && c_.valid(); };

    static bool collide(Triangle<T> t1, Triangle<T> t2) {
        const double EPS = 1e-9;

        // finding the normal to the plain of the first triangle
        Point<T> n1 = Point<T>::cross(t1.b_ - t1.a_, t1.c_ - t1.a_);

        double d1 = signed_distance(n1, t1.a_, t2.a_);
        double d2 = signed_distance(n1, t1.a_, t2.b_);
        double d3 = signed_distance(n1, t1.a_, t2.c_);

        if ((d1 > EPS && d2 > EPS && d3 > EPS) ||
            (d1 < -EPS && d2 < -EPS && d3 < -EPS))
            return false;

        // finding the normal to the plain of the second triangle
        Point<T> n2 = Point<T>::cross(t2.b_ - t2.a_, t2.c_ - t2.a_);

        double e1 = signed_distance(n2, t2.a_, t1.a_);
        double e2 = signed_distance(n2, t2.a_, t1.b_);
        double e3 = signed_distance(n2, t2.a_, t1.c_);

        if ((e1 > EPS && e2 > EPS && e3 > EPS) ||
            (e1 < -EPS && e2 < -EPS && e3 < -EPS))
            return false;
        
        return true;
    }
};

template<typename T>
std::vector<Point<T>> get_input(int argc, char **argv);
template<typename T>
double signed_distance(const Point<T>& normal, const Point<T>& plane_point, const Point<T>& p);

int main(int argc, char **argv) {
#ifndef TEST_MODE
    std::vector<Point<double>> points = get_input<double>(argc, argv);
    std::size_t N = points.size() / 3;
    std::vector<Triangle<double>> triangles;
    triangles.reserve(N);
    for (unsigned i = 0; i < points.size(); i += 3)
        triangles.emplace_back(points[i], points[i + 1], points[i + 2]);

    unsigned collisions = 0;
    for (unsigned i = 0; i < triangles.size(); ++i) {
        for (unsigned j = i + 1; j < triangles.size(); ++j) {
            if (Triangle<double>::collide(triangles[i], triangles[j]))
                collisions++;
        }
    }
    std::cout << "Collisions: " << collisions << ".\n";
    return 0;
#else    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}

template<typename T>
double signed_distance(
    const Point<T>& normal,
    const Point<T>& plane_point,
    const Point<T>& p
) {
    return Point<T>::inner_product(normal, p - plane_point);
}

template<typename T>
std::vector<Point<T>> get_input(int argc, char **argv) {
    std::size_t N;
    std::vector<Point<T>> points;
    if (argc > 1) {
        N = atoi(argv[1]);
        if (N % 3 != 0) {
            std::cerr << "N must be multiple of 3!";
        } else if ((argc - 2) / 3 == N) {
            points.resize(N);
            for (unsigned i = 0; i < N; i += 3)
                points[i] = Point<T>(atof(argv[i + 2]), atof(argv[i + 3]), atof(argv[i + 4]));
            return points;
        }
    } else {
        while (N % 3 != 0) {
            std::cout << "N: ";
            std::cin >> N;
        }
    }
    std::cout << "Enter " << N << " 3D points:\n";
    points.resize(N);
    T x, y, z;
    for (unsigned i = 0; i < N; ++i) {
        std::cout << i + 1 << ": ";
        std::cin >> x >> y >> z;
        points[i] = Point<T>(x, y, z);
    }
    return points;
}

TEST(PointTest, Subtraction) {
    Point<double> a(3, 2, 1);
    Point<double> b(1, 1, 1);

    Point<double> c = a - b;
    
    EXPECT_DOUBLE_EQ(c.x(), 2);
    EXPECT_DOUBLE_EQ(c.y(), 1);
    EXPECT_DOUBLE_EQ(c.z(), 0);
}

TEST(PointTest, InnerProduct) {
    Point<double> a(1, 0, 0);
    Point<double> b(0, 1, 0);

    double dot_product = Point<double>::inner_product(a, b);
    EXPECT_DOUBLE_EQ(dot_product, 0.f);
}

TEST(PointTest, CrossProduct) {
    Point<double> a(1, 0, 0);
    Point<double> b(0, 1, 0);

    Point<double> c = Point<double>::cross(a, b);

    EXPECT_DOUBLE_EQ(c.x(), 0);
    EXPECT_DOUBLE_EQ(c.y(), 0);
    EXPECT_DOUBLE_EQ(c.z(), 1);
}

TEST(TriangleTest, NoCollisionSeparatedByPlane) {
    Point<double> a1(0, 0, 0);
    Point<double> b1(1, 0, 0);
    Point<double> c1(0, 1, 0);

    Point<double> a2(0, 0, 5);
    Point<double> b2(1, 0, 5);
    Point<double> c2(0, 1, 5);

    Triangle<double> t1(a1, b1, c1);
    Triangle<double> t2(a2, b2, c2);

    EXPECT_FALSE(Triangle<double>::collide(t1, t2));
}

TEST(TriangleTest, Collision) {
    Point<double> a1(0, 0, 0);
    Point<double> b1(2, 0, 0);
    Point<double> c1(0, 2, 0);

    Point<double> a2(0.5, 0.5, -1);
    Point<double> b2(0.5, 0.5,  1);
    Point<double> c2(2,   2,   1);

    Triangle<double> t1(a1, b1, c1);
    Triangle<double> t2(a2, b2, c2);

    EXPECT_TRUE(Triangle<double>::collide(t1, t2));
}

