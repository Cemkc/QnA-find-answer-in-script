#include <string>
#include "Vectem.h"


class HashT
{
	Vectem<std::string>* hashArr;
	int size;
	int length;
public:
	HashT() {
		hashArr = new Vectem<std::string>[100];
		size = 100;
		length = 0;
	}
	int key(std::string elem) {
		unsigned long hash = 5381;
		int strSize = elem.size();
		for (int i = 0; i < strSize; i++) {
			hash = ((hash << 5) + hash) ^ elem[i];
		}
		return hash % size;
	}
	void insert(std::string elem, int qNum) {
		hashArr[key(elem)].insert(elem, qNum);
	}
	bool search(std::string elem) {
		if (hashArr[key(elem)].find(elem) != -1) {
			return true;
		}
		else {
			return false;
		}
	}
	int getQnum(std::string elem) {
		return hashArr[key(elem)].getQnumber(elem);
	}
	void print() {
		for (int i = 0; i < size; i++) {
			hashArr[i].print();
			std::cout << "\n";
		}
	}

};


