#include <iostream>
#include <string>

#include "colormod.h" // ANSI terminal colors hellper class
#include "shell.h"    // actuall shell implementation


/**
   @brief Global variables:
*/
std::string whoami = shell::exec("whoami");
std::string hostname = shell::exec("hostname");


/**
   @brief Main loop: get input, parse, execute.
*/
void main_loop(){
    //clean whoami and hostname strings
    if (!whoami.empty() && whoami[whoami.length()-1] == '\n') { 
        whoami.erase(whoami.length()-1);
    }
    if (!hostname.empty() && hostname[hostname.length()-1] == '\n') { 
        hostname.erase(hostname.length()-1);
    }

    std::string line;
    std::string args;
    int status;

    do {
        std::string pwd = shell::exec("pwd");
        //clean pwd string
        if (!pwd.empty() && pwd[pwd.length()-1] == '\n') { 
            pwd.erase(pwd.length()-1);
        }

        std::cout << Color::FG_RED << whoami << "@" << hostname << ":" << Color::FG_DEFAULT 
                  << Color::FG_BLUE << pwd << Color::FG_DEFAULT << "$ ";

        std::getline(std::cin, line);
        status = shell::parse(line);
        
        line.clear();
        args.clear();
    } while (status);    
}


/**
    @brief Main entry point.
    @param argc Argument count.
    @param argv Argument vector.
    @return status code
    
 */
int main(int argc, char **argv)
{
    /// \todo Handle sh scripts as cmd arg

    /// \todo setup/config
    
    main_loop();
    
    /// \todo shutdown/cleanup.

    return EXIT_SUCCESS;
}