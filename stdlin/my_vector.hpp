//
// Created by ubuntu on 9/19/22.
//

#ifndef STD_MY_VECTOR_H
#define STD_MY_VECTOR_H


#include <iostream>
#include <valarray>
#include <cstring>
#include <string>

template <typename T>
class my_vector
{
private:
    T* m_data;
    size_t m_size{};
    size_t m_capacity{};

public:

    static size_t constexpr base_capacity = 4; // Actually depends on algorithm

    my_vector();
    my_vector(const my_vector<T>& o);
    my_vector<T>& operator=(const my_vector<T>& o);
    my_vector(my_vector<T>&& o) noexcept;
    my_vector<T>& operator=(my_vector<T>&& o) noexcept;
    ~my_vector();
    void push_back(const T& element);
    void push_front(const T& element);
    void push_front(T&& element);
    template<typename ... Args>
    void emplace_back(T t, Args... args);
    T* data();
    T const* data() const;
    void clear();
    void pop_back();
    T& operator[](size_t i);
    const T& operator[](size_t i) const; //
    void reserve(size_t size);

};

#define checked_malloc(byte_size, res_ptr)\
do{\
    res_ptr = (T*)malloc(byte_size);\
    if(res_ptr == nullptr)\
    {\
        throw std::runtime_error(std::string(__FILE__) + std::to_string(__LINE__) + "Allocation Failed\n");\
    }\
}while(0)

#define checked_realloc(ptr, byte_size, res_ptr)\
do{\
    res_ptr = (T*)realloc(ptr, byte_size);\
    if(res_ptr == nullptr)\
    {\
        throw std::runtime_error(std::string(__FILE__) + std::to_string(__LINE__) + "Allocation Failed\n");\
    }\
}while(0)

template<typename T>
my_vector<T>& my_vector<T>::operator=(my_vector<T>&& o) noexcept {

    if (this == &o)
    {
        return *this;
    }

    for (size_t i = 0; i < m_size; i++) {
        m_data[i].~T();
    }

    if (m_data) {
        free(m_data);
    }

    this->m_data = o.m_data;
    this->m_capacity = o.m_capacity;
    this->m_size = o.m_size;
    o.m_size = 0;
    o.m_capacity = 0;
    o.m_data = nullptr;

    return *this;
}

template<typename T>
my_vector<T>::my_vector(my_vector<T>&& o)  noexcept {
    this->m_data = o.m_data;
    this->m_capacity = o.m_capacity;
    this->m_size = o.m_size;
    o.m_size = 0;
    o.m_capacity = 0;
    o.m_data = nullptr;
}

template<typename T>
my_vector<T>::my_vector() {
    m_size = 0;
    m_capacity = base_capacity;
    checked_malloc(m_capacity * sizeof(T), m_data);
}

template<typename T>
my_vector<T>::my_vector(const my_vector<T>& o)
{
    m_data = nullptr;
    reserve(o.m_capacity);
    m_size = 0;
    for (size_t i = 0; i < o.m_size; i++)
    {
        push_back(o[i]);
    }
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T>& o)
{
    if (this == &o)
    {
        return *this;
    }

    for (size_t i = 0; i < m_size; i++)
    {
        m_data[i].~T();
    }

    reserve(o.m_capacity);
    m_size = 0;
    for (size_t i = 0; i < o.m_size; i++)
    {
        push_back(o[i]);
    }

    return *this;
}

template<typename T>
my_vector<T>::~my_vector() {
    size_t size = m_size;
    for (size_t i = 0; i < size; i++) {
        m_data[i].~T();
    }
    free(m_data);
}

template<typename T>
void my_vector<T>::push_back(const T& element) {
    if (m_size + 1 > m_capacity) // check if the future size is included in capacity
    {
        reserve(m_capacity * 2);
    }
    new(&m_data[m_size])T(element);
    m_size++;
}

template<typename T>
template<typename ... Args>
void my_vector<T>::emplace_back(T t, Args ... args) {
    if (m_size + 1 > m_capacity) // check if the future size is included in capacity
    {
        reserve(m_capacity * 2);
    }
    new(&m_data[m_size])T(t, args...);
    m_size++;
}

template<typename T>
void my_vector<T>::push_front(const T& element) {
    if (m_size + 1 > m_capacity) // check if the future size is included in capacity
    {
        reserve(m_capacity * 2);
    }
    if (m_size) {
        new(&m_data[m_size])T(std::move(m_data[m_size - 1]));
        for (size_t i = m_size - 1; i > 0; i--) {
            m_data[i] = std::move(m_data[i - 1]);
        }
    }
    m_data[0] = element;
    m_size++;
}

// Add push front with move
template<typename T>
void my_vector<T>::push_front(T&& element) {
    if (m_size + 1 > m_capacity) // check if the future size is included in capacity
    {
        reserve(m_capacity * 2);
    }
    if (m_size) {
        new(&m_data[m_size])T(std::move(m_data[m_size - 1]));
        for (size_t i = m_size - 1; i > 0; i--) {
            m_data[i] = std::move(m_data[i - 1]);
        }
    }
    m_data[0] = std::move(element);
    m_size++;
}

template<typename T>
T* my_vector<T>::data()
{
    return m_data;
}

template<typename T>
void my_vector<T>::clear() {
    size_t size = m_size;
    for (size_t i = 0; i < size; i++) {
        pop_back();
    }
    m_capacity = base_capacity;
    m_data = (T*)realloc(m_data, m_capacity * sizeof(T));
}

template<typename T>
void my_vector<T>::pop_back()
{
    m_size--;
    m_data[m_size].~T();
}

template<typename T>
T& my_vector<T>::operator[](size_t i)
{
    return m_data[i];
}

template<typename T>
const T& my_vector<T>::operator[](size_t i) const
{
    return m_data[i];
}

template<typename T>
T const* my_vector<T>::data() const
{
    return m_data;
}

template<typename T>
void my_vector<T>::reserve(size_t size)
{
    checked_realloc(m_data, size * sizeof(T), m_data);
    m_capacity = size;
}

#endif //STD_MY_VECTOR_H