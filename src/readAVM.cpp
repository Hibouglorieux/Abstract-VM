/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:53 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 08:38:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readAVM.hpp"
#include <regex>
#define LINE_SYNTAX "INSTR ;*"
#define INSTR "push (VALUE)|pop|dump|assert (VALUE)|add|sub|mul|div|mod|print|exit"
#define VALUE "int8\\(N\\)|int16\\(N\\)|int32\\(N\\)|float\\(Z\\)|double\\(Z\\)"
#define N "[-]?[0-9]+"
#define Z "[-]?[0-9]+\\.[0-9]+"

#include <iostream>
#include <fstream>

void readAVM::readFile(std::string file, AVMcontainer& AVMcontainer)
{
	std::ifstream myFile(file);
	if (myFile.is_open())
	{
		int i = 0;
		std::string line;
		while (getline(myfile, line))
		{
			//TODO check line then call proper function
			//
		}
	}
	else
	{
		std::cerr << "Error: couldn't open " << file << std::endl;
	}
	//TODO load file in string;
	
	std::string pattern(LINE_SYNTAX);

	pattern = std::regex_replace(pattern, std::regex("INSTR"), INSTR);
	pattern = std::regex_replace(pattern, std::regex("VALUE"), VALUE);
	pattern = std::regex_replace(pattern, std::regex("N"), N);
	pattern = std::regex_replace(pattern, std::regex("Z"), Z);
	if (!std::regex_match(file, std::regex(pattern)))
		;//TODO throw error
	std::cout << pattern << std::endl;
}

void readAVM::readLine(std::string line, AVMcontainer& avmContainer)
{
	std::string pattern(INSTR);

	pattern = std::regex_replace(pattern, std::regex("VALUE"), VALUE);
	pattern = std::regex_replace(pattern, std::regex("N"), N);
	pattern = std::regex_replace(pattern, std::regex("Z"), Z);
	if (!std::regex_match(line, std::regex(pattern)))
		;//TODO throw error
}
