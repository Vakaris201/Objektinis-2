#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

template <typename T>
class Vector {
    public:
    // Member types
    using value_type = T;
    using allocator_type = std::allocator<T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Member functions
    Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {} //Default constructor

    explicit Vector(size_type count, const T& value = T()) //Constructor with count and default value: v(count, value)
        : data_(nullptr), size_(0), capacity_(0) { 
        if(count > 0) {
            data_ = allocate(count);
            capacity_ = count;
            for(size_type i = 0; i < count; i++) {
                construct_at(data_ + i, value);
            }
            size_ = count;
        }
    }

    Vector(std::initializer_list<T> list) //Constructor with in itializer list: v{a, b, c}
        : data_(nullptr), size_(0), capacity_(0) {
        data_ = allocate(list.size());
        capacity_ = list.size();
        for(auto i : list) {
            construct_at(data_ + size_++, i)
        }
    }

    Vector(const Vector& other) //Copy constructor
        : data_(nullptr), size_(0), capacity_(0) {
        copy_from(other);
    }

    Vector(Vector&& other) noexcept //Move constructor
        : data_(nullptr), size_(0), capacity_(0) {
        move_from(std::move(other));
    }

    template<class InputIt>
    Vector(InputIt first, InputIt last)  //Constructor with range: v(x.begin(), x.end())
        : data_(nullptr), size_(0), capacity_(0) {
        for(auto it = first; it != last; it++) {
            push_back(*it);
        }
    }
    ~Vector() { //Destructor
        clear();
        if(data_) deallocate(data_, capacity_);
    }
    Vector& operator=(const Vector& other); //Copy assignment operator: x = y
    Vector& operator=(Vector&& other) noexcept; //Move assignment operator: x = std::move(y)
    Vector& operator=(std::initializer_list<value_type> ilist); //Initializer list assignment operator: x = {a, b, c}

    void assign(size_type count, const T& value); //Assign new contents to the vector: v.assign(count, value)
    void assign(std::initializer_list<T> list); //Assign new contents from initializer list: v.assign{a, b, c}
    template <class InputIt> 
    void assign(InputIt first, InputIt last); //Assign new contents from range: v.assign(x.begin(), x.end())

    allocator_type get_allocator() const noexcept; //Get allocator

    // Element access
    reference at(size_type pos); //Access element with bounds checking: v.at(pos)
    const_reference at(size_type pos) const; //Access element with bounds checking: v.at

    reference operator[](size_type pos); //Access element without bounds checking: v[pos]
    const_reference operator[](size_type pos) const; //Access element without bounds checking: v[pos]

    reference front(); //Access first element: v.front()
    const_reference front() const; //Access first element: v.front()

    reference back(); //Access last element: v.back()
    const_reference back() const; //Access last element: v.back()

    // Iterators
    iterator begin() noexcept; //Return iterator to beginning: v.begin()
    const_iterator begin() const noexcept; //Return const iterator to beginning: v.begin()
    const_iterator cbegin() const noexcept; //Return const iterator to beginning: v.cbegin()

    iterator end() noexcept; //Return iterator to end: v.end()
    const_iterator end() const noexcept; //Return const iterator to end: v.end()
    const_iterator cend() const noexcept; //Return const iterator to end: v.cend()

    reverse_iterator rbegin() noexcept; //Return reverse iterator to beginning: v.rbegin()
    const_reverse_iterator rbegin() const noexcept; //Return const reverse iterator to beginning: v.rbegin()
    const_reverse_iterator crbegin() const noexcept; //Return const reverse iterator to beginning: v.crbegin()

    reverse_iterator rend() noexcept; //Return reverse iterator to end: v.rend()
    const_reverse_iterator rend() const noexcept; //Return const reverse iterator to end: v.rend()
    const_reverse_iterator crend() const noexcept; //Return const reverse iterator to end: v.crend()

    // Capacity
    bool empty() const noexcept; //Check if vector is empty: v.empty()
    size_type size() const noexcept; //Return number of elements: v.size()
    size_type max_size() const noexcept; //Return maximum number of elements: v.max_size()
    void reserve(size_type new_cap); //Request a change in capacity: v.reserve(new_cap)
    size_type capacity() const noexcept; //Return current capacity: v.capacity()
    void shrink_to_fit(); //Reduce capacity to fit size: v.shrink_to_fit()

    // Modifiers
    void clear() noexcept; //Clear contents: v.clear()

    iterator insert(const_iterator pos, const T& value); //Insert element before pos: v.insert(pos, value)
    iterator insert(const_iterator pos, T&& value); //Insert element before pos: v.insert(pos, std::move(value))
    iterator insert(const_iterator pos, size_type count, const T& value); //Insert count copies of value before pos: v.insert(pos, count, value)
    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last); //Insert elements from range [first, last) before pos: v.insert(pos, x.begin(), x.end())
    iterator insert(const_iterator pos, std::initializer_list<T> list); //Insert elements from initializer list before pos: v.insert(pos, {a, b, c})

    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args); //Construct element in-place before pos: v.emplace(pos, args...)

    iterator erase(const_iterator pos); //Erase element at pos: v.erase(pos)
    iterator erase(const_iterator first, const_iterator last); //Erase elements in range [first, last): v.erase(x.begin(), x.end())

    void push_back(const T& value); //Add element to end: v.push_back(value)
    void push_back(T&& value); //Add element to end: v.push_back(std::move(value))

    template <class... Args>
    void emplace_back(Args&&... args); //Construct element in-place at end: v.emplace_back(args...)

    void pop_back(); //Remove last element: v.pop_back()

    void resize(size_type count) { //Change size to count: v.resize(count)
        resize(count, value_type{});
    }
    void resize(size_type count, const value_type& value); //Change size to count and fill new elements with value: v.resize(count, value)

    void swap(Vector& other) noexcept; //Swap contents with another vector: v.swap(other)
    
    private:
    pointer data_ = nullptr; //Pointer to the underlying array
    size_type size_ = 0; //Number of elements in the vector
    size_type capacity_ = 0; //Capacity of the vector
    allocator_type allocator_; //Allocator for managing memory

    static constexpr size_type initial_capacity = 1; //Initial capacity for the vector

    pointer allocate(size_type n) { //Allocate memory for n elements
        return n ? std::allocator_traits<allocator_type>::allocate(allocator_, n) : nullptr;
    }

    void deallocate(pointer p, size_type n) noexcept { //Deallocate memory for n elements at pointer p
        if(p) std::allocator_traits<allocator_type>::deallocate(allocator_, p, n);
    }

    void reallocate(size_type new_capacity) { //Reallocate memory to new capacity
        pointer new_data = allocate(new_capacity);
        for(size_type i = 0; i < size_; i++) {
            construct_at(new_data + i, std::move(data_[i]));
            destroy_at(data_ + i);
        }
        deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = new_capacity;
    }
    void grow_if_needed() { //Grow the vector if size exceeds capacity
        if(size_ >= capacity_) {
            reallocate(capacity_ == 0 ? initial_capacity : capacity_ * 2);
        }
    }

    void construct_at(pointer p, const T& value) { //Construct element at pointer p with value
        std::allocator_traits<allocator_type>::construct(allocator_, p, value);
    }
    void construct_at(pointer p, T&& value) {
        std::allocator_traits<allocator_type>::construct(allocator_, p, std::move(value));
    }

    void destroy_at(pointer p) noexcept { //Destroy element at pointer p
        std::allocator_traits<allocator_type>::destroy(allocator_, p);
    }

    void move_from(Vector&& other) noexcept { //Move resources from another vector
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        allocator_ = std::move(other.allocator_);
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    void copy_from(const Vector& other) { //Copy resources from another vector
        if(other.size_ == 0) return;
        data_ = allocate(other.size_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        for(size_type i = 0; i < size_; i++) {
            construct_at(data_ + i, other.data_[i]);
        }
    }
};

// Non-member functions
template <typename T>
bool operator==(const Vector<T>& left, const Vector<T>& right) { //Equality comparison: v1 == v2
    if(left.size() != right.size()) return false;
    for(Vector<T>::size_type i = 0; i < left.size(); i++) {
        if(left[i] != right[i]) return false;
    }
    return true;
}

template <typename T>
bool operator!=(const Vector<T>& left, const Vector<T>& right) { //Inequality comparison: v1 != v2
    return !(left == right);
}

template <typename T>
bool operator<(const Vector<T>& left, const Vector<T>& right) { //Less-than comparison: v1 < v2
    return std::lexicographical_compare(
        left.begin(), left.end(),
        right.begin(), right.end());
}

template <typename T>
bool operator<=(const Vector<T>& left, const Vector<T>& right) { //Less-than or equal comparison: v1 <= v2
    return !(right < left);
}

template <typename T>
bool operator>(const Vector<T>& left, const Vector<T>& right) { //Greater-than comparison: v1 > v2
    return right < left;
}

template <typename T>
bool operator>=(const Vector<T>& left, const Vector<T>& right) { //Greater-than or equal comparison: v1 >= v2
    return !(left < right);
}

template <typename T>
void swap(Vector<T>& left, Vector<T>& right) noexcept { //Non-member swap: swap(left, right)
    left.swap(right);
}

#endif