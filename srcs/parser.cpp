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

static	void	handleLoginAndRegistration(Client *client, const std::string &cmd) {
	
	if (!client->getLogged() && cmd != "PASS") {
		sendError(client, 444, "ERR_NOLOGIN"); //ERR_NEEDMOREPARAMS
		return ;
	}

	if (!client->getRegistered() && client->getLogged()) {
		if (client->getNickname().empty()) {
			if (cmd != "NICK") {
				sendError(client, 444, "ERR_NONICKNAMEGIVEN 1");
				return ;
			}
		}

		if (client->getUsername().empty()) {
			if (cmd != "USER" && cmd != "NICK") {
				sendError(client, 1, "You need to use cmd /USER");
				return ;
			}
		}
	}
}


//"SERVER", "OPER""QUIT", "SQUIT", "NAMES", "LIST", "VERSION","PART",

static bool validCommand(Client *client, std::string &value, std::string &cmd)
{
	handleLoginAndRegistration(client, cmd);
	
	typedef void (*cmdFunction)(Client *, std::string&);
    
	std::string commands[9] = { "PASS", "NICK", "USER", "JOIN", "MODE", "TOPIC", "INVITE", "KICK", "PRIVMSG" };//, "SEND"};
	cmdFunction functions[9] = { pass, nick, user, join, mode, topic, invite, kick, privMsg }; //, sendFile };
	
	// if (!client->getLogged() && cmd != "PASS") {
	// 	std::string server = Server::getInstance().getServerName();
	// 	std::string response = ":" + server + " 451 :You have not registered\r\n"; //ERR_NOTREGISTERED
	// 	send(client->getFd(), response.c_str(), response.size(), 0);
	// 	return true;
	// }

	int index = 0;
	for (; index < 9; ++index) { //('/' + commands[index])) {
		if (cmd == commands[index])
			break;
	}

	if (index < 9) {
		functions[index](client, value);
		return true;
	} else
		return false;
}


void parser(Client *client, std::string str)
{
	if (!str.empty() && str[0] == '/')
		str = str.substr(1);
	std::cout << "STR BEFORE: -" << str << std::endl;
	while (!str.empty() && (str[str.size() - 1] == '\n' || str[str.size() - 1] == '\r'))
		str.erase(str.size() - 1);

	std::cout << "STR AFTER: -" << str << std::endl;

    std::string::size_type pos = str.find_first_of(" \t");
	std::string cmd = (pos == std::string::npos) ? str : str.substr(0, pos);

	std::cout << "cmd AFTER: -" << cmd << std::endl;

	//if (str == "\r\n") // revisar aquesta guarrada: Si treiem aixo mostra :UNKNOWN COMMAND!
    //    return ;

	//std::string cmdUpper = cmd;
	//for (size_t i = 0; i < cmd.length(); ++i)
	//	cmdUpper[i] = std::toupper(cmd[i]);

	std::string value = (pos == std::string::npos) ? "" : str.substr(pos + 1);
	value = trim(value);
    
	std::cout << "VALUE AFTER22: -" << value << std::endl;
    if (!str.empty()) {// && str[0] == '/') {
        if (!validCommand(client, value, cmd)) {
            std::string response = cmd + " :Unknown command\r\n";
            send(client->getFd(), response.c_str(), response.size(), 0);
        }
    }
}

void parsingbuffer(char *buffer, Client *client)
{
	std::istringstream	stream(buffer);
	//static std::string line;
	std::string	temp;

	while (std::getline(stream, temp))
		parser(client, temp);
	// {
	// 	line += temp;
	// 	temp.clear();
	// 	if (stream.eof() && temp.empty())
	// 		return ;
	// 	if (line.find('\0') != std::string::npos)
	// 		return ;

	// 	if (line != "CAP LS 302\r")
	// 		parser(client, line);
	// 	line.clear();
	// }
}
