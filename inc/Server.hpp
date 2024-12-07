/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/07 20:40:18 by anovio-c         ###   ########.fr       */
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
#include <set>
#include <poll.h>
#include <cstdlib>
#include <algorithm>
#include "Client.hpp"
#include "Channel.hpp"

class Server
{
	private:
		static Server			*instance;
		static std::string		_srvName;
		
		int 					_port;
		std::string				_pass;

		int 					_listeningSocket;
		std::vector<pollfd>		pollfds;
		std::vector<Client *>	_clients;
		std::vector<Channel *>	_channels;
		Server(int port, const std::string &pass)
			: _port(port), _pass(pass) { };
		~Server();

		// !!!!!  HACER PARA EVITAR LA COPIA!!!!!
		//Server(const Server &src);
		//Server	&operator=(const Server *src);

	public:
		static Server	*getInstance(int port, const std::string &pass) {
			if (port < 1024 || port > 49151)
				throw std::invalid_argument("Invalid port number");
			if (!instance)
				instance = new Server(port, pass);
			return (instance);
		}
		
		static void	destroyInstance() {
			if (instance) {
				//for (size_t i = 0; i < instance->_clients.size(); ++i)
				//	delete instance->_clients[i];
				instance->_clients.clear();
				//for (size_t i = 0; i < instance->_channels.size(); ++i)
				//	delete instance->_channels[i];
				instance->_channels.clear();
			}
			delete instance;
			instance = NULL;
		}

		int			start();
		int			getPort(void);
		std::string	getPass(void);
		
		static std::string	getServerName() {
			return _srvName;
		}
		// static void			setServerName(const std::string &name) {
		// 	_srvName = name;
		// }
};
