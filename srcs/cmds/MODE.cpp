/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:22:51 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/13 13:04:57 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <vector>
#include <string>
#include <iostream>

void	MODE(Client *client, std::string str)
{
    // i t k o l cmds que s'han de controlar
    std::vector<std::string> words = split(str, ' ');
    if (words.size() < 1)
    {
        sendError(client, 461, "Not enough parameters\n"); //ERR_NEEDMOREPARAMS
		return ;
    }
    
    for(long unsigned int i = 0; i < words[0].size() - 1; i++)
    {
        if (words[0][i] != '+' && words[0][i] != '-')
        {
            sendError(client, 472 , ":is unknown mode char to me", words[0]); //ERR_UNKNOWNMODE    
            return ;
        }
    }

    if (words[0][words[0].size() - 1] == 'i')
    {
        std::string response;
        if (words[0][words[0].size() - 2]  && (words[0][words[0].size() - 2] == '+'))
            response = "this is +i\n";
        else if (words[0][words[0].size() - 2]  && (words[0][words[0].size() - 2] == '-'))
            response = "this is -i\n";
        else 
            response = "this is mode i!\n";
        send(client->getFd(), response.c_str(), response.size(), 0);
    }
}