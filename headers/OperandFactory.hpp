#include "IOpearnd.hpp"
#include <vector>
#include <climits>
#include <cfloat>

#ifndef ABSTRACT_VM_OPERANDFACTORY_HPP
#define ABSTRACT_VM_OPERANDFACTORY_HPP

#include "Operand.hpp"

class Operand;

class OperandFactory {

public:

    OperandFactory() = default;

    OperandFactory &operator=(OperandFactory const &) = delete;

    OperandFactory(OperandFactory const &) = delete;

    ~OperandFactory() = default;

    static IOperand const * createOperand( IOperand::eOperandType type, std::string const & value );

private:

    static IOperand const * createInt8( std::string const & value );

    static IOperand const * createInt16( std::string const & value );

    static IOperand const * createInt32( std::string const & value );

    static IOperand const * createFloat( std::string const & value );

    static IOperand const * createDouble( std::string const & value );

};

#endif