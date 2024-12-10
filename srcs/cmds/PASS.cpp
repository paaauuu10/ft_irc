/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:57:43 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/10 15:35:13 by pbotargu         ###   ########.fr       */
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
   
	if (client->getLogged() == true)
    {
        std::cout << "Already registered" << std::endl; // EL MISSATGE HA DE SER EL CLIENT
		std::string response = "Already registered\r\n";
	//	send(client->getFd(), response.c_str(), response.size(), 0);
        return ;
    }

    if (clean_pass != password)
    {
        std::cout << "Wrong Password" << std::endl; // EL MISSATGE HA DE SER EL CLIENT 
        
		/*std::string response = "Error: Wrong password\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);*/
        // CALDRA VEURE COM ES GESTIONA EL CLIENT 
        
        return ;
    }
    std::cout << "Correct Password! Welcome to ft_irc!" << std::endl;
    client->setLogged(true);
}
