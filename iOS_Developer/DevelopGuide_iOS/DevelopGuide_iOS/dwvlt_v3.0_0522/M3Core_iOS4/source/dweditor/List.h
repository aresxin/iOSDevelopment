// $Archive: List.h $
//
// Copyright (c) 2011 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: liuxu $
// $Date: 2011/03/31 08:12:28 $
// $Revision: 1.0 $

#ifndef LIST_H
#define LIST_H

#include <stdio.h>

template <class Node> class List;

//listnode define
template <class Node>
class ListNode
{
	friend class List <Node>;
public:
	ListNode(const Node& node);
	const Node GetData();
private:
	Node m_data;
	ListNode <Node> *next;
};

template <class Node> ListNode<Node>::ListNode(const Node &node)
:m_data(node), next(NULL){}

template <class Node> const Node ListNode<Node>::GetData(){return m_data;}

//list define
template <class Node>
class List
{
public:
	List();
	~List();
	int AddData(const Node &node);
	int MoveNext();
	int GetCurrentData(Node &node);
	void CurrentPtrInit(){m_currentPtr = m_firstPtr;};
	bool IsEmpty();
	bool IsEndOfCurrent();
	int UpdateCurrentData(const Node &node);
	unsigned long GetCount();
private:
	int CreateNewNode(const Node &node, ListNode<Node>**new_node);
private:
	ListNode<Node> *m_firstPtr;
	ListNode<Node> *m_lastPtr;
	ListNode<Node> *m_currentPtr;
	enum StatusCode
	{
		kNOERROR							=0x00000000, 				//処理成功
		kERRUNEXPECTED				=0x8000FFFF, 				//予期せぬエラー
		kERROUTOFMEMORY			=0x8007000E, 				//メモリの獲得に失敗した
		kERRPOINTERISNULL			=0x00005001
	};
};

template <class Node> bool List<Node>::IsEmpty(){return m_firstPtr == NULL;}
template <class Node> bool List<Node>::IsEndOfCurrent(){return m_currentPtr == NULL;}
template <class Node> List<Node>::List():m_firstPtr(NULL), m_lastPtr(NULL), m_currentPtr(NULL){}

template <class Node> List<Node>::~List()
{
	ListNode<Node> *tempPtr, *currentPtr = m_firstPtr;

	try
	{
		if(!IsEmpty())
		{	
			while(currentPtr)
			{
				tempPtr = currentPtr;
				currentPtr = currentPtr->next;
				delete tempPtr;
			}
		}
	}
	catch (...) { }
}

template <class Node> int List<Node>::AddData(const Node &node)
{
	int sts = kNOERROR;
	ListNode<Node> *newNode;
	
	sts = CreateNewNode(node, &newNode);
	if(sts)
	{
		return sts;
	}

	if(IsEmpty())
	{
		m_firstPtr = m_lastPtr = m_currentPtr = newNode;
	}
	else
	{
		m_lastPtr->next = newNode;
		m_lastPtr = m_lastPtr->next;
	}

	return kNOERROR;
}

template <class Node> int List<Node>::GetCurrentData(Node &node)
{
	if(IsEmpty() || IsEndOfCurrent())
	{
		return kERRPOINTERISNULL;
	}

	node = m_currentPtr->m_data;

	return kNOERROR; 
}

template <class Node> int List<Node>::MoveNext()
{
	if(IsEmpty() || IsEndOfCurrent())
	{
		return kERRPOINTERISNULL;
	}

	if(m_currentPtr == m_lastPtr)
	{
		m_currentPtr = NULL;
	}
	else
	{
		m_currentPtr = m_currentPtr->next;
	}

	return kNOERROR;
}

template <class Node> int List<Node>::UpdateCurrentData(const Node &node)
{
	if(IsEmpty() || IsEndOfCurrent())
	{
		return kERRPOINTERISNULL;
	}
		
	m_currentPtr->m_data = node;

	return kNOERROR;
}

template <class Node> unsigned long List<Node>::GetCount()
{
	ListNode<Node> *tempPtr = m_firstPtr;
	unsigned long count = 0;

	if(IsEmpty())
	{
		return 0;
	}

	while(tempPtr != m_lastPtr->next)
	{
		tempPtr = tempPtr->next;
		count++;
	}

	return count;
}

template <class Node> int List<Node>::CreateNewNode(const Node &node, ListNode<Node>**new_node)
{
	ListNode<Node> *newNode = new ListNode<Node>(node);
	if(!newNode)
	{
		return kERROUTOFMEMORY;
	}
	
	*new_node = newNode;
		
	return kNOERROR;
}

#endif //LIST_H
// $History: List.h $
//
// *****************  Version 1.0  *****************
// User: liuxu       Date: 11/03/31   Time: 08:12
