#pragma once
#include <string>
#include <netinet/in.h>

namespace netx {
    class Socket {
    public:
        Socket();
        ~Socket();
        explicit Socket(const char *ip, const char *port, bool is_server_socket);

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

        const char *ip;

        const char *port;

        int setNonBlocking();

        int setCloseOnExec();

        bool server_socket;
    };
}
