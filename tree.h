/**
 * Title: Tree
 * Author: Toby Smedes
 * Date: May 24, 2024
 * Purpose: Define Tree class
 */

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;


#include "tree_node.h"


enum TraversalType {INORDER, PREORDER, POSTORDER};


class Tree {
private:
    TreeNode* _root;
    Tree(const Tree& other);
    const Tree& operator=(const Tree& rhs);
	string GetNext(string& expression)const;
	bool IsOperator(string data)const;
	string InOrderTraversal(TreeNode* curr)const;
    string PreOrderTraversal(TreeNode* curr)const;
    string PostOrderTraversal(TreeNode* curr)const;
    double RecursiveEval(TreeNode* curr)const;
    double Operation(double left, double right, string sym)const;
    void RecursiveOutput(ostream& output, TreeNode* curr, int& id, int parent, bool useLevel, size_t currLevel)const;
    void LeveledOutput(ostream& output, TreeNode* curr)const;
//    vector<vector<TreeNode*>> GetLevels(TreeNode* root)const;
    void AddLevels(TreeNode* curr, vector<string>& levels, int left, int right, int row)const;
public:
    Tree();
    ~Tree();
    bool BuildTree(const string& postfixExpression);
    string Traverse(TraversalType traversalType)const;
    double Evaluate()const;
    void StepByStepEvaluation(ostream& output, bool useLevel = false)const;
    size_t GetHeight(TreeNode* root)const;

};

#endif //TREE_H
