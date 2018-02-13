#include "cmath"
#include "IOpearnd.hpp"
#include "Exceptions.hpp"

#ifndef ABSTRACT_VM_OPERAND_HPP
#define ABSTRACT_VM_OPERAND_HPP

#include "OperandFactory.hpp"

class OperandFactory;

class Operand : public IOperand {

public:

    enum eOperation {
        PLUS, MINUS, DIV, MULT, MOD
    };
    Operand() = delete;

    explicit Operand(std::string str, eOperandType t);

    Operand(Operand const &) = delete;

    ~Operand() override = default;

    eOperandType getType() const override;

    Operand &operator=(Operand const &) = delete;

    int getPrecision() const override;

    std::string const &toString() const override;

    const IOperand * operator/(IOperand const &rhs) const override;

    const IOperand * operator*(IOperand const &rhs) const override;

    const IOperand * operator%(IOperand const &rhs) const override;

    const IOperand * operator-(IOperand const &rhs) const override;

    const IOperand  *operator+(IOperand const &rhs) const override;

private:

    std::string val;

    eOperandType type;

    int precision;

    IOperand const *more_than_float(const IOperand &new_operand, eOperation op, eOperandType new_type) const;

    IOperand const *less_than_float(const IOperand &Inew, eOperation op, eOperandType new_type) const;

};

#endif
