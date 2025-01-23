/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:00:21 by anovio-c          #+#    #+#             */
/*   Updated: 2025/01/23 11:00:17 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "ErrorCodes.hpp"

// :<server> <error_code> <target> :<error_message>

void sendError(Client* client, ErrorCode errorCode, const std::string& target) {
    if (!client) {
        std::cerr << "Error: Cliente no está conectado.\n";
        return;
    }

    std::string serverName = Server::getServerName();
	std::string	errorMessage = ErrorMessages.at(errorCode);

    std::ostringstream oss;
    oss << ":" << serverName << " " << errorCode << " " 
        << (target.empty() ? "*" : target) // Usa "*" si el target no está definido.
        << " :" << errorMessage << "\r\n";
	std::string msg = oss.str();
    send(client->getFd(), msg.c_str(), msg.size(), 0);
}

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
	if (input.empty())
		return tokens;
    for (std::string::size_type i = 0; i < input.size(); i++) {
        if (input[i] == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else
            token += input[i];
    }
    if (!token.empty())
        tokens.push_back(token);
    return (tokens);
}

std::string trim(const std::string &str)
{
	size_t first = str.find_first_not_of(" \t\r");
	if (first == std::string::npos)
		return "";
	size_t last = str.find_last_not_of(" \t\r");
	return str.substr(first, last - first + 1);
}


