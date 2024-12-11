/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:31:53 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/11 14:41:45 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static std::string cleanString(std::string& str) {
    std::string result;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != '\n' && str[i] != '\r') {
            result += str[i];
        }
    }
    return result;
}

bool validCommand(Client *client, std::string str)
{
    int index = 0;
    std::string commands[17] = { "PASS", "NICK", "USER", "SERVER", "OPER", "QUIT", "SQUIT", "JOIN", "PART", "MODE", "TOPIC", "NAMES", "LIST", "INVITE", "KICK", "VERSION", "PRIVMSG"};
    std::string cmd = str.substr(0, str.find(' '));
  /*  std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) {
        cmd = std::toupper(c);
    });*/ // Convert str into capital letters
	std::string	value = str.substr(cmd.size(), str.size() - cmd.size());
    value = cleanString(value);
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
            std::cout << commands[index - 1] << std::endl;
            //pass(client, value)
            break;
        case 2:
            std::cout << commands[index - 1] << std::endl;
			//NICK(client, value);
            break;
        case 3:
            //std::cout << commands[index - 1] << std::endl;
            //user(client, value);
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
			JOIN(client, value);
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
	std::cout << "FLAG PARSER INIT\n";
    if  (str.size() > 0)// && str[0] == '/')
    {
        if (!validCommand(client, str))
            std::cout << str.erase(0,1) << " :Unknown command" << std::endl;
    }
}

//void Server::parsingbuffer(char *buffer, Client *client)
//{
//	std::istringstream stream(buffer);
//    std::string line;
//
//	while (std::getline(stream, line))
//		parser(line, client);
//}
