/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:53 by nathan            #+#    #+#             */
/*   Updated: 2021/01/17 07:35:17 by nathan           ###   ########.fr       */
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

bool readAVM::isReadingFile = true;

void readAVM::readFile(std::string file, AVMcontainer& AVMcontainer)
{
	std::ifstream myFile(file);
	if (myFile.is_open())
	{
		int i = 0;
		std::string line;
		while (std::getline(myFile, line))
		{
			i++;
			if ((line.length()) && line.find(";") != 0)
				readLine(line, AVMcontainer);
			//TODO check line then call proper function
			//
		}
	}
	else
	{
		std::cerr << "Error: can't open " << file << std::endl;
	}
	//TODO load file in string;
	
	std::string pattern(LINE_SYNTAX);

	pattern = std::regex_replace(pattern, std::regex("INSTR"), INSTR);
	pattern = std::regex_replace(pattern, std::regex("VALUE"), VALUE);
	pattern = std::regex_replace(pattern, std::regex("N"), N);
	pattern = std::regex_replace(pattern, std::regex("Z"), Z);
	if (!std::regex_match(file, std::regex(pattern)))
	{
		;//TODO throw error
	}
}

void readAVM::readLine(std::string line, AVMcontainer& avmContainer)
{
	std::string pattern(INSTR);

	pattern = std::regex_replace(pattern, std::regex("VALUE"), VALUE);
	pattern = std::regex_replace(pattern, std::regex("N"), N);
	pattern = std::regex_replace(pattern, std::regex("Z"), Z);
	if (!std::regex_match(line, std::regex(pattern)))
	{
		;//TODO throw error
	}
	size_t commentPos;
	commentPos = line.find(";", 0);
	if (commentPos != std::string::npos)
	{
		line.erase(commentPos);// removing comments
	}
	executeLine(line, avmContainer);
}

void readAVM::executeLine(std::string line, AVMcontainer& avmContainer)
{
	if (line.find("push", 0) == 0)
		avmContainer.add(line.substr(line.find(" ", 0) + 1));
	if (line.find("pop", 0) == 0)
		avmContainer.pop();
	if (line.find("dump", 0) == 0)
		avmContainer.dump();
	if (line.find("assert", 0) == 0)
		avmContainer.assert(line.substr(line.find(" ", 0) + 1));
	if (line.find("add", 0) == 0)
		avmContainer.add();
	if (line.find("sub", 0) == 0)
		avmContainer.sub();;
	if (line.find("mul", 0) == 0)
		avmContainer.mul();;
	if (line.find("div", 0) == 0)
		avmContainer.div();;
	if (line.find("mod", 0) == 0)
		avmContainer.mod();;
	if (line.find("print", 0) == 0)
		avmContainer.print();;
	if (line.find("exit", 0) == 0)
		avmContainer.exit();;
}
