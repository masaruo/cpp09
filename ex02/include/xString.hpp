/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xString.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:39:34 by mogawa            #+#    #+#             */
<<<<<<< HEAD:ex02/include/XString.hpp
/*   Updated: 2024/05/24 11:35:49 by mogawa           ###   ########.fr       */
=======
/*   Updated: 2024/07/08 10:18:14 by mogawa           ###   ########.fr       */
>>>>>>> detach:ex02/include/xString.hpp
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
<<<<<<< HEAD:ex02/include/XString.hpp
	typedef std::string::iterator 		it_t;
	typedef std::string::const_iterator	cit_t;
	typedef std::string::size_type		str_size;
	typedef std::vector<std::string>	vec_str;
=======
	typedef std::string::iterator 			iterator;
	typedef std::string::const_iterator		const_iterator;
	typedef std::string::size_type			size_type;
	typedef std::vector<xString>			xstring_vector;
	typedef xstring_vector::const_iterator	xstring_vec_const_iterator;
>>>>>>> detach:ex02/include/xString.hpp

	xString();
	xString(std::string const &str);
	xString(char const *str);
	~xString();
	xString(xString const &rhs);
	xString &operator=(xString const &rhs);
	//! wrapper functions
<<<<<<< HEAD:ex02/include/XString.hpp
	bool		contain_not_of(std::string const &to_search, str_size pos = 0) const;
	bool		contain_not_of(char const *to_search, str_size pos = 0) const;
	bool		contain_any_of(std::string const &to_search, str_size pos = 0) const;
	bool		contain_any_of(char const *to_search, str_size pos = 0) const;
=======
	bool		contain_not_of(std::string const &to_search, size_type start = 0, size_type end = std::string::npos) const;
	bool		contain_any_of(std::string const &to_search, size_type start = 0, size_type end = std::string::npos) const;
>>>>>>> detach:ex02/include/xString.hpp
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
