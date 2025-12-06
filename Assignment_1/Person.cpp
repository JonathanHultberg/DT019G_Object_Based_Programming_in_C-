#include "Person.h"

std::wistream& operator>>(std::wistream& in, Person& p) {
	std::getline(in, p.name);
	std::getline(in, p.id);	

	in >> p.location; // Anropa operator>> för Address

	return in;
}