/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:57:43 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/21 21:17:51 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	pass( Client *client, std::string &pass)
{
   	std::string password = Server::getInstance().getPass(); // We get PASS from Server
    std::string clean_pass = pass.substr(pass.find(' ') + 1); // Delete initial space
    std::string server =  Server::getInstance().getServerName();
    std::string response;
	while (!clean_pass.empty() && ((clean_pass[clean_pass.size() - 1]) == '\n'
		|| (clean_pass[clean_pass.size() - 1]) == '\r'))
		clean_pass.erase(clean_pass.size() -1);

	if (pass.empty())
        response = ":" + server + " 461 :Not enought parameters\r\n"; //ERR_NEEDMOREPARAMS
    else if (client->getLogged() == true)
        response = ":" + server + " 462 :You may not reregister\r\n"; //ERR_ALREADYREGISTRED 
    else if (clean_pass != password)
        response = ":" + server + " 464 :Password incorrect\r\n"; //ERR_PASSWDMISMATCH
	else if (clean_pass == password) {
        response = "Correct Password!\r\n";
        client->setLogged(true);
    }
    send(client->getFd(), response.c_str(), response.size(), 0);
}
