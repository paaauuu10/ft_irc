/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:30:02 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/29 18:51:47 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

static void extractChannels(std::vector<std::string> &tokens, std::vector<std::string> &channels) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (!tokens[i].empty() && tokens[i][0] == '#') {
            channels.push_back(tokens[i]);
        }
    }
}

static void haveServername(std::string &arg, std::vector<std::string> &tokens, std::string &servername) {
    if (arg.find(' ') != std::string::npos) {
        tokens = split(arg, ' ');
        servername = tokens[1];
    } else {
        servername = Server::getInstance().getServerName();
    }
    if (arg.find(',') != std::string::npos) {
        tokens = split(arg, ',');
    } else {
        tokens.clear();
    }
}

void list(Client *client, std::string &args) {
    //[<channel>{,<channel>} [<server>]]
    //[<channel>            <channel>{,<channel>}]

    std::vector<std::string> tokens;
    std::vector<std::string> channels;
    std::string servername;

    args = trim(args);
    haveServername(args, tokens, servername);
    extractChannels(tokens, channels);

    std::ostringstream oss;
    oss << ":" << Server::getInstance().getServerName() << " 321 " << client->getNickname() << " Channel :Users Name\r\n";
    std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);

	// al mandar null como arg se recibe lista entera de canales en server.
    std::vector<Channel *> serverChannels = Server::getInstance().getChannels(NULL);

    // si no se especificaron canales listarlos todos
    if (channels.empty()) {
        for (size_t i = 0; i < serverChannels.size(); ++i) {
            Channel *channel = serverChannels[i];
            oss.str("");
            oss.clear();
            oss << ":" << Server::getInstance().getServerName() << " 322 " << client->getNickname() << " "
                << channel->getName() << " " << channel->getUserCount() << " :" << channel->getTopic() << "\r\n";
            msg = oss.str();
            send(client->getFd(), msg.c_str(), msg.size(), 0);
        }
    } else {
        // Listar solo los canales especificados
        for (size_t i = 0; i < channels.size(); ++i) {
            Channel *channel = Server::getInstance().getCheckChannel(channels[i]);
            if (channel) {
                oss.str("");
                oss.clear();
                oss << ":" << Server::getInstance().getServerName() << " 322 " << client->getNickname() << " "
                    << channel->getName() << " " << channel->getUserCount() << " :" << channel->getTopic() << "\r\n";
                msg = oss.str();
                send(client->getFd(), msg.c_str(), msg.size(), 0);
            }
        }
    }

    oss.str("");
    oss.clear();
    oss << ":" << Server::getInstance().getServerName() << " 323 " << client->getNickname() << " :End of /LIST\r\n";
    msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
}