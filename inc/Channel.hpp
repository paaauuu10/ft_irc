/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:08:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/03 09:18:56 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include <unordered_set>
#include <unordered_map>

class Client;
class Channel {
	private:
		std::string						_name;
		Client *						_operatorClient;
		std::string						_key;
		int								_limit;
		std::unordered_set<Client *>	_clients;
		std::unordered_map<char, bool>	_modes;
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
		bool	isEmtpy();
		void	leave(Client *client);

};
