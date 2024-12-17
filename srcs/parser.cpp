/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:31:53 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/17 10:27:13 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool validCommand(Client *client, std::string str, std::string cmd)
{
    int index = 0;
    std::string commands[17] = { "PASS", "NICK", "USER", "SERVER", "OPER", "QUIT", "SQUIT", "JOIN", "PART", "MODE", "TOPIC", "NAMES", "LIST", "INVITE", "KICK", "VERSION", "PRIVMSG"};
   	if (!client->getLogged() && cmd != "PASS")
	{	
		sendError(client, 1, "No logged, put the password PASS <password>");
		return true;
	}
	if (!client->getRegistered() && cmd != "USER" && cmd != "NICK" && client->getLogged())
	{
		if (client->getUsername().empty())
			sendError(client, 1, "You need to use cmd USER <username> <hostname> <servername> <realname>");
		if (client->getNickname().empty())
			sendError(client, 1, "You need to use cmd NICK <nickname>");
		return true;
	}

	std::string	value = str.substr(cmd.size(), str.size() - cmd.size());
	while ((cmd != commands[index]) && cmd != ('/' + commands[index]))
	{
		index++;
		if (index == 17)
			return false;
	}
	index++;
	switch(index)
	{
		case 1:
			PASS(client, value);
			break;
		case 2:
			NICK(client, value);
			break;
		case 3:
			USER(client, value);
			break;
		case 4:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 5:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 6:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 7:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 8:
			JOIN(client, value);
			break;
		case 9:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 10:
			MODE(client, value);
			break;
		case 11:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 12:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 13:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 14:
			INVITE(client, value);
			break;
		case 15:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 16:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 17:
			PRIVMSG(client, value);
			std::cout << commands[index - 1] << std::endl;
			break;
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
