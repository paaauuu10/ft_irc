/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:31:40 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/07 20:31:24 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"

class Channel;
class Client {
	private:
		int							 _fd;
		std::string					_username;
		std::string 				_nickname; // nickname max 9 chars
		// See the protocol grammar rules for what may and may not be used in a nickname. 
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

		// Checkers

		bool	NICK(std::string &str);
		bool	NAME(std::string &str);
		
		// Member functions
		void	addChannel(Channel *channelName);
		void	rmChannel(std::string &channelName);
		void	freeBuffer(void);
};
