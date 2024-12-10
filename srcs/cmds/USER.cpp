/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:12:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/10 14:33:50 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Utils.hpp"


void Server::user(std::string str, Client *client)
{
    if (checker(client) == false)
        return ;
    std::vector<std::string> words = split(str, ' ');
    if (words.size() < 4)
    {
        std::cout << "No hay los parametros necesarios" << std::endl;
        //send error
    }
    //username es unic? en cas que si cal revisar si ja existeix o no. Mirar si el client ja esta registrat?
    
    // <username> <hostname> <servername> <realname>
    client->setUsername(words[0]);
    client->setHostname(words[1]); // revisar com ha de ser hostname
    client->setRealName(words[3]);
    
    std::cout << client->getUsername() << std::endl;
    std::cout << client->getHostname() << std::endl;
    std::cout << client->getRealname() << std::endl;
   
}
