/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pborrull <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/09 12:22:54 by pborrull		  #+#	#+#			 */
/*   Updated: 2024/12/17 12:48:59 by pborrull         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"


static Client	*checkClient(std::string &nickname)
{

	std::vector<Client *>	vclient = Server::getInstance().getClients();
	for (long unsigned int i = 0; i < vclient.size(); i++)
	{
		if (vclient[i]->getNickname() == nickname)
			return vclient[i];
	}
	return NULL;
}


void PRIVMSG(Client *sender, std::string &value)
{
	std::vector<std::string> words = split(value, ' ');
	if (words.empty())
	{
		sendError(sender, 411, sender->getNickname() + " :No recipient given (PRIVMSG)");
		//ERR_NORECIPIENT
		return;
	}
	if (words[0].empty())
	{
		sendError(sender, 411, sender->getNickname() + " :No recipient given (PRIVMSG)");
		//ERR_NORECIPIENT
		return;
	}
	std::vector<std::string> targets = split(words[0], ',');
	std::string message;
	if (words.size() > 1)
	{
		message = words[1];
		for (long unsigned int i = 2; i < words.size(); i++)
		message += " " + words[i];
	}
	if (message.empty())
	{
		sendError(sender, 412, sender->getNickname() + " :No text to send");
		//ERR_NOTEXTTOSEND
		return;
	}
	
	for (long unsigned int i = 0; i < targets.size(); i++)
	{
		Channel *ctarget = Server::getInstance().getCheckChannel(targets[i]);
		Client *target = checkClient(targets[i]);
		if (ctarget != NULL)
		{
			std::vector<int> channelSockets = ctarget->listFdClients();
			for (size_t j = 0; j < channelSockets.size(); j++)
			{
    			int socket = channelSockets[j];
				if (socket == sender->getFd())
					continue; // No send to themselfs
				std::string fullMessage = ":" + sender->getNickname() + " PRIVMSG " + ctarget->getName() + " " + message + "\r\n";
				send(socket, fullMessage.c_str(), fullMessage.size(), 0);
			}
			break ;
		}
		if (target != NULL)
		{
			int targetSocket = target->getFd();	
			std::string fullMessage = ":" + sender->getNickname() + " PRIVMSG " + target->getNickname() + " :" + message + "\r\n";
			send(targetSocket, fullMessage.c_str(), fullMessage.size(), 0);
		}
		// For nobody
		if (target == NULL && ctarget == NULL)
		{
			std::string errorMsg = sender->getNickname() + " " + targets[0] + " :No such nick/channel";
			sendError(sender, 401, errorMsg.c_str());
		}
	}
}
