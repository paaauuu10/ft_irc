/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:56:19 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/22 19:25:49 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

/*
        ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
        RPL_NOTOPIC                     RPL_TOPIC
        ERR_CHANOPRIVSNEEDED

	Examples:

	:Wiz TOPIC #test :New topic     ;User Wiz setting the topic.

	TOPIC #test :another topic      ;set the topic on #test to "another topic".

   TOPIC #test                     ; check the topic for #test. */


static std::string	makeBroadcastMessage(Client *client, const std::string &channelName, std::string &topic) {
	
	std::ostringstream oss;
	
	// :<nickname>!<user>@<host> TOPIC <channel> :<topic>
    oss << ":" << client->getNickname() << "!" << client->getUsername()
        << "@" << "127.0.0.1" << " TOPIC " << channelName
		<< " :" << topic << "\r\n";

	return (oss.str());
}

void    topic(Client *client, std::string &arg) {

	std::cout << "ARG TOPIC: -" << arg << std::endl;
    size_t spacePos = arg.find(' ');
    std::string channelName = (spacePos == std::string::npos) ? arg : arg.substr(0, spacePos);
    std::string topic = (spacePos == std::string::npos) ? "" : arg.substr(spacePos + 1);

    if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&')) {
        sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid channel name");
        return ;
    }
	std::cout << "CHANNEL TOPIC: -" << channelName << std::endl;
    // verificar canal
    Channel *channel = Server::getInstance().getCheckChannel(channelName);
    if (!channel) {
        sendError(client, 403, "ERR_NOSUCHCHANNEL");
        return ;
    }

    if (topic.empty())
        channel->RPLTOPIC(client); //RPLTOPIC includes RPLNONTOPIC
    else {
        if (channel->getTopic().empty() && channel->getMode('t') && !channel->checkOperatorClient(client)) {
			sendError(client, 482, "ERR_CHANOPRIVSNEEDED - You don't have permission to set the topic.");
			return ;
		}

		if (topic[0] != ':') {
    		sendError(client, 461, "ERR_NEEDMOREPARAMS - Topic must start with ':'");
    		return;
		}
		
		channel->setTopic(topic.substr(1));
		std::string msg = makeBroadcastMessage(client, channelName, topic);
		channel->broadcast(client, msg);
    }   
}
