/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:53 by nathan            #+#    #+#             */
/*   Updated: 2021/01/21 10:21:44 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readAVM.hpp"
#include <regex>
#define FILE_SYNTAX "((^|\\n)+((LINE_SYNTAX)|(COMMENT_SYNTAX))?)+"
#define LINE_SYNTAX "(INSTR)(\\s?COMMENT_SYNTAX)?"
#define COMMENT_SYNTAX ";.*"
#define INSTR "push (VALUE)|pop|dump|assert (VALUE)|add|sub|mul|div|mod|print|exit"
#define VALUE "int8\\(N\\)|int16\\(N\\)|int32\\(N\\)|float\\(Z\\)|double\\(Z\\)"
#define N "-?[0-9]+"
#define Z "-?[0-9]+\\.[0-9]+"
#include "exceptions.hpp"

#include <iostream>
#include <fstream>

bool readAVM::isReadingFile = true;

void readAVM::verifyGlobalSyntax(std::stringstream& wholeFile)
{
	std::string pattern(FILE_SYNTAX);

	pattern = std::regex_replace(pattern, std::regex("LINE_SYNTAX"), LINE_SYNTAX);
	pattern = std::regex_replace(pattern, std::regex("INSTR"), INSTR);
	pattern = std::regex_replace(pattern, std::regex("COMMENT_SYNTAX"), COMMENT_SYNTAX);
	pattern = std::regex_replace(pattern, std::regex("VALUE"), VALUE);
	pattern = std::regex_replace(pattern, std::regex("N"), N);
	pattern = std::regex_replace(pattern, std::regex("Z"), Z);

	if (!std::regex_match(wholeFile.str(), std::regex(pattern)))
		throw parsingError("The assembly program includes one or several lexical errors or syntactic errors.");
}

void readAVM::readFile(std::string file, AVMcontainer& container)
{
	std::ifstream myFile(file);
	std::stringstream wholeFile;

	if (myFile.is_open())
	{
		wholeFile << myFile.rdbuf();
		try
		{
			verifyGlobalSyntax(wholeFile);
		}
		catch (std::exception& e){
			std::cerr << e.what() << std::endl;
		}

		int i = 0;
		std::string line;
		while (std::getline(wholeFile, line))
		{
			i++;
			if ((line.length()) && line.find(";") != 0)
			{
				try{
				verifyLine(line);
				readLine(line, container);
				}
				catch (std::exception& e)
				{
					std::cerr << "Line " << i << ": ";
					std::cerr << e.what() << std::endl;
				}
			}
		}
	}
	else
	{
		std::cerr << "Error: can't open " << file << std::endl;
	}
	if (!container.hasExited())
		throw exitError("Error: the program doesn't have an exit instruction");
}

void readAVM::readInput(AVMcontainer& container)
{
	std::stringstream	inputProgram;

	while (true)
	{
		std::string line;

		std::getline(std::cin, line);
		if (line.compare(";;") == 0)
			break;
		line += "\n";
		inputProgram << line;
	}
	try
	{
	verifyGlobalSyntax(inputProgram);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::string line;
	while (std::getline(inputProgram, line))
	{
		if ((line.length()) && line.find(";") != 0)
		{
			try{
				verifyLine(line);
				readLine(line, container);
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}
	if (!container.hasExited())
		throw exitError("Error: the program doesn't have an exit instruction");
}

void readAVM::verifyLine(std::string line)
{
	std::string pattern(LINE_SYNTAX);

	pattern = std::regex_replace(pattern, std::regex("INSTR"), INSTR);
	pattern = std::regex_replace(pattern, std::regex("COMMENT_SYNTAX"), COMMENT_SYNTAX);
	pattern = std::regex_replace(pattern, std::regex("VALUE"), VALUE);
	pattern = std::regex_replace(pattern, std::regex("N"), N);
	pattern = std::regex_replace(pattern, std::regex("Z"), Z);
	if (!std::regex_match(line, std::regex(pattern)))
	{
		std::string errorMsg("Parsing error: instruction unknown");
		throw parsingError(errorMsg);
	}
}

void readAVM::readLine(std::string line, AVMcontainer& container)
{
	size_t commentPos;
	commentPos = line.find(";", 0);
	if (commentPos != std::string::npos)
		line.erase(commentPos);// removing comments
	executeLine(line, container);
}

void readAVM::executeLine(std::string line, AVMcontainer& container)
{
	if (line.find("push", 0) == 0)
		container.push(line.substr(line.find(" ", 0) + 1));
	if (line.find("pop", 0) == 0)
		container.pop();
	if (line.find("dump", 0) == 0)
		container.dump();
	if (line.find("assert", 0) == 0)
		container.assert(line.substr(line.find(" ", 0) + 1));
	if (line.find("add", 0) == 0)
		container.add();
	if (line.find("sub", 0) == 0)
		container.sub();;
	if (line.find("mul", 0) == 0)
		container.mul();;
	if (line.find("div", 0) == 0)
		container.div();;
	if (line.find("mod", 0) == 0)
		container.mod();;
	if (line.find("print", 0) == 0)
		container.print();;
	if (line.find("exit", 0) == 0)
		container.exit();;
}
