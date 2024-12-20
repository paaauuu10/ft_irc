/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:56:19 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/19 12:36:48 by anovio-c         ###   ########.fr       */
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

void    topic(Client *client, std::string &arg) {

    std::string channelName;
    std::string topic;
    size_t      flag;

    topic = arg.substr(arg.find(':') + 1);
    flag = arg.find(' ');
    if (flag == arg.npos) {
        sendError(client, 461, "ERR_NEEDMOREPARAMS");
        return ;
    }
    channelName = arg.substr(0, flag - 1);

    if (!channelName.empty() && channelName[0] != '#' && channelName[0] != '&') {
        sendError(client, 461, "ERR_NEEDMOREPARAMS");
        return ;
    }
    // verificar canal
    Channel *channel = Server::getInstance().getCheckChannel(channelName);
    if (!channel) {
        sendError(client, 403, "ERR_NOSUCHCHANNEL");
        return ;
    }
    // verificar si hay topic, si no hay tokens[1] mandar topic
    if (topic.empty())
        channel->RPLTOPIC(client);
    else {
        if (channel->getTopic().empty() && channel->getMode('t') == false) {
            // Verifica si tokens[1] comienza con ':'
            if (topic[0] == ':') {
                channel->setTopic(topic.substr(1));
            } else {
                sendError(client, 461, "ERR_NEEDMOREPARAMS - Topic must start with ':'");
            }
        } else {
            sendError(client, 482, "ERR_CHANOPRIVSNEEDED - You don't have permission to set the topic.");
        }
    }   
}
