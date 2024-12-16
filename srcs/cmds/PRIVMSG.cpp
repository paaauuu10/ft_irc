/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pborrull <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/09 12:22:54 by pborrull		  #+#	#+#			 */
/*   Updated: 2024/12/16 12:10:59 by pborrull         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
//void PRIVMSG(const Client *sender, const std::string &target, const std::string &message)

static Channel	*checkChannel(std::string &nickname)
{

	std::vector<Channel *>	vchannel = Server::getInstance().getChannels();
	for (long unsigned int i = 0; i < vchannel.size(); i++)
	{
		if (vchannel[i]->getName() == nickname)
			return vchannel[i];
	}
	return NULL;
}
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
	std::vector<std::string> targets = split(words[0], ',');
	std::string	message = words[1];
	for (long unsigned int i = 2; i < words.size(); i++)
		message += " " + words[i];
	if (words[0].empty())
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
	
	// For clients
	for (long unsigned int i = 0; i < targets.size(); i++)
	{
		//Channel *ctarget = NULL;
	//	if (targets[i][0] == '&' || targets[i][0] == '#')
	//		ctarget = checkChannel(targets[i]);
		Client *target = checkClient(targets[i]);
	/*	if (target == NULL)) && ctarget != NULL)
		{
			std::set<int>& channelSockets = channels[target];
			for (std::set<int>::iterator it = channelSockets.begin(); it != channelSockets.end(); ++it)
			{
    			int socket = *it;
				if (clients[sender] == socket)
					continue; // No send to themselfs
				std::string fullMessage = ":" + sender->getNickname() + " PRIVMSG " + target->getNickname() + " :" + message + "\r\n";
				send(socket, fullMessage.c_str(), fullMessage.size(), 0);
			}
			break ;
		}*/
		if (target == NULL)// && ctarget == NULL)
			break ;
		int targetSocket = target->getFd();	
		std::string fullMessage = ":" + sender->getNickname() + " PRIVMSG " + target->getNickname() + " :" + message + "\r\n";
		send(targetSocket, fullMessage.c_str(), fullMessage.size(), 0);
	}
	// For channels
/*	if (channels.find(target) != channels.end())
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
	}*/
}
