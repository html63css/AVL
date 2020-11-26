#include "AVL.h"

AVL::AVL(const int& value) :
	count(1)
{
	root = static_cast<shared_ptr<AVL_Element>> (new AVL_Element(value));
}
shared_ptr<AVL_Element> AVL::getRoot() const
{
	return root;
}
int AVL::getCount() const
{
	return count;
}

shared_ptr<AVL_Element> AVL::search(const int& value) const
{
	shared_ptr<AVL_Element> element_search = root;
	while (element_search != 0 && element_search->getDate() != value)
	{
		if (value < element_search->getDate())
		{
			element_search = element_search->getLeft();
		}
		else
		{
			element_search = element_search->getRight();
		}
	}
	return element_search;
}
shared_ptr<AVL_Element> AVL::search_inexact(const int& value) const
{
	shared_ptr<AVL_Element> buff_element_search = 0;
	shared_ptr<AVL_Element> element_search = root;
	while (element_search != 0 && element_search->getDate() != value)
	{
		buff_element_search = element_search;
		if (value < element_search->getDate())
		{
			element_search = element_search->getLeft();
		}
		else
		{
			element_search = element_search->getRight();
		}
	}
	if (element_search != 0)
	{
		buff_element_search = element_search;
	}
	return buff_element_search;
}
shared_ptr<AVL_Element> AVL::search_successor(const shared_ptr<AVL_Element>& element) const
{
	shared_ptr<AVL_Element> element_search = element;
	if (element_search->getRight() != 0)
	{
		element_search = element_search->getRight();
		while (element_search->getLeft() != 0)
			element_search = element_search->getLeft();
		return element_search;
	}
	else
	{
		shared_ptr<AVL_Element> y = element->getParent();
		element_search = element;
		while (y != 0 && element_search == y->getRight())
		{
			element_search = y;
			y = y->getParent();
		}
		return y;
	}
}
shared_ptr<AVL_Element> AVL::tree_min() const
{
	shared_ptr<AVL_Element> element_search = root;
	while (element_search->getLeft() != 0)
	{
		element_search = element_search->getLeft();
	}
	return element_search;
}
shared_ptr<AVL_Element> AVL::tree_max() const
{
	shared_ptr<AVL_Element> element_search = root;
	while (element_search->getRight() != 0)
	{
		element_search = element_search->getRight();
	}
	return element_search;
}
int AVL::update_balance(shared_ptr<AVL_Element> A)
{
	if (A->getLeft() == 0 && A->getRight() == 0)
	{
		A->setBalance(0);
		return 0;
	}
	else
	{
		int left, right;
		left = A->getLeft() != 0 ? update_balance(A->getLeft()) + 1 : 0;
		right = A->getRight() != 0 ? update_balance(A->getRight()) + 1 : 0;
		A->setBalance(right - left);
		if (left >= right)
			return left;
		else
			return right;
	}
	
}

void AVL::insert(const int& value)
{
	shared_ptr<AVL_Element> element_parent = search_inexact(value);
	shared_ptr<AVL_Element> new_element;
	if (element_parent->getDate() != value)
	{
		new_element = static_cast<shared_ptr<AVL_Element>>(new AVL_Element(value));
		new_element->setParent(element_parent);
		if (value < element_parent->getDate())
		{
			element_parent->setLeft(new_element);
		}
		else if (value > element_parent->getDate())
		{
			element_parent->setRight(new_element);
		}
		++count;
	}
	update_balance(root);

	shared_ptr<AVL_Element> current = new_element;
	while (current != 0)
	{
		restore_balance(current);
		current = current->getParent();
	}
}
void AVL::tree_delete(const int& value)
{
	shared_ptr<AVL_Element> element_delete = search(value);
	if (getCount() < 3)
	{
		if (element_delete == root)
		{
			if (element_delete->getLeft() != 0)
			{
				root = element_delete->getLeft();
				element_delete->getLeft()->setParent(0);
			}
			else
			{
				root = element_delete->getRight();
				element_delete->getRight()->setParent(0);
			}
		}
		else
		{
			element_delete->setParent(0);
			root->setLeft(0);
			root->setRight(0);
		}
		--count;
	}
	else
	{

		shared_ptr<AVL_Element> current;
		if (element_delete != 0 && element_delete->getDate() == value)
		{
			current = element_delete->getParent();
			--count;
			if (element_delete->getLeft() == 0 && element_delete->getRight() == 0)
			{
				if (element_delete->getParent()->getLeft() == element_delete)
				{
					element_delete->getParent()->setLeft(0);
				}
				else if (element_delete->getParent()->getRight() == element_delete)
				{
					element_delete->getParent()->setRight(0);
				}
			}
			else if (element_delete->getLeft() == 0)
			{
				if (element_delete->getParent()->getLeft() == element_delete)
				{
					element_delete->getParent()->setLeft(element_delete->getRight());
				}
				else if (element_delete->getParent()->getRight() == element_delete)
				{
					element_delete->getParent()->setRight(element_delete->getRight());
				}
				element_delete->getRight()->setParent(element_delete->getParent());
			}
			else if (element_delete->getRight() == 0)
			{
				if (element_delete->getParent()->getLeft() == element_delete)
				{
					element_delete->getParent()->setLeft(element_delete->getLeft());
				}
				else if (element_delete->getParent()->getRight() == element_delete)
				{
					element_delete->getParent()->setRight(element_delete->getLeft());
				}
				element_delete->getLeft()->setParent(element_delete->getParent());
			}
			else
			{
				shared_ptr<AVL_Element> successor = element_delete;
				element_delete = search_successor(element_delete);
				int buff = element_delete->getDate();
				tree_delete(element_delete->getDate());
				++count;
				successor->setDate(buff);
			}
			update_balance(root);
			while (current != 0)
			{
				restore_balance(current);
				current = current->getParent();
			}
		}
	}
}
void AVL::right_rotate(shared_ptr<AVL_Element> B, shared_ptr<AVL_Element> A) //Поворачиваем В относительно А
{
	B->setLeft(A->getRight());
	if (A->getRight() != 0) A->getRight()->setParent(B);
	A->setParent(B->getParent());
	if (B->getParent() == 0)
	{
		root = A;
	}
	else if (B->getParent()->getLeft() == B)
	{
		B->getParent()->setLeft(A);
	}
	else
	{
		B->getParent()->setRight(A);
	}
	A->setRight(B);
	B->setParent(A);
	update_balance(root);
}
void AVL::left_rotate(shared_ptr<AVL_Element> B, shared_ptr<AVL_Element> A) //Поворачиваем В относительно А
{
	B->setRight(A->getLeft());
	if (A->getLeft() != 0) A->getLeft()->setParent(B);
	A->setParent(B->getParent());
	if (B->getParent() == 0)
	{
		root = A;
	}
	else if (B->getParent()->getLeft() == B)
	{
		B->getParent()->setLeft(A);
	}
	else
	{
		B->getParent()->setRight(A);
	}
	A->setLeft(B);
	B->setParent(A);
	update_balance(root);
}
int AVL::height(const shared_ptr<AVL_Element> x) const
{
	int height = 0;
	for (shared_ptr<AVL_Element> y = root; y != x; ++height)
	{
		if (x->getDate() < y->getDate())
		{
			y = y->getLeft();
		}
		else
		{
			y = y->getRight();
		}
	}
	return height;
}
void AVL::restore_balance(shared_ptr<AVL_Element> x)
{
	if (x->getBalance() < -1)
	{
		int xLL = x->getLeft()->getLeft() == 0 ? 0 : height(x->getLeft()->getLeft());
		int xLR = x->getLeft()->getRight() == 0 ? 0 : height(x->getLeft()->getRight());
		if (xLL > xLR)
		{
			right_rotate(x, x->getLeft());
		}
		else
		{
			left_rotate(x->getLeft(),x->getLeft()->getRight());
			right_rotate(x, x->getLeft());
		}
	}
	else if (x->getBalance() > 1)
	{
		int xRR = x->getRight()->getRight() == 0 ? 0 : height(x->getRight()->getRight());
		int xRL = x->getRight()->getLeft() == 0 ? 0 : height(x->getRight()->getLeft());
		if (xRR > xRL)
		{
			left_rotate(x, x->getRight());
		}
		else
		{
			right_rotate(x->getRight(), x->getRight()->getLeft());
			left_rotate(x, x->getRight());
		}
	}
}