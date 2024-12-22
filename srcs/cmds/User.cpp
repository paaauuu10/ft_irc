/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:12:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/22 18:54:27 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Utils.hpp"

static bool checkServerName(std::string &name) {
	
	std::cout << "serv : -" << name << std::endl;
	std::string serverName = Server::getInstance().getServerName();

	if (name == "*")
		return true;
	if (serverName == name)
		return true;
	return false;
}

static bool isValidIp(std::string &host) {

	std::vector<std::string>	tokens = split(host, '.');

	if (tokens.size() != 4)
		return false;
	
	for (size_t i = 0; i < tokens.size(); ++i) {
		const std::string &part = tokens[i];

		if (part.empty())
			return false;
		
		for (size_t j = 0; j < part.size(); ++j) {
			if (!std::isdigit(part[j]))
				return false;
		}
		
		if (part.size() > 1 && part[0] == '0')
			return false;
		
		long value = std::strtol(part.c_str(), NULL, 10);
		if (value < 0 || value > 255)
			return false;
	}
	return true;
}

static bool checkUser(std::string &username)
{
	std::vector<Client *>	vclient = Server::getInstance().getClients();
	for (long unsigned int i = 0; i < vclient.size(); i++)
	{
		if (vclient[i]->getUsername() == username)
			return false;
	}
	return true;
}

void	user(Client *client, std::string &pass)
{
    // if (checkerIsLogged(client) == false)
    //     return ;
	if (!client->getLogged() || client->getNickname().empty())
		return ;
    std::vector<std::string> words = split(pass, ' ');
    if (words.size() < 4)
        return (sendError(client, 461, "Not enought parameters. \n/USER <user> <hostname> <serverName> <realname> ")); //revisar codi d'error  i missatge!!!    
    //username es unic? en cas que si cal revisar si ja existeix o no. Mirar si el client ja esta registrat?
    if (!checkUser(words[0])) {    
        sendError(client, 433, "This username already exists!"); //revisar codi d'error  i missatge!!!    
        return ;
    }
    // <username> <hostname> <servername> <realname>
    if (client->getNickname().empty()) {
        sendError(client, 461, "ERR_NEEDMOREPARAMS - Nickname required"); //revisar codi d'error  i missatge!!!    
        return ;
    }
    client->setUsername(words[0]);
	if (!words[1].empty() && words[1][0] != '0' && !isValidIp(words[1])) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid ip"); //revisar codi d'error  i missatge!!!    
        return ;
	}
    client->setHostname(words[1]);
	if (!words[2].empty() && !checkServerName(words[2])) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid server"); //revisar codi d'error  i missatge!!!    
        return ;
	}
    client->setServername(words[2]); // hacer funcion que chequee que sea el mismo nombre del server y quitarle los ':'
    client->setRealName(words[3]);
	std::string response = "User created!\r\n";
    send(client->getFd(), response.c_str(), response.size(), 0);
    if (!client->getNickname().empty() && !client->getRegistered())
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
