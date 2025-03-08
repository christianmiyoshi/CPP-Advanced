#include <string>
#include <iostream>

using namespace std;

class Employee {
    public: 
        Employee(const string& firstName) : m_firstName{firstName} {}
        void setFirstName(const string& firstName){
            m_firstName = firstName;
        }
        const string& getFirst() const {
            return m_firstName;
        }
    private:
        string m_firstName;
};

int main() {
    const size_t size {2};
    Employee ** employees {new Employee*[size]};

    for (size_t i = 0; i < size; i++) {
        employees[i] = new Employee("name");        
    }

    for (size_t i = 0; i < size; i++) {
        delete employees[i];
        employees[i] = nullptr;
    }
    delete [] employees;
    employees = nullptr;

    return 0;
}