//
// Created by Antonin on 29/10/2023.
//
#include <iostream>
#include <glm/common.hpp>
int main(int argc, char *argv[])
{
    std::cout << "test";
    std::cout << "argc == " << argc << '\n';

    for (int ndx{}; ndx != argc; ++ndx)
        std::cout << "argv[" << ndx << "] == " << argv[ndx] << '\n';
    std::cout << "argv[" << argc << "] == "
              << static_cast<void*>(argv[argc]) << '\n';

    /*...*/

    return argc == 3 ? EXIT_SUCCESS : EXIT_FAILURE; // optional return value
}