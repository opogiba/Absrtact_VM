# include <stack>

# ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

template <class T>
class MutantStack : public std::stack<T> {

public:

    typedef typename std::stack<T>::container_type::iterator iterator;

    MutantStack() = default;

    MutantStack(MutantStack const & src)  = delete;

    ~MutantStack()  = default;

    using 	std::stack<T>::operator=;

    iterator	begin() { return this->c.begin(); }

    iterator	end() { return std::stack<T>::c.end(); }
};

#endif
