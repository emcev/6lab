// Copyright 2018 amirnyy <alex.mirnyy@gmail.com>

#ifndef INCLUDE_MULTITHREADS_HPP_
#define INCLUDE_MULTITHREADS_HPP_

#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Multithreads {
private:
    const unsigned number_iteration = 1500;
    std::recursive_mutex m;
    std::vector<unsigned char> Fill_vector_by_random();
    bool Is_hash_needable(const std::string& hash);
    void Do_counting();

public:
    void init();
    unsigned threads_number;
    Multithreads() {
        threads_number = std::thread::hardware_concurrency();
    }
    void Make_counting_in_threads(unsigned threads_count);
};


#endif  // INCLUDE_MULTITHREADS_HPP_
