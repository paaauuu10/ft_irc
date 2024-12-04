/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:57:43 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/04 11:05:08 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(std::string pass, Client *client)
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
		ssize_t bytes_sent = send(client->getFd(), response.c_str(), response.size(), 0);
        if (bytes_sent < 0)
        {
            std::cerr << "Error al enviar mensaje al cliente: " << strerror(errno) << std::endl;
        }
        else
        {
            std::cout << "Mensaje enviado al cliente: " << bytes_sent << " bytes." << std::endl;
        }   

        //send(client->getFd(), response.c_str(), response.size(), 0);
        // CALDRA VEURE COM ES GESTIONA EL CLIENT 
        
        return ;
    }
    client->setLogged(true);
}
