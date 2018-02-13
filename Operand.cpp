#include "headers/Operand.hpp"

Operand::Operand(std::string str, eOperandType t) : type(t), precision(type), val(std::move(str)) {}

// actions with Operand

IOperand const *Operand::more_than_float(const IOperand &new_operand, eOperation op, eOperandType new_type) const {

    long double result = std::stold(this->val);

    if (op == PLUS)
        result += std::stold(new_operand.toString());
    else if (op == MINUS)
        result -= std::stold(new_operand.toString());
    else if (op == DIV)
        result /= std::stold(new_operand.toString());
    else if (op == MULT)
        result *= std::stold(new_operand.toString());
    else if (op == MOD)
        result = fmodl(result, std::stold(new_operand.toString()));
    return OperandFactory::createOperand(new_type, std::to_string(result));
}

IOperand const *Operand::less_than_float(const IOperand &Inew, eOperation op, eOperandType new_type) const {

    long long result = std::stoll(this->val);

    if (op == PLUS)
        result += std::stoll(Inew.toString());
    else if (op == MINUS)
        result -= std::stoll(Inew.toString());
    else if (op == DIV)
        result /= std::stoll(Inew.toString());
    else if (op == MULT)
        result *= std::stoll(Inew.toString());
    else if (op == MOD)
        result = result % std::stoll(Inew.toString());
    return OperandFactory::createOperand(new_type, std::to_string(result));
}

// Overload Operators

const IOperand * Operand::operator+(IOperand const &rhs) const  {

    eOperandType new_type = rhs.getType();

    if (this->type > new_type)
        new_type = type;
    if (new_type >= FLOAT)
        return more_than_float(rhs, PLUS, new_type);
    else
        return less_than_float(rhs, PLUS, new_type);
}

const IOperand * Operand::operator-(IOperand const &rhs) const  {

    eOperandType new_type = rhs.getType();

    if (this->type > new_type)
        new_type = type;
    if (new_type >= FLOAT)
        return more_than_float(rhs, MINUS, new_type);
    else
        return less_than_float(rhs, MINUS, new_type);
}

const IOperand * Operand::operator*(IOperand const &rhs) const {

    eOperandType new_type = rhs.getType();

    if (this->type > new_type)
        new_type = type;
    if (new_type >= FLOAT)
        return more_than_float(rhs, MULT, new_type);
    else
        return less_than_float(rhs, MULT, new_type);
}

const IOperand * Operand::operator%(IOperand const &rhs) const {

    eOperandType new_type = rhs.getType();

    if(std::stold(rhs.toString()) == 0.0)
        throw EcxDivModbyZero();

    if (this->type > new_type)
        new_type = type;
    if (new_type >= FLOAT)
        return more_than_float(rhs, MOD, new_type);
    else
        return less_than_float(rhs, MOD, new_type);
}

const IOperand * Operand::operator/(IOperand const &rhs) const {

    eOperandType new_type = rhs.getType();

    if(std::stold(rhs.toString()) == 0.0)
        throw EcxDivModbyZero();

    if (this->type > new_type)
        new_type = type;
    if (new_type >= FLOAT)
        return more_than_float(rhs, DIV, new_type);
    else
        return less_than_float(rhs, DIV, new_type);
}

// Getters

std::string const & Operand::toString() const  {
    return (this->val);
}

IOperand::eOperandType Operand::getType() const {
    return this->type;
}

int Operand::getPrecision() const {
    return this->precision;
}
