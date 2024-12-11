/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:00:52 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/10 17:22:47 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Client.hpp"

// target se predefine en "", si no es pasado como parametro
void sendError(Client* client, int errorCode, const std::string& errorMessage,
	const std::string& target = "");

bool validCommand( Client *client, std::string str);
std::vector<std::string> split(const std::string& input, char delimiter);
bool    checkerIsLogged(Client *client);

