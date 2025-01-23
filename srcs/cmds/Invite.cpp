/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:51:35 by pborrull          #+#    #+#             */
/*   Updated: 2025/01/23 10:55:09 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "Utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "ErrorCodes.hpp"

static void makeInviterMessage(Client* client, const std::string &channelName, const std::string &invitedName) {

	// :servername 341 Inviter invited channelname
	
    std::string serverName = Server::getServerName();

    std::ostringstream oss;
    oss << ":" << serverName << " " << 341
		<< " " << client->getNickname()
		<< " " << invitedName << " "
		<< channelName << "\r\n";
		
	std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
}

static void	makeInvitedMessage(Client *client, std::string channelName, Client *invited) {

	// :invitador!user@host INVITE invitado canal\r\n
	
	std::ostringstream oss;

    oss << ":" << client->getNickname() << "!" 
        << client->getUsername() << "@" << client->getHostname() << " INVITE " << invited->getNickname() << " " << channelName << "\r\n";

	std::string msg = oss.str();
    send(invited->getFd(), msg.c_str(), msg.size(), 0);
}

void	invite(Client *client, std::string &invitation)
{
	std::vector<std::string> words = split(invitation, ' ');
	
	if (words.size() < 2) {
		sendError(client, ERR_NEEDMOREPARAMS);
		return ;
	}
	std::string invited = words[0];
	std::string	inviter = client->getNickname();
	std::string channelName = words[1];
	
	Channel *channel = Server::getInstance().getCheckChannel(channelName);
	if (!checkNickname(words[0]))
		sendError(client, ERR_NOSUCHNICK, invited);
	else if (!channel)
		sendError(client, ERR_NOSUCHCHANNEL, inviter + " " + channelName);
	else if (channel->getClientList(invited))
		sendError(client, ERR_USERONCHANNEL, client->getNickname() + " " + invited + " " + channelName);
	else if (!channel->getOperatorList(client->getNickname()))
		sendError(client, ERR_CHANOPRIVSNEEDED, channelName);
	else {
		channel->addClientsInvited(invited);
		Client *invited = Server::getInstance().getClientByNickname(words[0]);
		
		makeInviterMessage(client, channel->getName(), invited->getNickname());
		makeInvitedMessage(client, channel->getName(), invited);
	}
}
