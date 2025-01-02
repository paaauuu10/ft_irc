/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:12:30 by pbotargu          #+#    #+#             */
/*   Updated: 2025/01/02 19:19:51 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Utils.hpp"

static bool	checkRealname(std::string &name) {
	return !name.empty() && name[0] == ':';
}

static bool checkServerName(std::string &name) {

	std::string serverName = Server::getInstance().getServerName();

	if (name == "*") {
		name = serverName;
		return true;
	}
	return serverName == name;

}

/*static bool isValidIp(std::string &host) {

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
}*/

/*static bool checkUser(std::string &username)
{
	if (username.empty())
		return false;

	std::vector<Client *>	vclient = Server::getInstance().getClients();
	for (size_t i = 0; i < vclient.size(); i++) {
		if (vclient[i]->getUsername() == username)
			return false;
	}
	return true;
}*/

static bool isValidIp(const std::string &host) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, host.c_str(), &(sa.sin_addr)) != 0;
}

/*    Since it is easy for a client to lie about its username by relying
   solely on the USER message, the use of an "Identity Server" is
   recommended.  If the host which a user connects from has such a
   server enabled the username is set to that as in the reply from the
   "Identity Server". */

void	user(Client *client, std::string &args)
{
	if (client->getRegistered()) {
		sendError(client, 462, "ERR_ALREADYREGISTRED");
        return;
	}
	
	if (!client->getLogged() || client->getNickname().empty())
		return ;

    std::vector<std::string> tokens = split(args, ' ');
    if (tokens.size() < 4) {
		std::cerr << "USE: /USER <user> <hostname> <serverName> <realname>" << std::endl;
        sendError(client, 461, "ERR_NEEDMOREPARAMS");
		return ;
	}

	std::string username = tokens[0];
	std::string hostname = tokens[1];
	std::string servername = tokens[2];
	std::string realname = tokens[3];

	if (!isValidIp(hostname)) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid ip");
        return ;
	}
	
	if (!checkServerName(servername)) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid server");
        return ;
	}
	
	if (!checkRealname(realname)) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid realname");
        return ;
	}

    client->setUsername(username); // lo unico que no se puede repetir es nickname
    client->setHostname(hostname);
	client->setServername(servername);
    client->setRealName(realname);
	client->setRegistered(true);
	
	std::cout << "User " << client->getUsername() << " created!\n" << std::endl;

    std::ostringstream oss;
    oss << ":" << Server::getInstance().getServerName()
		<< " 001 " << client->getNickname() << " :Welcome to the IRC network, "
		<< client->getNickname() << "!" << client->getUsername() << "@"
		<< client->getHostname() << "\r\n";
    std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
    //send(client->getFd(), pikachu_art.c_str(), pikachu_art.size(), 0);
}
