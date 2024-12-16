/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:21:35 by pbotargu          #+#    #+#             */
/*   Updated: 2024/12/13 16:59:26 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <signal.h>
#include <cstring>

void	ctrlc(int signal)
{
    (void)signal;
    std::string art = 
"               ...\n"
"             ;::::;\n"
"           ;::::; :;\n"
"         ;:::::'   :;\n"
"        ;:::::;     ;.\n"
"       ,:::::'       ;           OOO\\\n"
"       ::::::;       ;          OOOOO\\\n"
"       ;:::::;       ;         OOOOOOOO\n"
"      ,;::::::;     ;'         / OOOOOOO\n"
"    ;:::::::::`. ,,,;.        /  / DOOOOOO\n"
"  .';:::::::::::::::::;,     /  /     DOOOO\n"
" ,::::::;::::::;;;;::::;,   /  /        DOOO\n"
";`::::::`'::::::;;;::::: ,#/  /          DOOO\n"
":`:::::::`;::::::;;::: ;::#  /            DOOO\n"
"::`:::::::`;:::::::: ;::::# /              DOO\n"
"`:`:::::::`;:::::: ;::::::#/               DOO\n"
" :::`:::::::`;; ;:::::::::##                OO\n"
" ::::`:::::::`;::::::::;:::#                OO\n"
" `:::::`::::::::::::;'`:;::#                O\n"
"  `:::::`::::::::;' /  / `:#\n"
"   ::::::`:::::;'  /  /   `#\"\n";

    std::cout << std::endl;
    std::cout << art << std::endl;
}

void	signals(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ctrlc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(56);
	memset(&sa, 0, sizeof(sa));
}
