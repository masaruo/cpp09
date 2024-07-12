/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XString.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:46:16 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/12 12:04:00 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xString.hpp"

xString::xString()
{
	return ;
}

xString::xString(std::string const &inStr)
:std::string(inStr)
{
	return ;
}

xString::xString(char const *inStr)
:std::string(inStr)
{
	return ;
}

xString::~xString()
{
	return ;
}

xString::xString(xString const &rhs)
:std::string(rhs)
{
	
}

xString &xString::operator=(xString const &rhs)
{
	if (this != &rhs)
	{
		this->std::string::operator = (rhs);
	}
	return (*this);
}

bool	xString::contain_not_of(std::string const &to_search, size_type start, size_type end) const
{
	if (end == std::string::npos)
		end = this->size();

	size_type const	pos = find_first_not_of(to_search, start);

	if (pos != std::string::npos && pos <= end)
		return (true);
	else
		return (false);
}

bool	xString::contain_any_of(std::string const &to_search, size_type start, size_type end) const
{
	if (end == std::string::npos)
		end = this->size();
	size_type const	pos = find_first_of(to_search, start);

	if (pos != std::string::npos && pos <= end)
		return (true);
	else
		return (false);
}

bool	xString::start_with(std::string const &to_search) const
{
	size_type pos = find_first_of(to_search);
	if (pos == 0)
		return (true);
	else
		return (false);
}

bool	xString::start_with(char const to_search) const
{
	size_type pos = find_first_of(to_search);
	if (pos == 0)
		return (true);
	else
		return (false);
}

bool	xString::end_with(std::string const &to_search) const
{
	size_type pos = find_last_of(to_search);
	if (pos + 1 == this->size())
		return (true);
	else
		return (false);
}

bool	xString::end_with(char const to_search) const
{
	size_type pos = find_last_of(to_search);
	if (pos + 1 == this->size())
		return (true);
	else
		return (false);
}

char	&xString::front(void)
{
	return (std::string::at(0));
}

char const	&xString::front(void) const
{
	return (std::string::at(0));
}

char	&xString::back(void)
{
	return (std::string::at(std::string::size() - 1));
}

char const	&xString::back(void) const
{
	return (std::string::at(std::string::size() - 1));
}

void	xString::pop(void)
{
	if (std::string::size() > 0)
		std::string::erase(0, 1);
}

void	xString::pop_back(void)
{
	if (std::string::size() > 0)
		std::string::erase(std::string::size() - 1, 1);
}

void	xString::trim(std::string const &target)
{
	while (start_with(target))
		this->pop();
	while (end_with(target))
		this->pop_back();
}

void	xString::trim(char const &target)
{
	while (start_with(target))
		this->pop();
	while (end_with(target))
		this->pop_back();
}

xString::xstring_vector	xString::split(std::string const &delims) const
{
	xstring_vector		split_v;
	size_type	cp_end = 0;
	size_type	cp_begin = 0;

	while (true)
	{
		cp_end = std::string::find_first_of(delims, cp_end);
		if (cp_end == std::string::npos)
		{
			break ;
		}
		else
		{
			split_v.push_back(std::string::substr(cp_begin, cp_end - cp_begin));
			cp_end = std::string::find_first_not_of(delims, cp_end);
			cp_begin = cp_end;
		}
	}
	if (cp_begin < std::string::size())
		split_v.push_back(std::string::substr(cp_begin, std::string::size() - cp_begin));
	return (split_v);
}

std::ostream &operator<<(std::ostream &os, xString::xstring_vector const &rhs)
{
	xString::xstring_vector::const_iterator it = rhs.begin();

	while (it != rhs.end())
	{
		os  << "[" << *it << "]";
		it++;
	}
	return (os);
}
