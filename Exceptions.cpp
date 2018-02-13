#include "headers/Exceptions.hpp"

const char *EcxDivModbyZero::what() const noexcept {
    return "Division/Module by zero";
}

const char *OverLimit::what() const noexcept {
    return "The value went over the limit";
}

const char *NotValidOperand::what() const noexcept {
    return "Not valid operand";
}

const char *InttoDouble::what() const noexcept {
    return "Int is not Double";
}

const char *PushAssert::what() const noexcept {
    return "Push and assert mush have parameter Operand";
}

const char *NotvalidCommand::what() const noexcept {
    return "Not valid command";
}

const char *NonExit::what() const noexcept {
    return "Program must end with the exit command, write exit to finish program";
}

const char *EmptyStack::what() const noexcept {
    return "Stack is empty, this command is forbidden";
}

const char *StackOperation::what() const noexcept {
    return "Stack size less than 2 element, math operation forbidden";
}

const char *TopType::what() const noexcept {
    return "Type of Operand at the top different";
}

const char *TopValue::what() const noexcept {
    return "Value of Operand at the top different";
}
