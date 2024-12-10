/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:31:53 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/10 11:53:36 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool Server::validCommand(std::string str, Client *client)
{
	(void)client;
    int index = 0;
    std::string commands[17] = { "PASS", "NICK", "USER", "SERVER", "OPER", "QUIT", "SQUIT", "JOIN", "PART", "MODE", "TOPIC", "NAMES", "LIST", "INVITE", "KICK", "VERSION", "PRIVMSG"};
    std::string cmd = str.substr(0, str.find(' '));
  /*  std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) {
        return std::toupper(c);
    });*/ // Convert str into capital letters
    std::string rest = str.substr(str.find(' ') + 1); // Eliminar el salto de línea (si existe) al final
	if (!rest.empty() && ((rest[rest.size() - 1]) == '\n' || (rest[rest.size() - 1]) == '\r'))
		rest.erase(rest.size() -1);
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
            //std::cout << commands[index - 1] << std::endl;
			pass(rest, client);
            break;
        case 2:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 3:
            //std::cout << commands[index - 1] << std::endl;
            user(rest, client);
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
            invite(rest, client);
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
void Server::parser(std::string str, Client *client)
{
    if  (str.size() > 0)
	{
		std::string s = str.substr(0, str.find(' '));
		if (!validCommand(str, client))
            std::cout << s << " :Unknown command" << std::endl;
			//ha de ser SEND
    }
}

void Server::parsingbuffer(char *buffer, Client *client)
{
	std::istringstream stream(buffer);
    std::string line;

	while (std::getline(stream, line))
		parser(line, client);
}
