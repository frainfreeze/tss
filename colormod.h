#ifndef COLORMOD_H__
#define COLORMOD_H__

#include <ostream>

/*
 * ANSI terminal colors hellper class
 * https://en.wikipedia.org/wiki/ANSI_escape_code
 * https://misc.flogisoft.com/bash/tip_colors_and_formatting
 */
namespace Color {

enum Code {
    FG_RED      = 31,
    FG_GREEN    = 32,
    FG_BLUE     = 34,
    FG_DEFAULT  = 39,
    BG_RED      = 41,
    BG_GREEN    = 42,
    BG_BLUE     = 44,
    BG_DEFAULT  = 49
};

std::ostream& operator<<(std::ostream& os, Code code) {
    return os << "\033[" << static_cast<int>(code) << "m";
}

}

#endif // COLORMOD_H_