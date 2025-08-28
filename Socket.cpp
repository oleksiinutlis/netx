#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>

#include "netx/Socket.h"

#include <iostream>

using namespace netx;

Socket::Socket() : fd(-1), ip(""), port(""), server_socket(false) {};

Socket::~Socket() {
    // todo
    ::close(fd);
}

Socket::Socket(const char *ip, const char *port, bool is_server_socket) {
    fd = -1;
    this->ip = ip;
    this->port = port;
    server_socket = is_server_socket;
};

int Socket::create() {
    // todo check error handling

    addrinfo hints{}, *sock;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (server_socket) hints.ai_flags = AI_PASSIVE;
    getaddrinfo(ip, port, &hints, &sock);


    for(addrinfo *p = sock; p != nullptr; p = p->ai_next)
    {
         if ( (fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1 )
         {
             perror("socket");
         }
    }
    if (fd < 0) return -1;

    freeaddrinfo(sock);
    setNonBlocking();
    setCloseOnExec();

    std::cout << "Success";
    return 0;
}

int Socket::bind(addrinfo* addr) {
    ::bind(fd, addr->ai_addr, addr->ai_addrlen);
    return 0; // todo
}
int Socket::setNonBlocking() {
    int flags = fcntl(fd, F_GETFL, 0);

    if(fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        perror("fcntl");
        return -1;
    }

    return 0;
}

int Socket::setCloseOnExec() {
    int flags = fcntl(fd, F_GETFL, 0);

    if(fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1)
    {
        perror("fcntl");
        return -1;
    }

    return 0;
}


