/**
 * Title: TreeNode
 * Author: Toby Smedes
 * Date: May 24, 2024
 * Purpose: Defines TreeNode class
 */

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>
using std::string;

class TreeNode {
private:
	string _data;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode* _parent;
public:
	TreeNode();
	TreeNode(TreeNode& rhs);
	TreeNode(string data, TreeNode* left, TreeNode* right);
	~TreeNode();
    TreeNode& operator=(const TreeNode& rhs);
	void SetData(string& data);
	string GetData()const;
	TreeNode* GetLeft()const;
	TreeNode* GetRight()const;
};


#endif //TREE_NODE_H
