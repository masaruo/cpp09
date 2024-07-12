/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:28:53 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/08 10:16:36 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <limits>
#include "SafeMath.hpp"

int const SPACE = ' ';

static int	is_operator(int c)
{
	if (c == '*' || c == '/' || c == '+' || c == '-')
		return (1);
	else
		return (0);
}

int	RPN::get_calc_num(int first, int last, int opter)
{
	switch (opter)
	{
		case ('*'):
			return (SafeMath<int>::mul(first, last));
		case ('+'):
			return (SafeMath<int>::add(first, last));
		case ('-'):
			return (SafeMath<int>::sub(first, last));
		case ('/'):
			return (SafeMath<int>::div(first, last));
		default:
			return (0);
	}
}

void	RPN::calculate(std::string const &num)
{
	std::string::const_iterator iter = num.begin();
	std::string::const_iterator	end = num.end();

	while (iter != end)
	{
		int const ch = static_cast<int>(*iter);
		if (std::isdigit(ch))
		{
			this->stack_.push(ch - '0');
			iter++;
		}
		else if (is_operator(ch))
		{
			if (stack_.size() < 2)
			{
				throw (std::invalid_argument("Error"));
			}
			int const last_ = this->stack_.top();
			this->stack_.pop();
			int const first_ = this->stack_.top();
			this->stack_.pop();
			int	answer = 0;
			answer = get_calc_num(first_, last_, ch);
			this->stack_.push(answer);
			iter++;
		}
		else if (ch == SPACE)
		{
			iter++;
			continue ;
		}
		else
		{
			std::cout << "Error" << std::endl;
			std::exit(1);
		}
	}
	if (this->stack_.size() != 1)
	{
		throw (std::invalid_argument("Error"));
	}
	std::cout << stack_.top() << std::endl;
}

RPN::RPN(){ return ; }

RPN::RPN(std::string const &num)
{
	calculate(num);
	return ;
}

RPN::RPN(RPN const &rhs)
{
	(void) rhs;
}

RPN::~RPN()
{
	return ;
}

RPN	&RPN::operator=(RPN const &rhs)
{
	(void) rhs;
	return (*this);
}

char const	*RPN::DivisionException::what() const throw ()
{
	return ("Zero Division.");
}

RPN::RPNOverflowException::RPNOverflowException(std::string const &e)
:err_msg(e)
{
	return ;
}

char const *RPN::RPNOverflowException::what() const throw ()
{
	return (err_msg.c_str());
}
