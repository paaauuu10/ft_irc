/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:24:51 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/16 12:17:55 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

Server Server::instance;
bool Server::_initialized = false;
std::string Server::_srvName = "pikachu.server.com";

void	Server::init(int port, const std::string &pass) {
	if (_initialized) {
		std::cout << "Server is already running" << std::endl;
		return ;
	}
	if (port < 1024 || port > 49151)
		throw std::invalid_argument("Invalid port number");
	instance._port = port;
	instance._pass = pass;
	_initialized = true;
}

Client	*Server::getClientBySocket(int fd) {
	for (size_t i = 0; i < _clients.size(); ++i) {
		if (_clients[i]->getFd() == fd)
			return (_clients[i]);
	}
	return (NULL);
}

std::vector<Client *> Server::getClients(void){ return _clients; }

void	Server::cleanServer() {
	for (size_t i = 0; i < _clients.size(); ++i)
		delete _clients[i];
	_clients.clear();
	for (size_t i = 0; i < _channels.size(); ++i)
		delete _channels[i];
	_channels.clear();
	}

Server::~Server() {
	if (this->_listeningSocket > 0)
		close(_listeningSocket);
	cleanServer();
	std::cout << "Server destroyed..." << std::endl;
	}

void			Server::addChannel(Channel *channel) {
	Server::getInstance()._channels.push_back(channel);
	}

Channel	*Server::getCheckChannel(const std::string &name) {
	for (size_t i = 0; i < _channels.size(); ++i) {
		if (_channels[i]->getName() == name)
			return (_channels[i]);
	}
	return (NULL);
}


int	Server::start()
{
	// check if port is free ?

	this->_listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_listeningSocket == -1)
	{
		std::cerr << "Error creating a socket" << std::endl;
		return 1;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(6667);
	hint.sin_addr.s_addr = INADDR_ANY;

	if (bind(this->_listeningSocket, (struct sockaddr*)&hint, sizeof(hint)) == -1)
	{
		std::cerr << "Error binding IP/Port" << std::endl;
		return 1;
	}
	
	if (listen(this->_listeningSocket, FD_SETSIZE) == -1)
	{
		std::cerr << "Error listening" << std::endl;
		return 1;
	}
	
	pollfd listeningPoll;
	listeningPoll.fd = this->_listeningSocket;
	listeningPoll.events = POLLIN;
	listeningPoll.revents = 0;
	pollfds.push_back(listeningPoll);

	while(42)
	{
		int pollCount = poll(pollfds.data(), pollfds.size(), -1); //poll espera infinito (-1), si consideramos ejem 1000 ms para ocntrolar clientes incactivos
		if (pollCount == -1)
		{
			//std::cerr << "Error doing poll" << std::endl;
			break ;
		}
	for (size_t i = 0; i < pollfds.size(); ++i)
	{
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == this->_listeningSocket)
				{
					// New connection
					sockaddr_in clientSock;
					socklen_t clientSize = sizeof(clientSock);
					int clientSocket = accept(this->_listeningSocket, (sockaddr*)&clientSock, &clientSize);
					if (clientSocket == -1)
					{
						std::cerr << "Error accepting client" << std::endl;
						continue;
					}
					std::cout << "New connection established" << std::endl;
					Client *newClient = new Client("", "", clientSocket);
					_clients.push_back(newClient);

					pollfd clientPoll;
					clientPoll.fd = clientSocket;
					clientPoll.events = POLLIN;
					clientPoll.revents = 0;
					pollfds.push_back(clientPoll);
				}
				else
				{
					// Old connection
					char buffer[1024] = {0}; //this atribute is in client.hpp
					int received = recv(pollfds[i].fd, buffer, sizeof(buffer) - 1, 0);
					if (received <= 0)
					{
						std::cout << "Client disconnected" << std::endl;
						// delete de client aqui??
						close(pollfds[i].fd);
						pollfds.erase(pollfds.begin() + i);
						--i;
					}
					else
					{
						buffer[received] = '\0';
						Client *client = getClientBySocket(pollfds[i].fd); // Implementar esta función según tu diseño
						if (client) {
							std::string message(buffer);
							parsingbuffer(buffer, client);
						//	parser(client, message);
						}
						//std::string response = "Message received: " + std::string(buffer) + "\r\n";
						//send(pollfds[i].fd, response.c_str(), response.size(), 0);
					}
				}
			}
		}
	}
	close(this->_listeningSocket);
	return 0;
}

int			Server::getPort(void) {return this->_port;}
std::string	Server::getPass(void) {return this->_pass;}


void Server::handleMode(Client *client, const std::string &channelName) {
    std::ostringstream oss;

    // Enviar respuesta 324: modos del canal
    oss << ":" << this->_srvName << " 324 " << client->getNickname()
        << " " << channelName << " +nt" << "\r\n";
    std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);

    oss.str("");
    oss.clear();

    oss << ":" << this->_srvName << " 329 " << client->getNickname()
        << " " << channelName << " " << std::time(0) << "\r\n";
    msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
}

void Server::handleWho(Client *client, const std::string &channelName) {

    Channel *channel = this->getCheckChannel(channelName);
    if (!channel) {
        sendError(client, 403, "ERR_NOSUCHCHANNEL");
        return;
    }

    std::vector<Client*> clients = getClients();
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        Client *c = *it;
        std::ostringstream oss;
        oss << ":" << this->_srvName << " 352 " << client->getNickname()
            << " " << channelName << " " << c->getUsername() << " "
            << "127.0.0.1" << " " << this->_srvName << " "
            << c->getNickname() << " H :0 " << c->getRealname() << "\r\n";
        std::string msg = oss.str();
        send(client->getFd(), msg.c_str(), msg.size(), 0);
    }

    // Enviar mensaje 315: End of WHO list
    std::ostringstream oss;
    oss << ":" << this->_srvName << " 315 " << client->getNickname()
        << " " << channelName << " :End of WHO list" << "\r\n";
    std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
}

