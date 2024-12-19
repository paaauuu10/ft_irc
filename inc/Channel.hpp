/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:08:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/19 12:08:29 by pborrull         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


class Client;
class Channel {
	private:
		std::string					_name;
		std::string					_key;
		std::string					_topic;
		int							_limit;
		std::vector<Client *>		_operatorClients;
		std::vector<Client *>		_clients;
		std::vector<std::string>	_clientsInvited;	
		std::map<char, bool>		_modes;
	public:
		Channel(void);
		Channel(const std::string &channelName, const std::string &key, Client *creator);
		~Channel();

		// Getters
		std::string	getName();
		bool		getMode(char key);
		std::string	getUserList();
  	std::string	getTopic();
		bool		getClientList(std::string nickname);
		bool		getOperatorList(std::string nickname);

		// Setters

		// Of course is not the definitive function
		void	setMode(char mode, bool status, int value);
		void	setKey(std::string str);
		void	setLimit(int limit);
		void	setTopic(const std::string &topic);
		
		// Methods
		
		bool	isKeyProtected();
		bool	checkKey(const std::string &key) const;
		bool	checkOperatorClient(Client *client);
		Client	*checkClient(std::string &nickname);
		bool	isEmtpy();
		bool	isFull();
		void	addOperatorClient(Client *client);
		void 	removeOperatorClient(Client *client); 
		void	addClient(Client *client);
		void	addClientsInvited(std::string client);
		void	rmClient(Client *client);
		std::vector<int>	listFdClients();
		void	broadcast(Client *client, std::string &msg);
		void	RPLTOPIC(Client *client);
		void	RPL_NAMREPLY(Client *client);

};

#endif
