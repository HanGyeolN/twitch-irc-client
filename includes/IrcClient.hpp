#pragma once

#include <iostream> // std::cout 정의
#include <string> // string 타입 정의
#include <sys/socket.h> // socket 함수 정의
#include <netinet/in.h> // sockaddr_in 구조체 정의
#include <arpa/inet.h> // inet_addr 함수 정의
#include <unistd.h> // write 함수 정의
#include <thread>
#include "IrcError.hpp"

#define TWITCH_IRC_PORT 6667
#define TWITCH_IRC_URL "irc.chat.twitch.tv" // resolve 필요
#define TWITCH_IRC_IP "34.217.198.238"

class IrcClient 
{
private:
	int		_socket_fd;
	int		get_socket(); // socket() wrapper
	void	set_twitch_irc_server_addr(struct sockaddr_in &twitch_server_addr);
	void	connect_to_twitch_irc_server();

public:
	IrcClient();
	virtual ~IrcClient();
	IrcClient(const IrcClient &ref);
	IrcClient &operator=(const IrcClient &ref);

	int 		connect_socket();
	int			send_message(const char *msg);
	int			receive_message();
	
};