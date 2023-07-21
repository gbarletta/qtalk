#include "message.hpp"

message::message(std::string producer, std::string msg)
{
    this->producer = producer;
    this->msg = msg;
    this->created_at = std::chrono::system_clock::now();
    this->has_error = false;
}

message::message(std::string error)
{
    this->has_error = true;
    this->error = error;
}

std::string message::get_msg() 
{
    return this->msg;
}

std::string message::get_producer()
{
    return this->producer;
}

std::chrono::system_clock::time_point message::get_created_at()
{
    return this->created_at;
}