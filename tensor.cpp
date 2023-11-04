// #include <iostream>
#include <exception>

#include "tensor.hpp"

int main() {
    try {
        Neptune::Tensor<float, 2, 4> t{ 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f };
        std::cout << t << '\n';

        Neptune::Tensor<float, 2, 2, 2> h{ 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f };
        std::cout << h << '\n';

    } catch ( std::exception& e ) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }    
    return EXIT_SUCCESS;
}