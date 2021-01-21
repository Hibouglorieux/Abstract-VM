/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:31:14 by nathan            #+#    #+#             */
/*   Updated: 2021/01/20 11:31:10 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXCEPTIONS_CLASS_H
# define EXCEPTIONS_CLASS_H
#include <stdexcept>
#include <string>

	std::string formatError(std::string msg, std::string typeOfNumber, std::string number);

class overflowError : public std::overflow_error {
public:
	overflowError(std::string typeOfNumber, std::string number);
	//virtual const char* what()const throw();
	virtual ~overflowError(void);
private:
	overflowError(void);
};

class underflowError : public std::underflow_error {
public:
	underflowError(std::string typeOfNumber, std::string number);
	//virtual const char* what()const throw();
	virtual ~underflowError(void);
private:
	underflowError(void);
};

class notEnoughStackElem : public std::runtime_error {
public:
	notEnoughStackElem(std::string msg);
	virtual ~notEnoughStackElem(void);

private:
	notEnoughStackElem(void);
};

class assertError : public std::runtime_error {
public:
	assertError(std::string msg);
	virtual ~assertError(void);
private:
	assertError(void);
};

class printError : public std::runtime_error {
public:
	printError(std::string msg);
	virtual ~printError(void);
private:
	printError(void);
};

class arythmeticError : public std::runtime_error {
public:
	arythmeticError(std::string msg);
	virtual ~arythmeticError(void);
private:
	arythmeticError(void);
};

class parsingError : public std::runtime_error {
public:
	parsingError(std::string msg);
	virtual ~parsingError(void);
private:
	parsingError(void);
};

class exitError : public std::runtime_error {
public:
	exitError(std::string msg);
	virtual ~exitError(void);
private:
	exitError(void);
};

#endif
