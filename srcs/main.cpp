#include "IrcClient.hpp"

int g_socket_fd;

void	send_input()
{
	int						send_res;
	std::string		msg;

	while (strcmp(msg.c_str(), "quit"))
	{
		try {
			getline(std::cin, msg);
			std::cout << "msg send to " << g_socket_fd << " : " << msg << std::endl;
			send_res = ::send(g_socket_fd, msg.c_str(), strlen(msg.c_str()), 0);
			if (send_res == -1)
				throw (IrcError("send return -1"));
		} catch (IrcError e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

int		main()
{
	int				fd;
	IrcClient *client;

	client = new IrcClient();
	g_socket_fd = client->connect_socket();

	std::thread		t1(send_input);

	sleep(10);
	std::cout << "sleep end" << std::endl;

	client->receive_message();
	delete client;

	t1.join();

	return 0;
}