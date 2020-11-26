#include "AVL_Element.h" 
class AVL
{
public:
	//������� ������
	explicit AVL(const int&);
	shared_ptr<AVL_Element> getRoot() const;
	int getCount() const;
	int getHeight() const;
	
	//������� ������
	shared_ptr<AVL_Element> search(const int&) const;
	shared_ptr<AVL_Element> search_inexact(const int&) const;
	shared_ptr<AVL_Element> search_successor(const shared_ptr<AVL_Element>&) const;
	shared_ptr<AVL_Element> tree_min() const;
	shared_ptr<AVL_Element> tree_max() const;
	
	//��������������� �������
	int update_balance(shared_ptr<AVL_Element>);
	void restore_balance(shared_ptr<AVL_Element>);
	int height(const shared_ptr<AVL_Element>) const;
	//�������� �������
	void insert(const int&);
	void tree_delete(const int&);
	void left_rotate(shared_ptr<AVL_Element>, shared_ptr<AVL_Element>);
	void right_rotate(shared_ptr<AVL_Element>, shared_ptr<AVL_Element>);
private:
	int count;
	shared_ptr<AVL_Element> root;

	AVL& operator=(const AVL&) const;
};

