﻿#pragma once

template <typename T>
class myList
{
public:
	struct Node
	{
		T _data;
		Node* _prev;
		Node* _next;
	};

	class iterator
	{
	private:
		Node* _node;
	public:
		iterator(Node* node = nullptr) : _node(node) {}
		
		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		iterator& operator++(int)
		{
			iterator temp = *this;
			_node = _node->_next;
			return temp;
		}

		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		iterator& operator--(int)
		{
			iterator temp = *this;
			_node = _node->_prev;
			return temp;
		}

		T& operator*()
		{
			return _node->_data;
		}

		bool operator==(const iterator& other)
		{
			return (_node == other._node) ? true : false;
		}

		bool operator!=(const iterator& other)
		{
			return (_node != other._node) ? true : false;
		}

		friend myList;
	};

private:
	int _size = 0;
	Node _head;
	Node _tail;
public:
	myList()
	{
		_head._next = &_tail;
		_tail._prev = &_head;
	}
	~myList() {}

	iterator begin()
	{
		return iterator(_head._next);
	}

	iterator end()
	{
		return iterator(&_tail);
	}

	void push_front(T data)
	{
		Node* temp = new Node;
		temp->_data = data;
		temp->_prev = &_head;
		temp->_next = _head._next;
		_head._next = temp;
		temp->_next->_prev = temp;
		_size++;
	}

	void push_back(T data)
	{
		Node* temp = new Node;
		temp->_data = data;
		temp->_prev = _tail._prev;
		temp->_next = &_tail;
		_tail._prev = temp;
		temp->_prev->_next = temp;
		_size++;
	}

	void pop_front()
	{
		if (!empty())
		{
			Node* temp = _head._next;
			_head._next = temp->_next;
			temp->_next->_prev = &_head;
			delete(temp);
			_size--;
		}
	}

	void pop_back()
	{
		if (!empty())
		{
			Node* temp = _tail._prev;
			_tail._prev = temp->_prev;
			temp->_prev->_next = &_tail;
			delete(temp);
			_size--;
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
		return _size;
	};

	bool empty()
	{
		return (_size == 0) ? true : false;
	};

	iterator erase(iterator iter)
	{
		Node* temp = iter._node;
		temp->_prev->_next = temp->_next;
		temp->_next->_prev = temp->_prev;
		iter++;
		delete(temp);
		return iter;
	}

	void remove(T data)
	{
		iterator iter;

		for (iter = this->begin(); iter != this->end();)
		{
			if (*iter == data)
				erase(iter);
			else
				iter++;
		}
	}
};