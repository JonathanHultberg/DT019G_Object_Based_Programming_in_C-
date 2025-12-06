#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_	

#include <iostream>	
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include "Person.h"

void menu();
std::vector<Person> read_file(std::string file_name);
size_t find_in_names(const std::vector<Person>& haystack, std::wstring name_part);
std::vector<Person> find_person_from_city(const std::vector<Person>& haystack, std::wstring city);
void lower_case(std::wstring& str);
void upper_case(std::wstring& str);
void empty_term();

#endif 
