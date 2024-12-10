/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:57:43 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/10 15:25:09 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	PASS( Client *client, std::string pass)
{
   	std::string password = Server::getInstance().getPass();
    std::string clean_pass = pass.substr(pass.find(' ') + 1); // Eliminar el salto de línea (si existe) al final
    if (!clean_pass.empty() && ((clean_pass[clean_pass.size() - 1]) == '\n' || (clean_pass[clean_pass.size() - 1]) == '\r'))
    {
		clean_pass.erase(clean_pass.size() -1);
		clean_pass.erase(clean_pass.size() -1);

        std::cout << "if" << std::endl;
    }
    std::cout << clean_pass << std::endl;
    // std::cout << "PASS: " << pass << std::endl; 
   	// std::cout << "_pass: " << Server::getInstance()._pass << std::endl;
    
	if (client->getLogged() == true)
    {
        std::cout << "Already registered" << std::endl; // EL MISSATGE HA DE SER EL CLIENT
		std::string response = "Already registered\r\n";
	//	send(client->getFd(), response.c_str(), response.size(), 0);
        return ;
    }
    std::cout << clean_pass.size() << std::endl;
    std::cout << password.size() << std::endl;
    if (clean_pass != password)
    {
        std::cout << "Wrong Password" << std::endl; // EL MISSATGE HA DE SER EL CLIENT 
        
		/*std::string response = "Error: Wrong password\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);*/
        // CALDRA VEURE COM ES GESTIONA EL CLIENT 
        
        return ;
    }
    client->setLogged(true);
}
