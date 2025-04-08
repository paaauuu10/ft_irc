ft_irc - Internet Relay Chat Server
==================================

Description
-----------
This project involves creating an IRC server in C++98 that handles multiple clients simultaneously with non-blocking I/O operations. The server implements core IRC functionality including authentication, channel operations, and operator commands

Features
--------
- Multi-client support with non-blocking I/O (using poll()/select())
- Password authentication
- Channel operations (JOIN/PART/PRIVMSG)
- Operator commands (KICK/INVITE/TOPIC/MODE)
- Cross-platform compatibility (Linux/macOS)

Requirements
------------
- C++98 compiler with -Wall -Wextra -Werror flags
- Makefile with standard rules (all, clean, fclean, re)
- Unix-like system (Linux/macOS)
- Forbidden: External libraries, Boost, forking

Installation
------------
1. Clone the repository:
   git clone <your-repo>
2. Navigate to project:
   cd ft_irc
3. Compile the project:
   make
4. Run the server:
   ./ircserv <port> <password>
   Example: ./ircserv 6667 mypassword

Basic Usage
-----------
Connect with netcat:
  nc -C 127.0.0.1 6667

Basic commands:
  PASS yourpassword
  NICK yournick
  USER youruser * * :Your Name
  JOIN #channel
  PRIVMSG #channel :Hello world!

Implemented Commands
-------------------
PASS     - Authentication
NICK     - Set nickname
USER     - Set username
JOIN     - Join channel
PART     - Leave channel
PRIVMSG  - Send message
KICK     - Remove user (operator only)
INVITE   - Invite to channel
TOPIC    - Set channel topic
MODE     - Channel modes (+i/t/k/o/l)

Technical Constraints
---------------------
- Single poll()/select() for all I/O operations
- Non-blocking file descriptors required
- No memory leaks or crashes allowed
- Must handle partial commands (test with ctrl+D splits)
- Must comply with C++98 standard

Testing
-------
Verify:
- Multiple simultaneous clients
- Partial command handling
- All error cases
- Operator privileges
- Non-blocking behavior
