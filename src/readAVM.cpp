/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:53 by nathan            #+#    #+#             */
/*   Updated: 2021/01/20 10:05:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readAVM.hpp"
#include <regex>
#define FILE_SYNTAX "((^|\\n)+((LINE_SYNTAX)|(COMMENT_SYNTAX))?)+"
#define LINE_SYNTAX "(INSTR)(COMMENT_SYNTAX)?"
#define COMMENT_SYNTAX "\\s?;.*"
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

	std::cout << pattern << std::endl;
	if (!std::regex_match(wholeFile.str(), std::regex(pattern)))
		throw parsingError("The assembly program includes one or several lexical errors or syntactic errors.");
}

void readAVM::readFile(std::string file, AVMcontainer& AVMcontainer)
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
				readLine(line, AVMcontainer, i);
			//TODO check line then call proper function
		}
	}
	else
	{
		std::cerr << "Error: can't open " << file << std::endl;
	}
	//TODO check hasexited
}

void readAVM::verifyLine(std::string line, int lineNumber)
{
	std::string pattern(LINE_SYNTAX);

	pattern = std::regex_replace(pattern, std::regex("INSTR"), INSTR);
	pattern = std::regex_replace(pattern, std::regex("COMMENT_SYNTAX"), COMMENT_SYNTAX);
	pattern = std::regex_replace(pattern, std::regex("VALUE"), VALUE);
	pattern = std::regex_replace(pattern, std::regex("N"), N);
	pattern = std::regex_replace(pattern, std::regex("Z"), Z);
	if (!std::regex_match(line, std::regex(pattern)))
	{
		std::string errorMsg("Parsing error");
		if (lineNumber)
			errorMsg += std::string(" at line: ") + std::to_string(lineNumber);
		errorMsg += " instruction unknown";
		throw parsingError(errorMsg);
	}
}

void readAVM::readLine(std::string line, AVMcontainer& avmContainer, int lineNumber)
{
	try
	{
		verifyLine(line, lineNumber);
	}
	catch (std::exception& e){
		std::cerr << e.what() << std::endl;
		return ;// not executed
	}
	size_t commentPos;
	commentPos = line.find(";", 0);
	if (commentPos != std::string::npos)
		line.erase(commentPos);// removing comments//TODO handle ";;"
	try
	{
		executeLine(line, avmContainer);
	}
	catch (std::exception& e){
		if (lineNumber)
			std::cerr << "Line " << lineNumber << ": ";
		std::cerr << e.what() << std::endl;
	}
}

void readAVM::executeLine(std::string line, AVMcontainer& avmContainer)
{
	if (line.find("push", 0) == 0)
		avmContainer.push(line.substr(line.find(" ", 0) + 1));
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
