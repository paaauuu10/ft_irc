/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:47:10 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/30 15:37:57 by anovio-c         ###   ########.fr       */
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

void	nick(Client *client, std::string &nickname)
{
	//nickname = trim(nickname);
	std::cout << "--> " << nickname << std::endl;

	if (nickname.empty()) {
		sendError(client, 431, "ERR_NONICKNAMEGIVEN"); // ERR_NONICKNAMEGIVEN
		return;
	}
	
	if (validateNick(nickname)) {
		sendError(client, 432, "ERR_ERRONEUSNICKNAME"); //ERR_ERRONEUSNICKNAME
		return ;
	}
	
	if (!client->getNickname().empty() && nickname == client->getNickname()) {
		sendError(client, 436, "ERR_NICKCOLLISION", client->getNickname() + " " + nickname); // ERR_NICKCOLLISION
		return;
	}
	if (checkNickname(nickname)) {
		sendError(client, 433, "ERR_NICKNAMEINUSE", client->getNickname() + " " + nickname); // ERR_NICKNAMEINUSE
		return;
	}
	
	std::string str = "";
	if (client->getNickname().empty()) {
		str = "Introducing new nick \"" + nickname + "\"\n";
		send(client->getFd(), str.c_str(), str.size(), 0);
	} else {
		str = ":" + client->getNickname() + " NICK :" + nickname + "\n";	
		send(client->getFd(), str.c_str(), str.size(), 0);
	}
	client->setNickname(nickname);
	/*
	if (!client->getUsername().empty() && !client->getRegistered()) {	
		//client->setRegistered(true);
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
	}*/
}
