#include "Address.h"

std::wistream& operator>>(std::wistream& in, Address& a) {
	std::wstring zip_and_city;

	std::getline(in, a.street, L',');

	in >> std::ws; // Ignorera whitespace

	std::getline(in, zip_and_city);

	// Säkerhetskontroll för att se till att strängen är tillräckligt lång
	if (zip_and_city.size() >= 6) {
		std::wstring zip = zip_and_city.substr(0, 3) + zip_and_city.substr(4, 2);

		try {
			a.zip = std::stoi(zip);
		}
		catch (std::invalid_argument) {
			std::cerr << "Invalid zip code" << std::endl;
			a.zip = 0;
		}
	}
	
	// Säkerhetskontroll för att se till att strängen är tillräckligt lång
	if (zip_and_city.size() >= 8) {
		std::wstring city = zip_and_city.substr(8);

		// Ta bort eventuella mellanslag i slutet av strängen
		while (!city.empty() && std::iswspace(city.back())) {
			city.pop_back();
		}

		a.city = city;
	}

	return in;
}