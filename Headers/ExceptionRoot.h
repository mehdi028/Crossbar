#pragma once
#include<exception>
#include<string>
class ExceptionRoot: public std::exception
{
public:
	ExceptionRoot(std::string  file, int line) noexcept ;
	std::string  virtual GetType() const = 0;
	const char* what() const override;
	

protected:
	mutable std::string WhatMessage;
	std::string  File;
	int Line; 
	


};

