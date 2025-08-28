#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "netx/Socket.h"

int main(int argc, char *argv[])
{
    auto servsock = netx::Socket(nullptr, "8080", true);
    servsock.create();
}

