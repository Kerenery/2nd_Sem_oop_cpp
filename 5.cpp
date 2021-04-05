#include <iostream>
#include <iterator>

using namespace std;

template <class T>
class Circular_buffer {
private:
    size_t head = 0;
    size_t tail = 0;
    size_t capacity;
    T* buffer = nullptr;
    size_t current_size = 0;
public:
    class ITERATOR : public iterator<random_access_iterator_tag, T> {
    private:
        T* pointer = nullptr;
    public:
        ITERATOR() : pointer(nullptr){}
        ITERATOR(T* p) : pointer(p) {}
        ITERATOR& operator++() {
            ++pointer;
            return *this;
        }
        ITERATOR operator++(T) { 
            ITERATOR tmp(*this); 
            operator++(); 
            return tmp; 
        }
        T& operator*() { 
            return *pointer; 
        }
        ITERATOR& operator+=(T value) {
            pointer += value;
            return *this;
        }
        ITERATOR& operator-=(T value) {
            pointer -= value;
            return *this;
        }
        ITERATOR& operator--() {
            pointer--;
            return *this;
        }

        ITERATOR operator + (T value) { 
            return ITERATOR(pointer + value); 
        }
        ITERATOR operator - (T value) {
            return ITERATOR(pointer - value);
        }
        //nice
        T& operator*() const {
            return *pointer; 
        }
        T* operator->() const { 
            return pointer; 
        }
        T& operator[](T value) {
            return pointer[value];
        }
        //ok
        bool operator == (const ITERATOR& value) const {
            return value.pointer == this->pointer; 
        }
        bool operator != (const ITERATOR& value) const{ 
            return value.pointer = this->pointer; 
        }
        bool operator < (const ITERATOR& value) const { 
            return value.pointer < this->pointer; 
        }
        bool operator > (const ITERATOR& value) const { 
            return value.pointer > this->pointer; 
        }
        bool operator >= (const ITERATOR& value) const {
            return value.pointer >= this->pointer; 
        }
        bool operator <= (const ITERATOR& value) const { 
            return this->pointer <= value.pointer;
        }

    };
    Circular_buffer<T>(size_t capacity) {
        this->capacity = capacity;
        buffer = new T[capacity];
    }
    ITERATOR begin() const {
        return ITERATOR(buffer + head);
    }

    ITERATOR end() const {
        return ITERATOR(buffer + tail);
    }
    void push_back(T value)
    {
        if (tail >= capacity) {
            tail = capacity - 1;
        }
        buffer[tail] = value;
        if (tail != capacity - 1) {
            tail++;
        }
    }

    void pop_back()
    {
        buffer[tail] = 0;
        tail--;
    }

    void push_front(T value)
    {
        if (tail == capacity) {
            buffer[head] = value;
            return;
        }
        for (size_t i = tail; i >= head; i--) {
            buffer[i + 1] = buffer[i];
        }
        buffer[head] = value;
        tail++;
    }

    void pop_front()
    {
        buffer[head] = 0;
        head++;
    }
    void print_inf(Circular_buffer v) {
        cout << "Capacity: " << capacity << endl;
        for (ITERATOR it = begin(); it <= end(); it++) {
            cout << *it << ' ';
        }
        cout << endl;
        cout << buffer[1];
    }
};


int main()
{
    Circular_buffer<int> v(3);
    v.push_back(38);
    v.push_back(32);
    v.push_back(51); 
    v.print_inf(v);
    
    return 0;
}
