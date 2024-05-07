/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:51:47 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/06 18:48:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, float>	data_;
	std::size_t						amount_;
	BitcoinExchange();//hidden
public:
	BitcoinExchange(std::string const &file, int amt);
	BitcoinExchange(BitcoinExchange const &rhs);
	~BitcoinExchange();
	BitcoinExchange &operator=(BitcoinExchange const &rhs);
};
