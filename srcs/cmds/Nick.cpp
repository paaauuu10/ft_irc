/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:47:10 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/20 22:12:46 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include <string>
#include <iostream>
#include <set>

int checkNickname(std::string &nickname)
{
	std::vector<Client *>	vclient = Server::getInstance().getClients();
	for (long unsigned int i = 0; i < vclient.size(); i++)
	{
		if (vclient[i]->getNickname() == nickname)
			return 1;
	}
	return 0;
}

static bool validateNick(std::string &nick)
{
	if (nick.size() >= 9 || (nick[0] >= '0' && nick[0] <= '9') || nick[0] == '-')
		return false;
	
	const char validCharArray[] = {'-', '[', ']', '\\', '^', '_', '{', '}', '|'};
	const std::set<char> validChar(validCharArray, validCharArray + sizeof(validCharArray) / sizeof(char));

	for (size_t i = 0; i < nick.size(); ++i)
	{
		if ((validChar.find(nick[i]) == validChar.end()) && (nick[i] < '0' || nick[i] > '9')
			&& (nick[i] < 'a' || nick[i] > 'z') && (nick[i] < 'A' || nick[i] > 'Z'))
			return false;
    }
	return true;
}

void	nick(Client *client, std::string &nickname)
{
	std::cout << "--> " << nickname << std::endl;
	
	if (nickname.empty())
		return (sendError(client, 431, "ERR_NONICKNAMEGIVEN", client->getNickname()));
		
	if (nickname.find(' ') != std::string::npos)
		return (sendError(client, 432, "ERR_ERRONEUSNICKNAME"));
	
	if (!validateNick(nickname))
		return (sendError(client, 432, "ERR_ERRONEUSNICKNAME", client->getNickname() + " " + nickname)); //ERR_ERRONEUSNICKNAME
	
	if (!client->getNickname().empty() && nickname == client->getNickname())
		return (sendError(client, 436, "Nickname collision KILL", client->getNickname() + " " + nickname)); //ERR_NICKCOLLISION
	
	if (checkNickname(nickname))
		sendError(client, 433, "Nickname is already in use", client->getNickname() + " " + nickname); //ERR_NICKNAMEINUSE
	else
	{
		std::string str = "";
		if (client->getNickname().empty())
		{
			str = "Introducing new nick \"" + nickname + "\"\n";
			send(client->getFd(), str.c_str(), str.size(), 0);
		}
		else
		{
			str = ":" + client->getNickname() + " NICK :" + nickname + "\n";	
			send(client->getFd(), str.c_str(), str.size(), 0);
		}
		client->setNickname(nickname);
		if (!client->getUsername().empty() && !client->getRegistered())
		{	
			client->setRegistered(true);
			std::string response = "Welcome to FT_IRC!!!!\r\n";
			std::string pikachu_art = 
			"quu..__\n"
			" $$$b  `---.__\n"
			"  \"$b        `--.                          ___.---uuudP\n"
			"   `$$b           `.__.------.__     __.---'      $$$$\"              .\n"
			"     \"$b          -'            `-.-'            $$$\"              .'|\n"
			"       \".                                       d$\"             _.'  |\n"
			"         `.   /                              ...\"             .'     |\n"
			"           `./                           ..::-'            _.'       |\n"
			"            /                         .:::-'            .-'         .'\n"
			"           :                          ::''\\          _.'            |\n"
			"          .' .-.             .-.           `.      .'               |\n"
			"          : /'$$|           .@\"$\\           `.   .'              _.-'\n"
			"         .'|$u$$|          |$$,$$|           |  <            _.-'\n"
			"         | `:$$:'          :$$$$$:           `.  `.       .-'\n"
			"         :                  `\"--'             |    `-.     \\\n"
			"        :##.       ==             .###.       `.      `.    `\\\n"
			"        |##:                      :###:        |        >     >\n"
			"        |#'     `..'`..'          `###'        x:      /     /\n"
			"         \\                                   xXX|     /    ./\n"
			"          \\                                xXXX'|    /   ./\n"
			"          /`-.                                  `.  /   /\n"
			"         :    `-  ...........,                   | /  .'\n"
			"         |         ``:::::::'       .            |<    `.\n"
			"         |             ```          |           x| \\ `.:``.\n"
			"         |                         .'    /'   xXX|  `:`M`M':.\n"
			"         |    |                    ;    /:' xXXX'|  -'MMMMM:'\n"
			"         `.  .'                   :    /:'       |-'MMMM.-'\n"
			"          |  |                   .'   /'        .'MMM.-'\n"
			"          `'`'                   :  ,'          |MMM<\n"
			"            |                     `'            |tbap\\\n"
			"             \\                                  :MM.-'\n"
			"              \\                 |              .''\n"
			"               \\.               `.            /\n"
			"                /     .:::::::.. :           /\n"
			"               |     .:::::::::::`.         /\n"
			"               |   .:::------------\\       /\n"
			"              /   .''               >::'  /\n"
			"              `',:                 :    .'\n"
			"                                   `:.:' \n";
			send(client->getFd(), response.c_str(), response.size(), 0);
			//send(client->getFd(), pikachu_art.c_str(), pikachu_art.size(), 0);
		}
	}
}
