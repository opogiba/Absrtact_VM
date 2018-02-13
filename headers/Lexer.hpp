#include "iostream"
#include "map"
#include <vector>

#ifndef ABSTRACT_VM_LEXER_H
#define ABSTRACT_VM_LEXER_H

#include "Token.hpp"
class Lexer {

public:

    Lexer();

    Lexer &operator=(Lexer const &) = delete;

    Lexer(Lexer const &) = delete;

    virtual ~Lexer() = default;

    std::vector <Token *> generate_tokens(const std::string &);

private:

    std::map<std::string, Token::eTokenType> tokenMap;

    bool white_spaces(std::string str);

    std::vector<std::string> split(const std::string& s, char c);

};

#endif
