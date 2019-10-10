template <typename T>
struct DQ {
     
    int left, right;
    T data[maxn * 2];
    
    DQ() : left(0), right(0) {}
     
    bool empty() const { return left == right; }
     
    const T& front() const { return data[left]; }
    const T& back() const { return data[right - 1]; }
     
    void pop_front() { ++left; }
    void push_back(T t) { data[right++] = t; }
    void pop_back() { --right; }
     
};
