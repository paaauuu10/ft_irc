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

/*     Command: TOPIC
   Parameters: <channel> [<topic>]

   The TOPIC message is used to change or view the topic of a channel.
   The topic for channel <channel> is returned if there is no <topic>
   given.  If the <topic> parameter is present, the topic for that
   channel will be changed, if the channel modes permit this action.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
           RPL_NOTOPIC                     RPL_TOPIC
           ERR_CHANOPRIVSNEEDED



   Examples:

   :Wiz TOPIC #test :New topic     ;User Wiz setting the topic.

   TOPIC #test :another topic      ;set the topic on #test to "another
                                   topic".

   TOPIC #test                     ; check the topic for #test. */

void	TOPIC(Client *client, std::string &arg) {
	std::vector<std::string>	tokens = split(arg, ' ');
	
	if (tokens.empty() ||  tokens.size() > 2) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
		return ;
	}
	// canal bien escrito
	if (!tokens[0].empty() && tokens[0][0] != '#' && tokens[0][0] != '&') {
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
		return ;
	}
	// verificar canal
	Channel *channel = Server::getInstance().getCheckChannel(tokens[0]);
	if (!channel) {
		sendError(client, 403, "ERR_NOSUCHCHANNEL");
		return ;
	}
	// verificar si hay topic, si no hay tokens[1] mandar topic
	if (tokens.size() == 1)
		channel->RPLTOPIC(client);
	if (tokens.size() == 2) {
		if (channel->getTopic().empty() && channel->getMode('t') == false) {
			// Verifica si tokens[1] comienza con ':'
			if (!tokens[1].empty() && tokens[1][0] == ':') {
				channel->setTopic(tokens[1].substr(1));
			} else {
				sendError(client, 461, "ERR_NEEDMOREPARAMS - Topic must start with ':'");
			}
		} else {
			sendError(client, 482, "ERR_CHANOPRIVSNEEDED - You don't have permission to set the topic.");
		}
	}	
}