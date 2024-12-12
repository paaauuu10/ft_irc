/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:57:43 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/12 11:40:48 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	PASS( Client *client, std::string pass)
{
   	std::string password = Server::getInstance().getPass(); // Conseguimos PASS del sever
    std::string clean_pass = pass.substr(pass.find(' ') + 1); // Eliminar el salto de línea (si existe) al final
    while (!clean_pass.empty() && ((clean_pass[clean_pass.size() - 1]) == '\n' || (clean_pass[clean_pass.size() - 1]) == '\r'))
    {
    	clean_pass.erase(clean_pass.size() -1);
    }
   
	if (pass.empty())
    {
        sendError(client, 461, "Not enough parameters", pass); //ERR_NEEDMOREPARAMS
        return ;
    }
    if (client->getLogged() == true)
    {
	    sendError(client, 462, "Unauthorized command (already registered)"); //ERR_ALREADYREGISTRED
        return ;
    }

    if (clean_pass != password)
    {
        sendError(client, 464, "Password incorrect"); //ERR_PASSWDMISMATCH
        return ; 
    }
	std::string response = "Correct Password! Welcome to ft_irc!\r\n";
    send(client->getFd(), response.c_str(), response.size(), 0);
    client->setLogged(true);
}
