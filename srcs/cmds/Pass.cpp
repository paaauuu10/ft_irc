/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:57:43 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/31 10:16:36 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	pass(Client *client, std::string &pass)
{
	if (client->getLogged()) {
		sendError(client, 462, "ERR_ALREADYREGISTRED");
		return ;
	}
   	std::string password = Server::getInstance().getPass();
    std::string server =  Server::getInstance().getServerName();

    pass = trim(pass);
	
	if (pass.empty()) {
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
		return ;
	}
    if (pass == password) {
        client->setLogged(true);
		std::cout << "Client with fd '"<< client->getFd() << "' put a correct password." << std::endl;
    } else
		sendError(client, 464, "ERR_PASSWDMISMATCH");
	return ;
}
