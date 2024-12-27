/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:43:49 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/25 20:40:51 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

void	quit(Client *client, std::string &message) {
	std::string	response = ":" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + " QUIT :" + message + "\r\n";
	std::vector<Channel *> channels = client->getChannels();

	for (size_t i = 0; i < channels.size(); ++i) {
		channels[i]->broadcast(client, response);
		channels[i]->rmClient(client);
	}
	client->disconnect();
}
