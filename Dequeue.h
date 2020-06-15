#pragma once

#include <stdexcept>

using ValueType = double;
template <typename ValueType>
class Dequeue
{
	
	struct Node {
		Node()
		{}
		Node(const ValueType& value, Node* next, Node* prev);
		/*~Node();

		void insertNext(const ValueType& value);
		void removeNext();*/

		ValueType value;
		Node* next;
		Node* prev;
	};

public:
	//тройка конструкторов
	Dequeue();
	Dequeue(const Dequeue& copyDequeue);
	//Dequeue& operator=(const Dequeue& copyDequeue);

	~Dequeue();

	// доступ к значению элемента по индексу
	ValueType& operator[](const size_t pos) const;

	//поиск по значению
	size_t find(ValueType value) const;

	//операция вставки нового элемента в конец
	void pushBack(ValueType value);

	//операция удаления конечного элемента,
	void popBack();

	//операция вставки нового элемента в начало,
	void pushFront(ValueType value);

	//операция удаления начального элемента.
	void popFront();

	//проверка на наличие элементов
	bool isEmpty();
	
	size_t size() const;
private:
	Node* _head;
	Node* _tail;
	size_t	_size;

	void forceNodeDelete(Node* node);
};

template<typename ValueType>
inline bool Dequeue<ValueType>::isEmpty()
{
	if (_size == 0)return true;
	return false;
}

template<typename ValueType>
inline size_t Dequeue<ValueType>::size() const
{
	return _size;
}

template<typename ValueType>
inline void Dequeue<ValueType>::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}

template<typename ValueType>
inline Dequeue<ValueType>::Dequeue()
{
	_size = 0;
	_head = nullptr;
	_tail = _head;
}

template<typename ValueType>
inline Dequeue<ValueType>::Dequeue(const Dequeue& copyDequeue)
{
	this->_size = copyDequeue._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		this->_tail = nullptr;
		return;
	}

	this->_head = new Node(copyDequeue._head->value, copyDequeue._head->next, copyDequeue._head->prev);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyDequeue._head;

	while (currentCopyNode->next) {
		currentCopyNode = currentCopyNode->next;
		currentNode->next = new Node(currentCopyNode->value, currentCopyNode->next, currentCopyNode->prev);
		currentNode = currentNode->next;
	}
	this->_tail = copyDequeue._tail;
	_tail->prev = copyDequeue._tail->prev;
	_tail->next = nullptr;


}

template<typename ValueType>
inline Dequeue<ValueType>::~Dequeue()
{
	forceNodeDelete(_head);
}

template<typename ValueType>
inline ValueType& Dequeue<ValueType>::operator[](const size_t pos) const
{
	if(pos >_size || _size < 0) throw std::out_of_range("Incorrect index");
	Node* buf;
	if (_size == 1)
	{
		return _head->value;
	}
	else if (pos < _size / 2)
	{
		buf = _head;
		for (size_t i = 0; i < pos; i++)
		{
			buf = buf->next;
		}
	}
	else
	{
		buf = _tail;
		for (size_t i = _size-1; i>pos ; i--)
		{
			buf = buf->prev;
		}
	}
	return buf->value;
}

template<typename ValueType>
inline size_t Dequeue<ValueType>::find(ValueType value) const
{
	Node* buf = _head;
	for (size_t i = 0; i < _size; i++)
	{
		if (buf->value == value)return i;
		buf = buf->next;
	}
	return -1;
}

template<typename ValueType>
inline void Dequeue<ValueType>::pushBack(ValueType value)
{
	if (_size == 0)
	{
		_head = new Node;
		_head->value = value;
		_head->prev = nullptr;
		_head->next = nullptr;
		_tail = _head;
	}
	else
	{
		Node* buf;
		_tail->next = new Node;
		buf = _tail;
		_tail = _tail->next;
		_tail->value = value;
		_tail->next = nullptr;
		_tail->prev = buf;

	}
		_size++;
}

template<typename ValueType>
inline void Dequeue<ValueType>::popBack()
{
	_tail = _tail->prev;
	delete _tail->next;
	_tail->next = nullptr;
	_size--;
}

template<typename ValueType>
inline void Dequeue<ValueType>::pushFront(ValueType value)
{
	Node* buf = _head;
	_head->prev = new Node;
	_head = _head->prev;
	_head->next = buf;
	_head->value = value;
	_head->prev = nullptr;
	_size++;
}

template<typename ValueType>
inline void Dequeue<ValueType>::popFront()
{
	_head = _head->next;
	_head->prev = nullptr;
	_size--;

}

template<typename ValueType>
inline Dequeue<ValueType>::Node::Node(const ValueType& value, Node* next, Node* prev)
{
	this->value = value;
	this->next = next;
	this->prev = prev;

}
