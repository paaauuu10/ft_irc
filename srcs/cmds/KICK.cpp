/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:07 by anovio-c          #+#    #+#             */
/*   Updated: 2024/11/26 13:31:28 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

// std::string SplitCmdK(std::string &cmd, std::vector<std::string> &tmp)
// {
// 	std::stringstream ss(cmd);
// 	std::string str, reason;
// 	int count = 3;
// 	while (ss >> str && count--)
// 		tmp.push_back(str);
// 	if(tmp.size() != 3) return std::string("");
// 	FindK(cmd, tmp[2], reason);
// 	return reason;
// }

std::string extractReason(std::string &line, std::vector<std::string> &parsed) {
	std::stringstream 	ss(line);
	std::string			str, reason;
	int					c = 3;

	while (ss >> parsed && c--)
		
	
}

std::string reason = SplitCmdK(cmd, tmp); // Extrae los primeros elementos y la razón.
if (tmp.size() < 2) { 
    // Error: No hay suficientes parámetros.
    senderror(461, GetClient(fd)->GetNickName(), GetClient(fd)->GetFd(), " :Not enough parameters\r\n"); 
    return ""; 
}

// Dividir canales.
std::vector<std::string> channels;
std::stringstream channelStream(tmp[0]);
std::string channel;
while (std::getline(channelStream, channel, ',')) {
    channels.push_back(channel);
}

// Dividir usuarios.
std::vector<std::string> users;
std::stringstream userStream(tmp[1]);
std::string user;
while (std::getline(userStream, user, ',')) {
    users.push_back(user);
}

// Verificar tamaño de las listas.
if (channels.size() != users.size()) {
    senderror(461, GetClient(fd)->GetNickName(), GetClient(fd)->GetFd(), " :Mismatched channel and user lists\r\n");
    return "";
}


void	extractChannels(std::vector<std::string> &channels, std::string &line) {
	
}


void KICK(std::string line, int fd) {
	std::vector<std::string>	channels;
	std::vector<std::string>	users;
	std::string					parsed;
	std::string					reason;
	
	
	reason = extractReason(line);
	extractChannels(channels, line);
}


cnanal,
user


 :reason