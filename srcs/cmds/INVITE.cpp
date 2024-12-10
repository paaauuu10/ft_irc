/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:51:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/12/05 14:25:13 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
*/

#include <string>
#include <iostream>

int		INVITE(Client *client, Channel *channel)
{
	if (client.empty() || channel.empty())
		std::cout << "Not enough parameters" << std::endl;
		//sendError(client, 461, "Not enough parameters"); //ERR_NEEDMOREPARAMS
	else if (!nickExist()) //Falta fer-la
		std::cout << "No such nickname" << std::endl;
		//sendError(client, 401, "No such nickname"); //ERR_NOSUCHNICK
	else if (!channelExist(channel))
		std::cout << "No such channel" << std::endl;
		//sendError(client, 403, "No such channel); //ERR_NOSUCHCHANNEL
	else if (!isOnChannel()) //Falta fer-la
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
		//sendError(client, 341, "Client is inviting you to #<channel>"); //
	return 0;
}
