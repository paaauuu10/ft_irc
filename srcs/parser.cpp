/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pbotargu <pbotargu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/25 10:31:53 by pbotargu		  #+#	#+#			 */
/*   Updated: 2024/12/12 13:10:18 by pborrull         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "Server.hpp"

bool validCommand(Client *client, std::string str)
{
	int index = 0;
	std::string commands[17] = { "PASS", "NICK", "USER", "SERVER", "OPER", "QUIT", "SQUIT", "JOIN", "PART", "MODE", "TOPIC", "NAMES", "LIST", "INVITE", "KICK", "VERSION", "PRIVMSG"};
	std::string cmd = str.substr(0, str.find(' '));
  /*  std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) {
		cmd = std::toupper(c);
	});*/ // Convert str into capital letters

	if (!client->getLogged() && cmd != "PASS")
	{	
		sendError(client, 1, "No logged, put the password PASS <password>");
		return 0;
	}
//	if (!client->getRegistered() && cmd != "USER" && cmd != "NICK")
//		sendError(client, 1, "No registered");


	std::string	value = str.substr(cmd.size(), str.size() - cmd.size());
	while (!value.empty() && ((value[value.size() - 1]) == '\n' || (value[value.size() - 1]) == '\r'))
	{
		value.erase(value.size() -1);
	}
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
			std::cout << commands[index - 1] << std::endl;
			//JOIN(client, value);
			break;
		case 9:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 10:
			std::cout << commands[index - 1] << std::endl;
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
			//std::cout << commands[index - 1] << std::endl;
			//invite(client, value);
			break;
		case 15:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 16:
			std::cout << commands[index - 1] << std::endl;
			break;
		case 17:
			std::cout << commands[index - 1] << std::endl;
			break;
	}
	return true;
}
void parser(Client *client, std::string str)
{
	//std::cout << "FLAG PARSER INIT\n";
	if  (str.size() > 0)// && str[0] == '/')
	{
		if (!validCommand(client, str))
			std::cout << str.erase(0,1) << " :Unknown command" << std::endl;
	}
}

void parsingbuffer(char *buffer, Client *client)
{
	std::istringstream stream(buffer);
	std::string line;

	while (std::getline(stream, line))
	{
		if (line != "CAP LS 302\r")
			parser(client, line);
	}
}
