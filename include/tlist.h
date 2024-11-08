#pragma once

#ifndef __TList_H__
#define __TList_H__

#include <iostream>

using namespace std;

// задача на список номер 9 : инвертаци€ списка за один проход, ќ(n)
// реализована в методе invertation()

template<typename T>
class List {
	struct Node {
		T data;
		Node* next;
		Node(T _data, Node* _next) :data(_data), next(_next){};
	};
	Node* first;
public:
	class iterator {
		Node* curr;
	public:
		explicit iterator(Node* node) : curr(node) {}
		iterator& operator++() {
			if (!curr) throw 1; // если указатель итак находитс€ на последнем элементе
			curr = curr->next;
			return *this;
		}
		iterator operator++(int) {
			iterator copy = *this;
			curr = curr->next;
			return copy;
		}
		iterator& operator+(int n) {
			while (n--) {
				(*this)++;
			}
			return *this;
		}
		T& operator*() { return curr->data; }
		T* operator->() { return &(curr->data); }
		friend bool operator!=(const iterator& it1, const iterator& it2) {
			return (it1.curr != it2.curr);
		}
		friend bool operator==(const iterator& it1, const iterator& it2) {
			return (it1.curr == it2.curr);
		}
		friend iterator& List::erase(iterator& it);
		friend iterator& List::insert(T value, iterator& it);
	};
	iterator& begin() const {
		return iterator(first);
	}

	iterator& end() const {
		return iterator(nullptr);
	}
	List() {
		first = nullptr;
	}
	List(int n, T def = T()) {
		if (n < 0) throw 1;
		if (n == 0) {
			first = nullptr;
			return;
		}
		first = new Node(T(), nullptr);
		Node* tmp = first;
		while (--n) {
			tmp->next = new Node(T(), nullptr);
			tmp = tmp->next;
		}

	}
	List(const List<T>& other) {
		if (!other.first) {
			first = nullptr;
			return;
		}
		Node *ocurrent = other.first;
		first = new Node(ocurrent->data, nullptr);
		Node* current = first;
		while (ocurrent->next) {
			ocurrent = ocurrent->next;
			current = current->next = new Node(ocurrent->data, nullptr);
		}
	}
	~List();
	List& operator=(const List&);
	void print();
	T& operator[](int index);
	iterator& insert(T value, iterator& it) {
		Node* prev = it.curr;
		Node* tmp = new Node(value, prev->next);
		prev->next = tmp;
		return ++it;
	}
	iterator& insert_front(T value) {
		first = new Node(value, first);
		return iterator(first);
	}
	
	
	iterator& erase(iterator& it) {
		Node* tmp = (it.curr)->next;
		if (!tmp) throw 1;
		(it.curr)->next = tmp->next;
		delete tmp;
		return ++it;
	}
	iterator& erase_front() {
		if (!first) { return iterator(first); }
		Node* tmp = first->next;
		delete first;
		first = tmp;
		return iterator(first);
	}
	iterator& find(T value) {
			Node* current = first;
			while (current) {
				if ((current->data) == value) { return iterator(current); };
				current = current->next;
			}
			return iterator(nullptr);  // когда элемент со значением value не найден
		}
	friend bool operator==(const List& l1, const List& other) {
		Node* current = l1.first, * ocurrent = other.first;
		while (current) {
			if (!ocurrent) return 0;
			if ((current->data) != (ocurrent->data)) return 0;
			current = current->next;
			ocurrent = ocurrent->next;
		}
		if (ocurrent) return 0;
		return 1;
	}

	friend bool operator!=(const List& list1, const List& list2) {
		return !(list1 == list2);
	}
	iterator& invertation() {
		if (!first) { return iterator(nullptr); }
		Node* current = first;
		Node* cnext = current->next;
		current->next = nullptr;
		while (cnext) {
			Node* tmp = cnext->next;
			cnext->next = current;
			current = cnext;
			cnext = tmp;
		}
		return iterator(first = current); //ссылка на новый first
	}
};


template<typename T>
inline List<T>::~List() {
	Node* current = first;
	while (current) {
		Node* tmp = current->next;
		delete[] current;
		current = tmp;
	}
	// можно ли короче?
}

//template<typename T>
//inline List<T>::List(const List& other) {
//	if (!other.first) {
//		first = nullptr;
//		return;
//	}
//	Node* current = first, *ocurrent = other.first;
//	first = new Node(occurent->data, nullptr);
//	while (ocurrent->next) {
//		ocurrent = ocurrent->next;
//		current = current->next = new Node(ocurrent->data, nullptr);
//	}
//}

template<typename T>
inline void List<T>::print() {
	Node* current = first;
	while (current) {
		std::cout << current->data << " ";
		current = current->next;
	}
}

template<typename T>
inline T& List<T>::operator[](int index) {
	if (index < 0) throw 1;
	if (!first) throw 1;
	Node* current = first;
	while(index--) {
		current = current->next;
		if (!current) throw 1;
	}
	return current->data;
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& other) {
	if (*this == other) { return *this; }
	Node* current = first;
	while (current) {
		Node* tmp = current->next;
		delete current;
		current = tmp;
	}
	Node *ocurrent = other.first;
	if (!ocurrent) {
		first = nullptr;
		return *this;
	}
	current = first = new Node(ocurrent->data, nullptr);
	while (ocurrent->next) {
		ocurrent = ocurrent->next;
		current = current->next = new Node(ocurrent->data, nullptr);

	}
	return *this;
}

//template<typename T>
//inline List<T>::Node* List<T>::insert(T value, List<T>::Node* prev) {
//	return prev->next = Node* tmp = new Node(value, prev->next);
//}

//template<typename T>
//inline List<T>::Node* List<T>::insert_front(T value) {
//	return first = new Node(value, first);
//}



//template<typename T>
//inline List<T>::Node* List<T>::erase_front() {
//	if (!first) {return first};
//	Node* tmp = first->next;
//	delete first;
//	return first = tmp;
//}

//template<typename T>
//inline List<T>::Node* List<T>::find(T value) {
//	Node* current = first;
//	while (current) {
//		if ((current->data) == value) { return current; };
//		current = current->next;
//	}
//	return nullptr;  // когда элемент со значением value не найден
//}



#endif __TList_H__