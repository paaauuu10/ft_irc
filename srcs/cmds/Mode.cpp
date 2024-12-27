/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:22:51 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/27 12:39:25 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include <vector>
#include <string>
#include <iostream>

void handleModeI(Channel *channel, Client *client, char s) {
    std::string response = client->getNickname() + (s == '-' ? " disables " : " enables ") + "i mode in " + channel->getName() + "'s channel\n";
    channel->setMode('i', s == '+', 0);
    send(client->getFd(), response.c_str(), response.size(), 0);
}

void handleModeT(Channel *channel, Client *client, char s) {
    std::string response = client->getNickname() + (s == '-' ? " disables " : " enables ") + "t mode in " + channel->getName() + "'s channel\n";
    channel->setMode('t', s == '+', 0);
    send(client->getFd(), response.c_str(), response.size(), 0);
}

void handleModeK(Channel *channel, Client *client, char s, std::string key) {
    key = trim(key);
	std::string response = client->getNickname() + (s == '-' ? " disables " : " enables ") + "k mode in " + channel->getName() + "'s channel\n";
    channel->setMode('k', s == '+', 0);
    if (s == '-')
        channel->setKey("");
	else
        channel->setKey(key);
		
    send(client->getFd(), response.c_str(), response.size(), 0);
}

void handleModeO(Channel *channel, Client *client, char s, std::string nickname) {
	nickname = trim(nickname);
    Client *clientO = Server::getInstance().getClientByNickname(nickname);
    if (!clientO) {
        sendError(client, 442, "They aren't on that channel", nickname); // ERR_NOTONCHANNEL
        return;
    }
    std::string response = client->getNickname() + (s == '-' ? " removes " : " grants ") + "operator status to " + nickname + " in " + channel->getName() + "'s channel\n";
    // chequear si el operator ya esta 
	if (s == '-') {
        channel->removeOperatorClient(clientO);
    } else {
		// revisar si ya es cliente 
        channel->addOperatorClient(clientO);
    }
    send(client->getFd(), response.c_str(), response.size(), 0);
}

void handleModeL(Channel *channel, Client *client, char s, std::string limitStr) {
    limitStr = trim(limitStr);
    int limit = 0;

    std::stringstream ss(limitStr);
    if (!(ss >> limit) || limit <= 0) {
        sendError(client, 461, "ERR_NEEDMOREPARAMS - Invalid limit value");
        return;
    }

    std::string response = client->getNickname() + (s == '-' ? " disables " : " enables ") + "l mode in " + channel->getName() + "'s channel\n";
    channel->setMode('l', s == '+', 0);
    if (s == '+') {
        channel->setLimit(limit);
    }
    send(client->getFd(), response.c_str(), response.size(), 0);
}

void mode(Client *client, std::string &str)
{
    std::vector<std::string> words = split(str, ' ');
    if (words.size() < 1) {
        sendError(client, 461, "ERR_NEEDMOREPARAMS - Not enough parameters");
        return;
    }

    Channel *channel = Server::getInstance().getCheckChannel(words[0]);
    if (!channel) {
        sendError(client, 403, "ERR_NOSUCHCHANNEL - Unknown channel", words[0]);
        return;
    }

    if (!channel->checkOperatorClient(client)) {
        sendError(client, 482, "ERR_CHANOPRIVSNEEDED - You are not an operator", words[0]);
        return;
    }

    if (words.size() < 2) {
        sendError(client, 461, "ERR_NEEDMOREPARAMS - Not enough parameters");
        return;
    }
    char s = '+';
    for (size_t i = 0; i < words[1].size(); ++i) {
        while (words[1][i] == '+' || words[1][i] == '-') {
            s = words[1][i++];
        }

        switch (words[1][i]) {
            case 'i':
                handleModeI(channel, client, s);
                break;
            case 't':
                handleModeT(channel, client, s);
                break;
            case 'k':
                if (words.size() < 3) {
                    sendError(client, 461, "ERR_NEEDMOREPARAMS - Not enough parameters for k mode");
                    return;
                }
                handleModeK(channel, client, s, words[2]);
                break;
            case 'o':
                if (words.size() < 3) {
                    sendError(client, 461, "ERR_NEEDMOREPARAMS - Not enough parameters for o mode");
                    return;
                }
                handleModeO(channel, client, s, words[2]);
                break;
            case 'l':
                if (s == '+' && words.size() < 3) {
                    sendError(client, 461, "ERR_NEEDMOREPARAMS - Not enough parameters for l mode");
                    return;
                }
                handleModeL(channel, client, s, trim(words[2]));
                break;
            default:
                sendError(client, 472, "ERR_UNKNOWNMODE - Unknown mode character", std::string(1, words[1][i]));
                break;
        }
    }
}

/*void	mode(Client *client, std::string &str)
{
    //S'ha de mirar si es un operador abans de continuar. Si no return ; i ciao! NO borrar comentari!
    std::vector<std::string> words = split(str, ' ');
    if (words.size() < 1) {
        sendError(client, 461, "ERR_NEEDMOREPARAMS - Not enough parameters");
        return;
    }
	
	Channel *channel = Server::getInstance().getCheckChannel(words[0]);
    if (!channel)
        return (sendError(client, 461, "Unknown channel", words[0])); //revisar el missatge i el codi, ara estan a boleo
    
	if (!channel->getOperatorList(client->getNickname())) //revisar el missatge i el codi, ara estan a boleo
        return (sendError(client, 461, "Is not an operator", words[0]));    
    
	if (words.size() < 2)
    {
        sendError(client, 461, "Not enough parameters\n"); //ERR_NEEDMOREPARAMS
		return ;
    }
    char s = '+';
    for(long unsigned int i = 0; i < words[1].size(); i++)
    {
        while (words[1][i] == '+' || words[1][i] == '-')
            s = words[1][i++];      
        if (words[1][i] == 'i' || words[1][i] == 't' || words[1][i] == 'k' || words[1][i] == 'o' || words[1][i] == 'l') {
            std::string response;
            if (s == '-')
            {
                response = client->getNickname() + " disables " +  std::string(1, words[1][i]) + " mode in " + words[0] + "'s channel\n";
                if (words[1][i] == 'i' || words[1][i] == 't') {
                    channel->setMode(words[1][i], false, 0);
                    send(client->getFd(), response.c_str(), response.size(), 0);
                    continue ;
                }
                if (words[1][i] == 'k')
                {
                    channel->setMode(words[1][i], false, 0);
                    channel->setKey("");
                }
                if (words[1][i] == 'o')
                {
                    //Delete chanel operator
					if (words.size() < 3)
                    {
                        sendError(client, 461, "Not enough parameters\n"); //ERR_NEEDMOREPARAMS
                        continue;
                    }
                    Client *clientO = Server::getInstance().getClientByNickname(words[2]);
                    if (!clientO) //|| channel->getClientList(clientO->(getNickname()))) //descomentar en tenir la funcio en fer merge. Necessitem veure si el client esta al canal!
                        return (sendError(client, 442, "They aren't on that channel", words[2])); //ERR_NOTONCHANNEL
                    channel->removeOperatorClient(clientO);
                    std::cout << "El cliente " << words[2] << " ha sido ELIMINADO como operador del canal!" << std::endl;
                }
                if (words[1][i] == 'l')
                {
                    channel->setMode(words[1][i], false, 0);
                    channel->setLimit(-1); 
                }

            }
            else 
            {
                response = client->getNickname() + " enables " +  std::string(1, words[1][i]) + " mode in " + words[0] + "'s channel\n";
                if (words[1][i] == 'i' || words[1][i] == 't')
                {
                    channel->setMode(words[1][i], false, 0);
                    send(client->getFd(), response.c_str(), response.size(), 0);
                    continue;
                }
                if (words.size() < 3)
                {
                    sendError(client, 461, "Not enough parameters\n"); //ERR_NEEDMOREPARAMS
                    continue;
                }
                if (words[1][i] == 'k')
                {
                    channel->setMode(words[1][i], true, 0);
                    channel->setKey(words[2]);
                    std::cout << "El canal ahora tiene contraseña!" << std::endl;   
                }
                if (words[1][i] == 'o')
                {
                    //Give chanel operator
                    Client *clientO = Server::getInstance().getClientByNickname(words[2]);
                    if (!clientO)// || channel->getClientList(clientO->(getNickname()))) //descomentar en tenir la funcio en fer merge. Necessitem veure si el client esta al canal!
                        return (sendError(client, 442, "They aren't on that channel", words[2])); //ERR_NOTONCHANNEL
                    channel->addOperatorClient(clientO);
                    std::cout << "El cliente " << words[2] << " ha sido asigando como operador del canal!" << std::endl;
                }
                if (words[1][i] == 'l')
                {
                    //user limit to channel
                    channel->setMode(words[1][i], true, 0);
                    channel->setLimit(atoi(words[2].c_str()));
                    std::cout << "El canal se ha limitado a " << words[2] << " clientes!" << std::endl;
                }
            }
            send(client->getFd(), response.c_str(), response.size(), 0);
        }
        else 
        {
            std::string charError = std::string(1, words[1][i]);
            sendError(client, 472 , "is unknown mode char to me", charError); //ERR_UNKNOWNMODE    
            return ;
        }
    }  
}*/
