/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:29:00 by mogawa            #+#    #+#             */
/*   Updated: 2024/04/30 18:59:34 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <deque>
#include <string>

class RPN
{
private:
	enum	type_e { num_, operator_};
	typedef struct	elem_s
	{
		std::string	data_;
		type_e		type_;
	}	elem_t;
	std::deque<std::string>	deque_;
	RPN();
	// helper functions
	void	fill_deque(std::string const &input);
public:
	RPN(std::string const &num);
	RPN(RPN const &rhs);
	~RPN();
	RPN &operator=(RPN const &rhs);
};

#endif
