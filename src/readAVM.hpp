/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:57 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 16:00:39 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef READAVM_CLASS_H
# define READAVM_CLASS_H
#include <stack>
#include <string>
#include "IOperand.hpp"
#include "AVMcontainer.hpp"

class readAVM {
public:
	static void readProgram(std::stringstream& fileName, AVMcontainer& container);
	static std::stringstream readInput();
	static std::stringstream openFile(std::string file);
private:
	static bool readLine(std::string line, AVMcontainer& container);
	static bool debugMode(AVMcontainer& container, std::string originalLine);
	static bool executeLine(std::string line, AVMcontainer& container);
	static void verifyGlobalSyntax(std::stringstream& program);
	static void verifyLine(std::string line);
	readAVM(void) = delete;
	readAVM(readAVM const & copy) = delete;
	readAVM & operator=(readAVM const & rhs) = delete;
	~readAVM(void);
	static bool isReadingFile;
};

#endif
