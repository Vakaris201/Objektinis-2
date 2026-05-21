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
};