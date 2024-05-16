/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:29:00 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/16 14:52:18 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <stack>
#include <list>
#include <string>
#include <stdexcept>

class RPN
{
private:
	std::stack<int, std::list<int> > 	stack_;
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
	class RPNOverflowException
	{
	private:
		std::string	err_msg;
		RPNOverflowException();
	public:
		explicit RPNOverflowException(std::string const &e);
		char const *what() const throw ();
	};
};

// ./RPN.hpp:45:8: error: exception specification of overriding function is more lax than base version
//         class RPNOverflowException : public std::overflow_error
//               ^
// /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/stdexcept:168:13: note: overridden virtual function
//       is here
//     virtual ~overflow_error() _NOEXCEPT;
//             ^
// 1 error generated.

#endif
