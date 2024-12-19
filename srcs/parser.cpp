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

static bool validCommand(Client *client, std::string str, std::string cmd)
{
	//"SERVER", "OPER""QUIT", "SQUIT", "NAMES", "LIST", "VERSION","PART",
    int index = 0;
    std::string commands[9] = { "PASS", "NICK", "USER", "JOIN", "MODE", "TOPIC", "INVITE", "KICK", "PRIVMSG"};
	if (!client->getLogged() && cmd != "PASS") {
		std::string server = Server::getInstance().getServerName();
		std::string response = ":" + server + " 451 :You have not registered\r\n"; //ERR_NOTREGISTERED
		send(client->getFd(), response.c_str(), response.size(), 0);
		return true;
	}
	if (client->getLogged() && cmd == "PASS") {
		sendError(client, 462, "You may not reregister"); //ERR_NEEDMOREPARAMS
		return true;
	}
	if (!client->getRegistered() && cmd != "USER" && cmd != "NICK" && client->getLogged()) {
		if (client->getUsername().empty())
			sendError(client, 1, "You need to use cmd USER <username> <hostname> <servername> <realname>");
		if (client->getNickname().empty())
			sendError(client, 1, "You need to use cmd NICK <nickname>");
		return true;
	}

	std::string	value = str.substr(cmd.size(), str.size() - cmd.size());
	while ((cmd != commands[index]) && cmd != ('/' + commands[index])) {
		index++;
		if (index == 9)
			return false;
	}
	index++;
	switch(index) {
		case 1:
			pass(client, value);
			break;
		case 2:
			nick(client, value);
			break;
		case 3:
			user(client, value);
			break;
		case 4:
			join(client, value);
			break;
		case 5:
			mode(client, value);
			break;
		case 6:
			topic(client, value);
			break;
		case 7:
			invite(client, value);
			break;
		case 8:
			kick(client, value);
			break;
		case 9:
			privMsg(client, value);
			break;
/* 		case 10:
			MODE(client, value);
			break; */
		//default:
		//	break ;
	}
	return true;
}
void parser(Client *client, std::string str)
{
	while (!str.empty() && ((str[str.size() - 1]) == '\n' || (str[str.size() - 1]) == '\r'))
		str.erase(str.size() -1);

    std::string cmd = str.substr(0, str.find(' '));
	std::string cmdUpper = cmd;
	
	for (size_t i = 0; i < cmd.length(); ++i)
		cmdUpper[i] = std::toupper(cmd[i]);
    if (str == "\r\n") // revisar aquesta guarrada: Si treiem aixo mostra :UNKNOWN COMMAND!
        return ;
    if  (str.size() > 0)// && str[0] == '/')
    {
        if (!validCommand(client, str, cmdUpper))
        {
            std::string response = cmd + " :Unknown command\r\n";
            send(client->getFd(), response.c_str(), response.size(), 0);
        }
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
			parser(client, line);
		line.clear();
	}
}
