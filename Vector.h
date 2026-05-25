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
            size_ = count;
            capacity_ = count;
            for(size_type i = 0; i < count; i++) {
                construct_at(data_ + i, value);
            }
        }
    }

    Vector(std::initializer_list<T> list) //Constructor with in itializer list: v{a, b, c}
        : data_(nullptr), size_(0), capacity_(0) {
        data_ = allocate(list.size());
        capacity_ = list.size();
        for(const T& val : list) {
            construct_at(data_ + size_, val);
            size_++;
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

    Vector& operator=(const Vector& other) { //Copy assignment operator: x = y
        if(this == &other) return *this;
        clear();
        deallocate(data_, capacity_);
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        copy_from(other);
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept { //Move assignment operator: x = std::move(y)
        if(this == &other) return *this;
        clear();
        deallocate(data_, capacity_);
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        move_from(std::move(other));
        return *this;
    }
    Vector& operator=(std::initializer_list<value_type> list) { //Initializer list assignment operator: x = {a, b, c}
        clear();
        deallocate(data_, capacity_);
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        data_ = allocate(list.size());
        capacity_ = list.size();
        for(const auto& val : list) {
            construct_at(data_ + size_, val);
            size_++;
        }
        return *this;
    }
    void assign(size_type count, const T& value) { //Assign new contents to the vector: v.assign(count, value)
        clear();
        if(count > capacity_) {
            deallocate(data_, capacity_);
            data_ = allocate(count);
            capacity_ = count;
        }
        for(size_type i = 0; i < count; i++) {
            construct_at(data_ + i, value);
        }
        size_ = count;
    }
    void assign(std::initializer_list<T> list) { //Assign new contents from initializer list: v.assign{a, b, c}
        assign(list.begin(), list.end());
    }
    template <class InputIt> 
    void assign(InputIt first, InputIt last) { //Assign new contents from range: v.assign(x.begin(), x.end())
        clear();
        for(auto it = first; it != last; it++) {
            push_back(*it);
        }
    }

    allocator_type get_allocator() const noexcept {return allocator_;} //Get allocator

    // Element access
    reference at(size_type pos) { //Access element with bounds checking: v.at(pos)
        if(pos >= size_) {
            throw std::out_of_range("Vector::indeksas uz ribu");
        }
        return data_[pos];
    }

    const_reference at(size_type pos) const { //Access element with bounds checking: v.at(pos)
        if(pos >= size_) {
            throw std::out_of_range("Vector::at - indeksas uz ribu");
        }
        return data_[pos];
    }

    reference operator[](size_type pos) {return data_[pos];} //Access element without bounds checking: v[pos]
    const_reference operator[](size_type pos) const {return data_[pos];} //Access element without bounds checking: v[pos]

    reference front() {return data_[0];} //Access first element: v.front()
    const_reference front() const {return data_[0];} //Access first element: v.front()

    reference back() {return data_[size_ - 1];} //Access last element: v.back()
    const_reference back() const {return data_[size_ - 1];} //Access last element: v.back()

    pointer data() noexcept {return data_;}
    const_pointer data() const noexcept {return data_;}

    // Iterators
    iterator begin() noexcept {return data_;} //Return iterator to beginning: v.begin()
    const_iterator begin() const noexcept {return data_;} //Return const iterator to beginning: v.begin()
    const_iterator cbegin() const noexcept {return data_;} //Return const iterator to beginning: v.cbegin()

    iterator end() noexcept {return data_ + size_;} //Return iterator to end: v.end()
    const_iterator end() const noexcept {return data_ + size_;} //Return const iterator to end: v.end()
    const_iterator cend() const noexcept {return data_ + size_;} //Return const iterator to end: v.cend()

    reverse_iterator rbegin() noexcept {return reverse_iterator(end());} //Return reverse iterator to beginning: v.rbegin()
    const_reverse_iterator rbegin() const noexcept {return reverse_iterator(end());}//Return const reverse iterator to beginning: v.rbegin()
    const_reverse_iterator crbegin() const noexcept {return reverse_iterator(end());} //Return const reverse iterator to beginning: v.crbegin()

    reverse_iterator rend() noexcept {return reverse_iterator(begin());} //Return reverse iterator to end: v.rend()
    const_reverse_iterator rend() const noexcept {return reverse_iterator(begin());} //Return const reverse iterator to end: v.rend()
    const_reverse_iterator crend() const noexcept {return reverse_iterator(begin());} //Return const reverse iterator to end: v.crend()

    // Capacity
    bool empty() const noexcept {return size_ == 0;} //Check if vector is empty: v.empty()

    size_type size() const noexcept {return size_;} //Return number of elements: v.size()

    size_type max_size() const noexcept { //Return maximum number of elements: v.max_size()
        return std::allocator_traits<allocator_type>::max_size(allocator_);
    }

    void reserve(size_type new_cap) { //Request a change in capacity: v.reserve(new_cap)
        if(new_cap <= capacity_) return;
        if(new_cap >= max_size()) {
            throw std::length_error("Vector::reserve - per didelis dydis")
        }
        reallocate(new_cap);
    }
    size_type capacity() const noexcept {return capacity_;} //Return current capacity: v.capacity()

    void shrink_to_fit() { //Reduce capacity to fit size: v.shrink_to_fit()
        if(size_ < capacity_) {
            reallocate(size_);
        }
    }

    // Modifiers
    void clear() noexcept { //Clear contents: v.clear()
        for(size_type i = 0; i < size_; i++) {
            destroy_at(data_ + i);
        }
        size_ = 0;
    }

    iterator insert(const_iterator pos, const T& value) {//Insert element before pos: v.insert(pos, value)
        return emplace(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) { //Insert element before pos: v.insert(pos, std::move(value))
        return emplace(pos, std::move(value));
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {//Insert count copies of value before pos: v.insert(pos, count, value)
        if(count == 0) return const_cast<iterator>(pos);
        size_type index = pos - data_;
        if(size_ + count > capacity_) {
            reallocate(std::max(capacity_ * 2, size_ + count));
        }
        for(size_type i = size_; i > index; i--) {
            if(i < size_) {
                destroy_at(data_ + i + count - 1);
            }
            construct_at(data_ + i + count - 1, std::move(data_[i - 1]));
        }
        for(size_type i = 0; i < count; i++) {
            construct_at(data_ + index + i, value);
        }
        size_ += count;
        return data_ + index;
    }

    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {//Insert elements from range [first, last) before pos: v.insert(pos, x.begin(), x.end())
        size_type index = pos - data_;
        size_type count = std::distance(first, last);
        if(count == 0) return data_ + index;
        if(size_ + count > capacity_) {
            reallocate(std::max(capacity_ * 2, size_ + count));
        }
        for(size_type i = size_ + count - 1; i >= index + count; i--) {
            construct_at(data_ + i, std::move(data_[i - count]));
        }
        size_type i = index;
        for(auto it = first; it != last; it++) {
            construct_at(data_ + i, *it);
            i++;
        }
        size_ += count;
        return data_ + index;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> list) {//Insert elements from initializer list before pos: v.insert(pos, {a, b, c})
        return insert(pos, list.begin(), list.end());
    }

    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args) { //Construct element in-place before pos: v.emplace(pos, args...)
        size_type index = pos - data_;
        grow_if_needed();
        for(size_type i = size_; i > index; i--) {
            construct(data_ + i, std::move(data_[i - 1]));
        }
        if(index < size_) {
            destroy_at(data_ + index);
        }
        construct_at(data_ + index, std::forward<Args>(args)...);
        size++;
        return data_ + index;
    }

    iterator erase(const_iterator pos) {//Erase element at pos: v.erase(pos)
        return erase(pos, pos + 1);
    }

    iterator erase(const_iterator first, const_iterator last) {//Erase elements in range [first, last): v.erase(x.begin(), x.end())
        size_type first_index = first - data_;
        size_type last_index = last - data_;
        size_type count = last_index - first_index;
        if(count == 0) return data_ + first_index;
        for(size_type i = first_index; i < last_index; i++) {
            destroy_at(data_ + i);
        }
        for(size_type i = last_index; i < size_; ++i) {
            construct_at(data_ + i - count, std::move(data_[i]));
        }
        size_ -= count;
        return data_ + first_index;
    }

    void push_back(const T& value) { //Add element to end: v.push_back(value)
        grow_if_needed();
        construct_at(data_ + size_, value);
        size++;
    }

    void push_back(T&& value) { //Add element to end: v.push_back(std::move(value))
        grow_if_needed();
        construct_at(data_ + size_, std::move(value));
        size++;
    }

    template <class... Args>
    void emplace_back(Args&&... args) {//Construct element in-place at end: v.emplace_back(args...)
        grow_if_needed();
        construct_at(data_ + size_, std::forward<Args>(args)...);
        return data_[size_++];
    }

    void pop_back() {//Remove last element: v.pop_back()
        destroy_at(data_ + size_--);
    }

    void resize(size_type count) { //Change size to count: v.resize(count)
        resize(count, value_type{});
    }
    void resize(size_type count, const value_type& value) {//Change size to count and fill new elements with value: v.resize(count, value)
        if(count < size_) {
            for(size_type i = count; i < size_; ++i)
                destroy_at(data_ + i);
        }
        else if(count > size_) {
            if(count > capacity_) reallocate(count);
            for(size_type i = size_; i < count; ++i)
                construct_at(data_ + i, value);
        }
        size_ = count;
    }
    
    void swap(Vector& other) noexcept {  //Swap contents with another vector: v.swap(other)
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(allocator_, other.allocator_);
    }
    
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

    void copy_from(const Vector& other) { //Copy resources from another vector
        if(other.size_ == 0) return;
        data_ = allocate(other.size_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        for(size_type i = 0; i < size_; i++) {
            construct_at(data_ + i, other.data_[i]);
        }
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