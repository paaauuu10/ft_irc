/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:07 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/10 12:05:16 by anovio-c         ###   ########.fr       */
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

// std::string SplitCmdKICK(std::string &cmd, std::vector<std::string> &tmp)
// {
// 	std::stringstream ss(cmd);
// 	std::string str, reason;
// 	int count = 3;
// 	while (ss >> str && count--)
// 		tmp.push_back(str);
// 	if(tmp.size() != 3) return std::string("");
// 	FindKICK(cmd, tmp[2], reason);
// 	return reason;
// }

