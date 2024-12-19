/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:51:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/12/19 12:52:25 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "Utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"


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


void		INVITE(Client *client, std::string &invitation)
{
	std::vector<std::string> words = split(invitation, ' ');
	
	if (words.size() < 2)
	{
		sendError(client, 461, "Not enough parameters"); //ERR_NEEDMOREPARAMS
		return ;
	}
	Channel *channel = Server::getInstance().getCheckChannel(words[1]);
	if (!checkNickname(words[0]))
		sendError(client, 401, "No such nickname"); //ERR_NOSUCHNICK
	else if (!channel)
		sendError(client, 403, "No such channel"); //ERR_NOSUCHCHANNEL
	else if (channel->getClientList(words[0])) //Falta fer-la
		sendError(client, 443, "is already on channel <channel name>"); //ERR_USERONCHANNEL
	else if (!channel->getOperatorList(client->getNickname())) //&& i is true)
		sendError(client, 482, "You don't have channel operator privileges"); //ERR_CHANOPRIVSNEEDED
	else
	{
		channel->addClientsInvited(words[0]);
		std::cout << client->getNickname() << " is inviting you to " << channel->getName() << std::endl;
		//sendError(client, 341, "Client is inviting you to #<channel>");
	std::ostringstream oss;
    oss << channel->getName() << " " << words[0] << "\r\n";
    std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
	}
}
