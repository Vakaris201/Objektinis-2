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

    // Constructors
    Vector(); //Default constructor
    explicit Vector(size_type count, const T& value = T()); //Constructor with size and default value: v(size, value)
    Vector(std::initializer_list<T> list); //Constructor with initializer list: v{a, b, c}
    Vector(const Vector& other); //Copy constructor
    Vector(Vector&& other) noexcept; //Move constructor
    ~Vector(); //Destructor

    Vector& operator=(const Vector& other); //Copy assignment operator
    Vector& operator=(Vector&& other) noexcept; //Move assignment operator

};