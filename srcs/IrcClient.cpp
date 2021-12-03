#include "IrcClient.hpp"
#include "utils.hpp"

IrcClient::IrcClient() : _socket_fd(0)
{
	std::cout << "IRC Client Constructed." << std::endl;
}

IrcClient::~IrcClient()
{
	std::cout << "IRC Client Destructed." << std::endl;
}

int		IrcClient::get_socket()
{
	int		socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd <= 0)
		throw (IrcError("socket create error"));
	return (socket_fd);
}

void	IrcClient::set_twitch_irc_server_addr(struct sockaddr_in &twitch_server_addr)
{
	memset(&twitch_server_addr, 0, sizeof(twitch_server_addr));
	twitch_server_addr.sin_family = AF_INET;
	twitch_server_addr.sin_port = htons(TWITCH_IRC_PORT);
	twitch_server_addr.sin_addr.s_addr = inet_addr(TWITCH_IRC_IP);
}

void	IrcClient::connect_to_twitch_irc_server()
{
	int									connect_res;
	struct sockaddr_in	twitch_server_addr;

	set_twitch_irc_server_addr(twitch_server_addr);
	std::cout << "port:" << twitch_server_addr.sin_port << std::endl;
	std::cout << "addr:" << twitch_server_addr.sin_addr.s_addr << std::endl;
	connect_res = connect(_socket_fd, (struct sockaddr *)&twitch_server_addr, sizeof(twitch_server_addr));
	// return 이 올때까지 blocking 상태
	if (connect_res == -1)
	{
		throw (IrcError("twitch server connect error"));
	}
	std::cout << "socket connected" << std::endl;
}

int		IrcClient::connect_socket()
{
	try
	{
		_socket_fd = this->get_socket();
		this->connect_to_twitch_irc_server();
	}
	catch (IrcError const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (_socket_fd);
}

int			IrcClient::send_message(const char *msg)
{
	int		send_res;

	send_res = ::send(_socket_fd, msg, strlen(msg), 0);
	std::cout << "SEND " << _socket_fd << " " << msg << std::endl;
	if (send_res == -1)
		throw (IrcError("send return -1"));
	return (send_res);
}

int			IrcClient::receive_message()
{
	int		ret;
	int		size;
	char	buffer[100];

	memset(buffer, 0, 100);
	ret = 1;
	while (ret)
	{
		ret = read_until_crlf(_socket_fd, buffer, &size);
		std::cout << "buffer" << buffer << std::endl;
	}
	return (ret);
}
