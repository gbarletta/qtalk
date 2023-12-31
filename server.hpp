#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <csignal>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class server {
    private:
        int listen_descr;
        int epoll_descr;
        struct epoll_event events[1024];
        std::vector<unsigned char> buffers[1024];

    public:
        server(std::string ip, int port);
        void set_non_blocking(int fd);
        bool add_descriptor(int fd, bool read, bool write);
        bool remove_descriptor(int fd);
        bool handle_accept();
        int read(int fd);
        bool process_request(int fd);
        bool handle_read(struct epoll_event *event);
        std::string read_request(int fd, unsigned short int size);
        bool handle_disconnection(int fd);
        bool handle_event(int idx);
        bool event_loop();
        
};

#endif