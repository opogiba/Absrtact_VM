#include <exception>

#ifndef ABSTRACT_VM_EXCEPTIONS_HPP
#define ABSTRACT_VM_EXCEPTIONS_HPP

class  EcxDivModbyZero : public std::exception {
public:
    const char * what() const noexcept;
};

class  OverLimit : public std::exception {
public:
    const char * what() const noexcept;
};

class  NotValidOperand : public std::exception {
public:
    const char * what() const noexcept;
};

class  InttoDouble : public std::exception {
public:
    const char * what() const noexcept;
};

class  PushAssert : public std::exception {
public:
    const char * what() const noexcept;
};

class  NotvalidCommand : public std::exception {
public:
    const char * what() const noexcept;
};

class  NonExit : public std::exception {
public:
    const char * what() const noexcept;
};

class  EmptyStack : public std::exception {
public:
    const char * what() const noexcept;
};

class  StackOperation : public std::exception {
public:
    const char * what() const noexcept;
};

class  TopValue : public std::exception {
public:
    const char * what() const noexcept;
};

class  TopType : public std::exception {
public:
    const char * what() const noexcept;
};

#endif
