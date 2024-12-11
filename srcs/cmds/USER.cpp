/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:12:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/10 16:13:42 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Utils.hpp"


void	USER(Client *client, std::string pass)
{
    if (checkerIsLogged(client) == false)
        return ;
    std::vector<std::string> words = split(pass, ' ');
    std::cout << words[0] << std::endl;
    if (words.size() < 4)
    {
        std::cout << "No hay los parametros necesarios" << std::endl;
        return ;
        //send error
    }
    //username es unic? en cas que si cal revisar si ja existeix o no. Mirar si el client ja esta registrat?
    
    // <username> <hostname> <servername> <realname>
    client->setUsername(words[1]);
    client->setHostname(words[2]); // revisar com ha de ser hostname
    client->setServername(words[3]);
    client->setRealName(words[4]);
    
    std::cout << client->getUsername() << std::endl;
    std::cout << client->getHostname() << std::endl;
    std::cout << client->getServername() << std::endl;
    std::cout << client->getRealname() << std::endl;
   
}
