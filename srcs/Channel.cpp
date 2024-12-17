/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:58:33 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/17 13:51:52 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"
#include "Client.hpp"

Channel::Channel(const std::string &channelName, const std::string &key, Client *creator) : _topic("") {
	if (channelName.empty() || (channelName[0] != '&' && channelName[0] != '#'))
		throw std::invalid_argument("Invalid channel name. Must start with '&' or '#'.");
	else
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
	std::cout << "Channel '" << channelName << "' created by " << creator->getUsername() << ".\n";
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
		if (i != _operatorClients.size() - 1) {
            names += " ";
        }
	}
	if (_clients.size() >= 1)
		names += " ";
	for (size_t i = 0; i < _clients.size(); ++i) {
		names += _clients[i]->getNickname();
		if (i != _clients.size() - 1) {
            names += " ";
        }
	}
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
	return (_key == str);
}

bool	Channel::checkOperatorClient(Client *client) {
	for (size_t i = 0; this->_operatorClients.size(); ++i) {
		if (this->_operatorClients[i]->getNickname() == client->getNickname())
			return true;
	}
	return false;
}

Client	*Channel::checkClient(std::string &nickname) {
	for (size_t i = 0; this->_clients.size(); ++i) {
		if (this->_clients[i]->getNickname() == nickname)
			return this->_clients[i];
	}
	return NULL;
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

void Channel::broadcast(Client *client, std::string &msg) {
    std::vector<int> fds = listFdClients();
	(void)client;

    //std::ostringstream oss;

    // Mensaje JOIN con el prefijo correcto
	// :<nickname>!<username>@<hostname> JOIN :<channelName>\r\n
	
    //oss << ":" << client->getNickname() << "!" 
    //    << client->getUsername() << "@127.0.0.1 JOIN :" 
     //   << this->getName() << "\r\n";

    //std::string msg = oss.str();

    // Enviar a todos los clientes del canal
    for (size_t i = 0; i < fds.size(); ++i) {
        send(fds[i], msg.c_str(), msg.size(), 0);
    }
}


/*
void	Channel::broadcast(Client *client) {
	//:<servidor> JOIN <cliente> <canal>
	
	std::vector<int> fds = listFdClients();
	std::ostringstream oss;

	oss << ":" << Server::getServerName() << " JOIN :"
		<< client->getNickname() << " " << this->getName()
		<< "\r\n";
		
	std::string msg = oss.str();
	//:<server_name> JOIN :#canal1
	std::ostringstream ossOwn;

	ossOwn << ":" << Server::getServerName() << " JOIN :"
		<< this->getName() << "\r\n";
	std::string msgOwn = ossOwn.str();

	for (size_t i = 0; i < fds.size(); ++i) {
		if (fds[i] == client->getFd()) {
			send(fds[i], msgOwn.c_str(), msgOwn.size(), 0);
			continue ;
		}
		std::cout << "FD  == " << fds[i] << std::endl;
		send(fds[i], msg.c_str(), msg.size(), 0);
	}
}*/

void	Channel::RPLTOPIC(Client *client) {
	std::ostringstream oss;
	
	// :<servername> 331/332 <nickname> <username> : <topic or no topic is set>
	oss << ":" << Server::getServerName() << " " << ((this->_topic.empty()) ? 331 : 332)
		<< " " << client->getNickname() << " " << this->getName() << " :"
		<< ((this->_topic.empty()) ? "No topic is set" : this->_topic)
		<< "\n";
	std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
}

void	Channel::RPL_NAMREPLY(Client *client) {
	std::string	list = this->getUserList();

	//:<servidor> 353 <cliente> = <canal> :<nicks>,{<nick>}
	std::ostringstream oss;

	oss << ":" << Server::getServerName() << " " << 353 << " "
		<< client->getNickname() << " = " << this->getName()
		<< " :" << list << "\n";
	std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);

	// :<servidor> 366 <cliente> <canal> :End of NAMES list.
	oss.str("");
	oss.clear();
	oss << ":" << Server::getServerName() << " " << 366 << " "
		<< client->getNickname() << " " << this->getName()
		<< " :End of NAMES list." << "\r\n";
	msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
}
