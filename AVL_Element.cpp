#include "AVL_Element.h"

AVL_Element::AVL_Element(const int& value) :
	date(value),
	balance(0),
	left(0),
	right(0),
	parent(0)
{};

int AVL_Element::getDate()
{
	return date;
}
int AVL_Element::getBalance()
{
	return balance;
}
shared_ptr<AVL_Element> AVL_Element::getLeft() const
{
	return left;
}
shared_ptr<AVL_Element> AVL_Element::getRight() const
{
	return right;
}
shared_ptr<AVL_Element> AVL_Element::getParent() const
{
	return parent;
}

void AVL_Element::setDate(int value)
{
	date = value;
}
void AVL_Element::setBalance(int value)
{
	balance = value;
}
void AVL_Element::setLeft(shared_ptr<AVL_Element> value)
{
	left = value;
}
void AVL_Element::setRight(shared_ptr<AVL_Element> value)
{
	right = value;
}
void AVL_Element::setParent(shared_ptr<AVL_Element> value)
{
	parent = value;
}