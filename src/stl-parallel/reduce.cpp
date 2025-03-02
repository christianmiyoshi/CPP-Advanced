// Based on https://www.youtube.com/watch?v=v-1NlaDS9Fc

#include <execution>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> list (1 << 30); // 4GB Integers
    auto result = std::reduce(std::execution::par_unseq, list.begin(), list.end(), 0);
    // auto result = std::reduce(std::execution::seq, list.begin(), list.end(), 0);
    // auto result = std::reduce(std::execution::par, list.begin(), list.end(), 0);

    return result;
}