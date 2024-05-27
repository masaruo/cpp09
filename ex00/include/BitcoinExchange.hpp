/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:45:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/27 11:54:17 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "xString.hpp"
#include <map>
#include <utility>

class BitcoinExchange
{
public:
	typedef std::map<xString, double>	btc_map;
	typedef btc_map::const_iterator		const_iterator;
private:
	btc_map	px_list;
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &rhs);
	BitcoinExchange &operator=(BitcoinExchange const &rhs);
};
