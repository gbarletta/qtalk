#include "server.hpp"

server::server(std::string ip, int port)
{
    // classic TCP server setup
    struct sockaddr_in server_addr;
    this->listen_descr = socket(AF_INET, SOCK_STREAM, 0);

    if (this->listen_descr == -1) {
        perror("can't initialize server (socket)");
        std::exit(1);
    }

    const int enable = 1;

    // for debug-only purposes, i'll leave it here for now
    if (setsockopt(this->listen_descr, SOL_SOCKET, SO_REUSEADDR, 
        &enable, sizeof(int)) < 0) {
        perror("setsockopt");
        std::exit(1);
    }

    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    server_addr.sin_port = htons(port);

    if (bind(this->listen_descr, (struct sockaddr *) &server_addr, 
        sizeof(server_addr)) == -1) {
        perror("can't initialize server (bind)");
        std::exit(1);
    }

    if (listen(this->listen_descr, SOMAXCONN) == -1) {
        perror("can't initialize server (listen)");
        std::exit(1);
    }

    // set listen socket fd to non-blocking
    this->set_non_blocking(this->listen_descr);

    // size is ignored since Linux 2.6.8 but must be positive
    this->epoll_descr = epoll_create(1);

    // add listen socket fd to epoll (read and write)
    this->add_descriptor(this->listen_descr, true, true);
}

void server::set_non_blocking(int fd)
{
    int flags;

    // get fd flags
    if ((flags = fcntl(fd, F_GETFL, 0)) == -1) {
        perror("set_non_blocking() [fcntl F_GETFL]");
        std::exit(1);
    }

    // set fd to non-blocking
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("set_non_blocking() [fcntl F_SETFL]");
        std::exit(1);
    }
}

bool server::add_descriptor(int fd, bool read, bool write)
{
    struct epoll_event ev;

    // edge-triggered epoll
    ev.events = EPOLLET;
    ev.data.fd = fd;

    if (read) {
        ev.events |= EPOLLIN;
    }

    if (write) {
        ev.events |= EPOLLOUT;
    }

    if ((epoll_ctl(this->epoll_descr, EPOLL_CTL_ADD, fd, &ev)) == -1) {
        perror("add_descriptor");
        return false;
    }

    return true;
}

bool server::remove_descriptor(int fd)
{
    if ((epoll_ctl(this->epoll_descr, EPOLL_CTL_DEL, fd, nullptr)) == -1) {
        perror("remove_descriptor");
        return false;
    }

    return true;
}

bool server::handle_accept()
{
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // accept new client and set its socket to non-blocking
    // man accept4
    client_fd = accept4(
        this->listen_descr,
        (struct sockaddr *) &client_addr,
        &client_addr_len,
        SOCK_NONBLOCK
    );
    
    if (client_fd == -1) {
        perror("couldn't accept client");
        return false;
    }

    if (client_fd >= 1024) {
        std::cout << "couldn't accept client: reached socket limit" << std::endl;
        return false;
    }

    this->add_descriptor(client_fd, true, true);
    return true;
}

bool server::handle_read(struct epoll_event *event)
{
    int fd = event->data.fd;
    int recv_bytes;
    unsigned short int size;
    char *buffer;

    recv_bytes = recv(fd, &size, 2, 0);

    if (recv_bytes > 0) {
        size = ntohs(size);
        std::cout << "packet size: " << size << std::endl;
        buffer = new char[size];
        recv(fd, &buffer, size, 0);
        std::cout << "Received: " << std::string(buffer) << std::endl; 
    }

    send(fd, "ok", 2, 0);
    return true;
}

bool server::handle_event(int idx)
{
    struct epoll_event *event = &this->events[idx];

    if (event->data.fd == this->listen_descr) {
        return this->handle_accept();
    } 

    if (event->events & EPOLLIN) {
        return this->handle_read(event);
    }

    return true;
}

bool server::event_loop()
{
    while (true) {
        // wait for some ready file descriptors (no timeout)
        int ready_fds = epoll_wait(this->epoll_descr, this->events, 1024, -1);

        for (int i = 0; i < ready_fds; i++) {
            this->handle_event(i);
        }
    }
}