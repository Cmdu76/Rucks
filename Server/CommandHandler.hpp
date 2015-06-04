#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Server;

class CommandHandler
{
    public:
        CommandHandler(Server& server);

        void run();

        friend Server;

    protected:
        typedef std::vector<std::string> Arguments;
        static Arguments splitArguments(std::string const& command);

    public:
        void handle(std::string const& command);
        void handleStop(Arguments args);
        void handleList(Arguments args);
        void handleConnected(Arguments args);
        void handleSay(Arguments args);
        void handleHelp(Arguments args);

    protected:
        Server& mServer;
};

#endif // COMMANDHANDLER_HPP