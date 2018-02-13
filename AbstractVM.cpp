#include "headers/AbstractVM.hpp"

AbstractVM::AbstractVM(int fd) : fd(fd), stack()  {
    parser = new Parser(fd);
}

AbstractVM::~AbstractVM()  {
    delete(parser);
    this->v_func.clear();

    for (IOperand const *operand: stack) {
        delete (operand);
        stack.pop();
    }

//    if (!stack.empty())
//    {
//        for (auto i = stack.end() - 1; i >= stack.begin(); --i) {
//            printf("dsadasdsadasdsa\n");
//            delete(*i);
//            stack.pop();
//        }
//    }
}

// Start of the parsing

void AbstractVM::analyze_line(std::string line) {

    Parser::eParserStatsus status = parser->parse_line(line);
    this->fd = parser->getFd();

    if (status == Parser::comment || status == Parser::exit) {
        return;
    }
    if (status == Parser::exitfd)
    {
        if(!get_exit_flag())
            throw NonExit();
    }
    if (status == Parser::sucsess)
    {
        if (v_func.empty())
        {
            v_func.push_back(&AbstractVM::push);
            v_func.push_back(&AbstractVM::pop);
            v_func.push_back(&AbstractVM::dump);
            v_func.push_back(&AbstractVM::assert);
            v_func.push_back(&AbstractVM::add);
            v_func.push_back(&AbstractVM::sub);
            v_func.push_back(&AbstractVM::mul);
            v_func.push_back(&AbstractVM::div);
            v_func.push_back(&AbstractVM::mod);
            v_func.push_back(&AbstractVM::print);
        }
        (this->*(v_func[parser->getTokens()[0]->getType()]))(parser->getTokens());
        return;
    }
}

// Additional - make value and type for Operand

void AbstractVM::make_value(IOperand::eOperandType &type, Token * token, std::string &value) {

    std::regex rex(R"(((?:(?:Int|int|INT)(?:8|16|32))|(?:(?:Float|float|FLOAT))|(?:(?:Double|double|DOUBLE)))\(([+-]?\d+(?:\.?\d+)?)\))");
    std::cmatch res;

    std::regex_match(token->getVal().c_str(), res, rex);
    std::string tmp = res[1];

    if (tmp.find('8') != std::string::npos)
        type = IOperand::INT8;
    if (tmp.find("16") != std::string::npos)
        type = IOperand::INT16;
    if (tmp.find("32") != std::string::npos)
        type = IOperand::INT32;
    if (tmp.find('F') != std::string::npos || tmp.find('f') != std::string::npos)
    {
        value = std::to_string(std::stold(res[2]));
        type = IOperand::FLOAT;
        return;
    }
    if (tmp.find('D') != std::string::npos || tmp.find('d') != std::string::npos)
    {
        value = std::to_string(std::stold(res[2]));
        type = IOperand::DOUBLE;
        return;
    }
    value = res[2];
}

// Additional - make stack operation add - sub - div - mod - mult

void AbstractVM::make_operation(Operand::eOperation op) {

    if (stack.size() < 2)
        throw StackOperation();

    IOperand const *left;
    IOperand const *right;

    right = stack.top();
    stack.pop();
    left = stack.top();
    stack.pop();

    try {

        if (op == Operand::PLUS)
            stack.push(*left + *right);
        if (op == Operand::MINUS)
            stack.push(*left - *right);
        if (op == Operand::MULT)
            stack.push(*left * *right);
        if (op == Operand::DIV) {
            try {
                stack.push(*left / *right);
            }
            catch (std::exception &e) {
                throw ;
            }
        }
        if (op == Operand::MOD) {
            try {
                stack.push(*left % *right);
            }
            catch (std::exception &e) {
                throw ;
            }
        }
        delete(left);
        delete(right);
    }
    catch (std::exception &e){
        stack.push(left);
        stack.push(right);
        throw ;
    }
}

// Stack Operations

void AbstractVM::push(std::vector<Token *> token) {

    IOperand::eOperandType type;
    std::string value;

    make_value (type, token[1], value);
    this->stack.push(OperandFactory::createOperand(type, value));
}

void AbstractVM::pop(std::vector<Token *>) {

    if (stack.empty())
        throw EmptyStack();
    else
        stack.pop();
}

void AbstractVM::assert(std::vector<Token *> token) {

    IOperand::eOperandType type;
    std::string value;

    make_value (type, token[1], value);
    if (stack.top()->getType() != type)
        throw TopType();
    if (value != stack.top()->toString())
        throw TopValue();
}

void AbstractVM::add(std::vector<Token *>) {
    make_operation(Operand::PLUS);
}

void AbstractVM::sub(std::vector<Token *>) {
    make_operation(Operand::MINUS);
}

void AbstractVM::mul(std::vector<Token *>) {
    make_operation(Operand::MULT);
}

void AbstractVM::div(std::vector<Token *>) {
    make_operation(Operand::DIV);
}

void AbstractVM::mod(std::vector<Token *>) {
    make_operation(Operand::MOD);
}

void AbstractVM::dump(std::vector<Token *>) {
    if (stack.empty())
        throw EmptyStack();
    for (auto i = stack.end() - 1; i >= stack.begin(); i--)
        std::cout << (*i)->toString() << std::endl;
}

void AbstractVM::print(std::vector<Token *>) {
    if(stack.top()->getType() != IOperand::INT8)
        throw TopType();
    else {
       printf("%c\n", std::stoi(stack.top()->toString()));
    }
}

// GET

bool AbstractVM::get_exit_flag(){
    return parser->isFlag_exit();
}

