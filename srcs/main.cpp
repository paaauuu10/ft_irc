/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:18:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/10 18:27:12 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Utils.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Please use ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	
	try {
		Server::init(atoi(argv[1]), argv[2]);
		Server	&server = Server::getInstance();
		
		// Init the server
		if (server.start() != 0) {
			std::cerr << "Failed to start the server." << std::endl;
			return (1);
		}
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
