#include "linked_list.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <string>

void print_list (linked_list list) {
	list.print();
}

linked_list merg(linked_list& list1, linked_list& list2) {
	linked_list temp_list;

	while (!list1.is_empty() && !list2.is_empty()) {
		if (list1.front() < list2.front()) {
			temp_list.push_back(list1.pop_front());
		}
		else {
			temp_list.push_back(list2.pop_front());
		}
	}

	temp_list += list1 += list2;

	return temp_list;
}

void is_sorted(linked_list& list) {
	if (list.is_empty()) {
		std::cout << "is empty" << std::endl;
		return;
	}

	for (size_t pos = 0; pos < (list.size() - 1); pos++) {
		if (list.at(pos) > list.at(pos + 1)) {
			std::cout << "is not sorted" << std::endl;
			return;
		}
	}

	std::cout << "is sorted" << std::endl;
}

int main() {
	
	//1
	linked_list list1;

	std::srand(std::time(0)); 

	int value = 0;
	for (int i = 0; i < 10; i++) {
		list1.push_back(value);
		int increase = std::rand() % 11;
		value += increase;	
	}

	linked_list list2;

	value = 0;
	for (int i = 0; i < 10; i++) {
		list2.push_back(value);
		int increase = std::rand() % 11;
		value += increase;
	}


	std::cout << "----------------------------\n_Test 1_\n" 
		<< "Generate two linked lists containing random integers.\n"
		<< "Both lists start at 0, and each subsequent integer is randomly between 0 and 10 greater than the preceding one.\n\n"
		<< "[List 1] ";
	list1.print();
	
	std::cout << "[List 2] ";
	list2.print();
	std::cout << "----------------------------\n";
	
	//2
	double removed;
	double list1_at_4 = list1.at(4);
	double list2_at_4 = list2.at(4);

	std::string removed_from;

	if (list1.at(4) >= list2.at(4)) {
		list1.remove(4);
		removed = list1_at_4;
		removed_from = "List 1";
	}
	else {
		list2.remove(4);
		removed = list2_at_4;
		removed_from = "List 2";
	}

	std::cout << "----------------------------\n_Test 2_\n" 
		<< "The fifth elements(index 4) of two linked lists are compared, and the greater one is removed.\n\n"
		<< "[List 1] ";
	list1.print();

	std::cout << "[List 2] ";
	list2.print();
	std::cout << "\nRemoved element from " << removed_from << ": " << removed << std::endl;
	std::cout << "----------------------------\n";
	
	//3
	linked_list list3;
	std::string used_list;

	if (list1.size() < list2.size()) {
		list3 = list1;
		used_list = "List 1";
	}
	else {
		list3 = list2;
		used_list = "List 2";	
	}

	std::cout << "----------------------------\n_Test 3_\n" 
		<< "A new linked list is created and initialized based on the modified list from test 2,\n"
		<< "using the overloaded assignment operator (=).\n\n"
		<< "[List 3 in reversed order] ";
	list3.print_reverse();
	std::cout << "\nThe list was created from " << used_list << std::endl;
	std::cout << "----------------------------\n";

	//4

	linked_list removed_list;
	
	std::cout << "----------------------------\n_Test 4_\n"
		<< "Every other element was removed from the list that was not modified in test 2.\n\n";

	if (list1.size() == 10) {

		std::cout << "[List 1 before] ";
		list1.print();

		for (int i = 0; i < 5; i++) {
			removed_list.push_front(list1.pop_back());
			list1.push_front(list1.pop_back());
		}
		std::cout << "[List 1 after] ";
		list1.print();
	}
	else {
		std::cout << "[List 2 before] ";
		list2.print();

		for (int i = 0; i < 5; i++) {
			removed_list.push_front(list2.pop_back());
			list2.push_front(list2.pop_back());
		}

		std::cout << "[List 2 after] ";
		list2.print();
	}

	std::cout << "\nRemoved elements: ";
	removed_list.print();
	std::cout << "----------------------------\n";
	
	//5

	std::cout << "----------------------------\n_Test 5_\n"
		<< "The list that remained unchanged in test 2 is printed using the global print_list function,\n"
		<< "in order to test the copy constructor and destructor.\n\n";
	
	if (list2.size() == 5) {
		std::cout << "[List 1] ";
		print_list(list1);
	}
	else {
		std::cout << "[List 2] ";
		print_list(list2);
	}
	std::cout << "----------------------------\n";

	//6
	linked_list list4 = merg(list1, list2);

	std::cout << "----------------------------\n_Test 6_\n" 
		<< "The two original lists were merged using the global merge function.\n"
		<< "The resulting list is expected to be sorted after merging.\n\n"
		<< "[List 4] ";
	list4.print();
	std::cout << "----------------------------\n";

	//7
	std::cout << "----------------------------\n_Test 7_\n"
		<< "Verifying whether the list created in test 6 is sorted.\n\n"
		<< "List 4 ";
	is_sorted(list4);
	std::cout << "----------------------------\n" << std::endl;

	//eget self.assignment +=

	linked_list test1;

	for (int i = 0; i < 5; i++) {
		test1.push_back(i);
	}

	test1.print();

	test1 += test1; 

	test1.print();

	linked_list test2;

	test2 += test1;

	test2.print();

	return 0;
}