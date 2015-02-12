#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <assert.h>
using namespace std;

template <class Etype>

class TreeNode
{
public:
	Etype element;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	TreeNode(Etype e = 0, TreeNode *l = NULL, TreeNode *r = NULL, TreeNode *p = NULL) :
		element(e), left(l), right(r), parent(p) { }
};

template <class Etype>
class BinarySearchTree
{
protected:
	TreeNode<Etype> *root;
	bool insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype>*  p);
	string toString(TreeNode<Etype> * t, string indent) const;
	string traverse(TreeNode<Etype> * t) const;
	TreeNode<Etype> * minimumEle(TreeNode<Etype> * & t);
	TreeNode<Etype> * maximumEle(TreeNode<Etype> * & t);
	TreeNode<Etype> * predecessor(TreeNode<Etype> * & t);
	int nodesInLevel(TreeNode<Etype> * & t, int level, int currentLevel);
	TreeNode<Etype> * findKthInOrder(TreeNode<Etype> * t, int k);
	int count(TreeNode<Etype> *t);
	int width(TreeNode<Etype> * t, int &height);
	bool isIsomorphic(TreeNode<Etype> *t1, TreeNode<Etype> *t2);
	bool isQuasiIsomorphic(TreeNode<Etype> *t1, TreeNode<Etype> *t2);
	TreeNode<Etype> * find(TreeNode<Etype> * curr, Etype value);
	void makeEmpty(TreeNode<Etype> *&t);
	int countFringe(TreeNode<Etype> *t) const;
	TreeNode<Etype>* leastCommonAncestor(TreeNode <Etype>* r, Etype a, Etype b);
public:
	TreeNode<Etype>* leastCommonAncestor(Etype a, Etype b) {  // order the elements so we know which is smaller
		if (a < b) return leastCommonAncestor(root, a, b);
		return leastCommonAncestor(root, b, a);
	}
	void makeTree(vector<Etype> all);
	Etype predecessor(Etype value)
	{
		TreeNode<Etype> *curr = find(root, value);
		TreeNode<Etype> * p = predecessor(curr);
		if (p != NULL) return p->element;
		else return 0;
	}
	BinarySearchTree() : root(NULL) { }
	TreeNode<Etype> * minimumEle(){
		return minimumEle(root);
	}
	TreeNode<Etype> * maximumEle(){
		return maximumEle(root);
	}
	TreeNode<Etype> * successor(){
		return minimumEle();
	}
	string toString(string msg = "") const
	{
		,	return msg + "\n" + toString(root, "  ");
	}
	virtual int insert(Etype & x) { return insert(x, root, NULL); }
	string traverse(string msg) const
	{
		return msg + "\n" + traverse(root);
	}
	int nodesInLevel(int level) { return nodesInLevel(root, level, 0); }
	int findKthInOrder(int k) {
		TreeNode<Etype>* t = findKthInOrder(root, k);
		if (t == NULL) return -999;
		return t->element;
	}
	int count() { return count(root); }
	int width() { int height; return width(root, height); }
	bool isIsomorphic(BinarySearchTree<Etype> t) { return isIsomorphic(root, t.root); }
	bool isQuasiIsomorphic(BinarySearchTree<Etype> t) { return isQuasiIsomorphic(root, t.root); }
	TreeNode<Etype> * clone(TreeNode<Etype> *t, TreeNode<Etype> *p) const;
	void makeEmpty() { makeEmpty(root); }
	int countFringe() { return countFringe(root); }

};

template <class Etype> //O(log fn) complexity
TreeNode<Etype>*  BinarySearchTree<Etype>::leastCommonAncestor(TreeNode < Etype>* r, Etype a, Etype b)
{
	if (r == NULL) return r;
	if (a < r->element && b < r->element)
	{
		return leastCommonAncestor(r->left, a, b);
	}
	if (a > r->element && b > r->element)
	{
		return leastCommonAncestor(r->right, a, b);
	}
	if (a <= r->element && b >= r->element || a >= r->element && b <= r->element) return r;

	return NULL;
}

template <class Etype> //O(n) complexity
bool BinarySearchTree<Etype>::isIsomorphic(TreeNode<Etype>*t1, TreeNode<Etype>*t2)
{	
	if (t1 == NULL && t2 == NULL) return true;
	if (t1 == NULL || t2 == NULL) return false;
	return isIsomorphic(t1->left, t2->left) && isIsomorphic(t1->right, t2->right);
}

template <class Etype> //O(n^2) complexity
bool BinarySearchTree<Etype>::isQuasiIsomorphic(TreeNode<Etype>*t1, TreeNode<Etype>*t2)
{

	if (t1 == NULL && t2 == NULL) return true;
	if (t1 == NULL || t2 == NULL) return false;
	bool case1 = isQuasiIsomorphic(t1->left, t2->left);
	bool case2 = isQuasiIsomorphic(t1->right, t2->right);
	bool case3 = isQuasiIsomorphic(t1->right, t2->left);
	bool case4 = isQuasiIsomorphic(t1->left, t2->right);

	return case1 && case2 || case3 && case4;
} 
template <class Etype> //O(n) complexity
int BinarySearchTree<Etype>::width(TreeNode<Etype> *t, int &height)
{
	if (t == NULL)  return 0;
	int heightLeft = 0;
	int heightRight = 0;
	int leftW = width(t->left, heightLeft);
	int rightW = width(t->right, heightRight);
	int rootW = heightLeft + heightRight + 1;
	height = max(heightLeft, heightRight) + 1;
	return max(rootW, max(leftW, rightW));
}
template <class Etype> //O(n) complexity
int BinarySearchTree<Etype>::count(TreeNode<Etype>*t)
{	
	int total = 0;
	if (t == NULL) return 0;
	if (t->left == NULL && t->right == NULL) return 1;
	if (t->left != NULL){
		total += count(t->left);
	}
	if (t->right != NULL){
		total +=count(t->right);
	}
	return total + 1;
}

// Using the iterator would be better, as this repeatedly searches the left subtree.
template <class Etype> //O(n) complexity
TreeNode<Etype> * BinarySearchTree<Etype>::findKthInOrder(TreeNode<Etype>*t, int k)
{
	static int count = 0;
	if (t == root) count = 0;
	TreeNode<Etype> *temp = NULL;
	if (t == NULL) return NULL;
	if (t->left != NULL){
		temp = findKthInOrder(t->left, k);
		if (temp != NULL) return temp;
	}
	count++;
	if (count == k) return t;
	if (t->right != NULL){
		temp = findKthInOrder(t->right, k);
		if (temp != NULL) return temp;
	}
	return NULL;
}
template <class Etype> //O(n) complexity
int BinarySearchTree<Etype>::nodesInLevel(TreeNode<Etype>*&t, int level, int currentLevel)
{	
	int total = 0;
	if (t == NULL) return 0;
	if (level == currentLevel) return 1;
	if (t->left != NULL){
		total += nodesInLevel(t->left, level, currentLevel + 1);
	}
	if (t->right != NULL){
		total += nodesInLevel(t->right, level, currentLevel + 1);
	}
	return total;
}



template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::minimumEle(TreeNode<Etype> * & t)
{
	if (t->left != NULL)
		return minimumEle(t->left);
	return t;

}
template <class Etype>
string BinarySearchTree<Etype>::traverse(TreeNode<Etype> *t) const
{
	stringstream ss;
	if (t == NULL) return "";
	ss << traverse(t->left);
	ss << t->element << " ";
	ss << traverse(t->right);
	return ss.str();
}

template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::maximumEle(TreeNode<Etype> * & t)
{
	if (t->right != NULL) return maximumEle(t->right);
	return t;
}

template <class Etype> //O(n) complexity
TreeNode<Etype> * BinarySearchTree<Etype>::predecessor(TreeNode<Etype> * & t)
{
	TreeNode<Etype> *temp;
	if (t== NULL) return NULL;
	if (t->left != NULL){
		temp = t->left;
		while(temp->right != NULL){
				 temp = temp->right;
			}
		return temp;
		}
	else{
		if (t->parent == NULL) return NULL;
		if (t->element > t->parent->element){
			return t->parent;
		}
		else{
			return t->parent->parent;
		}
	}
}

template <class Etype> //O(n) complexity
string BinarySearchTree<Etype>::toString(TreeNode<Etype> *t, string indent) const
{
	stringstream ss;
	if (t == NULL) return "";
	if (t != NULL){
		indent += "  ";
		if (t->right != NULL)
		ss << toString(t->right, indent);
		if (t->parent == NULL){
			ss << indent << t->element << "< no parent >" << endl;
		}
		else{
			ss << indent << t->element << "<" << t->parent->element << ">" << endl;
		}
		ss << toString(t->left, indent);
		return ss.str();	
	}
}

// Return true if insertion is successful
template <class Etype>
bool BinarySearchTree<Etype>::insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype> *  p)
{
	if (t == NULL)
	{  // cout << "inserting " << x << endl;
		t = new TreeNode<Etype>(x, NULL, NULL, p);
		if (t == NULL) return false;
		return true;
	}
	if (x < t->element) return insert(x, t->left, t);
	if (x > t->element) return insert(x, t->right, t);
	// cout << "Warning, duplicate ignored " << x << endl;

	return false;  // does not allow duplicate insertions
}
template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::find(TreeNode<Etype> * curr, Etype value)
{
	if (curr == NULL) return NULL;
	if (curr->element == value)
		return curr;
	if (value < curr->element) return find(curr->left, value);
	return find(curr->right, value);
}

template <class Etype>
void BinarySearchTree<Etype>::makeTree(vector<Etype> all)
{
	makeEmpty(root);
	for (unsigned i = 0; i < all.size(); i++)
		insert(all[i]);
}


template <class Etype> //O(n) complexity
void BinarySearchTree<Etype>::makeEmpty(TreeNode<Etype> *&t)
{
	if (t == NULL) return;
	if (t != NULL){
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = NULL;
	}
}


template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::clone(TreeNode<Etype> *t, TreeNode<Etype> *parent) const
{
	if (t == NULL)
		return NULL;
	TreeNode<Eype>* newNode = new TreeNode < Etype >{ t->element, NULL, NULL, parent };
	newNode->left = clone(t->left, newNode);
	newNode->right = clone(t->right, newNode);
	return newNode;
}

template <class Etype> //O(n) complexity
int BinarySearchTree<Etype>::countFringe(TreeNode<Etype> *t) const
{
	int total = 0;
	if (t == NULL) return 0;
	if (t->left == NULL && t->right == NULL){
		return 1;
	}
	total += countFringe(t->left);
	total += countFringe(t->right);
	return total;
}
