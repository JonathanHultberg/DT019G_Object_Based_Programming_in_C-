#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <iostream>
#include <locale>
#include <cwctype>

struct Address
{
	std::wstring street;
	int zip;
	std::wstring city;
};

std::wistream& operator>>(std::wistream& in, Address& a);

#endif
#pragma once
