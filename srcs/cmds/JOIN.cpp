/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:55:32 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/08 19:13:26 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
// #include "Client.hpp"
// #include "Utils.hpp"

//JOIN <channel1>{,<channel2>} [<key1>{,<key2>}]
// :irc.example.com 353 <nick> = <channel> :user1 user2 user3
// :irc.example.com 366 <nick> <channel> :End of /NAMES list


// 403 <channel> :No such channel: El canal especificado no existe.
// 475 <channel> :Cannot join channel (+k): El canal requiere una clave y la proporcionada es incorrecta.
// 471 <channel> :Cannot join channel (+l): El canal ha alcanzado su límite de usuarios.

static bool isValidChannelName(std::string &name) {
	if (name[0] == '#' || name[0] == '&')
		return (true);
	return (false);
}

// default password == "default"

void	JOIN(Client *client, const std::string& args) {
	std::vector<std::string> tokens = split(args, ' ');
    std::vector<std::string> channels = split(tokens[0], ',');
    std::vector<std::string> keys = (tokens.size() > 1)
		? split(tokens[1], ',')
		: std::vector<std::string>();
	
	for (size_t i = 0; i < channels.size(); ++i) {
		std::string channelName = channels[i];
		std::string key = (i < keys.size()) ? keys[i] : "";
		
		if (!isValidChannelName(channelName)) {
			sendError(client, 403, "No such channel");
			continue ;
		}
		
		Channel *channel = Server::getCheckChannel(channelName);
		
		if (!channel) {
			channel = new Channel(channelName, key, client);
		}
		if (channel->isKeyProtected() && !channel->checkKey(key))
			sendError(client, 475, "Cannot join channel (+k)"); // channelName
		if (channel->isFull())
			sendError(client, 471, "Cannot join channel (+l)"); // channelName
		channel->addClient(client);
        //channel->broadcast(":" + client->getNick() + " JOIN :" + channelName);
        //send(client, 353, channelName, channel->getUserList());
        //send(client, 366, channelName, "End of /NAMES list");
	}

}