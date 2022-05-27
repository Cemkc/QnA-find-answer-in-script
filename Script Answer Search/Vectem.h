#include <iostream>
#include <assert.h>

template<typename T>
struct node {
	T data;
	int counter = 1;
	int qNum = 0;
	node<T>* next;
};

template<typename T>
class Vectem {
protected:
	node<T>* head;
	node<T>* last;
	int lenght;
public:
	Vectem() {
		head = NULL;
		last = NULL;
		lenght = 0;
	}
	Vectem(int firstLenght, T value) : lenght(firstLenght) {
		node<T>* current;
		head = new node<T>;
		current = head;
		for (int i = 0; i < firstLenght; i++) {
			current->data = value;
			current->next = new node<T>;
			if (i != firstLenght - 1) {
				current = current->next;
			}
		}
		last = current;
		last->next = NULL;
	}
	bool isEmpty() {
		if (lenght == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	node<T>* search(int indx) {
		node<T>* current;
		current = head;
		int count = 0;
		while (current != NULL) {
			if (count == indx) {
				break;
			}
			current = current->next;
			count++;
		}
		return current;
	}
	int find(T value) {
		assert(lenght >= 0);
		bool isFound = false;
		node<T>* current;
		current = head;
		int pos = 0;
		while (current != NULL) {
			if (current->data == value) {
				return pos;
				isFound = true;
				break;

			}
			pos++;
			current = current->next;
		}
		if (!isFound) {
			return -1;
		}
	}
	void insert(T value, int qNum) {

		if (find(value) != -1) {
			node<T>* current;
			current = head;
			for (int i = 0; i < find(value); i++) {
				current = current->next;
			}
			current->counter++;
		}
		if (isEmpty()) {
			head = new node<T>;
			last = head;
			last->data = value;
			last->qNum = qNum;
			last->next = NULL;
			lenght++;
		}
		else {
			last->next = new node<T>;
			last = last->next;
			last->data = value;
			last->qNum = qNum;
			last->next = NULL;
			lenght++;
		}

	}
	void insertAt(int indx, T value) {
		node<T>* current;
		node<T>* track;
		current = head;
		if (indx == 0) {
			head = new node<T>;
			head->data = value;
			head->next = current;
		}
		else if (indx == 1) {
			track = head->next->next;
			current->next = new node<T>;
			current->next->data = value;
			current->next->next = track;
		}
		else {
			for (int i = 0; i < indx - 1; i++) {
				current = current->next;
			}
			track = current->next;
			current->next = new node<T>;
			current->next->next = track;
			current->next->data = value;
		}
		lenght++;
		/*if the user adds an alament to the last remember to
		point the "last" pointer to NULL */
	}
	void deleteAt(int indx) {
		node<T>* current;
		node<T>* track;
		track = search(indx);
		current = search(indx - 1);
		current->next = current->next->next;
		delete track;
		lenght--;
	}
	void print() {
		node<T>* current;
		current = head;
		while (current != NULL) {
			std::cout << current->data << " " << current->counter << std::endl;
			current = current->next;
		}
	}
	int size() {
		return lenght;
	}
	T& operator [](int indx) {
		assert(indx < lenght);
		return search(indx)->data;

	}
	void destroyList() {
		node<T>* current;
		while (head != NULL) {
			current = head;
			head = head->next;
			delete current;
		}
		last = NULL;
		lenght = 0;
	}
	int getQnumber(T elem) {
		int indx = find(elem);
		return search(indx)->qNum;
	}
	~Vectem() {
		destroyList();
		std::cout << "Vectem has been destroyed. ";
	}

};








