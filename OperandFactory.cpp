#include "headers/OperandFactory.hpp"

IOperand const * OperandFactory::createInt8(std::string const &value ) {
    if (std::stoll(value) > SCHAR_MAX || std::stoll(value) < SCHAR_MIN)
        throw OverLimit();
    return new Operand(value, IOperand::INT8);
}

IOperand const * OperandFactory::createInt16(std::string const &value ) {
    if (std::stoll(value) > SHRT_MAX || std::stoll(value) < SHRT_MIN)
        throw OverLimit();
    return new Operand(value, IOperand::INT16);
}

IOperand const * OperandFactory::createInt32(std::string const &value ) {
    if (std::stoll(value) > INT_MAX || std::stoll(value) < INT8_MIN)
        throw OverLimit();
    return new Operand(value, IOperand::INT32);
}

IOperand const * OperandFactory::createFloat(std::string const &value ) {
    if (std::stold(value) > FLT_MAX || std::stold(value) < -FLT_MAX)
        throw OverLimit();
    return new Operand(value, IOperand::FLOAT);
}

IOperand const * OperandFactory::createDouble(std::string const &value ) {
    if (std::stold(value) > DBL_MAX || std::stold(value) < -DBL_MAX)
        throw OverLimit();
    return new Operand(value, IOperand::DOUBLE);
}

IOperand const *OperandFactory::createOperand(IOperand::eOperandType type, std::string const &value)  {

    std::vector<IOperand const * (*) (std::string const &)> v_func;

    if (v_func.empty())
    {
        v_func.push_back(OperandFactory::createInt8);
        v_func.push_back(OperandFactory::createInt16);
        v_func.push_back(OperandFactory::createInt32);
        v_func.push_back(OperandFactory::createFloat);
        v_func.push_back(OperandFactory::createDouble);
    }
    return v_func[type](value);
}