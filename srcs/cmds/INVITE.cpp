/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:32:23 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/10 11:26:57 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    
    return result;
}

void Server::invite(std::string str, Client *client)
{
    if (checker(client) == false)
        return ;
    std::vector<std::string> words = split(str, ' ');
    if (words.size() < 2)
    {
        std::cout << "Need more params" << std::endl; // ha de ser un missatge al client no sortida per la terminal
        return ;
    }
    std::string channel_n = words[1];
    std::string client_i = words[0];
    
    //estructura de la funció
    // existeix el canal?
    
    //es membre del canal el client que fa la invitacio
    //es membre del canal el client convidat
    
    //enviar el missatge d'invitacio al client convidat
    
}

/*#include <string>
#include <iostream>

int		INVITE(Client *client, Channel *channel)
{
	
    
    if (client.empty() || channel.empty())
		std::cout << "Not enough parameters" << std::endl;
		//sendError(client, 461, "Not enough parameters"); //ERR_NEEDMOREPARAMS
	else if (!nickExist()) //Falta fer-la
		std::cout << "No such nickname" << std::endl;
		//sendError(client, 401, "No such nickname"); //ERR_NOSUCHNICK
	else if (!channelExist(channel))
		std::cout << "No such channel" << std::endl;
		//sendError(client, 403, "No such channel); //ERR_NOSUCHCHANNEL
	else if (!isOnChannel()) //Falta fer-la
		std::cout << "is already on channel" << channel.getName() << std::endl;
		//sendError(client, 443, "is already on channel <channel name>"); //ERR_USERONCHANNEL
	else if (!isOperator(client))
		std::cout << "You don't have channel operator privileges" << std::endl;
		//sendError(client, 482, "You don't have channel operator privileges"); //ERR_CHANOPRIVSNEEDED
	else if (!isAway(client))
		std::cout << "I'm away, please try later" << std::endl;
		//sendError(client, 301, "I'm away, please try later"); //
	else
		std::cout << client.getNickname() << " is inviting you to #" << channel.getName << std::endl;
		//sendError(client, 341, "Client is inviting you to #<channel>"); //
	return 0;
}*/
