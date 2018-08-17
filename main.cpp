#include <iostream>
#include <string>
#include <array>

//#include <cstdio>

#include <memory>
#include <stdexcept>


#include <sys/wait.h> /* waitpid() and associated macros */
#include <unistd.h>   /* chdir(), fork(), exec(), getopt, pid_t */
#include <stdlib.h>   /* malloc(), realloc(), free(), exit(), execvp(), getenv(), EXIT_SUCCESS, EXIT_FAILURE */
#include <stdio.h>    /* fprintf(), printf(), stderr, getchar(), perror(), */

/* Function prototypes for builtin shell commands:
---------------------------------------------------*/

/**
    @brief Builtin command: change directory.
    @param args List of args.  args[0] is "cd".  args[1] is the directory.
    @return Always returns 1, to continue executing.
*/
int tss_cd(std::pair<std::string, std::string> args);

/**
   @brief Builtin command: print help.
   @return Always returns 1, to continue executing.
 */
int tss_help();

/**
   @brief Builtin command: exit.
   @return Always returns 0, to terminate execution.
 */
int tss_exit();


/* Function prototypes for hellper functions:
----------------------------------------------*/

/**
    @brief Get system path using getenv("PATH")
    @return PATH as string
*/
std::string get_path();


/* Main functions prototypes:
---------------------------------------------------*/

/**
   @brief Main loop: get input, parse, execute.
*/
void main_loop();

/**
    @brief Parse user input.
    @param std::string line: user input
    @return arguments
*/
std::string parse(std::string line);


/**
    @brief Execute command and get output back.
    @param cmd: command to execute
    @return command ouput
 */
std::string exec(std::string cmd);


/**
    @brief Execute arguments
    @param std::string args: arguments to execute
    @return status
*/
int execute(std::string args);



/* Global variables:
---------------------------------------------------*/
std::string whoami = exec("whoami");
std::string hostname = exec("hostname");


/**
    @brief Main entry point.
    @param argc Argument count.
    @param argv Argument vector.
    @return status code
 */
int main(int argc, char **argv)
{
    // setup
    
    main_loop();
    
    // shutdown/cleanup.

    return EXIT_SUCCESS;
}


/* Builtin function definitons
----------------------------------------------*/
int tss_cd(std::pair<std::string, std::string> args)
{
    std::cout << "changing dir..." << std::endl;
}

int tss_help()
{
    std::cout << "help..." << std::endl;
}

int tss_exit()
{
    return 0;
}


/* Helper function definitons
----------------------------------------------*/
std::string get_path(){
    return getenv("PATH");
}


/* Main functions definitions:
---------------------------------------------------*/
void main_loop()
{
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
        std::string pwd = exec("pwd");
        //clean pwd string
        if (!pwd.empty() && pwd[pwd.length()-1] == '\n') { 
            pwd.erase(pwd.length()-1);
        }

        std::cout << whoami << "@" << hostname << ":" << pwd << "$ ";
        
        std::getline(std::cin, line);
        args = parse(line);
        status = execute(args);     
        
        line.clear();
        args.clear();
    } while (status);
}


std::string parse(std::string line)
{
    std::cout << "parsing..." << std::endl;
    return line;
}


int execute(std::string args)
{
    std::cout << "executing... " << args << std::endl;
    std::cout << exec(args);
    return 1;
}


std::string exec(std::string cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);

    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    
    return result;
}