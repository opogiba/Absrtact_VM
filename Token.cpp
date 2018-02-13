#include "headers/Token.hpp"

Token::Token(std::string value, eTokenType t) : val(std::move(value)), type(t) {}

// Getter

const std::string &Token::getVal() const {
    return val;
}

Token::eTokenType Token::getType() const {
    return type;
}
