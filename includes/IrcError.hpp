#pragma once

#include <exception>
#include <string>

class IrcError : std::exception
{
private:
	const std::string	_msg;

public:
	IrcError(std::string const &msg);
	virtual ~IrcError() throw();
	virtual const char *what() const throw();
};