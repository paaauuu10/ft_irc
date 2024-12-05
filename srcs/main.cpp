/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:18:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/03 10:54:08 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Please use ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	Server server(atoi(argv[1]), argv[2]);

	server.start();
}
