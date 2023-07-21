#include <iostream>
#include "service.hpp"

int main(int argc, char **argv)
{
    service srv = service();
    
    srv.register_entity("producer_test", "addr1");
    srv.register_entity("consumer_test", "addr2");

    srv.register_topic("topic1");
    srv.register_topic("topic2");

    srv.print_entities();
    srv.print_topics();

    srv.produce("producer_test", "topic1", "ciao!");
    srv.produce("fail_test", "topic1", "prova!");
    srv.consume("fail_test", "topic1");

    message msg = srv.consume("consumer_test", "topic1");
    std::cout << "Consumed message: \"" << msg.get_msg() << "\" from: " << msg.get_producer() << std::endl;
    
    srv.produce("consumer_test", "topic1", "prova!");
    srv.print_topic_messages("topic1");

    return 0;
}