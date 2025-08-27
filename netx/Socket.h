#pragma once
#include <netinet/in.h>

namespace netx {
    class Socket {
    public:
        inline Socket();
        inline ~Socket();
        explicit Socket(int fileDescriptor);

        int create();
        int bind(addrinfo* addr);
        int listen(int backlog = SOMAXCONN);

        Socket accept(sockaddr_in* clientAddr = nullptr);
        int connect(const sockaddr_in& addr);


        ssize_t send(const void* data, size_t len);
        ssize_t recv(void* buf, size_t len);
        void close();

        int getFd() const;

        static Socket createNonBlocking();

    private:
        int fd;

        int setNonBlocking();

        int setCloseOnExec();
    };
}
