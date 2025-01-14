/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:31:53 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/19 13:06:08 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* static	void	handleLoginAndRegistration(Client *client, const std::string &cmd) {
	
	if (!client->getLogged() && cmd != "/PASS") {
		sendError(client, 444, "ERR_NOLOGIN");
		return ;
	}

	if (!client->getRegistered() && client->getLogged() && cmd != "/PASS") {
		if (client->getNickname().empty()) {
			if (cmd != "/NICK") {
				sendError(client, 444, "ERR_NONICKNAMEGIVEN");
				return ;
			}
		}

		if (client->getUsername().empty()) {
			if (cmd != "/USER" && cmd != "/NICK") {
				sendError(client, 451, "ERR_NOTREGISTERED");
				return ;
			}
		}
	}
} */

static	bool	handleLoginAndRegistration(Client *client, const std::string &cmd) {
	
	if (client->getRegistered())
		return true;

	if (!client->getLogged() && cmd != "/PASS") {
		sendError(client, 444, "ERR_NOLOGIN");
		return false;
	}

	if ( client->getLogged() && !client->getRegistered() ) {// && cmd != "/PASS" && (cmd == "/NICK" || cmd == "/USER")) {
		if (cmd != "/NICK" && cmd != "/USER") {
        	sendError(client, 451, "ERR_NOTREGISTERED");
        	return false;
        }
	}
	//if (!client->getNickname().empty() && !client->getUsername().empty())
	//	client->setRegistered(true);
	return true;
}


//"SERVER", "OPER", "SQUIT", "NAMES", "LIST", "VERSION","PART",

static bool validCommand(Client *client, std::string &value, std::string &cmd)
{
	//if (client == NULL)
	//	return false;

	//if (!handleLoginAndRegistration(client, cmd))
	//	return true;
	
	typedef void (*cmdFunction)(Client *, std::string&);
    
	std::string commands[10] = { "PASS", "NICK", "USER", "JOIN", "MODE", "TOPIC", "INVITE", "KICK", "PRIVMSG"};//, "QUIT" };
	cmdFunction functions[10] = { pass, nick, user, join, mode, topic, invite, kick, privMsg};//, quit };
	
	// if (!client->getLogged() && cmd != "PASS") {
	// 	std::string server = Server::getInstance().getServerName();
	// 	std::string response = ":" + server + " 451 :You have not registered\r\n"; //ERR_NOTREGISTERED
	// 	send(client->getFd(), response.c_str(), response.size(), 0);
	// 	return true;
	// }

	int index = 0;
	for (; index < 10; ++index) {
		if (cmd == '/' + std::string(commands[index]))
			break;
	}

	if (index < 10) {
		functions[index](client, value);
		return true;
	} else
		return false;
}


void parser(Client *client, std::string str)
{
	if (!str.empty() && str[0] != '/')
		str = "/" + str;

	size_t tab = str.find('/');
	if (tab == std::string::npos)
		return;

	std::string cmd = str.substr(tab, str.find_first_of(" \t", tab) - tab);

	size_t value_start = str.find_first_not_of(" \t", tab + cmd.size());
	std::string value = (value_start == std::string::npos) ? "" : str.substr(value_start);
	value = trim(value);

	if (value.empty()) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
		return ;
	}
	if (!handleLoginAndRegistration(client, cmd))
		return ;

	// falta otro if
	if (!cmd.empty() && !validCommand(client, value, cmd)) {
		std::string response = cmd + " :Unknown command\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
}


void parsingbuffer(char *buffer, Client *client)
{
	std::istringstream	stream(buffer);
	static std::string line;
	std::string	temp;

	while (std::getline(stream, temp))
	{
		line += temp;
		temp.clear();
		if (stream.eof() && temp.empty())
			return ;

		if (line.find('\0') != std::string::npos)
			return ;

		if (line != "CAP LS 302\r")
			parser(client, trim(line));
		line.clear();
	}
}
