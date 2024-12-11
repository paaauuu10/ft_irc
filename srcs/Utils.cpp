/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:00:21 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/11 12:39:49 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

// :<server> <error_code> <target> :<error_message>
// :irc.example.com 432 user123 :Erroneous nickname

// target se predefine en "", si no es pasado como parametro
void sendError(Client* client, int errorCode, const std::string& errorMessage, const std::string& target) {
    /*if (!client || !client->getLogged()) {
        std::cerr << "Error: Cliente no está conectado.\n";
        return;
    }*/
	(void)errorCode;

    std::string serverName = Server::getServerName();
    std::string str = ":" + serverName + " "// + errorCode + " " 
        + (target.empty() ? "*" : target) // Usa "*" si el target no está definido.
        + " :" + errorMessage + "\n\r";
    send(client->getFd(), str.c_str(), str.size(), 0);
}

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    for (std::string::size_type i = 0; i < input.size(); i++) {
        if (input[i] == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else {
            token += input[i];
        }
    }
    if (!token.empty())
        tokens.push_back(token);
    return (tokens);
}

bool    checkerIsLogged(Client *client)
{
    if (client->getLogged() == false)
    {
        // el missatge s'ha d'enviar al Client!!!
        std::cout << "First you have to enter the password" << std::endl;
        return false;
    }
    return true;
}
