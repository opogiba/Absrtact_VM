#include <string>
#include "Lexer.hpp"
#include "Exceptions.hpp"
#include <cstring>
#include "regex"

#ifndef ABSTRACT_VM_PARSER_HPP
#define ABSTRACT_VM_PARSER_HPP

class Parser {

public:

    enum eParserStatsus {
        comment, exitfd, exit, sucsess
    };

    Parser() = delete;

    explicit Parser(int flag_fd);

    Parser(Parser const &) = delete;

    Parser &operator=(Parser const &) = delete;

    virtual ~Parser();

    eParserStatsus parse_line (std::string line);

    bool isFlag_exit() const;

    const std::vector<Token *> &getTokens() const;

    int getFd() const;

private:

    bool flag_exit;

    int fd;

    Lexer *lex;

    std::vector<Token *> tokens;

    void check_operand(std::string);

    bool check_comment(std::string);

};

#endif
