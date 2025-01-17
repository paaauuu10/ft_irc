#include "ErrorCodes.hpp"

std::map<ErrorCode, std::string> createErrorMessages() {
    std::map<ErrorCode, std::string> m;
    m[ERR_NOSUCHNICK] = "No such nick/channel";
    m[ERR_NOSUCHCHANNEL] = "No such channel";
    m[ERR_NORECIPIENT] = "No recipient given (PRIVMSG)";
    m[ERR_NOTEXTTOSEND] = "No text to send";
    m[ERR_NONICKNAMEGIVEN] = "No nickname given";
    m[ERR_ERRONEUSNICKNAME] = "Erroneus nickname";
    m[ERR_NICKNAMEINUSE] = "Nickname is already in use";
    m[ERR_NICKCOLLISION] = "Nickname collision KILL";
    m[ERR_NOTONCHANNEL] = "You're not on that channel";
    m[ERR_USERONCHANNEL] = "is already on channel";
    m[ERR_NOLOGIN] = "User not logged in";
    m[ERR_NOTREGISTERED] = "You have not registered";
    m[ERR_NEEDMOREPARAMS] = "Not enough parameters";
    m[ERR_ALREADYREGISTRED] = "You may not reregister";
    m[ERR_PASSWDMISMATCH] = "Password incorrect";
    m[ERR_UNKNOWNMODE] = "Unknown mode";
    m[ERR_INVITEONLYCHAN] = "Cannot join channel (+i)";
    m[ERR_CHANNELISFULL] = "Cannot join channel (+l)";
    m[ERR_BADCHANNELKEY] = "Cannot join channel (+k)";
    m[ERR_CHANOPRIVSNEEDED] = "You're not channel operator";
    return m;
}

const std::map<ErrorCode, std::string> ErrorMessages = createErrorMessages();