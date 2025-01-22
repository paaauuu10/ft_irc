/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:00:52 by anovio-c          #+#    #+#             */
/*   Updated: 2025/01/21 12:27:08 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Client.hpp"
#include "ErrorCodes.hpp"

void sendError(Client* client, ErrorCode errorCode, const std::string& target = "");

std::vector<std::string>	split(const std::string& input, char delimiter);
std::string 				trim(const std::string &str);
int 						checkNickname(std::string &nickname);

void						signals(void);


