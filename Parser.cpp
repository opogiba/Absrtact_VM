#include "headers/Parser.hpp"

Parser::~Parser() {
    for (auto &token : tokens)
        delete token;
    tokens.clear();
    delete(this->lex);
}

Parser::Parser(int flag_fd) : fd(flag_fd) {
    this->lex = new Lexer();
}

// Check Value for commands

void    Parser::check_operand(std::string token_operand) {

    std::regex rex(R"(((?:(?:Int|int|INT)(?:8|16|32))|(?:(?:Float|float|FLOAT))|(?:(?:Double|double|DOUBLE)))\(([+-]?\d+(?:\.?\d+)?)\))");
    std::cmatch res;
    std::string tmp;
    std::regex_match(token_operand.c_str(), res, rex);

    if (res.size() != 3)
        throw NotValidOperand();
    tmp = res[0];
    if(tmp.find("Int") != std::string::npos && tmp.find('.') != std::string::npos)
        throw InttoDouble();
}

// Check for comment and if fd == 0 for command ;;

bool    Parser::check_comment(std::string comment) {

    if (comment.length() == 2 && comment[0] == ';' && comment[1] == ';' && this->fd == 0)
    {
        this->fd = -1;
        return true;
    }
    else if(comment[0] == ';')
        return true;
    return false;
}

// Parse line

Parser::eParserStatsus    Parser::parse_line(std::string line) {


    for (auto &token : tokens)
        delete token;
    tokens.clear();

    if(line.empty())
        return comment;

    tokens = this->lex->generate_tokens(line);

    if (tokens.empty())
        return sucsess;

    if(check_comment(tokens[0]->getVal()))
    {
        if (this->fd == -1)
            return exitfd;
        return comment;
    }

    if (tokens.size() > 2)
        throw NotvalidCommand();

    if((tokens[0]->getVal() == "push" || tokens[0]->getVal() == "assert"))
    {
        if (tokens.size() < 2)
            throw PushAssert();
        else
            check_operand(tokens[1]->getVal());
    }
    else if (tokens[0]->getVal() == "exit") {
        flag_exit = true;
        return exit;
    }
    else if (tokens[0]->getType() == 11) {
        throw NotvalidCommand();
    }
    return sucsess;
}

// Getter

bool Parser::isFlag_exit() const {
    return flag_exit;
}

const std::vector<Token *> &Parser::getTokens() const {
    return tokens;
}

int Parser::getFd() const {
    return fd;
}