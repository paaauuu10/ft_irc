/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:37 by anovio-c          #+#    #+#             */
/*   Updated: 2025/01/22 11:16:38 by anovio-c         ###   ########.fr       */
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
#include <ctime>
#include <limits.h>
#include <fcntl.h>
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
		
	public:
		Server() : _port(6667), _pass("default") {}
		Server(const Server &src);
		Server	&operator=(const Server *src);
		~Server();
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
		Client				*getClientByNickname(std::string nickname);
		Channel				*getCheckChannel(const std::string &name);
		std::vector<Channel *>	getChannels(Client *client);
		// tener que hacerlo en vector tambien
		std::vector<Client *>	getClients(void);
		void				handleMode(Client *client, const std::string &channelName);
		void				handleWho(Client *client, const std::string &channelName);
		static std::string	getServerName() {
			return _srvName;
		}
		void				removeClientFromPolls(int fd);
		void				removeClientFromServer(Client *client);
		void				removeChannel(Channel *channel);
};


void 	parser(Client *client, std::string str);
void 	parsingbuffer(char *buffer, Client *client);

void	join(Client *client, std::string& args);
void	kick(Client *client, std::string& args);
void	topic(Client *client, std::string& args);
void	pass(Client *client, std::string &pass);
void	user(Client *client, std::string &pass);
void	nick(Client *client, std::string &nickname);
void	invite(Client *client, std::string &invitation);
void	mode(Client *client, std::string &str);
void	quit(Client *client, std::string &message);
void 	privMsg(Client *sender, std::string &value);

#endif
