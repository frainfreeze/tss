#ifndef COLORMOD_H__
#define COLORMOD_H__

#include <ostream>

/**
 * ANSI terminal colors hellper class
 * 
 * https://en.wikipedia.org/wiki/ANSI_escape_code
 * 
 * https://misc.flogisoft.com/bash/tip_colors_and_formatting
 */
namespace Color {

enum Code {
    FG_RED      = 31, //!< 31 foreground red    
    FG_GREEN    = 32, //!< 32 foreground green  
    FG_BLUE     = 34, //!< 34 foreground blue   
    FG_DEFAULT  = 39, //!< 39 foreground default
    BG_RED      = 41, //!< 41 background red    
    BG_GREEN    = 42, //!< 42 background green  
    BG_BLUE     = 44, //!< 44 background blue   
    BG_DEFAULT  = 49  //!< 49 background default
};

std::ostream& operator<<(std::ostream& os, Code code) {
    return os << "\033[" << static_cast<int>(code) << "m";
}

}

#endif // COLORMOD_H_