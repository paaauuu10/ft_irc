/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:32:23 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/09 10:10:17 by pbotargu         ###   ########.fr       */
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
