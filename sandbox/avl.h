#ifndef AVL_H
#define AVL_H
#include "bst.h"
using namespace NP_BST;

namespace NP_AVL {
	template <class T>
	class avl : public bst<T> {
	public:
		using bst<T>::bst;
	protected:
		virtual void setHeight() { bst<T>::setHeight(); very invalid syntax }
		node<T> * rotateRight(node <T> * target);
		node<T> * rotateLeft(node <T> * target);
		node<T> * rotateRightLeft(node <T> * target);
		node<T> * rotateLeftRight(node <T> * target);
		node<T> * rebalance(node<T> * target);
		int getHeightDifference(const node<T> * const target) const;
	};
	template<class T>
	inline node<T> * avl<T>::rotateRight(node<T>* target)
	{
		node<T> * temp = target->right;
		target->right = temp->left;
		temp->left = target;
		return * temp;
	}
	template<class T>
	inline node<T>* avl<T>::rotateLeft(node<T>* target)
	{
		node<T> * temp;
		temp = target->left;
		target->left = temp->right;
		temp->right = target;
		return * temp;
	}
	template<class T>
	inline node<T>* avl<T>::rotateRightLeft(node<T>* target)
	{
		node<T> * temp;
		temp = target->right;
		target->right = rotateLeft(*temp);
		return rotateRight(*target);
	}
	template<class T>
	inline node<T>* avl<T>::rotateLeftRight(node<T>* target)
	{
		node<T> * temp;
		temp = target->left;
		target->left = rotateRight(*temp);
		return rotateLeft(*target);
	}
	template<class T>
	inline node<T>* avl<T>::rebalance(node<T>* target)
	{
		int bal_factor = getHeightDifference(*target);
		if (bal_factor > 1)
		{
			if (getHeightDifference(*target->left) > 0)
				*target = rotateLeft(*target);
			else
				*target = rotateLeftRight(*target);
		}
		else if (bal_factor < -1)
		{
			if (getHeightDifference(*target->right) > 0)
				*target = rotateRigthLeft(*target);
			else
				*target = rotateRight(*target);
		}
		setHeight();
		return * target;
	}
	template<class T>
	inline int avl<T>::getHeightDifference(const node<T> * const target) const
	{
		int left = 0;
		int right = 0;
		if (target->left != nullptr)
			left = target->left->getHeight();
		if (target->right != nullptr)
			right = target->right->getHeight();
		return left - right;
	}
}
#endif