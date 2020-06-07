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
	//������ �������������
	Dequeue();
	Dequeue(const Dequeue& copyDequeue);
	Dequeue& operator=(const Dequeue& copyDequeue);

	~Dequeue();

	// ������ � �������� �������� �� �������
	ValueType& operator[](const size_t pos) const;

	//�������� ������� ������ �������� � �����
	void pushBack(ValueType value);

	//�������� �������� ��������� ��������,
	void popBack();

	//�������� ������� ������ �������� � ������,
	void pushFront(ValueType value);

	//�������� �������� ���������� ��������.
	void popFront();

	//�������� �� ������� ���������
	bool isEmpty();

	size_t size() const;
private:
	Node* _head;
	Node* _tail;
	size_t	_size;

	void forceNodeDelete(Node* node);
};