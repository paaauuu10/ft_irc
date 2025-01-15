/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:51:35 by pborrull          #+#    #+#             */
/*   Updated: 2025/01/14 12:30:31 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "Utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"

// CHECKnickname la he pasado a BOOL!!!

/*
static int checkNickname(std::string &nickname)
{
	
	std::vector<Client *>	vclient = Server::getInstance().getClients();
	for (long unsigned int i = 0; i < vclient.size(); i++)
	{
		if (vclient[i]->getNickname() == nickname)
			return 1;
	}
	return 0;
}

int checkChannel(std::string &nickname)
{
	
	Channel	*vchannel = Server::getInstance().getCheckChannel(nickname);
	if (vchannel)
		return 1;
	return 0;
}*/
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

void		invite(Client *client, std::string &invitation)
{

	// CHEQUEAR QUE NO SE INVITE AL MISMO CLIENTE QUE ENVIA LA PETICION DEL IVNITE
	
	std::vector<std::string> words = split(invitation, ' ');
	
	if (words.size() < 2) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS"); //ERR_NEEDMOREPARAMS
		return ;
	}
	Channel *channel = Server::getInstance().getCheckChannel(words[1]);
	if (!checkNickname(words[0]))
		sendError(client, 401, "ERR_NOSUCHNICK"); //ERR_NOSUCHNICK
	else if (!channel)
		sendError(client, 403, "ERR_NOSUCHCHANNEL"); //ERR_NOSUCHCHANNEL
	else if (channel->getClientList(words[0]))
		sendError(client, 443, "ERR_USERONCHANNEL"); //ERR_USERONCHANNEL
	else if (!channel->getOperatorList(client->getNickname())) //&& i is true)
		sendError(client, 482, "ERR_CHANOPRIVSNEEDED"); //ERR_CHANOPRIVSNEEDED
	else
	{
		channel->addClientsInvited(words[0]);
		Client *invited = Server::getInstance().getClientByNickname(words[0]);
		
		makeInviterMessage(client, channel->getName(), invited->getNickname());
		makeInvitedMessage(client, channel->getName(), invited);
	}
}
