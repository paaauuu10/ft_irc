/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:24:51 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/03 15:26:33 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, const std::string &pass)
	: _port(port), _pass(pass)
{
}

Server::~Server()
{
}

bool Server::validCommand(std::string str, Client *client)
{
	(void)client;
    int index = 0;
    std::string commands[17] = { "PASS", "NICK", "USER", "SERVER", "OPER", "QUIT", "SQUIT", "JOIN", "PART", "MODE", "TOPIC", "NAMES", "LIST", "INVITE", "KICK", "VERSION", "PRIVMSG"};
    std::string cmd = str.substr(0, str.find(' '));
  /*  std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) {
        return std::toupper(c);
    });*/ // Convert str into capital letters
    std::string rest = str.substr(str.find(' ') + 1); // Eliminar el salto de línea (si existe) al final
	if (!rest.empty() && ((rest[rest.size() - 1]) == '\n' || (rest[rest.size() - 1]) == '\r'))
		rest.erase(rest.size() -1);
	while ((cmd != commands[index]) && cmd != ('/' + commands[index]))
    {
        index++;
        if (index == 17)
            return false;
    }
    index++;
    switch(index)
    {
        case 1:
            //std::cout << commands[index - 1] << std::endl;
			pass(rest, client);
            break;
        case 2:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 3:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 4:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 5:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 6:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 7:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 8:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 9:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 10:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 11:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 12:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 13:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 14:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 15:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 16:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 17:
            std::cout << commands[index - 1] << std::endl;
            break;
    }
    return true;
}
void Server::parser(std::string str, Client *client)
{
    if  (str.size() > 0)
	{
		std::string s = str.substr(0, str.find(' '));
		if (!validCommand(str, client))
            std::cout << s << " :Unknown command" << std::endl;
			//ha de ser SEND
    }
}

void Server::parsingbuffer(char *buffer, Client *client)
{
	std::istringstream stream(buffer);
    std::string line;

	while (std::getline(stream, line))
		parser(line, client);
}

int	Server::start()
{
	// check if port is free ?

	if (this->_port < 1024 || this->_port > 49151)
	{
		std::cerr << "Error trying to use a invalid port" << std::endl;
		return 1;
	}

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
	pollfds.push_back(listeningPoll);

	while(42)
	{
		int pollCount = poll(pollfds.data(), pollfds.size(), -1);
		if (pollCount == -1)
		{
			std::cerr << "Error doing poll" << std::endl;
			break ;
		}

	/*	sockaddr_in client;
		socklen_t clientSize = sizeof(client);
		int clientSocket = accept(listening, (struct sockaddr *)&client, &clientSize);
		int clientSocket = accept(listening, NULL, NULL);
		if (clientSocket == -1)
		{
			std::cerr << "Error connecting with client" << std::endl;
			return 1;
		}
		char host[1024] = {0};
		int	received = recv(clientSocket, host, sizeof(host) - 1, 0);
		if (received > 0)
			host[received] = '\0';
		std::cout << "Message from client: " << host << std::endl;
	}*/
	Client *client;
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
					
					client = new Client();
					pollfd clientPoll;
					clientPoll.fd = clientSocket;
					clientPoll.events = POLLIN;
					pollfds.push_back(clientPoll);
					client->setFd(pollfds[i].fd);
				}
				else
				{
					// Old connection
					char buffer[1024] = {0};
					int received = recv(pollfds[i].fd, buffer, sizeof(buffer) - 1, 0);
					if (received <= 0)
					{
						std::cout << "Client disconnected" << std::endl;
						close(pollfds[i].fd);
						pollfds.erase(pollfds.begin() + i);
						--i;
					}
					else
					{
						buffer[received] = '\0';
						parsingbuffer(buffer, client);
					//	std::cout << "Message from client: " << buffer << std::endl;
						std::string response = "Message received: " + std::string(buffer) + "\r\n";
						send(pollfds[i].fd, response.c_str(), response.size(), 0);
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

