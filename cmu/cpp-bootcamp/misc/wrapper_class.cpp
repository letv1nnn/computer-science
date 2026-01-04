#include <gtest/gtest.h>
#include <utility>

template <typename T> class smart_ptr {
private:
    T *ptr_;
public:
    smart_ptr() : ptr_(nullptr) {}
    smart_ptr(T &&val) : ptr_(&std::move(val)) {}
    smart_ptr(T *val) : ptr_(val) {}
    smart_ptr(smart_ptr &&ptr) : ptr_(std::move(ptr)) {}
    ~smart_ptr() { delete ptr_; }
    
    smart_ptr(const smart_ptr &) = delete;
    T &operator=(const smart_ptr &) = delete;

    T &operator=(smart_ptr &&other) {
        ptr_(other.ptr_);
        other.ptr_ = nullptr;
        return *this;
    }
    T *operator->() { return ptr_; }
    const T *operator->() const { return ptr_; }
    T operator*() { return *ptr_; }
    const T operator*() const { return *ptr_; }
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

struct Entity { int a; };

TEST(SmartPtrTest, MainTest) {
    EXPECT_EQ(sizeof(Entity), 4); 
    Entity *e = new Entity{};
    smart_ptr<Entity> sp(e);
    EXPECT_EQ(sp->a, 0); 
}
