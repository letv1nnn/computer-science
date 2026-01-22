// C++ foundational course, MIPT, 2021-2022
// compile with: g++ drilldown.cpp -lgtest -lgtest_main -pthread

#include <gtest/gtest.h>

template <typename T> class scoped_ptr {
private:
    T *ptr_;
public:
    scoped_ptr(T *ptr) : ptr_{ptr} {}
    ~scoped_ptr() { delete ptr_; }
    scoped_ptr(const scoped_ptr &other) : ptr_{other.ptr_} {}
    T *operator->() { return ptr_; }
    const T *operator->() const { return ptr_; }
    T &operator*() { return *ptr_; }
    const T &operator*() const { return *ptr_; }
};

struct X { int a, b; };

TEST(PointerTest, AllTests) {
    scoped_ptr<X> pt{new X{}};
    EXPECT_EQ(pt->a, 0);
    EXPECT_EQ(pt->b++, 0);
    EXPECT_EQ(pt->b++, 1);
    EXPECT_EQ((*pt).b, 2);

    const scoped_ptr<X> ptc{new X{{}, 13}};
    EXPECT_EQ(ptc->b, 13);
    EXPECT_EQ(ptc->a, int{});
}
