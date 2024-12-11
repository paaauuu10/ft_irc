/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:47:10 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/11 14:09:45 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include <string>
#include <iostream>
#include <set>

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

static int validateNick(std::string &nick)
{
	if (nick.size() > 9 || (nick[0] >= '0' && nick[0] <= '9') || nick[0] == '-')
		return 1;
	
	const char validCharArray[] = {'-', '[', ']', '\\', '^', '_', '{', '}', '|'};
	const std::set<char> validChar(validCharArray, validCharArray + sizeof(validCharArray) / sizeof(char));

	for (size_t i = 0; i < nick.size(); ++i)
	{
		if ((validChar.find(nick[i]) == validChar.end()) && (nick[i] < '0' || nick[i] > '9')
	   	 && (nick[i] < 'a' || nick[i] > 'z') && (nick[i] < 'A' || nick[i] > 'Z'))
			return 1;
    }
	return 0;
}

void	NICK(Client *client, std::string &nickname)
{
	while(nickname[0] == ' ')
		nickname.erase(0, 1);
	if (nickname.empty())	
		sendError(client, 431, "No nickname given", client->getNickname()); //ERR_NONICKNAMEGIVEN
	else if (validateNick(nickname))
		sendError(client, 432, "Erroneous nickname", client->getNickname()); //ERR_ERRONEUSNICKNAME
	else if (!client->getNickname().empty() && nickname == client->getNickname())
		sendError(client, 436, "Nickname collision KILL", client->getNickname()); //ERR_NICKCOLLISION
	else if (checkNickname(nickname))
		sendError(client, 433, "Nickname is already in use", client->getNickname()); //ERR_NICKNAMEINUSE
	else
	{
		std::string str = "";
		if (client->getNickname().empty())
		{
			str = "Introducing new nick \"" + nickname + "\"\n";
			send(client->getFd(), str.c_str(), str.size(), 0);
		}
		else
			str = client->getNickname() + " changed his nickname to " + nickname + ".\n";	
			send(client->getFd(), str.c_str(), str.size(), 0);
		}
		client->setNickname(nickname);
	}
}
