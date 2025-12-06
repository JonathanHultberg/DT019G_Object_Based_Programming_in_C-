#include "linked_list.h"

linked_list::node::node(double value) {
	data = value;
	next = nullptr;
	prev = nullptr;
}

linked_list::linked_list() {
	head = nullptr;
	tail = nullptr;
}

linked_list::linked_list(const linked_list& src) {
	head = nullptr;
	tail = nullptr;
	for (node* current = src.head; current != nullptr; current = current->next) {
		push_back(current->data);
	}
}

linked_list::~linked_list() {
	node* current = head;
	while (current != nullptr) {
		node* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
	tail = nullptr;
}

linked_list& linked_list::operator=(linked_list rhs) {
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
}

linked_list& linked_list::operator+=(const linked_list& rhs) {
	node* current = rhs.head;
	node* old_tail = tail;

	while (current != nullptr) {
		push_back(current->data);
		
		if (current == old_tail) {
			break;
		}

		current = current->next;
	}

	return *this;
}

void linked_list::insert(double value, size_t pos) {
	if (is_empty()) {
		if (pos != 0) {
			throw std::out_of_range("Index out of range");
		}
		push_front(value);
		return;
	}
	if (pos == 0) {
		push_front(value);
		return;
	}
	if (pos == size()) {
		push_back(value);
		return;
	}
	if (pos > size()) {
		throw std::out_of_range("Index out of range");
	}

	node* new_node = new node(value);

	node* new_node_next = head;
	node* new_node_prev = nullptr;

	for (size_t i = 0; i != pos; i++) {
		new_node_next = new_node_next->next;
	}

	new_node_prev = new_node_next->prev;

	new_node->next = new_node_next;
	new_node->prev = new_node_prev;

	new_node_next->prev = new_node;
	new_node_prev->next = new_node;
}

void linked_list::push_front(double value) {
	node* new_node = new node(value);

	if (is_empty()) {
		head = new_node;
		tail = new_node;
	}
	else {
		head->prev = new_node;
		new_node->next = head;
		head = new_node;
	}
}

void linked_list::push_back(double value) {
	node* new_node = new node(value);
	
	if (is_empty()) {
		head = new_node;
		tail = new_node;
	}
	else {
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}
}	

double linked_list::at(size_t pos) const {
	if (is_empty()) {
		throw std::out_of_range("List is empty");
	}
	if (pos >= size()) {
		throw std::out_of_range("Index out of range");
	}
	
	node* pointer = head;
	for (size_t i = 0; i != pos; i++) {
		pointer = pointer->next;
	}
	return pointer->data;
}

void linked_list::remove(size_t pos) {
	if (is_empty()) {
		throw std::out_of_range("List is empty");
	}
	if (pos == 0) {
		pop_front();
		return;
	}
	if (pos == (size() - 1)) {
		pop_back();
		return;
	}
	if (pos >= size()) {
		throw std::out_of_range("Index out of range");
	}

	node* del = head;
	node* del_prev = nullptr;
	node* del_next = nullptr;

	for (size_t i = 0; i != pos; i++) {
		del = del->next;
	}

	del_prev = del->prev;
	del_next = del->next;	

	del_prev->next = del_next;
	del_next->prev = del_prev;

	delete del;
}

double linked_list::pop_front() {
	if (is_empty()) {
		throw std::out_of_range("List is empty");
	}

	double pop_value = head->data;
	
	node* del = head;
	head = head->next;
	
	if (head != nullptr) {
		head->prev = nullptr;
	} 
	else {
		tail = nullptr;
	}

	delete del;
	
	return pop_value;
}

double linked_list::pop_back() {
	if (is_empty()) {
		throw std::out_of_range("List is empty");
	}

	double pop_value = tail->data;
	
	node* del = tail;
	tail = tail->prev;
	
	if (tail != nullptr) {
		tail->next = nullptr;
	}
	else {
		head = nullptr;
	}

	delete del;

	return pop_value;
}

size_t linked_list::size() const {
	size_t count = 0;
	for (node* pointer = head; pointer != nullptr; pointer = pointer->next) {
		count++;
	}
	return count;
}

void linked_list::print() const {
	for (node* pointer = head; pointer != nullptr; pointer = pointer->next) {
		std::cout << pointer->data << " ";
	}
	std::cout << std::endl;
}

void linked_list::print_reverse() const {
	for (node* pointer = tail; pointer != nullptr; pointer = pointer->prev) {
		std::cout << pointer->data << " ";
	}
	std::cout << std::endl;
}