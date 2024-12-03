 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:31:53 by pbotargu          #+#    #+#             */
/*   Updated: 2024/11/29 11:27:35 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <cctype> 

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:31:40 by anovio-c          #+#    #+#             */
/*   Updated: 2024/11/25 17:17:54 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Client {
	private:
		int							 _fd;
		std::string					_username;
		std::string 				_nickname; // nickname max 9 chars
		// See the protocol grammar rules for what may and may not be used in a nickname. 
		bool						_logged;
		bool						_isRegistered;
		std::string					_buffer;
		std::vector<std::string>	_channels;
		
	public:
		Client();
		Client(std::string username, std::string nickname, int fd);
		Client(const Client &src);
		Client &operator=(const Client &src);
		~Client();

		// Getters

		int			getFd(void);
		std::string	getUsername(void);
		std::string	getNickname(void);
		bool		getLogged(void);
		std::string	getBuffer(void);
		bool		getRegistered(void);
		bool		getChannel(std::string &channelName);
		// Setters

		bool	setNickname(std::string &nickname);
		bool	setUsername(std::string &username);
		void	setFd(int fd);
		void	setLogged(bool value);
		void	setBuffer(std::string &buffer);
		void	setRegistered(bool value);
		
		// Member functions
		void	addChannel(std::string &channelName);
		void	rmChannel(std::string &channelName);
		void	freeBuffer(void);
};


void pass(std::string pass, Client client)
{ 
    if (client.getRegistered())
    {
        std::cout << "Already registered" << std::endl;
    }
    if (pass != _pass) /*Modificar "HOLA" por la variable donde almacenemos la contraseña*/)

}



bool validCommand(std::string str)
{
    int index = 0;
    std::string commands[17] = { "PASS", "NICK", "USER", "SERVER", "OPER", "QUIT", "SQUIT", "JOIN", "PART", "MODE", "TOPIC", "NAMES", "LIST", "INVITE", "KICK", "VERSION", "PRIVMSG"};
    std::string cmd = str.substr(0, str.find(' '));
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) {
        return std::toupper(c);
    }); // Convert str into capital letters
    while (cmd != ('/' + commands[index++]))
    {
        if (index == 17)
            return false;
    }

    switch(index)
    {
        case 1:
            std::cout << commands[index - 1] << std::endl;
            //pass()
            break;
        case 2:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 3:
            std::cout << commands[index - 1] << std::endl;
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
            std::cout << commands[index - 1] << std::endl;
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
void parser(std::string str)
{
    if  (str.size() > 0 && str[0] == '/')
    {
        if (!validCommand(str))
            std::cout << str.erase(0,1) << " :Unknown command" << std::endl;
    }
    else
        std::cout << "Message send: " << str << std::endl;

}
int main(int argc, char **argv)
{
    (void)argc;
    Client *client;
    parser(argv[1]);
    pass(argv[2], *client);
}