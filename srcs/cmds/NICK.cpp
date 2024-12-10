/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:47:10 by anovio-c          #+#    #+#             */
/*   Updated: 2024/12/10 12:15:24 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include <string>
#include <iostream>
#include <set>

static int checkNickname(Client *client, std::string &nickname)
{
	for (int i = 0; i < client.size(); i++)
	{
		if (client[i].getNickname() == nickname)
			return 1;
	}
	return 0;
}

static int validateNick(std::string &nick)
{
	if (nick.size() > 9 || (nick[0] >= '0' && nick[0] <= '9') || nick[0] == '-')
		return 1;
	//	std::cout << "Erroneous nickname (Erroneous first letter)" << std::endl;
    const std::set<char> validChar =  {'-', '[', ']', '\\', '^', '_', '{', '}', '|'};
	for (size_t i = 0; i < nick.size(); ++i)
	{
		if ((validChar.find(nick[i]) == validChar.end()) && (nick[i] < '0' || nick[i] > '9')
	   	 && (nick[i] < 'a' || nick[i] > 'z') && (nick[i] < 'A' || nick[i] > 'Z'))
			return 1;
	//		std::cout << "Erroneous nickname (Erroneous letter)" << std::endl;
    }
	return 0;
}

//int		NICK(Client *client, std::string &nickname) //Este es el correcto
int		NICK(std::string &nick, std::string &nicka)
{
	if (nick.empty())	
		std::cout << "No nickname given" << std::endl;
		//sendError(client, 431, "No nickname given"); //ERR_NONICKNAMEGIVEN
	else if (validateNick(nick))
		std::cout << "Erroneous nickname" << std::endl;
		//sendError(client, 432, "Erroneous nickname"); //ERR_ERRONEUSNICKNAME
	//if (nick == client.getNickname()) //Este es el correcto
	else if (nick == nicka)
		std::cout << "Nickname collision KILL" << std::endl;
		//sendError(client, 436, "Nickname collision KILL"); //ERR_NICKCOLLISION
	else if (checkNickname(client, nickname))
		std::cout << "Nickname is already in use" << std::endl;
		//sendError(client, 433, "Nickname is already in use"); //ERR_NICKNAMEINUSE
	else
	{
		if (client._nickname.empty())
			std::cout << "Introducing new nick \"" << nick << "\"." << std::endl; //Se tiene que utilizar send
		else
			std::cout << client.getNickname() << " changed his nickname to " << nick << "." << std::endl; //Se tiene que utilizar send y enviarlo a todos
		client.setNickname(nick);
	}
	return 0;
}

int main(void)
{
	std::string s= ".asds";
	std::string r= "hola";
	NICK(s, r);
	return 0;
}



/*Reglas básicas para los nicknames en un servidor IRC
Longitud máxima:

Un nickname debe tener como máximo 9 caracteres, según el estándar del RFC 2812. Sin embargo, muchos servidores modernos permiten más caracteres (típicamente entre 15 y 30) como extensión al estándar.
Carácteres válidos:

Permitidos:
Letras (a-z, A-Z).
Dígitos (0-9).
Guiones (-), guion bajo (_), corchetes ([ ]), barras invertidas (\), acentos graves (<code>`</code>), y caracteres de corchete (^, {, }).
No permitido como primer carácter:
Números (0-9).
Guiones (-).
Caracteres especiales como . (punto), @, !, y espacios no están permitidos.
Distinción de mayúsculas y minúsculas:

Los nicknames son case-insensitive según el estándar del IRC. Por ejemplo, John, john, y JOHN se consideran equivalentes.
Sin embargo, esto puede variar en implementaciones específicas dependiendo de la configuración del servidor.
Nickname único:

Cada cliente debe tener un nickname único dentro del servidor. Si el nickname que solicita está en uso, el servidor devolverá un error (ERR_NICKNAMEINUSE, código 433).
Prohibiciones específicas:

Los servidores pueden restringir nicknames que contengan palabras reservadas, ofensivas o ya utilizadas por bots del sistema.
Algunos servidores bloquean caracteres específicos dependiendo del soporte para juegos de caracteres, como UTF-8.
Errores comunes al configurar un nickname
Cuando un cliente intenta usar un nickname que no cumple con las reglas, el servidor responde con uno de los siguientes códigos de error:

ERR_ERRONEUSNICKNAME (432)

El nickname contiene caracteres no permitidos o no cumple con las reglas de formato.
ERR_NICKNAMEINUSE (433)

El nickname solicitado ya está en uso por otro cliente en el servidor.
ERR_NICKCOLLISION (436)

Hay un conflicto de nickname al conectar dos servidores.
Ejemplo de nicknames válidos e inválidos
Válidos:
JohnDoe
_IRCUser
user-123
{coolNick}
Inválidos:
123John (empieza con un número)
user name (contiene un espacio)
nick!@ (caracteres no permitidos como ! o @)
.nickname (empieza con un punto)*/
