/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:58:33 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/11 16:04:30 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(void) : _name(""), _key(""), _topic(""), _limit(999) {}


Channel::Channel(const std::string &channelName, const std::string &key, Client *creator) : _topic("") {
	if (channelName.empty() || (channelName[0] != '&' && channelName[0] != '#'))
		throw std::invalid_argument("Invalid channel name. Must start with '&' or '#'.");
	_name = channelName;
	_operatorClients.push_back(creator);
	// invitation mode, by default is false
	_modes['i'] = false;
	if (key.empty()) {
		_key = "";
		_modes['k'] = false;
	}
	else {
		_key = key;
		_modes['k'] = true;
	}
	_limit = 999; // ?? -1
	std::cout << "Channel '" << _name << "' created by " << creator->getUsername() << ".\n";
}

Channel::~Channel() { }

std::string	Channel::getName() { return this->_name ; }

bool		Channel::getMode(char key) {
	if (_modes.find(key) != _modes.end()) {
        return true; //_modes[key];
    }
    return false;
}

std::string	Channel::getUserList() {
	std::string	names;
	for (size_t i = 0; i < _operatorClients.size(); ++i) {
		names += _operatorClients[i]->getNickname();
		names += " ,";
	}
	for (size_t i = 0; i < _clients.size(); ++i) {
		names += _clients[i]->getNickname();
		names += " ,";
	}
	names += "\r\n";
	return names;
}

void	Channel::setMode(char mode, bool status, int value) {

// · i: Set/remove Invite-only channel
// · t: Set/remove the restrictions of the TOPIC command to channel operators
// · k: Set/remove the channel key (password)
// · o: Give/take channel operator privilege
// l: Set/remove the user limit to channel
	(void)value;
	_modes[mode] = status;
	std::cout << "Channel " << _name << " mode " << mode << " set to " << (status ? "ON" : "OFF") << ".\n";
}

bool	Channel::isKeyProtected() { 
	return (getMode('k'));
	}

bool	Channel::checkKey(const std::string &str) const {
	return ((str.compare(_key)));
}

bool	Channel::isEmtpy() { return this->_clients.empty() ; }

bool	Channel::isFull() { 
	return ((this->_clients.size() + this->_operatorClients.size()) == static_cast<u_long>(this->_limit) ? true : false );
	}

void	Channel::addClient(Client *client) { this->_clients.push_back(client); }

void	Channel::addOperatorClient(Client *client) { this->_operatorClients.push_back(client); }

void	Channel::rmClient(Client *client) {
	for (size_t i = 0; i < _clients.size(); ++i) {
		// send message all of clients before erase.
		if (_clients[i]->getUsername() == client->getUsername())
			delete _clients[i];
	}
	if (_clients.empty())
		delete this;
}

std::vector<int>	Channel::listFdClients() {
	std::vector<int>	list;
	std::vector<Client *>::iterator it = _clients.begin();

	for (; it != _clients.end(); ++it) {
		list.push_back((*it)->getFd());
	}
	it = _operatorClients.begin();
	for (; it != _operatorClients.end(); ++it) {
		list.push_back((*it)->getFd());
	}
	return (list);
}

void	Channel::broadcast(std::string message) {

	std::vector<int> fds = listFdClients();
	std::cout << "MESSAGE: " << message << std::endl;
	for (size_t i = 0; i < fds.size(); ++i) {
		//usleep(500000);
		std::cout << "Broadcasting to fd: " << fds[i] << std::endl;
		ssize_t bytesSent = send(fds[i], message.c_str(), message.size(), 0);
		if (bytesSent == -1) {
    		std::cerr << "Error sending message to fd: " << fds[i] << std::endl;
		} else {
    		std::cout << "Sent " << bytesSent << " bytes to fd: " << fds[i] << std::endl;
		}
	}
	
}
