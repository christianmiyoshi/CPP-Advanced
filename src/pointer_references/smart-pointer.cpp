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

#include <iostream>
#include <memory>

class Node {
public:
  explicit Node(int value) : m_value {value} {}
  ~Node() {
    std::cout << "Destroying Node " << m_value << std::endl;
  }
  void setNext(shared_ptr<Node> next) {
    m_next = next;
  }

  auto getValue(){
    return m_value;
  }

  auto getNextNode(){
    return m_next.lock();
  }
private:
  int m_value = 0;
  std::weak_ptr<Node> m_next;
};


int nodeExample(){
  std::cout << "Start" << endl;
  auto node1 { std::make_shared<Node>(1) };
  auto node2 { std::make_shared<Node>(2) };
  auto node3 { std::make_shared<Node>(3) };
  
  node1->setNext(node2);
  node2->setNext(node3);  

  auto currentNode {node1};
  while(currentNode) {
    std::cout << "Node " << currentNode->getValue() << endl;
    currentNode = currentNode->getNextNode();
  }

  {
    auto node4 { std::make_shared<Node>(4) };
    auto node5 { std::make_shared<Node>(5) };

    node4->setNext(node5);
    node5->setNext(node4);  
  }
    
  std::cout << "End" << endl;
  return 0;
}
int main() {
    // leaky();
    // notLeaky();
    // release();
    // shared_pointer();
    // weak_pointer();
    // nodeExample();

    std::cout << "Start" << endl;
    auto node4 { std::make_shared<Node>(4) };
    auto node5 { std::make_shared<Node>(5) };

    node4->setNext(node5);
    node5->setNext(node4);  
    std::cout << "End" << endl;
      

    return 0;
}