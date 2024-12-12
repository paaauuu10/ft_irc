/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:00:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/12 14:00:12 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Channel.hpp"

Client::Client(void)
	: _fd(-1), _username(""), _nickname(""), _logged(false),
	_isRegistered(false), _buffer("") {
	
}

Client::Client(std::string username, std::string nickname, int fd)
	: _fd(fd), _username(username), _nickname(nickname), _logged(false), _isRegistered(false) {
	
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
std::string	Client::getRealname(void) { return this->_realname; }
std::string	Client::getHostname(void) { return this->_hostname; }
std::string	Client::getServername(void) { return this->_servername; }
bool		Client::getLogged(void) { return this->_logged; }
std::string	Client::getBuffer(void) { return this->_buffer; }
bool		Client::getRegistered(void) { return this->_isRegistered; }

Channel		*Client::getChannel(Channel *channel) {
	std::vector<Channel *>::iterator it;

	it = std::find(_channels.begin(), _channels.end(), channel);
	if (it != _channels.end())
		return (*it);
	return (NULL);
}


// SETTERS

void	Client::setNickname(std::string &nickname) {
	this->_nickname = nickname ;
}
void	Client::setUsername(std::string &username) {
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

void	Client::setRealName(std::string str) {
		this->_realname = str;
}

void	Client::setServername(std::string str) {
		this->_servername = str;
}

void	Client::setHostname(std::string str) {
		this->_hostname = str;
}

void	Client::addChannel(Channel *channel) {
	if (channel != NULL) { // Verifica que el puntero no sea nulo
        _channels.push_back(channel); // Añade el puntero al vector
    }
}

void	Client::rmChannel(std::string &channelName) {
	for (size_t i = 0; i < _channels.size(); ++i) {
		if (_channels[i]->getName() == channelName)
			delete _channels[i];
	}
}

void	Client::freeBuffer(void) {
	this->_buffer.clear();
}

