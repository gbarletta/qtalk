#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <string>
#include <chrono>

class message {
    private:
        std::string producer;
        std::string msg;
        std::chrono::system_clock::time_point created_at;

    public:
        message(std::string producer, std::string msg);
        message(std::string error);
        bool has_error;
        std::string error;
        std::string get_msg();
        std::string get_producer();
        std::chrono::system_clock::time_point get_created_at();
};

#endif