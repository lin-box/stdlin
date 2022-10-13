#include <iostream>
#include "my_vector.hpp"

using namespace std;

class Dog {
private:
    int m_age;
public:
    Dog() {
        cout << "default ctor" << endl;
        m_age = 0;
    }

    explicit Dog(int age) {
        cout << "default ctor" << endl;
        m_age = age;
    }

    ~Dog() {
        cout << "dtor" << endl;
    }

    Dog(const Dog& d) {
        cout << "copy ctor" << endl;
        m_age = d.m_age;
    }

    Dog(const Dog&& d)
        noexcept {
        cout << "move ctor" << endl;
        m_age = d.m_age;
    }

    Dog& operator=(const Dog& d) {
        cout << "copy =" << endl;
        m_age = d.m_age;
        return *this;
    }

    Dog& operator=(Dog&& d)
        noexcept {
        cout << "move =" << endl;
        m_age = 0;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    //Dog d(8);
    //Dog d2 = 7;

    my_vector<int> vec;
    vec.push_back(6);
    std::cout << vec[0] << std::endl;
    vec.push_back(5);
    vec.push_back(4);
    vec.push_back(3);
    std::cout << vec[0] << std::endl;
    std::cout << vec[1] << std::endl;
    std::cout << vec[2] << std::endl;
    std::cout << vec[3] << std::endl;
    vec.clear();
    vec.push_back(15);
    vec.push_back(14);
    vec.push_back(13);
    std::cout << vec[0] << std::endl;
    std::cout << vec[1] << std::endl;
    std::cout << vec[2] << std::endl;
    std::cout << vec[3] << std::endl;
    vec.push_front(800);
    std::cout << vec[0] << std::endl;
    std::cout << vec[1] << std::endl;
    std:cout << "------" << std::endl;


    return 0;
}