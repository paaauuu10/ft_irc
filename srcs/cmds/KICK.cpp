/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:07 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/17 16:43:42 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

// 403: Canal no existe.
// 441: Usuario no está en el canal.
// 461: Parámetros insuficientes.
// 482: Cliente no es administrador.

// KICK <channel>{,<channel>} <user>{,<user>} [<comment>] 
// KICK #test1,#test2 Alice,dan :Razón de kick 
// kick alice de test1 y a dan de test2
// KICK #test alice :dan
// For example, if dan, alice, and matthew are on channel #v4, and dan kicks
// matthew, all three clients will receive a KICK message indicating that dan
// has removed matthew from the channel.

// fd from poll is for identify the channel and the client in the channel 
// for expulse, and notificate the others clients in channel
// Only a channel operator may kick another user out of a  channel.

/*   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
           ERR_NOTONCHANNEL*/

static void	reviewChannels(std::vector<std::string> &old) {
	std::vector<std::string> filtered;

	for (size_t i = 0; i < old.size(); ++i) {
        bool isDuplicate = false;

        for (size_t j = 0; j < filtered.size(); ++j) {
            if (filtered[j] == old[i]) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            filtered.push_back(old[i]);
        }
    }
	old = filtered;
	for (size_t i = 0; i < filtered.size(); ++i)
		std::cout << "STR ==> " << filtered[i] << std::endl;
}

/*static std::vector<std::string>	extractUsers(std::vector<std::string> &tokens) {
	std::vector<std::string>	filteredTokens;
	std::string					users;
	
	for (size_t i= 0; i < tokens.size(); ++i) {
		if (tokens[i][0] == '#' || tokens[i][0] == '&')
			filteredTokens.push_back(tokens[i]);
		else {
			if (users.empty())
				users = tokens[i];
		}
	}
	if (users.empty())
		return std::vector<std::string> ();
	return split(users, ',');
}*/

static std::vector<std::string> extractUsers(std::vector<std::string> &tokens) {
    std::vector<std::string> users;

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i][0] != '#' && tokens[i][0] != '&' && tokens[i][0] == ':') {
        	users = split(tokens[i], ',');
            break;
        }
    }

    return users;
}

static std::string extractReason(std::vector<std::string> &tokens) {
    std::string reason;
    std::vector<std::string> filteredTokens;

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i][0] == '#' || tokens[i][0] == '&' || tokens[i].find_first_not_of(",") == 0) {
            filteredTokens.push_back(tokens[i]);
        } else {
            if (reason.empty())
                reason = tokens[i];
        }
    }

    tokens = filteredTokens;
    return (reason.empty() ? "No reason specified" : reason) ;
	/*std::string reason;

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i][0] != '#' && tokens[i][0] != '&' && tokens[i].find(',') == std::string::npos) {
            reason = tokens[i];
            break;
        }
    }

    return (reason.empty() ? "No reason specified" : reason);*/
}


static std::string	makeBroadcastMessage(Client *client, std::string &channelName, std::string &userToKick, std::string &reason) {
	
	std::ostringstream oss;
	
	// :<nickname>!<username>@<hostname> JOIN :<channelName>\r\n
    oss << ":" << client->getNickname() << "!" << client->getUsername()
        << "@" << "127.0.0.1" << " KICK " << channelName << " "
        << userToKick << " :" << reason << "\r\n";

	return (oss.str());
}

// KICK <channel>{,<channel>}  <user>{,<user>} [<comment>]


void	KICK(Client *client, std::string &args) {
	if (args.empty())
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
		
	std::vector<std::string>	tokens = split(args, ' ');
	
	if (tokens.size() < 2) // for check channels and users minim
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
	
	std::string reason = extractReason(tokens);
	std::vector<std::string> users = extractUsers(tokens);
	
	std::vector<std::string> channels;
	if (tokens.size() > 1) { // hay doble str de canales, uno del cliente y otro de hexchat
		std::string channelsJoin = tokens[0] + ',' + tokens[1];
		channels = split(channelsJoin, ',');
	} else 
		channels = split(tokens[0], ',');
	reviewChannels(channels);
	
	for (size_t i = 0; i < channels.size(); ++i) {
		std::string channelName = channels[i];
		std::string userToKick = (i < users.size() && !users[i].empty()) ? users[i] : "";
		
		Channel *channel = Server::getInstance().getCheckChannel(channelName);

		if (!channel) {
			sendError(client, 403, "ERR_NOSUCHCHANNEL");
			continue ;
		}
		if (!channel->checkOperatorClient(client)) {
			sendError(client, 482, "ERR_CHANOPRIVSNEEDED");
			continue ;
		}
		if (userToKick.empty()) {
			sendError(client, 482, "ERR_NEEDMOREPARAMS - No user specified for channel " + channelName);
			continue ;
		}
		// checkear si han introducido user o si el user to kick no se encuentra en el canal
		Client *toKick = channel->checkClient(userToKick);
		if (!toKick) {
			sendError(client, 442, "ERR_NOTONCHANNEL");
			continue ;
		}
		// sends message priv
		        // Notify the channel about the kick
        std::string msg = makeBroadcastMessage(client, channelName, userToKick, reason);

        channel->broadcast(client, msg); // Sends message to all clients in the channel
		// rm client of channel
        channel->rmClient(toKick);
	}
}

/* void	KICK(Client *client, std::string &args) {
	if (args.empty())
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
		
	// <channel>{,<channel>} <user>{,<user>} [<comment>]
	std::vector<std::string>	tokens = split(args, ' ');
	
	if (tokens.size() < 2) // for check channels and users minim
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
	
	
		
	std::vector<std::string>	channels = split(tokens[0], ',');
	reviewChannels(channels);
	std::vector<std::string>	users = (tokens.size() > 1)
		? split(tokens[1], ',')
		: std::vector<std::string>();
		
	std::string reason = (tokens.size() > 2) ? tokens[2] : "No reason specified";
	
	for (size_t i = 0; i < channels.size(); ++i) {
		std::string channelName = channels[i];
		std::string userToKick = (i < users.size() && !users[i].empty()) ? users[i] : "";
		
		Channel *channel = Server::getInstance().getCheckChannel(channelName);

		if (!channel) {
			sendError(client, 403, "ERR_NOSUCHCHANNEL");
			continue ;
		}
		if (!channel->checkOperatorClient(client)) {
			sendError(client, 482, "ERR_CHANOPRIVSNEEDED");
			continue ;
		}
		// checkear si han introducido user o si el user to kick no se encuentra en el canal
		Client *toKick = channel->checkClient(userToKick);
		if (!toKick) {
			sendError(client, 442, "ERR_NOTONCHANNEL");
			continue ;
		}
		
		// sends message priv
		        // Notify the channel about the kick
        std::string msg = makeBroadcastMessage(client, channelName, userToKick, reason);

        channel->broadcast(client, msg); // Sends message to all clients in the channel
		// rm client of channel
        channel->rmClient(toKick);

		// OJITO CUIDAO
		// HEXCHAT MANDA ==> KICK #canal1 #canal2 :asier2
	}
} */

