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
    @brief Execute arguments
    @param cmd: command to execute
    @return command ouput
 */
std::string exec(std::string cmd) {
    // http://man7.org/linux/man-pages/man3/popen.3.html
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
    /// \todo Ignores stderr
}


/**
    @brief Parse user input.
    @param std::string line: user input
    @return status
*/
int parse(std::string input)
{
    std::string arg = input.substr(0, input.find(" "));
    if(arg=="exit"){
        return 0;
    } 
    else if(arg=="help"){
        return builtins::funcMap["help"]("");
    } 
    else if(arg=="cd"){
        builtins::tss_cd(input.substr(input.find_first_of(" \t")+1));
    } 
    else {
        std::cout << exec(input);   
        return 1; 
    }

    /// \todo Actual input parsing
}

}
#endif // SHELL_H__