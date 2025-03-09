#include <iostream>
#include <boost/compute.hpp>

using namespace std;

// sudo apt update
// sudo apt install libboost-all-dev
// sudo apt install libboost-compute-dev

// sudo apt install ocl-icd-opencl-dev opencl-headers clinfo

int main()
{
    namespace bc = boost::compute;
    auto device = bc::system::default_device();
    return 0;
}
