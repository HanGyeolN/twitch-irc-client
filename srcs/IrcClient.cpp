#include "IrcClient.hpp"
#include "utils.hpp"

/*
	@brief connect to twitch server socket when construct client
*/
IrcClient::IrcClient()
{
	_socket = new IrcSocket();
	std::cout << "IRC Client Constructed." << std::endl;
}

IrcClient::~IrcClient()
{
	std::cout << "IRC Client Destructed." << std::endl;
}

/*
	@brief 트위치 계정으로 채팅 서버에 로그인
*/
void	IrcClient::login_twitch()
{
	std::string	id;
	std::string	code;

	std::cout << "twitch id: ";
	std::cin >> id;
	std::cout << "twitch oauth code(https://twitchapps.com/tmi): ";
	std::cin >> code;
	_socket->connect_to_twitch_irc_server();
	code = "pass " + code;
	id = "nick " + id;
	send_to_server(code);
	send_to_server(id);
}

/*
	@brief 채팅 서버로 메세지 전송
	@detail 서버로 보내는 메세지의 끝은 "\n" 을 추가해서 알린다 (IRC RFC)
*/
void	IrcClient::send_to_server(const std::string &msg)
{
	return _socket->send_msg((msg + "\n").c_str());
}

/*
	@brief 서버로 부터 메세지를 받아와서 출력한다.
	@todo	코드 이해가 필요한 부분
*/
void	IrcClient::recv_from_server()
{
	std::string buffer = _socket->recv_msg();
	std::string line;
	std::istringstream iss(buffer);

	while (std::getline(iss, line))
	{
		if (line.find("\r") != std::string::npos)
			line = line.substr(0, line.size() - 1);
		std::cout << line << std::endl;
	}
}