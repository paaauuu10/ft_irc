/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:00:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/03 11:48:37 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <algorithm>

Client::Client(void)
	: _fd(-1), _username(""), _nickname(""), _logged(false),
	_isRegistered(false), _buffer("") {
	
}

Client::Client(std::string username, std::string nickname, int fd)
	: _username(username), _nickname(nickname), _fd(fd) {
	
}

Client::Client(const Client &src) {
	*this = src;
}

Client	&Client::operator=(const Client &src) {
	if (this != &src) {
		this->_fd = src._fd;
		this->_username = src._username;
		this->_nickname = src._nickname;
		this->_logged = src._logged;
		this->_isRegistered = src._isRegistered;
		this->_buffer = src._buffer;
	}
	return (*this);
}

Client::~Client(void) {
	
} 

// GETTERS

int			Client::getFd(void) { return this->_fd; }
std::string	Client::getUsername(void) { return this->_username; }
std::string	Client::getNickname(void) { return this->_nickname; }
bool		Client::getLogged(void) { return this->_logged; }
std::string	Client::getBuffer(void) { return this->_buffer; }
bool		Client::getRegistered(void) { return this->_isRegistered; }

bool		Client::getChannel(std::string &channelName) {
	std::vector<std::string>::iterator it;

	it = std::find(_channels.begin(), _channels.end(), channelName);
	return (it != _channels.end());
}


// SETTERS

bool	Client::setNickname(std::string &nickname) {
	this->_nickname = nickname ;
}
bool	Client::setUsername(std::string &username) {
		this->_username = username;
}
void	Client::setFd(int fd) {
		this->_fd = fd;
}
void	Client::setLogged(bool value) {
		this->_logged = value;
}
void	Client::setBuffer(std::string &buffer) {
		this->_buffer = buffer;
}
void	Client::setRegistered(bool value) {
		this->_isRegistered = value;
}


// MEMBER FUNCTIONS

void	Client::addChannel(std::string &channelName) {
	this->_channels.push_back(channelName);
}

void	Client::rmChannel(std::string &channelName) {
	std::vector<std::string>::iterator it;

	it = std::find(_channels.begin(), _channels.end(), channelName);
	if (it != _channels.end())
		this->_channels.erase(it);
}

void	Client::freeBuffer(void) {
	this->_buffer.clear();
}

