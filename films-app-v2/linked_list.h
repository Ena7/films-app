#pragma once
#include <exception>
#include <iostream>

template <typename TElem>
struct Node {
	TElem data;
	Node* next;
	Node(TElem data) : data{ data }, next{ nullptr } {};
	Node(TElem data, Node* next) : data{ data }, next{ next } {};
};

template <typename TElem>
class LkdLstIter;

template <typename TElem>
class LkdLst {
	Node<TElem>* head;
	void destroyNodes() noexcept;
	Node<TElem>* copyNodes(Node<TElem>* current);
public:
	LkdLst() noexcept: head{ nullptr } {};
	
	//rule of 3
	LkdLst(const LkdLst& other);
	void operator=(const LkdLst& other);
	~LkdLst();
	//LkdLst(LkdLst&& other);
	//LkdLst& operator=(LkdLst&& other);

	TElem& operator[](unsigned int pos);

	//returneaza dimensiunea listei
	unsigned int size() const noexcept;

	//adauga un nod la finalul listei
	void push_back(TElem elem);

	//returneaza valoarea nodului de la pozitia data
	TElem at(unsigned int posToBeRet) const;

	//sterge un nod de la pozitia data
	void erase(unsigned int posToBeDel) noexcept;

	//returneaza un iterator pozitionat pe primul nod
	LkdLstIter<TElem> begin() const noexcept;

	//returneaza un iterator pozitionat pe ultimul nod
	LkdLstIter<TElem> end() const noexcept;

};

template<typename TElem>
void LkdLst<TElem>::destroyNodes() noexcept {
	Node<TElem>* currentNode = head;
	while (currentNode != nullptr) {
		Node<TElem>* aux = currentNode->next;
		delete currentNode;
		currentNode = aux;
	}
	head = nullptr;
}

template<typename TElem>
Node<TElem>* LkdLst<TElem>::copyNodes(Node<TElem>* current) {
	if (current == nullptr) {
		return nullptr;
	}
	Node<TElem>* node = new Node<TElem>{ current->data };
	node->next = copyNodes(current->next);
	return node;
}

//rule of 3
template <typename TElem>
LkdLst<TElem>::LkdLst(const LkdLst& other) {
	head = copyNodes(other.head);
	//std::cout << " $ ";
}

//rule of 3
template<typename TElem>
void LkdLst<TElem>::operator=(const LkdLst& other) {
	destroyNodes();
	head = copyNodes(other.head);
}

//rule of 3
template <typename TElem>
LkdLst<TElem>::~LkdLst() {
	destroyNodes();
}

template <typename TElem>
TElem& LkdLst<TElem>::operator[](unsigned int pos) {
	Node<TElem>* currentNode = head;
	unsigned int lg = 0;
	while (lg < pos) {
		lg++;
		currentNode = currentNode->next;
	}
	return currentNode->data;
}

template<typename TElem>
unsigned int LkdLst<TElem>::size() const noexcept {
	Node<TElem>* currentNode = head;
	unsigned int lg = 0;
	while (currentNode != nullptr) {
		lg++;
		currentNode = currentNode->next;
	}
	return lg;
}

template<typename TElem>
void LkdLst<TElem>::push_back(TElem elem) {
	Node<TElem>* currentNode = head;
	while (currentNode != nullptr && currentNode->next != nullptr) {
		currentNode = currentNode->next;
	}
	if (currentNode == nullptr) {
		head = new Node<TElem>{ elem, nullptr };
	}
	else {
		currentNode->next = new Node<TElem>{ elem, nullptr };
	}
}

template<typename TElem>
TElem LkdLst<TElem>::at(unsigned int posToBeRet) const {
	Node<TElem>* currentNode = head;
	unsigned int lg = 0;
	while (lg < posToBeRet) {
		lg++;
		currentNode = currentNode->next;
	}
	return currentNode->data;
}

template<typename TElem>
void LkdLst<TElem>::erase(unsigned int posToBeDel) noexcept{
	Node<TElem>* currentNode = head;
	unsigned int pos = 0;
	if (pos == posToBeDel) {
		head = currentNode->next;
		delete currentNode;
		return;
	}
	posToBeDel--;
	while (currentNode != nullptr && currentNode->next != nullptr) {
		if (pos == posToBeDel) {
			Node<TElem>* aux = currentNode->next;
			currentNode->next = currentNode->next->next;
			delete aux;
			return;
		}
		currentNode = currentNode->next;
		pos++;
	}
}

template<typename TElem>
LkdLstIter<TElem> LkdLst<TElem>::begin() const noexcept{
	return LkdLstIter<TElem>{ head };
}

template<typename TElem>
LkdLstIter<TElem> LkdLst<TElem>::end() const noexcept{
	return LkdLstIter<TElem>{ nullptr };
}

template<typename TElem>
class LkdLstIter {
	Node<TElem>* current;
public:
	LkdLstIter(Node<TElem>* current) noexcept :current{ current } {}
	void operator++() noexcept;
	TElem& operator*() const noexcept;
	bool operator==(LkdLstIter& other);
	bool operator!=(LkdLstIter& other) noexcept;
};

template <typename TElem>
void LkdLstIter<TElem>::operator++() noexcept {
	current = current->next;
}

template<typename TElem>
TElem& LkdLstIter<TElem>::operator*() const noexcept {
	return current->data;
}

template<typename TElem>
bool LkdLstIter<TElem>::operator==(LkdLstIter& other) {
	return current == other.current;
}

template<typename TElem>
bool LkdLstIter<TElem>::operator!=(LkdLstIter& other) noexcept {
	return current != other.current;
}
