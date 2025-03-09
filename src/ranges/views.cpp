#include <string>
#include <iostream>
#include <vector>
#include <ranges>

using namespace std;

void printValues(auto& range) {
    for (const auto& value: range) {
        cout << value << " ";
    }
    cout << endl;
}

int main() {
    vector<int> values {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto evenValues {values | views::filter([](const auto& value) {return value %2 == 0;})};
    printValues(evenValues);

    auto squareEven {evenValues | views::transform([](const auto& value) {return value*value;})};
    printValues(squareEven);

    auto dropFirst {squareEven | views::drop(1)};
    printValues(dropFirst);

    auto reversed {dropFirst | views::reverse | views::drop(1)};
    printValues(reversed);

    return 0;
}