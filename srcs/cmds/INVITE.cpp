/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:51:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/12/13 18:01:07 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"


#include <string>
#include <iostream>
#include <vector>

void		INVITE(Client *client, std::string &invitation)
{
	std::vector<std::string> words = split(invitation, ' ');
	
	if (words.size() < 2)
	{
		sendError(client, 461, "Not enough parameters"); //ERR_NEEDMOREPARAMS
		return ;
	}
	//Channel *channel = Server::getInstance().getCheckChannel(words[1]);
	if (!checkNickname(words[0])) //Falta fer-la
		sendError(client, 401, "No such nickname"); //ERR_NOSUCHNICK
	/*else if (!channel)
		sendError(client, 403, "No such channel"); //ERR_NOSUCHCHANNEL*/
	/*else if (!isOnChannel()) //Falta fer-la
		std::cout << "is already on channel" << channel.getName() << std::endl;
		//sendError(client, 443, "is already on channel <channel name>"); //ERR_USERONCHANNEL
	else if (!isOperator(client))
		std::cout << "You don't have channel operator privileges" << std::endl;
		//sendError(client, 482, "You don't have channel operator privileges"); //ERR_CHANOPRIVSNEEDED
	else if (!isAway(client))
		std::cout << "I'm away, please try later" << std::endl;
		//sendError(client, 301, "I'm away, please try later"); //
	else
		std::cout << client.getNickname() << " is inviting you to #" << channel.getName << std::endl;
		//sendError(client, 341, "Client is inviting you to #<channel>"); //*/
}
