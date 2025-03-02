#include <iostream>
#include <vector>
#include <execution>
#include <cmath>

constexpr int NUM_STEPS = 200000000;

double compute_pi() {
    double step = 1.0 / NUM_STEPS;
    std::vector<double> values(NUM_STEPS);
    std::iota(values.begin(), values.end(), 0);

    std::transform(std::execution::par_unseq, values.begin(), values.end(), values.begin(),
        [step](int i) {
            double x = (i + 0.5) * step;
            return 4.0 / (1.0 + x * x);
        });
    double sum = std::reduce(std::execution::par_unseq, values.begin(), values.end());

    return sum * step;
}

int main() {
    double pi = compute_pi();
    std::cout << "π = " << pi << std::endl;
    return 0;
}