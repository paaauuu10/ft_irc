/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/04 11:15:34 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <poll.h>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#include "Client.hpp"

class Client;
class Server
{
	private:
		int _port;
		std::string	_pass;

		int _listeningSocket;
		std::vector<pollfd> pollfds;
	//	std::vector<Client *> client;
	//	std::map<int, Client> clients;
	//	std::map<std::string, Channel> channels;

	public:
		
		Server(int port, const std::string &pass);
		~Server();
		int			getPort(void);
		std::string	getPass(void);

		void parser(std::string str, Client *client);
		bool validCommand(std::string str, Client *client);
		void pass(std::string pass, Client *client);
		void parsingbuffer(char *buffer, Client *client);
		void user(std::string str, Client *client);


		int	start();
};


