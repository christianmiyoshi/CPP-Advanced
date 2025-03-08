#include <string>
#include <iostream>
#include <compare>
#include <vector>
#include <string_view>

using namespace std;

string_view extractExtension(string_view filename)  {
    // Avoid using string_view as return since it will only
    // work provided that the pointer filename is not invalidate
    // Return string instead
    return filename.substr(filename.rfind('.'));
}

void printString(const string& value) {
    cout << value << endl;
}

int main() 
{
    string a {"ab"};
    string b {"cd"};

    auto result { a <=> b};
    if (is_lt(result)) cout << "less" << endl;
    if (is_gt(result)) cout << "great" << endl;
    if (is_eq(result)) cout << "equal" << endl;

    vector names = {"Maria"s, "Pedro"s};

    cout << to_string(3.14) << endl;

    string filename = "doc.pdf";
    cout << extractExtension(filename) << endl;
    printString(extractExtension(filename).data());

    return 0;
}