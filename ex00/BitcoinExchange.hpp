/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:51:47 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/07 13:08:20 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double>	data_;
	std::map<std::string, double>	input_;
	//helper
	template <typename F>
	void	parseData(std::string const &file, F functor);
	BitcoinExchange();//hidden
public:
	BitcoinExchange(std::string const &file);
	BitcoinExchange(BitcoinExchange const &rhs);
	~BitcoinExchange();
	BitcoinExchange &operator=(BitcoinExchange const &rhs);
};
