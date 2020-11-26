#pragma once
#include <memory>
using namespace std;
class AVL_Element
{
public:
	AVL_Element(const int&);
	
	int getDate();
	int getBalance();
	shared_ptr<AVL_Element> getLeft() const;
	shared_ptr<AVL_Element> getRight() const;
	shared_ptr<AVL_Element> getParent() const;

	void setDate(int);
	void setBalance(int);
	void setLeft(shared_ptr<AVL_Element>);
	void setRight(shared_ptr<AVL_Element>);
	void setParent(shared_ptr<AVL_Element>);

private:
	int date;
	int balance;
	shared_ptr<AVL_Element> left;
	shared_ptr<AVL_Element> right;
	shared_ptr<AVL_Element> parent;

	AVL_Element& operator = (const AVL_Element&);
	AVL_Element(const AVL_Element&);
};

