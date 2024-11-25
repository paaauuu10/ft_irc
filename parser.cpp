/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:31:53 by pbotargu          #+#    #+#             */
/*   Updated: 2024/11/25 12:56:32 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include <cctype> 


bool validCommand(std::string str)
{
    int index = 0;
    std::string commands[17] = { "PASS", "NICK", "USER", "SERVER", "OPER", "QUIT", "SQUIT", "JOIN", "PART", "MODE", "TOPIC", "NAMES", "LIST", "INVITE", "KICK", "VERSION", "PRIVMSG"};
    std::string cmd = str.substr(0, str.find(' '));
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) {
        return std::toupper(c);
    }); // Convert str into capital letters
    while (cmd != ('/' + commands[index++]))
    {
        if (index == 17)
            return false;
    }

    switch(index)
    {
        case 1:
            std::cout << commands[index - 1] << std::endl;
            //pass()
            break;
        case 2:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 3:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 4:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 5:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 6:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 7:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 8:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 9:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 10:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 11:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 12:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 13:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 14:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 15:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 16:
            std::cout << commands[index - 1] << std::endl;
            break;
        case 17:
            std::cout << commands[index - 1] << std::endl;
            break;
    }
    return true;
}
void parser(std::string str)
{
    if  (str.size() > 0 && str[0] == '/')
    {
        if (!validCommand(str))
            std::cout << str.erase(0,1) << " :Unknown command" << std::endl;
    }
    else
        std::cout << "Message send: " << str << std::endl;

}
int main(int argc, char **argv)
{
    (void)argc;
    parser(argv[1]);
}