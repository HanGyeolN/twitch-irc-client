#pragma once

#include <iostream> // std::cout 정의
#include <string> // string 타입 정의
#include <sys/socket.h> // socket 함수 정의
#include <netinet/in.h> // sockaddr_in 구조체 정의
#include <arpa/inet.h> // inet_addr 함수 정의
#include <unistd.h> // write 함수 정의
#include <thread> // thread 사용
#include <stdio.h> // getline 함수
#include <sstream> // istringstream 타입
#include "IrcError.hpp"
#include "IrcSocket.hpp"

class IrcClient 
{
private:
	IrcSocket		*_socket;

public:
	IrcClient();
	virtual ~IrcClient();
	IrcClient(const IrcClient &ref);
	IrcClient &operator=(const IrcClient &ref);
	
	void	send_to_server(const std::string &msg);
	void	recv_from_server();
	void	login_twitch();
};