#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename predicate>
bool all_of(const T& first, const T& last, predicate pred)
{
    for(T it = first; it != last; ++it){
        if (!pred(*it)) return false;
    }
    return true;
}

template <typename T, typename predicate>
bool any_of(const T& first, const T& last, predicate pred)
{
    for (T it = first; it != last; ++it) {
        if (pred(*it)) return true;
    }
    return false;
}

template <typename T, typename predicate>
bool none_of(const T& first, const T& last, predicate pred)
{
    for (T it = first; it != last; ++it) {
        if (pred(*it)) return false;
    }
    return true;
}

template <typename T, typename predicate>
bool one_of(const T& first, const T& last, predicate pred)
{
    for (T it = first; it != last; ++it) {
        if (pred(*it)) return true;
    }
    return false;
}
template <typename T, typename predicate>
bool is_sorted(const T& first, const T& last, predicate pred)
{
    for (T it = first; it != last; ++it) {
        if (pred(*it, *(it - 1)))     
            return false;
    }
    return true;
}

template <typename T, typename predicate>
bool is_partitioned(T& first, T& last, predicate pred)
{
    while (first != last && pred(*first)) {
        ++first;
    }
    while (first != last) {
        if (pred(*first)) return false;
        ++first;
    }   
    return true;
}

template <typename T, typename Element>
Element find_not(const T& first, const T& last, Element elem) {
    for (T it = first; it != last; ++it) {
        if (*it != elem) {
            return *it;
        }
    }
    return elem;
}

template <typename T, typename Element>
Element find_backward(const T& first,const T& last, Element elem) {
    for (T it = last - 1; it != first; --it) {
        if (elem == *it) {
            return *it;
        }
    }
    return elem;
}

template <typename T, typename predicate>
bool is_palindrome(const T& first,const T& last, predicate pred)
{
    T start, finish;
    for (start = first, finish = last - 1; start != last && finish != first; start++, finish--) {
        if (*start != *finish) {
            return false;
        }
    }
    return true;
}

template <typename N>
bool bigger_then_seven(N x) {
    return x > 7;
};

template <typename N>
bool compare(N x, N y) {
    if (y > x) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    vector <int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    if (all_of(v.begin(), v.end(), bigger_then_seven<int>)) {
        cout << "True";
    }
    else {
        cout << "False";
    }
    return 0;
}