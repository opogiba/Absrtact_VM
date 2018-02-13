#ifndef ABSTRACT_VM_TOKEN_HPP
#define ABSTRACT_VM_TOKEN_HPP

#include "IOpearnd.hpp"

class Token {

public:

    enum eTokenType {
        push, pop, dump, assert, add, sub, mul, div, mod, print, exit, value
    };

    Token() = delete;

    Token(std::string, eTokenType);

    Token &operator=(Token const &) = delete;

    Token(Token const &) = delete;

    ~Token() = default;

    const std::string &getVal() const;

    eTokenType getType() const;

private:

    std::string val;

    eTokenType type;
};

#endif
