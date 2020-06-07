#pragma once
using ValueType = double;
template <typename ValueType>
class Dequeue
{
	
	struct Node {
		Node(const ValueType& value, Node* next = nullptr, Node* prev = nullptr);
		~Node();

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType value;
		Node* next;
		Node* prev;
	};

public:
	//тройка конструкторов
	Dequeue();
	Dequeue(const Dequeue& copyDequeue);
	Dequeue& operator=(const Dequeue& copyDequeue);

	~Dequeue();

	// доступ к значению элемента по индексу
	ValueType& operator[](const size_t pos) const;

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