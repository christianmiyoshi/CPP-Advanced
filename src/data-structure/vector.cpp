#include <execution>
#include <numeric>
#include <vector>

constexpr int getSizeCompileRunTime() {
    // Evaluate at either compile time or run time
    return 20;
}

consteval int getSizeCompileTime() { 
    // Evaluate at compile time
    return 20;
}

int main()
{
    std::vector<int> vector_int {10, 20};
    vector_int.push_back(30);

    int myArray[getSizeCompileRunTime()];
    int myArray2[getSizeCompileTime()];

    return 0;
}