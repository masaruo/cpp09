/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:29:00 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/02 18:31:12 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <stack>
#include <string>
#include <stdexcept>

class RPN
{
private:
	std::stack<int> 	stack_;
	std::string const	input_;
	RPN();
	RPN &operator=(RPN const &rhs);
	RPN(RPN const &rhs);
	// helper functions
	int		get_calc_num(int first, int last, int opter);
	void	calculate(std::string const &num);
public:
	RPN(std::string const &num);
	~RPN();
	class RPNException : public std::runtime_error
	{
	public:
		RPNException():std::runtime_error("RPN Error."){};// constructorが必要
		virtual char const	*what() const throw () = 0;
	};
	class ZeroDivisionException : public RPNException
	{
	public:
		char const	*what() const throw ();
	};
};

#endif


//ゼロ徐算
