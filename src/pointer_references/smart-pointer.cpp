#include <string>
#include <iostream>
#include <memory>

using namespace std;

class Employee : public enable_shared_from_this<Employee> {
    public: 
        Employee() = delete;
        Employee(const string& firstName) : m_firstName{firstName} {}
        void setFirstName(const string& firstName){
            m_firstName = firstName;
        }
        const string& getFirst() const {
            return m_firstName;
        }
        const void process() const {
            cout << "Processing" << endl;
        }
        shared_ptr<Employee> getPointer(){
            // return shared_ptr<Employee>(this); // TOTALLY WRONG
            return shared_from_this();
        }
        friend ostream& operator<<(ostream& ostr, const Employee& employee) {
            ostr << employee.m_firstName;
            return ostr;
        }
    private:
        string m_firstName;
};

void leaky() {
    Employee * emp {new Employee("leak")};
    emp->process(); // If this method throws an exception, emp wont be deleated
    delete emp;
}

void notLeaky() {
    auto emp { make_unique<Employee>("not leaky")};
    unique_ptr<Employee> emp2 {new Employee("not leaky")}; // Possible, but not recommended

    auto age { make_unique<int>()}; // age starts with 0
    cout << "age: " << *age << endl;
    auto age_undetermined { make_unique_for_overwrite<int>()}; // Performance critical. age will be initialized with whatever is in memory
    cout << "age_undetermined: " << *age_undetermined<< endl;
    emp->process();
}

void release() {
    auto emp { make_unique<Employee>("name")};
    emp.reset();
    emp.reset(new Employee {"name"});
    
    Employee * pointer { emp.release()};
    delete pointer;
    pointer = nullptr;

}

void closeFile(FILE * filePtr) {
    if (filePtr == nullptr) return;
    fclose(filePtr);
    cout << "File closed" << endl;
}

void shared_pointer() {
    auto emp = { make_shared<Employee>("shared")};
    FILE * file {fopen("README", "w")};
    shared_ptr<FILE> filePtr {file, closeFile};
    if (filePtr == nullptr) cerr << "Error opening file" << endl;
    else {
        cout << "File opened" << endl;        
    }

}

void weak_lock(weak_ptr<Employee> weakEmp) {
    auto resource = weakEmp.lock();
    if (resource) {
        cout << "Resource alive" << endl;
    } else {
        cout << "Resource has been freed" << endl;
    }
}

void weak_pointer(){
    auto sharedEmp {make_shared<Employee> ("shared")};
    cout << *sharedEmp << endl;
    weak_ptr<Employee> weakEmp {sharedEmp};
    weak_lock(weakEmp);
    sharedEmp.reset();
    weak_lock(weakEmp);
}

unique_ptr<Employee> createUnique() {
    auto emp {make_unique<Employee>("unique")};
    return emp; // NRVO
}

int main() {
    leaky();
    notLeaky();
    release();
    shared_pointer();
    weak_pointer();

    return 0;
}