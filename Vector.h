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
    Vector(); //Default constructor
    explicit Vector(size_type count, const T& value = T()); //Constructor with count and default value: v(count, value)
    Vector(std::initializer_list<T> list); //Constructor with initializer list: v{a, b, c}
    Vector(const Vector& other); //Copy constructor
    Vector(Vector&& other) noexcept; //Move constructor
    template<class InputIt>
    Vector(InputIt first, InputIt last); //Constructor with range: v(x.begin(), x.end())
    ~Vector(); //Destructor

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

    void resize(size_type count); //Change size to count: v.resize(count)
    void resize(size_type count, const value_type& value); //Change size to count and fill new elements with value: v.resize(count, value)

    void swap(Vector& other) noexcept; //Swap contents with another vector: v.swap(other)

    // Non-member functions
    template <class T, class Alloc>
    friend bool operator==(const Vector<T, Alloc>& left, const Vector<T, Alloc>& right); //Equality operator: v1 == v2
    friend bool operator!=(const Vector<T, Alloc>& left, const Vector<T, Alloc>& right); //Inequality operator: v1 != v2
    friend bool operator<(const Vector<T, Alloc>& left, const Vector<T, Alloc>& right); //Less-than operator: v1 < v2
    friend bool operator<=(const Vector<T, Alloc>& left, const Vector<T, Alloc>& right); //Less-than or equal operator: v1 <= v2
    friend bool operator>(const Vector<T, Alloc>& left, const Vector<T, Alloc>& right); //Greater-than operator: v1 > v2
    friend bool operator>=(const Vector<T, Alloc>& left, const Vector<T, Alloc>& right); //Greater-than or equal operator: v1 >= v2
    friend bool operator<=>(const Vector<T, Alloc>& left, const Vector<T, Alloc>& right); //Three-way comparison operator: v1 <=> v2

    void swap(Vector<T, Alloc>& left, Vector<T, Alloc>& right) noexcept; //Non-member swap function: swap(v1, v2)
    
    private:
    pointer data_ = nullptr; //Pointer to the underlying array
    size_type size_ = 0; //Number of elements in the vector
    size_type capacity_ = 0; //Capacity of the vector
    allocator_type allocator_; //Allocator for managing memory

    static constexpr size_type initial_capacity = 1; //Initial capacity for the vector

    pointer allocate(size_type n); //Allocate memory for n elements
    void deallocate(pointer p, size_type n) noexcept; //Deallocate memory for n elements at pointer p
    void reallocate(size_type new_capacity); //Reallocate memory to new capacity
    void grow_if_needed(); //Grow the vector if size exceeds capacity

    void construct_at(pointer p, const T& value); //Construct element at pointer p with value
    void destroy_at(pointer p) noexcept; //Destroy element at pointer p

    void move_from(Vector&& other) noexcept; //Move resources from another vector
    void copy_from(const Vector& other); //Copy resources from another vector
};