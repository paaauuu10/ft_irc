/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pborrull <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/09 12:22:54 by pborrull		  #+#	#+#			 */
/*   Updated: 2024/12/09 15:08:40 by pborrull         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

void privMsg(Client *sender, const std::string &target, const std::string &message)
{
	if (target.empty())
	{
		std::cerr << "Error: Target is empty" << std::endl;
		sendError(sender, 411, "No recipient (PRIVMSG)");
		//ERR_NORECIPIENT
		return;
	}
	if (message.empty())
	{
		std::cerr << "Error: Message is empty" << std::endl;
		sendError(sender, 412, "No text to send");
		//ERR_NOTEXTTOSEND
		return;
	}
	
	std::string fullMessage = ":" + sender->getNickname() + " PRIVMSG " + target + " :" + message + "\r\n";

	// For clients
	if (clients.find(target) != clients.end())
	{
		int targetSocket = clients._fd;
		send(targetSocket, fullMessage.c_str(), fullMessage.size(), 0);
	}
	// For channels
	else if (channels.find(target) != channels.end())
	{
		std::set<int>& channelSockets = channels[target];
		for (std::set<int>::iterator it = channelSockets.begin(); it != channelSockets.end(); ++it)
		{
    		int socket = *it;
			if (clients[sender] == socket)
				continue; // No send to themselfs
			send(socket, fullMessage.c_str(), fullMessage.size(), 0);
		}
	}
	// For nobody
	else
	{
		int senderSocket = clients[sender];
		std::string errorMsg = target + " :No such nick/channel\r\n";
		sendError(sender, 401, errorMsg.c_str(), 0);
		std::cerr << "Error: No such nick/channel -> " << target << std::endl;
	}
}
