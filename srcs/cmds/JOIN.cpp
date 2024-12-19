/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:55:32 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/17 10:27:33 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

//JOIN  <channel1>{,<channel2>} [<key1>{,<key2>}]

static bool isValidChannelName(std::string &name) {
	if (name[0] == '#' || name[0] == '&')
		return (true);
	return (false);
}

static std::string	makeBroadcastMessage(Client *client, std::string &channelName) {
	std::ostringstream oss;

    // Mensaje JOIN con el prefijo correcto
	// :<nickname>!<username>@<hostname> JOIN :<channelName>\r\n
    oss << ":" << client->getNickname() << "!" 
        << client->getUsername() << "@127.0.0.1 JOIN :" 
        << channelName << "\r\n";

	return (oss.str());
}

// default password == "default"
//          ERR_INVITEONLYCHAN
//		    ERR_TOOMANYCHANNELS

void	JOIN(Client *client, std::string& args) {
	if (args.empty())
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
	std::vector<std::string> tokens = split(args, ' ');
    std::vector<std::string> channels = split(tokens[0], ',');
    std::vector<std::string> keys = (tokens.size() > 1)
		? split(tokens[1], ',')
		: std::vector<std::string>();
	//the user must be invited if the channel is invite-only
	for (size_t i = 0; i < channels.size(); ++i) {
		std::string channelName = channels[i];
		std::string key = (i < keys.size()) ? keys[i] : "";
		
		if (!isValidChannelName(channelName)) {
			sendError(client, 403, "ERR_NOSUCHCHANNEL");
			continue ;
		}

		Channel *channel = Server::getInstance().getCheckChannel(channelName);
		
		if (!channel) {
			// channel constructor puts the creator client to operator client;
			channel = new Channel(channelName, key, client);
			Server::getInstance().addChannel(channel);
		} else {
			if (channel->isKeyProtected() && !channel->checkKey(key)) {
				sendError(client, 475, "ERR_BADCHANNELKEY"); // channelName
				continue ;
			}
			if (channel->isFull()) {
				sendError(client, 471, "ERR_CHANNELISFULL"); // channelName
				continue ;
			}
			channel->addClient(client);
		}
		std::string message = makeBroadcastMessage(client, channelName);
        channel->broadcast(client, message);
		channel->RPLTOPIC(client);
		channel->RPL_NAMREPLY(client);
		// enviar lista de comandos
	}
}
