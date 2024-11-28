/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:08:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/11/28 12:44:54 by anovio-c         ###   ########.fr       */
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
		std::unordered_set<Client *>	_client;
		std::unordered_map<char, bool>	_modes;
	public:
		Channel();
		Channel(const std::string &channelName, Client *creator);
		Channel(const Channel *src);
		Channel &operator=(const Channel *src);
		~Channel();

		

};