#include <iostream>
#include <string>
#include <stdlib.h>     /* getenv */

/**
   @brief Get system path using getenv("PATH")
   @return PATH as string
 */
std::string get_path(){
  return getenv("PATH");
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main ()
{
  std::string path;
  path = get_path();
  std::cout << path << std::endl;
}