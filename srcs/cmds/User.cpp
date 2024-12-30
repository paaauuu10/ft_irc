/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:12:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/30 15:36:09 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Utils.hpp"

static bool	checkRealname(std::string &name) {
	if (name.empty() && name[0] == ':')
		return true;
	return false;
}

static bool checkServerName(std::string &name) {
	
	std::cout << "serv : -" << name << std::endl;
	std::string serverName = Server::getInstance().getServerName();

	if (name == "*") {
		name = serverName;
		return true;
	}
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
	if (username.empty())
		return false;

	std::vector<Client *>	vclient = Server::getInstance().getClients();
	for (size_t i = 0; i < vclient.size(); i++) {
		if (vclient[i]->getUsername() == username)
			return false;
	}
	return true;
}

/*    Since it is easy for a client to lie about its username by relying
   solely on the USER message, the use of an "Identity Server" is
   recommended.  If the host which a user connects from has such a
   server enabled the username is set to that as in the reply from the
   "Identity Server". */

void	user(Client *client, std::string &pass)
{
	if (!client->getLogged() || client->getNickname().empty())
		return ;

    std::vector<std::string> words = split(pass, ' ');
    if (words.size() < 4) {
		std::cerr << "USE: /USER <user> <hostname> <serverName> <realname>" << std::endl;
        return (sendError(client, 461, "ERR_NEEDMOREPARAMS"));
		
	}
    //username es unic? en cas que si cal revisar si ja existeix o no. Mirar si el client ja esta registrat?
    if (!checkUser(words[0])) {    
        sendError(client, 462, "ERR_ALREADYREGISTRED"); 
        return ;
    }
    client->setUsername(words[0]);
	
	if (!words[1].empty() && words[1][0] != '0' && !isValidIp(words[1])) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid ip");
        return ;
	}
    client->setHostname(words[1]);
	
	if (!words[2].empty() && !checkServerName(words[2])) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid server"); //revisar codi d'error  i missatge!!!    
        return ;
	}
	if (words[2][0] == ':')
    	client->setServername(words[2].substr(1));
	else
		client->setServername(words[2]);

		
	if (words[3].empty() && !checkRealname(words[3])) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid realname");  
        return ;
	}
    client->setRealName(words[3].substr(1));
	
	std::cout << "User " << client->getUsername() << " created!\n" << std::endl;

    if (!client->getNickname().empty() && !client->getRegistered()) {
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
