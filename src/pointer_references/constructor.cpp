#include <string>
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

class Employee {
    public: 
        Employee() : Employee(""){}

        explicit Employee (const string& firstName) : m_firstName{firstName} {}

        Employee(const Employee& src) : m_firstName{src.m_firstName} { // Copy constructor
            
        }
        void setFirstName(const string& firstName){
            m_firstName = firstName;
        }
        const string& getFirst() const {
            return m_firstName;
        }

        friend ostream& operator<<(ostream& ostr, const Employee& employee) {
            ostr << employee.m_firstName;
            return ostr;
        }

        Employee& operator=(const Employee& emp) {
            if (this == &emp) return *this;
            m_firstName = emp.m_firstName;
            return *this;
        }

    private:
        string m_firstName;
};

class School;
void swap_school(School& s1, School& s2) noexcept;

class School {
    public:
        School(string name) : m_director{new Employee(name)} {}
        School(const School& src) : School {src.m_director->getFirst()} {} // Copy constructor

        void swap(School& other) noexcept {
            std::swap(m_director, other.m_director);
        }

        School& operator=(const School& rhs) {
            if (this == &rhs) return *this;

            School temp {rhs}; // temporary instance
            swap(temp);
            return *this;
        }

        // Other options is disabling assignment and pass-by-value
        // School(const School& src) = delete;
        // School& operator=(const School& rhs) = delete;

        School(School&& src) noexcept {
            // moveFrom(src);
            swap_school(*this, src);
        } // Move Constructor
        School& operator=(School&& rhs) noexcept {
            // if (this == &rhs) {
            //     return *this;
            // }
            // cleanup();
            // moveFrom(rhs);
            // return *this;
            swap_school(*this, rhs);
            return *this;
        } // Move assign

    private:
        void cleanup() noexcept {
            delete m_director;
        }
        void moveFrom(School& src) noexcept {
            m_director = exchange(src.m_director, nullptr); // Primitive => direct assignment

            // m_name = move(src.m_name); Object => move
        }

        Employee * m_director; // Dynamically allocated resource
};

void swap_school(School& s1, School& s2) noexcept {
    s1.swap(s2);
}

void printValue(string&& message) {
    cout << "Rvalue: " <<  message << endl;
}

void printValue(const string& message) {
    cout << "LValue: " <<  message << endl;
}

int main() {

    // int number {10 * 50};
    // int result = number + 10;

    // // Employee empA;
    // // Employee empB;
    // // Employee empC {empB}; // copy constructor
    // // Employee empD = empC; // Copy Constructor

    // // empA = empB; // Assignment operator since empA is already constructed

    printValue("Hello"); // RValue
    string hello = "Hello";
    printValue(hello); // LValue
    printValue(std::move(hello)); // move(Lvalue) -> Rvalue

    return 0;
}