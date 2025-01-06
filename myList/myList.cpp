#include <iostream>

template <typename T>
class myList
{
public:
	struct Node
	{
		T data;
		Node* prev;
		Node* next;
	};

	class iterator
	{
	private:
		Node* node;
	public:
		iterator(Node* node = nullptr) : node(node) {}
		
		iterator& operator++()
		{
			node = node->next;
			return *this;
		}

		iterator& operator++(int)
		{
			iterator temp = *this;
			node = node->next;
			return temp;
		}

		iterator& operator--()
		{
			node = node->prev;
			return *this;
		}

		iterator& operator--(int)
		{
			iterator temp = *this;
			node = node->prev;
			return temp;
		}

		T& operator*()
		{
			return node->data;
		}

		bool operator==(const iterator& other)
		{
			return node == other.node;
		}

		bool operator!=(const iterator& other)
		{
			return node != other.node;
		}
	};

private:
	int list_size = 0;
	Node* head;
	Node* tail;
public:
	myList()
	{
		head = new Node;
		tail = new Node;

		head->next = tail;
		tail->prev = head;

		head->prev = nullptr;
		tail->next = nullptr;
	}
	~myList() {}

	iterator begin()
	{
		return iterator(head->next);
	}

	iterator end()
	{
		return iterator(tail);
	}

	void push_front(T data)
	{
		Node* temp = new Node;
		temp->data = data;
		temp->prev = head;
		temp->next = head->next;
		head->next = temp;
		temp->next->prev = temp;
		list_size++;
	}

	void push_back(T data)
	{
		Node* temp = new Node;
		temp->data = data;
		temp->prev = tail->prev;
		temp->next = tail;
		tail->prev = temp;
		temp->prev->next = temp;
		list_size++;
	}

	void pop_front()
	{
		if (!empty())
		{
			Node* temp = head->next;
			head->next = temp->next;
			temp->next->prev = head;
			delete(temp);
			list_size--;
		}
	}

	void pop_back()
	{
		if (!empty())
		{
			Node* temp = tail->prev;
			tail->prev = temp->prev;
			temp->prev->next = tail;
			delete(temp);
			list_size--;
		}
	}

	void clear()
	{
		iterator iter = this->begin();

		while (iter != this->end())
		{
			delete(iter++);
		}
	}

	int size()
	{
		return list_size;
	};

	bool empty()
	{
		return list_size == 0 ? true : false;
	};

	iterator erase(iterator iter)
	{
		//return temp;
	}

	void remove(T data)
	{
		iterator iter;

		for (iter = this->begin(); iter != this->end(); iter++)
		{
			if (*iter == data)
				erase(iter);
		}
	}
};

int main()
{
	myList<int> list;

	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.push_back(8);
	list.push_back(9);
	list.push_back(10);

	list.pop_back();
	list.pop_back();
	list.pop_front();
	list.pop_front();

	list.remove(6);

	myList<int>::iterator iter;

	for (iter = list.begin(); iter != list.end(); iter++)
	{
		printf("%d\n", *iter);
	}
}