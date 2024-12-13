/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:00:52 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/13 11:47:03 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Client.hpp"

// target se predefine en "", si no es pasado como parametro
void sendError(Client* client, int errorCode, const std::string& errorMessage,
	const std::string& target = "");

std::vector<std::string> split(const std::string& input, char delimiter);
bool    checkerIsLogged(Client *client);
int 	checkNickname(std::string &nickname);

void	signals(void);


