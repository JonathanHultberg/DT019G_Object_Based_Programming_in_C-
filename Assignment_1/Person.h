#ifndef PERSON_H_
#define PERSON_H_	


#include <string>
#include <iostream>
#include <locale> 
#include "Address.h"

struct Person
{
	std::wstring name;
	std::wstring id;
	Address location;
};

std::wistream& operator>>(std::wistream& in, Person& p);

#endif
