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

using namespace netx;

Socket::Socket() : fd(-1) {};

Socket::~Socket() {
    close();
}

Socket::Socket(int fileDescriptor) : fd(fileDescriptor){};

int Socket::create() {
    fd = socket(AF_UNSPEC, SOCK_STREAM, 0); // todo maybe change later
    if (fd < 0) return -1;
    setNonBlocking();
    setCloseOnExec();
    return 0;
}

int Socket::bind(addrinfo* addr) {
    ::bind(fd, addr->ai_addr, addr->ai_addrlen);
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


