#pragma once
#include "stdfx.h"

template <typename T>
struct ListNode
{
	T data;
	shared_ptr<ListNode<T>> next;
};

//////////////////////////////////////////////////////////////////////////////////////
//								Merge two sorted lists								//
//////////////////////////////////////////////////////////////////////////////////////
void AppendNode(shared_ptr<ListNode<int>>* node, shared_ptr<ListNode<int>>* tail)
{
	(*tail)->next = *node;
	*tail = *node;
	*node = (*node)->next;
}

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2)
{
	shared_ptr<ListNode<int>> dummy_head(new ListNode<int>);
	auto tail = dummy_head;

	while (L1 && L2)
	{
		AppendNode(L1->data <= L2->data ? &L1 : &L2, &tail);
	}

	tail->next = L1 ? L1 : L2;
	return dummy_head->next;
}

//////////////////////////////////////////////////////////////////////////////////////
//							Reverse a singly linked list							//
//////////////////////////////////////////////////////////////////////////////////////
shared_ptr<ListNode<int>> ReverseLinkedList(const shared_ptr<ListNode<int>>& head)
{
	if (!head || !head->next)
		return head;

	auto new_head = ReverseLinkedList(head->next);
	head->next->next = head;
	head->next = nullptr;
	return new_head;
}

shared_ptr<ListNode<int>> ReverseLinkedList2(const shared_ptr<ListNode<int>>& head)
{
	shared_ptr<ListNode<int>> prev = nullptr, curr = head;
	while (curr)
	{
		auto next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}

//////////////////////////////////////////////////////////////////////////////////////
//								Reverse a single sub list							//
//////////////////////////////////////////////////////////////////////////////////////
shared_ptr<ListNode<int>> ReverseSubList(shared_ptr<ListNode<int>> L, int start, int finish)
{
	if (start == finish)
		return L;

	auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
	auto sublist_head = dummy_head;
	int k = 1;
	while (k++ < start)
		sublist_head = sublist_head->next;
	
	auto sublist_iter = sublist_head->next;
	while (++start < finish)
	{
		auto temp = sublist_iter->next;
		sublist_iter->next = temp->next;
		temp->next = sublist_head->next;
		sublist_head->next = temp;
	}
	return dummy_head->next;
}