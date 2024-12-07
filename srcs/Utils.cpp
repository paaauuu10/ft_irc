/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:00:21 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/03 12:00:22 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

// :<server> <error_code> <target> :<error_message>
// :irc.example.com 432 user123 :Erroneous nickname

// target se predefine en "", si no es pasado como parametro
void sendError(Client* client, int errorCode, const std::string& errorMessage, const std::string& target) {
    if (!client || !client->getLogged()) {
        std::cerr << "Error: Cliente no está conectado.\n";
        return;
    }

    std::string serverName = Server::getServerName();

    std::ostringstream oss;
    oss << ":" << serverName << " " << errorCode << " " 
        << (target.empty() ? "*" : target) // Usa "*" si el target no está definido.
        << " :" << errorMessage;
    //client->SendMessage(oss.str());
}
