#include "Server.hpp"
#include <signal.h>
#include <cstring>

void	ctrlc(int signal)
{
    (void)signal;
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