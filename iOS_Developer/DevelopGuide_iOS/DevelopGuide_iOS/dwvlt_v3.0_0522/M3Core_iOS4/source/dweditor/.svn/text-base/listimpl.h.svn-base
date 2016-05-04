#ifndef _LIST_IMPL_H
#define _LIST_IMPL_H

namespace EMFGenCom {

template <class T>
struct ListNode
{
	ListNode<T>* m_next;
	ListNode<T>* m_prev;
	T m_data;
};

template <class T>
struct ListIterator
{
	ListNode<T>* m_node;

	ListIterator(ListNode<T>* x) : m_node(x) {}
	ListIterator() {}
	ListIterator(const ListIterator<T>& x) : m_node(x.m_node) {}

	T& operator*() const { return m_node->m_data; }

	void incr() { m_node = m_node->m_next; }
	void decr() { m_node = m_node->m_prev; }

	bool operator==(const ListIterator& x) const { return m_node == x.m_node; }
	bool operator!=(const ListIterator& x) const { return m_node != x.m_node; }

	ListIterator<T>& operator++() { incr(); return *this; }
	ListIterator<T>& operator--() { decr(); return *this; }
};

template <class T>
class List
{
public:
	List() {
		m_node = getnode();
		m_node->m_next = m_node;
		m_node->m_prev = m_node;
	}
	~List() {
		clear(); putnode(m_node);
	}
	void clear() {
		ListNode<T>* cur = m_node->m_next;
		while (cur != m_node) {
			ListNode<T>* tmp = cur;
			cur = cur->m_next;
			putnode(tmp);
		}
		m_node->m_next = m_node;
		m_node->m_prev = m_node;
	}

protected:
	ListNode<T>* getnode() { return new ListNode<T>; }
	void putnode(ListNode<T>* p) { delete p; }
	ListNode<T>* createNode(const T& x) {
		ListNode<T>* p = getnode();
		if (p != 0) p->m_data = x;
		return p;
	}

protected:
	ListNode<T>* m_node;

public:
	ListIterator<T> begin() { return m_node->m_next; }
	ListIterator<T> end() { return m_node; }
	bool empty() const { return m_node->m_next == m_node; }

	T& front() { return *begin(); }
	T& back() { return *(--end()); }

	void push_back(const T& x) { insert(end(), x); }
	void push_front(const T& x) { insert(begin(), x); }

	ListIterator<T> insert(ListIterator<T> position, const T& x) {
		ListNode<T>* tmp = createNode(x);
		tmp->m_next = position.m_node;
		tmp->m_prev = position.m_node->m_prev;
		position.m_node->m_prev->m_next = tmp;
		position.m_node->m_prev = tmp;
		return tmp;
	}

	ListIterator<T> erase(ListIterator<T> position) {
		ListNode<T>* next = position.m_node->m_next;
		ListNode<T>* prev = position.m_node->m_prev;
		ListNode<T>* n = position.m_node;
		prev->m_next = next;
		next->m_prev = prev;
		putnode(n);
		return ListIterator<T>(next);
	}

	size_t size() {
		int count = 0;
		for (ListIterator<T> it = begin(); it != end(); ++it) {
			count += 1;
		}
		return count;
	}
};

template <class T>
class MyList : private List<T> {
public:
	typedef ListIterator<T> iterator;

	iterator begin() { return List<T>::begin(); }
	iterator end() { return List<T>::end(); }

	int push_back(const T& x) {
		try {
			List<T>::push_back(x);
		} catch (...) {
			return 0x8007000E; // kERROUTOFMEMORY
		}
		return 0; // kNOERROR
	}

	bool IsEmpty() { return List<T>::empty(); }
	int size() { return (int)List<T>::size(); }
};

} // end of namespace

#endif
