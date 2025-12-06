#include "functions.h"

void menu() {
	// Variabler
	int switch_alt;
	std::string file_name;
	std::wstring name_part,city;
	std::vector<Person> run_time_mem,found_match;

	// Set locale, använder "" för att använda datorns standardinställningar
	std::setlocale(LC_ALL, "");      
	std::wcin.imbue(std::locale(""));    

	std::cout << "Welcome to the program!" << std::endl;	

	do {
		std::cout << "There are currently " << run_time_mem.size() << " people in memory." << std::endl;
		std::cout << "1. Read from file" << std::endl;
		std::cout << "2. Search by name" << std::endl;
		std::cout << "3. Search by city" << std::endl;
		std::cout << "4. Exit" << std::endl;

		std::cin >> switch_alt;
		std::cin.ignore();

		// Error handling
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input! Please enter a number between 1 and 4.\n";
		}

		switch (switch_alt)
		{
		case 1:
			std::cout << "Enter the name of the file, end whit \".txt\": ";
			std::getline(std::cin, file_name);
			run_time_mem = read_file(file_name);
			std::cout << "Read " << run_time_mem.size() << " people from file." << std::endl;
			std::cout << "Press ENTER to continue...";
			std::cin.get(); // Vänta på ENTER
			empty_term(); // Rensa terminalen
			break;

		case 2:
			std::cout << "Enter the name you want to search for: ";
			std::getline(std::wcin, name_part); // Använd wcin för att kunna läsa in och hantera å, ä och ö
			std::cout << "Found " << find_in_names(run_time_mem, name_part) << " matches." << std::endl;
			std::cout << "Press ENTER to continue...";
			std::cin.get(); // Vänta på ENTER
			empty_term(); // Rensa terminalen
			break;

		case 3:	
			std::cout << "Enter the city you want to search for: ";
			std::getline(std::wcin, city); // Använd wcin för att kunna läsa in och hantera å, ä och ö
			found_match = find_person_from_city(run_time_mem, city);
			if (found_match.empty()) {
				std::cout << "No matches found." << std::endl;
			}
			else {
				for (const Person& p : found_match) {
					std::wcout << p.id << " " << p.name << " " << p.location.zip << " " << p.location.city << std::endl;
				}
			}
			std::cout << "Press ENTER to continue...";
			std::cin.get(); // Vänta på ENTER
			empty_term(); // Rensa terminalen
			break;

		case 4:
			return;

		default:
			empty_term(); // Rensa terminalen
			std::cout << "Invalid input! Please enter a number between 1 and 4.\n";
			break;
		}
	} while (true);
	
}

std::vector<Person> read_file(std::string file_name) {
	std::vector<Person> people;
	Person p;
	
	// Set locale
	std::wifstream file(file_name);
	file.imbue(std::locale("sv_SE.UTF-8")); // Sätt locale för fil kodad i UTF-8

	// Error handling
	if (!file.is_open()) {
		std::cerr << "Could not open file" << std::endl;
		return people;
	}

	// Inläsning
	while (file >> p) {
		people.push_back(p);
		p = Person(); // Nollställ, för säkerhets skull
	}

	return people;
}

size_t find_in_names(const std::vector<Person>& haystack, std::wstring name_part) {
	size_t found_matches = 0;
	lower_case(name_part); // Egen funktion

	for (const Person& p : haystack) {

		std::wstring temp_name = p.name;

		lower_case(temp_name); // Egen funktion
		
		if (temp_name.find(name_part) != std::string::npos) {
			found_matches++;
		}
	}

	return found_matches;
}

std::vector<Person> find_person_from_city(const std::vector<Person>& haystack, std::wstring city) {
	std::vector<Person> found_people;
	upper_case(city); // Egen funktion

	for (const Person& p : haystack) {

		if (p.location.city == city) {
			found_people.push_back(p);
		}
	}
	return found_people;
}

// Funktion för att konvertera versaler till gemener som hanterar å, ä och ö
void lower_case(std::wstring& str) {
	for (wchar_t& c : str) {
		if (c == L'Å' || c == L'å') {
			c = L'å';
		} else if (c == L'Ä' || c == L'ä') {
			c = L'ä';
		} else if ( c == L'Ö' || c == L'ö') {
			c = L'ö';
		} else {
			c = std::tolower(c);
		}
	}
}

// Funktion för att konvertera gemener till versaler som hanterar å, ä och ö
void upper_case(std::wstring& str) {
	for (wchar_t& c : str) {
		if (c == L'Å' || c == L'å') {
			c = L'Å';
		} else if (c == L'Ä' || c == L'ä') {
			c = L'Ä';
		} else if (c == L'Ö' || c == L'ö') {
			c = L'Ö';
		} else {
			c = std::toupper(c);
		}
	}
}

// Funktion för att rensa terminalen
void empty_term() {
	for (int i = 0; i < 50; i++)
	{
		std::cout << "\n" << std::endl;
	}
}