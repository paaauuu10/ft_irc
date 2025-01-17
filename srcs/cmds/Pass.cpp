/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:57:43 by pbotargu          #+#    #+#             */
/*   Updated: 2025/01/17 13:36:19 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ErrorCodes.hpp"

void	pass(Client *client, std::string &pass)
{
	if (client->getLogged()) {
		sendError(client, ERR_ALREADYREGISTRED);
		return ;
	}
   	std::string password = Server::getInstance().getPass();
    std::string server =  Server::getInstance().getServerName();

    pass = trim(pass);
	
	if (pass.empty()) {
		sendError(client, ERR_NEEDMOREPARAMS);
		return ;
	}
    if (pass == password) {
        client->setLogged(true);
		std::cout << "Client with fd '"<< client->getFd() << "' put a correct password." << std::endl;
    } else
		sendError(client, ERR_PASSWDMISMATCH);
	return ;
}
