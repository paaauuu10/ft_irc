/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:31:40 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/10 15:53:38 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class Channel;

class Client {
	private:
		int							 _fd;
		std::string					_username;
		std::string 				_nickname; // nickname max 9 chars
		// See the protocol grammar rules for what may and may not be used in a nickname. 
		std::string					_hostname;
		std::string					_realname;
		std::string					_servername;
		bool						_logged;
		bool						_isRegistered;
		std::string					_buffer;
		std::vector<Channel *>		_channels;
		
	public:
		Client();
		Client(std::string username, std::string nickname, int fd);
		Client(const Client &src);
		Client &operator=(const Client &src);
		~Client();

		// Getters

		int			getFd(void);
		std::string	getUsername(void);
		std::string	getNickname(void);
		std::string	getRealname(void);
		std::string	getHostname(void);
		std::string	getServername(void);
		bool		getLogged(void);
		std::string	getBuffer(void);
		bool		getRegistered(void);
		Channel		*getChannel(Channel *channel);
		
		// Setters
		void	setNickname(std::string &nickname);
		void	setUsername(std::string &username);
		void	setFd(int fd);
		void	setLogged(bool value);
		void	setBuffer(std::string &buffer);
		void	setRegistered(bool value);
		void	setRealName(std::string str);
		void	setHostname(std::string str);
		void	setServername(std::string str);

		// Checkers

		bool	NICK(std::string &str);
		bool	NAME(std::string &str);
		
		// Member functions
		void	addChannel(Channel *channel);
		void	rmChannel(std::string &channelName);
		void	freeBuffer(void);
};

#endif
