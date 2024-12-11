/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:55:32 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/10 18:14:00 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

//JOIN <channel1>{,<channel2>} [<key1>{,<key2>}]
// :irc.example.com 353 <nick> = <channel> :user1 user2 user3
// :irc.example.com 366 <nick> <channel> :End of /NAMES list

static bool isValidChannelName(std::string &name) {
	if (name[0] == '#' || name[0] == '&')
		return (true);
	return (false);
}

static void cleanStr(std::string &str) {
	if (str.back() == '\n')
		str.pop_back();
}

// default password == "default"
//          ERR_INVITEONLYCHAN             ERR_BADCHANMASK
//		    ERR_TOOMANYCHANNELS
//          RPL_TOPIC

void	JOIN(Client *client, std::string& args) {
	std::cout << args << "\n";
	cleanStr(args);
	std::cout << args << "\n";
	std::vector<std::string> tokens = split(args, ' ');
	std::cout << "FLAG 2\n";
    std::vector<std::string> channels = split(tokens[0], ',');
    std::vector<std::string> keys = (tokens.size() > 1)
		? split(tokens[1], ',')
		: std::vector<std::string>();
	std::cout << "FLAG 3\n";
	//the user must be invited if the channel is invite-only
	if (args.empty())
		sendError(client, 1, "ERR_NEEDMOREPARAMS");
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
		}
		std::cout << "CHANNEL =====" << channelName << "\n";
		if (channel->isKeyProtected() && !channel->checkKey(key))
			sendError(client, 475, "ERR_BADCHANNELKEY"); // channelName
		if (channel->isFull())
			sendError(client, 471, "ERR_CHANNELISFULL"); // channelName
		channel->addClient(client);
		
		//sendTopic
        //channel->broadcast(":" + client->getNick() + " JOIN :" + channelName);
        //send(client, 353, channelName, channel->getUserList());
        //send(client, 366, channelName, "End of /NAMES list");
	}
}
