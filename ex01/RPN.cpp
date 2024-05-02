/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:28:53 by mogawa            #+#    #+#             */
/*   Updated: 2024/04/30 18:56:56 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <algorithm>
#define SPACE (' ')

static int	is_operator(int c)
{
	if (c == '*' || c == '/' || c == '+' || c == '-')
		return (1);
	else
		return (0);
}

static bool	is_valid_input(std::string const &word)
{
	if (word.length() == 1)
	{
		if (is_operator(word.at(0)) || isnumber(word.at(0)))
			return (true);
		else
			return (false);
	}
	else
	{
		std::string::const_iterator it = word.begin();
		while (it < word.end())
		{
			if (!isnumber(*it))
				return (false);
			it++;
		}
		return (true);
	}
}

void	RPN::fill_deque(std::string const &input)
{
	std::string::const_iterator	begin = input.begin();
	std::string::const_iterator	checker = input.begin();
	std::string::const_iterator	follower = input.begin();
	std::string::const_iterator	end = input.end();
	std::string					token;
	while (true)
	{
		if (*checker == SPACE)
		{
			token = input.substr(follower - begin, checker - follower);
			checker++;
			follower = checker;
			std::cout << token << std::endl;
		}
		else if (checker == end)
		{
			if (follower != checker)
			{
				token = input.substr(follower - begin, checker - follower);
				std::cout << token << std::endl;
			}
			break ;
		}
		else
		{
			checker++;
		}
	}
}

RPN::RPN(){ return ; }
RPN::RPN(std::string const &input)
{
	fill_deque(input);
	(void) is_operator('a');
	return ;
}

RPN::RPN(RPN const &rhs)
{
	(void) rhs;
	//todo
}

RPN::~RPN()
{
	//todo
}

RPN	&RPN::operator=(RPN const &rhs)
{
	//todo
	(void) rhs;
	return (*this);
}
