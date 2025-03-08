#include <string>
#include <iostream>

using namespace std;

void printString(const string& myString) {
    cout << myString << endl;
}

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
    string hello {"Hello world"};
    printString(hello);
    printString("literal");

    Employee emp{ "Mario" };
    string name = emp.getFirst();
    name = "";
    printString(name);

}