/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:57:43 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/10 12:45:58 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	PASS( Client *client, std::string pass)
{
   	std::cout << "PASS: " << pass << std::endl; 
   	std::cout << "_pass: " << this->_pass << std::endl; 
	if (client->getLogged() == true)
    {
        std::cout << "Already registered" << std::endl; // EL MISSATGE HA DE SER EL CLIENT
		std::string response = "Already registered\r\n";
	//	send(client->getFd(), response.c_str(), response.size(), 0);
        return ;
    }
    if (pass != this->_pass)
    {
       // std::cout << "Wrong Password" << std::endl; // EL MISSATGE HA DE SER EL CLIENT 
        
		std::string response = "Error: Wrong password\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
        // CALDRA VEURE COM ES GESTIONA EL CLIENT 
        
        return ;
    }
    client->setLogged(true);
}
