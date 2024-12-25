/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:24:25 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/23 15:27:16 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include <fstream>

void sendFile(Client *client, std::string &args) {
    std::vector<std::string> tokens = split(args, ' ');
    if (tokens.size() < 3) {
        sendError(client, 461, "ERR_NEEDMOREPARAMS - Usage: SEND <recipient> <filename> <filesize>");
        return;
    }

    std::string recipientNick = tokens[0];
    std::string filename = tokens[1];
    size_t filesize = std::stoul(tokens[2]);

    Client *recipient = Server::getInstance().getClientByNickname(recipientNick);
    if (!recipient) {
        sendError(client, 401, "ERR_NOSUCHNICK - No such nickname");
        return;
    }

    std::string response = "Ready to receive file: " + filename + " (" + std::to_string(filesize) + " bytes)\n";
    send(recipient->getFd(), response.c_str(), response.size(), 0);

    char buffer[1024];
    size_t received = 0;
    while (received < filesize) {
        int bytes = recv(client->getFd(), buffer, sizeof(buffer), 0);
        if (bytes <= 0) {
            sendError(client, 451, "ERR_FILETRANSFER - File transfer interrupted");
            return;
        }
        send(recipient->getFd(), buffer, bytes, 0);
        received += bytes;
    }

    response = "File transfer complete: " + filename + "\n";
    send(recipient->getFd(), response.c_str(), response.size(), 0);
}
