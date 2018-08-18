#ifndef SHELL_H__
#define SHELL_H__

#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>

#include "builtins.h" // builtin shell commands

namespace shell {

/**
    @brief Get system path using getenv("PATH")
    @return PATH as string
*/
std::string get_path(){
    return getenv("PATH");
}

/**
    @brief Parse user input.
    @param std::string line: user input
    @return arguments
*/
std::string parse(std::string line)
{
    /// \todo Parse input
    return line;
}


/**
    @brief Execute arguments
    @param cmd: command to execute
    @return command ouput
 */
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


/**
    @brief Handle builtin and system commands execution.
    @param std::string args: arguments to execute
    @return status
*/
int execute(std::string args)
{
    if(args=="exit"){
        return 0;
    }

    std::cout << exec(args);

    /// \todo Execution management

    return 1;
}

}
#endif // SHELL_H__