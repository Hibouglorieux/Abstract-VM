/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:53 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 16:45:11 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readAVM.hpp"
#include <regex>
#define FILE_SYNTAX "((^|\\n)+((LINE_SYNTAX)|(COMMENT_SYNTAX))?)+"
#define LINE_SYNTAX "(INSTR)(\\s?COMMENT_SYNTAX)?"
#define COMMENT_SYNTAX ";.*"
#define INSTR "push (VALUE)|pop|dump|assert (VALUE)|add|sub|mul|div|mod|print|exit|min|max|pow|debug"
#define VALUE "int8\\(N\\)|int16\\(N\\)|int32\\(N\\)|float\\(Z\\)|double\\(Z\\)"
#define N "-?[0-9]+"
#define Z "-?[0-9]+\\.[0-9]+"
#include "exceptions.hpp"

#include <iostream>
#include <fstream>
#define EXIT 1

bool readAVM::isReadingFile = true;

void readAVM::verifyGlobalSyntax(std::stringstream& program)
{
	std::string pattern(FILE_SYNTAX);

	pattern = std::regex_replace(pattern, std::regex("LINE_SYNTAX"), LINE_SYNTAX);
	pattern = std::regex_replace(pattern, std::regex("INSTR"), INSTR);
	pattern = std::regex_replace(pattern, std::regex("COMMENT_SYNTAX"), COMMENT_SYNTAX);
	pattern = std::regex_replace(pattern, std::regex("VALUE"), VALUE);
	pattern = std::regex_replace(pattern, std::regex("N"), N);
	pattern = std::regex_replace(pattern, std::regex("Z"), Z);

	if (!std::regex_match(program.str(), std::regex(pattern)))
		throw parsingError("The assembly program includes one or several lexical errors or syntactic errors.");
}

bool readAVM::debugMode(AVMcontainer& container, std::string originalLine)
{

	std::cout << "\033[31mdebugging command: " + originalLine + "\033[0m" << std::endl;
	while (true)
	{
		std::string debugLine;
		std::getline(std::cin, debugLine);
		if (debugLine.compare(";;") == 0 || debugLine.compare("") == 0)
			break ;
		try{
			verifyLine(debugLine);
			if (readLine(debugLine, container) == EXIT)
				return (EXIT);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return (!EXIT);
}

std::stringstream readAVM::openFile(std::string file)
{
	std::ifstream myFile(file);
	std::stringstream wholeFile;

	if (myFile.is_open())
	{
		wholeFile << myFile.rdbuf();
	}
	else
	{
		throw parsingError("Error: can't open " + file);
	}
	return wholeFile;
}

void readAVM::readProgram(std::stringstream& program, AVMcontainer& container)
{
	try {
		verifyGlobalSyntax(program);
	}
	catch (std::exception& e){
		std::cerr << e.what() << std::endl;
	}

	int i = 0;
	std::string line;
	while (std::getline(program, line))
	{
		i++;
		if ((line.length()) && line.find(";") != 0)
		{
			try {
				verifyLine(line);
				if (readLine(line, container) == EXIT)
					return ;
			}
			catch (std::exception& e) {
				std::cerr << "Line " << i << ": ";
				std::cerr << e.what() << std::endl;
				if (container.isInDebug())
					if (debugMode(container, line) == EXIT)
						return ;
			}
		}
	}
	throw exitError("Error: the program doesn't have an exit instruction");
}

std::stringstream readAVM::readInput()
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
	return inputProgram;
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

bool readAVM::readLine(std::string line, AVMcontainer& container)
{
	size_t commentPos;
	commentPos = line.find(";", 0);
	if (commentPos != std::string::npos)
		line.erase(commentPos);// removing comments
	return (executeLine(line, container));
}

bool readAVM::executeLine(std::string line, AVMcontainer& container)
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
		container.sub();
	if (line.find("mul", 0) == 0)
		container.mul();
	if (line.find("div", 0) == 0)
		container.div();
	if (line.find("mod", 0) == 0)
		container.mod();
	if (line.find("print", 0) == 0)
		container.print();
	if (line.find("exit", 0) == 0)
		return (EXIT);
	if (line.find("max", 0) == 0)
		container.max();
	if (line.find("min", 0) == 0)
		container.min();
	if (line.find("pow", 0) == 0)
		container.pow();
	if (line.find("debug", 0) == 0)
		container.debug();
	return (!EXIT);
}
