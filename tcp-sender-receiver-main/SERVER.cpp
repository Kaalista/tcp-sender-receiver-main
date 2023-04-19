
#include <iostream>
#include <fstream>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDRESS "127.0.0.1" // Адрес сервера
#define SERVER_PORT 12345          // Порт сервера
#define BUFFER_SIZE 1024           // Размер буфера для получения данных

int socket_fd;
std::ofstream output_file;

// Обработчик сигналов
void signal_handler(int signum)
{
    if (signum == SIGTERM || signum == SIGHUP)
    {
        std::cout << "Received signal " << signum << ", shutting down...\n";
        close(socket_fd);
        output_file.close();
        exit(0);
    }
}

int main()
{
    // Настройка обработчика сигналов
    struct sigaction action;
    action.sa_handler = signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGHUP, &action, NULL);

    // Создание сокета
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        std::cerr << "Error: cannot create socket\n";
        return 1;
    }

    // Настройка адреса сервера и привязка к сокету
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server_address.sin_port = htons(SERVER_PORT);

    if (bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "Error: cannot bind socket\n";
        return 1;
    }

    // Прослушивание сокета
    if (listen(socket_fd, 1) < 0)
    {
        std::cerr << "Error: cannot listen on socket\n";
        return 1;
    }

    std::cout << "Server started, listening on port " << SERVER_PORT << "\n";

    // Ожидание подключений
    struct sockaddr_in client_address;
    int client_address_size = sizeof(client_address);
    int client_fd = accept(socket_fd, (struct sockaddr*)&client_address, (socklen_t*)&client_address_size);
    if (client_fd < 0)
    {
        std::cerr << "Error: cannot accept incoming connection\n";
        return 1;
    }

    std::cout << "Client connected, receiving data...\n";

    // Получение данных
    char buffer[BUFFER_SIZE];
    int bytes_received;
    
    output_file.open("received_data.txt", std::ios_base::open_mode _Mode);
