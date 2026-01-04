template <typename T> struct Node {
    Node *next_, prev_;
    T value_;
    Node(T value) : value_(value), next_(nullptr), prev_(nullptr) {}
};

template <typename T> class dll_iterator {
private:
    Node<T> *curr_;
public:
    dll_iterator(Node<T> *head) : curr_(head) {}
    dll_iterator &operator++() {
        curr_ = curr_->next_;
        return *this;
    }
    dll_iterator &operator++(int) {
        dll_iterator temp = *this;
        ++*this;
        return temp;
    }
    bool operator==(const dll_iterator &other) const { return other.curr_ == curr_; }
    bool operator!=(const dll_iterator &other) const { return other.curr_ != curr_; }
    T operator*() const { return *curr_; } 
    
};

