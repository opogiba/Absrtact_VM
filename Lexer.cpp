#include "headers/Lexer.hpp"

Lexer::Lexer() {
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("push", Token::push));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("pop", Token::pop));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("dump", Token::dump));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("assert", Token::assert));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("add", Token::add));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("sub", Token::sub));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("mul", Token::mul));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("div", Token::div));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("mod", Token::mod));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("print", Token::print));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("exit", Token::exit));
    this->tokenMap.insert(std::pair<std::string, Token::eTokenType> ("value", Token::value));
}

// Generate New Tokens

std::vector <Token *> Lexer::generate_tokens(const std::string &line) {

    std::vector<std::string> v = split(line, ' ');
    std::map<std::string, Token::eTokenType>::iterator it;
    std::vector<Token *> tokens;

    for (long long i = 0; i < v.size(); i++)
    {
        it = tokenMap.find(v[i]);
        if (it != tokenMap.end())
            tokens.push_back(new Token(v[i], it->second));
        else
            tokens.push_back(new Token(v[i], Token::value));
    }
    v.clear();
    return tokens;
}

// Additional functions

bool Lexer::white_spaces(std::string str) {

    int i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
        i++;
    return i != str.length();
}

std::vector<std::string> Lexer::split(const std::string& s, char c) {

    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);
    std::vector<std::string> v;

    if(j == std::string::npos && white_spaces(s))
        v.push_back(s.substr(i, s.length()));
    while (j != std::string::npos) {
        if (s[i] != c)
            v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);
        if (j == std::string::npos && white_spaces(s.substr(i, s.length())))
            v.push_back(s.substr(i, s.length()));
    }
    return v;
}