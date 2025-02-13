#include "RPN.hpp"

RPN::RPN(std::string expr): _expr(expr){}

RPN::RPN(const RPN &src)
{
    *this = src;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        this->_expr = other._expr;
        this->_stack = other._stack;
    }
    return *this;
}

bool RPN::evaluate()
{
    std::stringstream   str(_expr);
    std::string         token;

    while(str >> token)
    {
        if (std::isdigit(token[0]))
            _stack.push(token[0] - '0');
        else if(token == "+")
        {
            if(_stack.size() < 2)
            {
                std::cout << "Error +" << std::endl;
                return (false);
            }
            int a = _stack.top();
            _stack.pop();
            int b = _stack.top();
            _stack.pop();
            _stack.push(a + b);
        }
        else if (token == "-")
        {
            if (_stack.size() < 2)
            {
                std::cout << "Error -" << std::endl;
                return (false);
            }
            int a = _stack.top();
            _stack.pop();
            int b = _stack.top();
            _stack.pop();
            _stack.push(b - a);
        }
        else if (token == "*")
        {
            if(_stack.size() < 2)
            {
                std::cout << "Error *" << std::endl;
                return (false);
            }
            int a = _stack.top();
			_stack.pop();
			int b = _stack.top();
			_stack.pop();
			_stack.push(a * b);
        }
        else if (token == "/")
        {
            if ( _stack.size() < 2)
			{
				std::cout << "Error /" << std::endl;
				return (false);
			}
            int a = _stack.top();
			_stack.pop();
			int b = _stack.top();
			_stack.pop();
			if (a == 0)
			{
				std::cout << "Division by zero" << std::endl;
				return (false);
			}
			_stack.push(b / a);
        }
        if (std::isalpha(token[0]))
        {

            std::cout << "Error char" << std::endl;
                return (false);
        }
    }
    if(_stack.size() != 1)
    {
        std::cout << "Error" << std::endl;
        return(false);
    }

    std::cout << _stack.top() << std::endl;
    return true;
}