// Copyright 2018 amirnyy <alex.mirnyy@gmail.com>

#include <gtest/gtest.h>
#include <multithreads.hpp>

TEST(Multithreads, Test1) {
    Multithreads m;
    m.init();
    SUCCEED();
}

TEST(Multithreads, Test2) {
    Multithreads m;
    m.init();
    m.Make_counting_in_threads(std::thread::hardware_concurrency());
    SUCCEED();
}
