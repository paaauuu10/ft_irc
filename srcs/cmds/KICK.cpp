/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:07 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/16 17:19:52 by anovio-c         ###   ########.fr       */
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

static std::string	makeBroadcastMessage(Client *client, std::string &channelName, std::string &userToKick, std::string &reason) {
	std::ostringstream oss;

    // Mensaje JOIN con el prefijo correcto
	// :<nickname>!<username>@<hostname> JOIN :<channelName>\r\n
    oss << ":" << client->getNickname() << "!" << client->getUsername()
        << "@" << "127.0.0.1" << " KICK " << channelName << " "
        << userToKick << " :" << reason << "\r\n";

	return (oss.str());
}

void	KICK(Client *client, std::string &args) {
	if (args.empty())
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
	// <channel>{,<channel>} <user>{,<user>} [<comment>]
	std::vector<std::string>	tokens = split(args, ' ');
	if (tokens.size() < 2) // for check channels and users minim
		sendError(client, 461, "ERR_NEEDMOREPARAMS");
		
	std::vector<std::string>	channels = split(tokens[0], ',');
	std::vector<std::string>	users = (tokens.size() > 1)
		? split(tokens[1], ',')
		: std::vector<std::string>();
		
	std::string reason = (tokens.size() > 2) ? tokens[2] : "No reason specified";
	
	for (size_t i = 0; i < channels.size(); ++i) {
		std::string channelName = channels[i];
		std::string userToKick = (i < users.size()) ? users[i] : "";
		
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
	}
}

