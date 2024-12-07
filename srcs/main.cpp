/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:18:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/07 11:33:33 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Please use ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	
	try {
		Server	*server = Server::getInstance(atoi(argv[1]), argv[2]);
		
		// Init the server
		if (server->start() != 0) {
			std::cerr << "Failed to start the server." << std::endl;
			Server::destroyInstance();
			return (1);
		}
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	// free recurses of server instance
	Server::destroyInstance();
	return (0);
}
