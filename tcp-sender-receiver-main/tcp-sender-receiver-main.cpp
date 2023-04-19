#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDRESS "127.0.0.1" // Адрес сервера
#define SERVER_PORT 12345          // Порт сервера
#define BUFFER_SIZE 1024           // Размер буфера для передачи данных

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file " << argv[1] << "\n";
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cerr << "Error: cannot create socket\n";
        return 1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server_address.sin_port = htons(SERVER_PORT);

    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "Error: cannot connect to server\n";
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;
    while ((bytes_read = file.read(buffer, BUFFER_SIZE).gcount()) > 0)
    {
        if (send(sock, buffer, bytes_read, 0) != bytes_read)
        {
            std::cerr << "Error: cannot send data to server\n";
            return 1;
        }
    }

    std::cout << "Data sent successfully\n";

    close(sock);
    return 0;
}
