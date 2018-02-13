//
// Created by Oleksiy Pogiba on 2/8/18.
//

#ifndef ABSTRACT_VM_ABSTRACTVM_HPP
#define ABSTRACT_VM_ABSTRACTVM_HPP

#include "Parser.hpp"
#include "../MutantStack.cpp"
#include "OperandFactory.hpp"

class AbstractVM {

public:

    AbstractVM() = delete;

    explicit AbstractVM(int fd);

    AbstractVM &operator=(AbstractVM const &) = delete;

    AbstractVM(AbstractVM const &) = delete;

    virtual ~AbstractVM();

    void analyze_line(std::string line);

    bool get_exit_flag();

    MutantStack<IOperand const *> stack;

private:

    void make_operation(Operand::eOperation);

    void make_value(IOperand::eOperandType &type, Token * token, std::string &value);

    void push(std::vector<Token *>);

    void pop(std::vector<Token *>);

    void dump(std::vector<Token *>);

    void assert(std::vector<Token *>);

    void add(std::vector<Token *>);

    void sub(std::vector<Token *>);

    void mul(std::vector<Token *>);

    void div(std::vector<Token *>);

    void mod(std::vector<Token *>);

    void print(std::vector<Token *>);

    std::vector<void (AbstractVM::*)(std::vector<Token *>)> v_func;

    Parser *parser;

    int fd;
};


#endif //ABSTRACT_VM_ABSTRACTVM_HPP

