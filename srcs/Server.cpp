/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:24:51 by anovio-c          #+#    #+#             */
/*   Updated: 2024/11/27 10:53:04 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"



int	server(int port, std::string pass)
{
	// check if port is free ?
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == -1)
	{
		std::cerr << "Error creating a socket" << std::endl;
		return 1;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(6667);
	hint.sin_addr.s_addr = INADDR_ANY;

	if (bind(listening, (struct sockaddr*)&hint, sizeof(hint)) == -1)
	{
		std::cerr << "Error binding IP/Port" << std::endl;
		return 1;
	}
	
	if (listen(listening, 5) == -1)
	{
		std::cerr << "Error listening" << std::endl;
		return 1;
	}
	
	std::vector<pollfd> fds;
	pollfd listeningPoll;
	listeningPoll.fd = listening;
	listeningPoll.events = POLLIN;
	fds.push_back(listeningPoll);

	while(42)
	{// use epoll??
		int pollCount = poll(fds.data(), fds.size(), -1);
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
	 for (size_t i = 0; i < fds.size(); ++i)
	 {
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == listening)
				{
					// New connection
					sockaddr_in client;
					socklen_t clientSize = sizeof(client);
					int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
					if (clientSocket == -1)
					{
						std::cerr << "Error accepting client" << std::endl;
						continue;
					}
					std::cout << "New connection established" << std::endl;

					pollfd clientPoll;
					clientPoll.fd = clientSocket;
					clientPoll.events = POLLIN;
					fds.push_back(clientPoll);
				}
				else
				{
					// Old connection
					char buffer[1024] = {0};
					int received = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
					if (received <= 0)
					{
						std::cout << "Client disconnected" << std::endl;
						close(fds[i].fd);
						fds.erase(fds.begin() + i);
						--i;
					}
					else
					{
						buffer[received] = '\0';
						std::cout << "Message from client: " << buffer << std::endl;
						std::string response = "Message received: " + std::string(buffer) + "\r\n";
						send(fds[i].fd, response.c_str(), response.size(), 0);
					}
				}
			}
		}
	}


	close(listening);
	return 0;
}
