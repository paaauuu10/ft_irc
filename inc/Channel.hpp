/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:08:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/11/28 19:44:32 by anovio-c         ###   ########.fr       */
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
		std::unordered_set<Client *>	_clients;
		std::unordered_map<char, bool>	_modes;
	public:
		Channel(const std::string &channelName, Client *creator);
		~Channel();

		// Getters
		std::string	getName();

		// Setters

		// Of course is not the definitive function
		void	setMode(char mode, bool status, int value);
		
		// Methods
		bool	isEmtpy();
		void	leave(Client *client);

};