/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xString.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:39:34 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/08 10:18:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <ostream>

class xString : public std::string
{
private:

public:
	typedef std::string::iterator 			iterator;
	typedef std::string::const_iterator		const_iterator;
	typedef std::string::size_type			size_type;
	typedef std::vector<xString>			xstring_vector;
	typedef xstring_vector::const_iterator	xstring_vec_const_iterator;

	xString();
	xString(std::string const &str);
	xString(char const *str);
	~xString();
	xString(xString const &rhs);
	xString &operator=(xString const &rhs);
	//! wrapper functions
	bool		contain_not_of(std::string const &to_search, size_type start = 0, size_type end = std::string::npos) const;
	bool		contain_any_of(std::string const &to_search, size_type start = 0, size_type end = std::string::npos) const;
	bool		start_with(std::string const &to_search) const;
	bool		start_with(char const to_search) const;
	bool		end_with(std::string const &to_search) const;
	bool		end_with(char const to_search) const;
	char		&front(void);
	char const	&front(void) const;
	char		&back(void);
	char const	&back(void) const;
	void		pop(void);
	void		pop_back(void);
	void		trim(std::string const &target);
	void		trim(char const &target);
	xstring_vector		split(std::string const &to_split) const;
};

std::ostream &operator<<(std::ostream &os, xString::xstring_vector const &rhs);
