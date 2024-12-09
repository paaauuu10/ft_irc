/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:08:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:14:02 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class Client;
class Channel {
	private:
		std::string						_name;
		std::string						_key;
		std::string						_topic;
		int								_limit;
		std::set<Client *>	_operatorClients;
		std::set<Client *>	_clients;
		std::map<char, bool>	_modes;
	public:
		Channel(const std::string &channelName, const std::string &key, Client *creator);
		~Channel();

		// Getters
		std::string	getName();
		bool		getMode(char key);

		// Setters

		// Of course is not the definitive function
		void	setMode(char mode, bool status, int value);
		
		// Methods
		
		bool	isKeyProtected();
		bool	checkKey(const std::string &key) const;
		bool	isEmtpy();
		bool	isFull();
		void	addOperatorClient(Client *client);
		void	addClient(Client *client);
		void	rmClient(Client *client);
		std::vector<int>	listFdClients();

};

#endif
