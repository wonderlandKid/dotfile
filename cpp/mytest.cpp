#include <iostream>
#include <stdexcept>
#include <vector>

#include "backward.hpp"

int main() {
    backward::SignalHandling sh;
    std::vector<int> vec{1,2};
    std::cout<< vec[5];
    return 0;
}
