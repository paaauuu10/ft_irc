/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:22:51 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/13 14:59:57 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <vector>
#include <string>
#include <iostream>

void	MODE(Client *client, std::string str)
{
    //S'ha de mirar si es un operador abans de continuar. Si no return ; i ciao! NO borrar comentari!
    std::vector<std::string> words = split(str, ' ');
    //Channel *channel = Server::getInstance().getCheckChannel(words[0]);
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
        if (words[1][i] == 'i' || words[1][i] == 't' || words[1][i] == 'k' || words[1][i] == 'o' || words[1][i] == 'l')
        {
            std::string response;
            if (s == '-')
            {
                response = "this is -" + std::string(1, words[1][i]) + "\n";
                //channel->setMode(words[1][i], false, 0);
            }
            else 
            {
                response = "this is +" + std::string(1,words[1][i]) + "\n";
                //channel->setMode(words[1][i], true, 0);
            }
            send(client->getFd(), response.c_str(), response.size(), 0);
        }
       /* else if (words[1][i] == 't')
        {
            std::string response;
            if (s == '-')
                response = "this is -t\n";
            else 
                response = "this is mode +t!\n";
            send(client->getFd(), response.c_str(), response.size(), 0);
        }
        else if (words[1][i] == 'k')
        {
            std::string response;
            if (s == '-')
                response = "this is -k\n";
            else 
                response = "this is mode +k!\n";
            send(client->getFd(), response.c_str(), response.size(), 0);
        }
        else if (words[1][i] == 'o')
        {
            std::string response;
            if (s == '-')
                response = "this is -o\n";
            else 
                response = "this is mode +o!\n";
            send(client->getFd(), response.c_str(), response.size(), 0);
        }
        else if (words[1][i] == 'l')
        {
            std::string response;
            if (s == '-')
                response = "this is -l\n";
            else 
                response = "this is mode +l!\n";
            send(client->getFd(), response.c_str(), response.size(), 0);
        }*/
        else 
        {
            std::string charError = std::string(1, words[1][i]);
            sendError(client, 472 , "is unknown mode char to me", charError); //ERR_UNKNOWNMODE    
            return ;
        }
    }

   
}