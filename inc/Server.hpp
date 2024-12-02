/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/02 13:25:58 by pborrull         ###   ########.fr       */
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
#include "Client.hpp"

class Server
{
	private:
		int _port;
		std::string	_pass;

		int _listeningSocket;
		std::vector<pollfd> pollfds;
	//	std::map<int, Client> clients;

	//	std::map<std::string, Channel> channels;

	public:
		
		Server(int port, const std::string &pass);
		~Server();
		int			getPort(void);
		std::string	getPass(void);

		int	start();
};
