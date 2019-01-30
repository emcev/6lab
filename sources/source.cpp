// Copyright 2018 amirnyy <alex.mirnyy@gmail.com>

#include <multithreads.hpp>

#include <boost/core/null_deleter.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <picosha2.h>

#include <iomanip>
#include <ostream>
#include <iostream>
#include <cstdlib>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;


std::vector<unsigned char> Multithreads::Fill_vector_by_random() {
    std::vector<unsigned char> char_vector_random;
    unsigned int size = std::rand() % 10 + 4;
    for (unsigned i = 0; i < size; i++) {
        char_vector_random.push_back(
        static_cast<unsigned char>(std::rand() % 256));
    }
    return char_vector_random;
}

bool Multithreads::Is_hash_needable(const std::string& hash) {
    for (unsigned i = hash.size() - 4; i < hash.size(); i++) {
        if (hash[i] != '0') return false;
    }
    return true;
}

void Multithreads::init()
{
    boost::shared_ptr< logging::core > core = logging::core::get();

    boost::shared_ptr< sinks::text_file_backend > backend =
        boost::make_shared< sinks::text_file_backend >(
            keywords::file_name = "file_%5N.log",
            keywords::rotation_size = 5 * 1024 * 1024,
            keywords::format = "[%TimeStamp%]: %Message%",
            keywords::time_based_rotation =
            sinks::file::rotation_at_time_point(12, 0, 0));

    typedef sinks::synchronous_sink< sinks::text_file_backend > sink_t;
    boost::shared_ptr< sink_t > sink(new sink_t(backend));
    core->add_sink(sink);
}

void Multithreads::Do_counting() {
    std::srand(std::time(0));
    for (unsigned int i = 0; i < number_iteration; i++) {
        std::vector<unsigned char> char_vector_random = Fill_vector_by_random();
        const std::string hash =
        picosha2::hash256_hex_string(char_vector_random);
        std::lock_guard<std::recursive_mutex> lock(m);
        BOOST_LOG_TRIVIAL(trace) << "[trace]" <<"ID thread: "
        << std::this_thread::get_id();
        std::string prototype = "";
        for (unsigned z = 0; z < char_vector_random.size(); z++) {
        prototype += char_vector_random[z];
        }
        BOOST_LOG_TRIVIAL(trace) << "[trace]" << "prototype = " << prototype;
        BOOST_LOG_TRIVIAL(trace) << "[trace]" << "HASH- function: " << hash;
        if (Is_hash_needable(hash)) {
            BOOST_LOG_TRIVIAL(info) << "[info]" << "ID thread: "
             << std::this_thread::get_id();
            BOOST_LOG_TRIVIAL(info) << "[info]" <<"prototype = " << prototype;
            BOOST_LOG_TRIVIAL(info) << "[info]" <<"HASH- function: " << hash;
        }
    }
}

void Multithreads::Make_counting_in_threads(unsigned threads_count) {
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < threads_count; i++) {
        threads.push_back(std::thread{&Multithreads::Do_counting, this});
    }
    for (unsigned i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
}
