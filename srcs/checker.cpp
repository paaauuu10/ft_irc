/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:03:18 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/09 10:07:49 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool    Server::checker(Client *client)
{
    if (client->getLogged() == false)
    {
        // el missatge s'ha d'enviar al Client!!!
        std::cout << "First you have to enter the password" << std::endl;
        return false;
    }
    return true;
}
