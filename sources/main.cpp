// Copyright 2018 amirnyy <alex.mirnyy@gmail.com>

#include "multithreads.hpp"

#include <cstdlib>

int main(int argc, char* argv[] ) {
    Multithreads m;
    m.init();
    if (argc > 1) {
        m.Make_counting_in_threads(std::atoi(argv[1]));
    } else {
        m.Make_counting_in_threads(std::thread::hardware_concurrency());
    }
}
