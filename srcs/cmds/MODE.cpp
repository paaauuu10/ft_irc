/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:22:51 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/13 17:47:00 by pbotargu         ###   ########.fr       */
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
                response = client->getNickname() + " disables " +  std::string(1, words[1][i]) + " mode in " + words[0] + "'s channel\n";
                if (words[1][i] == 'i' || words[1][i] == 't')
                {
                    std::cout << "Hemos seteado I o T a false!" << std::endl;
                   //channel->setMode(words[1][i], false, 0);
                    continue ;
                }
                if (words[1][i] == 'k')
                {
                    //channel->setMode(words[1][i], false, 0);
                    //channel->setPassword(words[2]);
                    std::cout << "El canal ahora NO tiene contraseña!" << std::endl;   
                }
                if (words[1][i] == 'o')
                {
                    //Give chanel operator
                    //channel->setMode(words[1][i], false, 0);
                    //channel->_operatorClients->deleteClientOperator(words[2]);
                    if (words.size() < 3)
                    {
                        sendError(client, 461, "Not enough parameters\n"); //ERR_NEEDMOREPARAMS
                        continue;
                    }
                    std::cout << "El cliente " << words[2] << " ha sido ELIMINADO como operador del canal!" << std::endl;
                }
                if (words[1][i] == 'l')
                {
                    //user limit to channel
                    //channel->setMode(words[1][i], false, 0);
                    //channel->_limit = (NULL); 
                    std::cout << "El canal NO tiene limite de clientes!" << std::endl;
                }

            }
            else 
            {
                response = client->getNickname() + " enables " +  std::string(1, words[1][i]) + " mode in " + words[0] + "'s channel\n";
                if (words[1][i] == 'i' || words[1][i] == 't')
                {
                    std::cout << "Hemos seteado I o T a true!" << std::endl;
                   //channel->setMode(words[1][i], false, 0);
                    continue ;
                }
                if (words.size() < 3)
                {
                    sendError(client, 461, "Not enough parameters\n"); //ERR_NEEDMOREPARAMS
                    continue;
                }
                if (words[1][i] == 'k')
                {
                    //channel->setMode(words[1][i], true, 0);
                    //channel->setPassword(words[2]);
                    std::cout << "El canal ahora tiene contraseña!" << std::endl;   
                }
                if (words[1][i] == 'o')
                {
                    //Give chanel operator
                    //channel->setMode(words[1][i], true, 0);
                    //channel->_operatorClients->addClientOperator(words[2]);
                    std::cout << "El cliente " << words[2] << " ha sido asigando como operador del canal!" << std::endl;
                }
                if (words[1][i] == 'l')
                {
                    //user limit to channel
                    //channel->setMode(words[1][i], true, 0);
                    //channel->_limit = atoi(words[2]);
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
}
