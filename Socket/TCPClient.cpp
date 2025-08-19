#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        return 1;
    }

    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    const char *msg = "Hello from client!";
    send(sock, msg, strlen(msg), 0);

    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    std::cout << "Server replied: " << buffer << std::endl;

    close(sock);
    return 0;
}





//Bhavesh Written below

/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

int main()
{
    //Creating socket FD :
    
    int serverFD = socket(AF_INET,SOCK_STREAM,0);
    if(serverFD == 0)
    {
    std::cout<<"Error server FD"<<std::endl;
    return 1;
    }

    else
    {
        std::cout<<"Server Socket creatd"<<std::endl;
    }
    
    //Setting sockaddr_in ip and port for binding : 
    sockaddr_in addr{};
    
    int addrLength = sizeof(addr);
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    
    
if(bind(serverFD,(struct sockaddr*)&sockaddr_in,sizeof(addr)<0)
{
    std::cerr<<"Bind Failed"<<std::endl;
    return 1;
}

if(listen(serverFD,3)<0)
{
    std::cerr<<"listen Failed"<<std::endl;
    return 1;
}

std::cout << "Server listening on port 8080...\n";
    
int new_socket = accept(serverFD,(struct sockaddr*)&sockaddr_in,
((socklen_t *))sizeof(addr)); 


if(new_socket < 0)
{
    std::cerr<<"Accept Failed";
    return 1;
}

char buffer[1024] = {0};
read(new_socket,buffer,1024);

std::cout<<"Recived from Client :  "<<buffer<<std::endl;


const char *reply = "Hello from server!";
send(new_socket, reply, strlen(reply), 0);

close(new_socket);
close(server_fd);


///Creating clinet here only:

int socketClient = socket(AF_INET,SOCK_STREAM,0);

if(socketClient == 0)
{
    std::cerr<<"Socket creation failed"<<std::endl;
    return 1;
}

//binding IP and address to Socket

sockaddr_in serv_addr{};

serv_addr.sin_family = AF_INET;
serv_addr.sin_port  = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        return 1;
    }
    
    if(connect(socketClient ,(struct sockaddr*)&serv_addr,sizeof(serv_addr) )<0)
    {
                std::cerr << "Invalid address\n";
        return 1;
    }
    
    const char *msg = "Hello from client!";
    send(socketClient, msg, strlen(msg), 0);

    char buffer[1024] = {0};
    read(socketClient, buffer, 1024);
    std::cout << "Server replied: " << buffer << std::endl;

    close(sock);
    return 0;
    return 0;
}