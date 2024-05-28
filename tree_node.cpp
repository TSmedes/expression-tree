/**
 * Title: TreeNode
 * Author: Toby Smedes
 * Date: May 24, 2024
 * Purpose: Implements methods from TreeNode class
 */

#include "tree_node.h"

/**
 * Default constructor, initializes values
 */
TreeNode::TreeNode() {
	_data = "";
	_left = nullptr;
	_right = nullptr;
	_parent = nullptr;
}
/**
 * Copy constructor
 * @param rhs TreeNode to copy
 */
TreeNode::TreeNode(TreeNode& rhs) {
	if(this == &rhs) {
		return;
	}
	_data = rhs._data;
	_left = rhs._left;
	_right = rhs._right;
	_parent = rhs._parent;
}
/**
 * Constructor with node's data, and left and right nodes
 * @param data data
 * @param left left child node
 * @param right right child node
 */
TreeNode::TreeNode(string data, TreeNode* left, TreeNode* right) {
	_data = data;
	_left = left;
	_right = right;
	_left->_parent = this;
	_right->_parent = this;
}
/**
 * Destructor
 */
TreeNode::~TreeNode() {
	delete _left;
	delete _right;
}
/**
 * Copy assignment operator
 * @param rhs TreeNode to copy
 * @return this TreeNode
 */
TreeNode& TreeNode::operator=(const TreeNode& rhs) {
	if(this == &rhs) {
		return *this;
	}
	_left = rhs._left;
	_right = rhs._right;
	_parent = rhs._parent;
	_data = rhs._data;
	return *this;
}
/**
 * Sets node's data
 * @param data
 */
void TreeNode::SetData(string& data) {
	_data = data;	
}
/**
 * Returns data attribute
 * @return data
 */
string TreeNode::GetData()const {
	return _data;
}
/**
 * Returns left child node
 * @return left child
 */
TreeNode* TreeNode::GetLeft()const {
	return _left;
}
/**
 * Returns right child node
 * @return right child
 */
TreeNode* TreeNode::GetRight()const {
	return _right;
}