#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <algorithm>    

class linked_list {
public:
	linked_list();
	linked_list(const linked_list& src);

	~linked_list();

	linked_list& operator=(linked_list rhs);

	linked_list& operator+=(const linked_list& rhs);

	void insert(double value, size_t pos);
	void push_front(double value);
	void push_back(double value);

	inline double front() const { return head->data; };
	inline double back() const { return tail->data; };
	double at(size_t pos) const;

	void remove(size_t pos);
	double pop_front();
	double pop_back();

	size_t size() const;
	inline bool is_empty() const { return head == nullptr && tail == nullptr; };
	void print() const;
	void print_reverse() const;

private:
	struct node {
		node(double value);
		double data;
		node* next;
		node* prev;
	};

	node* head;
	node* tail;
};

#endif 