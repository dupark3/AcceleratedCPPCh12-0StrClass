#ifndef GUARD_Vec_H
#define GUARD_Vec_H

#include <cstddef> // size_t
#include <memory>


template <class T>
class Vec {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;

    Vec() { create(); }  // default constructor
    explicit Vec(size_t n, const T& val = T()) { create(n, val); } // argument constructor
    Vec(const Vec& v) { create(v.begin(), v.end()); } // copy constructor
    ~Vec() { uncreate(); } // destructor

    Vec& operator=(const Vec&);
    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }

    size() const { return avail - data; }
    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    void push_back(const T& val) {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }

    void erase(iterator it){
        while (it != (avail - 1)){
            *it = *(it + 1);
            ++it;
        }
        alloc.destroy(it);
        --avail;
    }

    void clear(){
        if (data){
            iterator it = avail;
            while (it != data)
                alloc.destroy(--it);
        }
        avail = data;
    }

private:
    iterator data; // points to the first element
    iterator avail; // points to one past the last element
    iterator limit; // points to one past the last allocated element when grow() allocates twice the memory

    // facilities for memory allocation
    std::allocator<T> alloc; // object to handle memeory allocation

    // allocate and initialize the underlying array
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    // destroy the elements in the array and free the memery
    void uncreate();

    // support functions for push_back
    void grow();
    void unchecked_append(const T&);
};


template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs){
    if (&rhs != this ) {
        // frees the array in the lhs (this)
        uncreate();

        // copies elements from the rhs to the lhs
        create(rhs.begin(), rhs.end());
    }

    return *this;
}

template <class T>
void Vec<T>::create(){
    data = avail = limit = 0;
}

template <class T>
void Vec<T>::create(size_t n, const T& val){
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator first, const_iterator end){
    data = alloc.allocate(end - first);
    limit = avail = std::uninitialized_copy(first, end, data);
}

template <class T>
void Vec<T>::uncreate(){
    if (data){
        // destroy (in reverse order) the elements that were constructed
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);

        // return all the sapce that was allocated
        alloc.deallocate(data, limit - data);
    }
    // reset pointed to indicate that the Vec is empty again
    data = avail = limit = 0;
}

template <class T>
void Vec<T>::grow(){
    // grow twice as much as space currently in use, or if empty, by one
    size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

    // allocate new space and copy existing elements to the new space
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    // return old space
    uncreate();

// reset pointers to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

// assumes avail points to allocated, uninitialized space, since grow is called if this is not true
template <class T>
void Vec<T>::unchecked_append(const T& val){
    alloc.construct(avail++, val);
}

#endif

