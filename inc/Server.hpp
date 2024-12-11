/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/10 18:11:12 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

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
#include <limits.h>
#include "Utils.hpp"

class Client;
class Channel;

class Client;
class Server
{
	private:
		static	Server					instance;
		static	std::string				_srvName;
		static	bool					_initialized;
		
		int 							_port;
		std::string						_pass;

		int 							_listeningSocket;
		std::vector<pollfd>				pollfds;
		std::vector<Channel *>			_channels;
		std::vector<Client *>			_clients;
		
		Server() : _port(6667), _pass("default") {}
		// Server(int port, const std::string &pass)
		// 	: _port(port), _pass(pass) {
		// 		if (port < 1024 || port > 49151)
		// 			throw std::invalid_argument("Invalid port number");
		// 	};
		~Server();

		// !!!!!  HACER PARA EVITAR LA COPIA!!!!!
		Server(const Server &src);
		Server	&operator=(const Server *src);

	public:
		static Server	&getInstance() {
			return (instance);
		}

		static void	init(int port, const std::string &pass);
		
		void	cleanServer();

		int					start();
		int					getPort(void);
		std::string			getPass(void);
		void				addChannel(Channel *channel);
		Client 				*getClientBySocket(int fd);
		Channel				*getCheckChannel(const std::string &name);
		
		static std::string	getServerName() {
			return _srvName;
		}
};

bool validCommand(Client *client, std::string str);
void parser(Client *client, std::string str);
void	JOIN(Client *client, std::string& args);
void 	PASS(std::string pass, Client *client);

#endif
