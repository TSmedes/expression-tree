/**
 * Title: Tree
 * Author: Toby Smedes
 * Date: May 24, 2024
 * Purpose: Implements methods in Tree class
 */

#include "tree.h"

#include <stack>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
#include <sstream>

using std::stringstream;
using std::stack;
using std::pow;
using std::vector;
using std::queue;
using std::setprecision;
using std::fixed;

/**
 * Default constructor, initializes values
 */
Tree::Tree() {
	_root = nullptr;
}
/**
 * Copy constructor
 * @param other Tree to copy
 */
Tree::Tree(const Tree& other) {
	if(this == &other) {
		return;
	}
	_root = other._root;
}
/**
 * Copy assignment operator
 * @param rhs Tree to assign
 * @return this tree
 */
const Tree& Tree::operator=(const Tree& rhs) {
	if(this == &rhs) {
		return *this;
	}
	_root = rhs._root;
	return *this;
}
/**
 * Destructor
 */
Tree::~Tree() {
	delete _root;
}
/**
 * Finds and returns the next symbol in a string, and
 * removes it from the string
 * @param expression string to search from
 * @return symbol found, empty string if none left
 */
string Tree::GetNext(string& expression)const {
	size_t nextSpace = expression.find_first_of(' ');
    //Case where only one symbol is left
    if(nextSpace == string::npos) {
        string retString = expression;
        expression = "";
        return retString;
    }
    //Empty string
    if(expression.empty()) {
        return expression;
    }
	string retString = expression.substr(0, nextSpace);
	expression = expression.substr(nextSpace + 1, expression.length() - nextSpace);
	return retString;
}
/**
 * Checks if the string given is a common arithmetic operator
 * @param data string to check
 * @return true if is operator, false otherwise
 */
bool Tree::IsOperator(string data)const {
	return(!isdigit(data.at(0)));
}
/**
 * Builds binary expression tree from postfix expression
 * @param postfixExpression string to build tree from
 * @return success state
 */
bool Tree::BuildTree(const string& postfixExpression) {
    //Not enough operands/operators to make a valid expression
	if (postfixExpression.length() < 3) 
		return false;
	stack<TreeNode*> treeStack;
    string expressionCpy = postfixExpression;
	string nextData = GetNext(expressionCpy);
    //Loop while there are still operands/operators left
	while(!nextData.empty()) {
		if(IsOperator(nextData)) {
			TreeNode* secondOperand = treeStack.top();
			treeStack.pop();
			TreeNode* firstOperand = treeStack.top();
			treeStack.pop();
			TreeNode* newRoot = new TreeNode(nextData, firstOperand, secondOperand);
			treeStack.push(newRoot);
		}
		else {
            TreeNode* newTree = new TreeNode();
            newTree->SetData(nextData);
			treeStack.push(newTree);
		}
        nextData = GetNext(expressionCpy);
	}
	if(nextData.size() > 1) 
		return false;
	_root = treeStack.top();
	return true;
}
/**
 * Wraps different traversal types
 * @param traversalType method for traversing tree
 * @return string representation of traversal order
 */
string Tree::Traverse(TraversalType traversalType)const {
	TreeNode* curr = _root;
	if(traversalType == INORDER) {
		return InOrderTraversal(curr);
	}
	if(traversalType == POSTORDER) {
		return PostOrderTraversal(curr);
	}
    return PreOrderTraversal(curr);
}
/**
 * Recursively traverses tree using inorder sequence and returns string
 * @param curr root node to traverse from
 * @return traversal output
 */
string Tree::InOrderTraversal(TreeNode* curr)const {
	if(curr->GetLeft() == nullptr)
		return curr->GetData();
	return InOrderTraversal(curr->GetLeft()) +  " " + curr->GetData() + " " + InOrderTraversal(curr->GetRight());
}
/**
 * Recursively traverses tree using preorder sequence and returns string
 * @param curr root node to traverse from
 * @return traversal output
 */
string Tree::PreOrderTraversal(TreeNode* curr)const {
	if(curr->GetLeft() == nullptr)
		return curr->GetData();
	return curr->GetData() + " " + PreOrderTraversal(curr->GetLeft()) + " " + PreOrderTraversal(curr->GetRight());
}
/**
 * Recursively traverses tree using postorder sequence and returns string
 * @param curr root node to traverse from
 * @return traversal output
 */
string Tree::PostOrderTraversal(TreeNode* curr)const {
    if(curr->GetLeft() == nullptr)
        return curr->GetData();
    return PostOrderTraversal(curr->GetLeft()) + " " + PostOrderTraversal(curr->GetRight()) + " " + curr->GetData();
}
/**
 * Wrapper method to RecursiveEval
 * @return evaluation
 */
double Tree::Evaluate()const {
    return RecursiveEval(_root);
}
/**
 * Recursively evaluates the whole tree, given the starting node
 * @param curr starting node
 * @return evaluation
 */
double Tree::RecursiveEval(TreeNode* curr) const {
    //Base case if is an operand
    if(curr->GetLeft() == nullptr) {
        return stod(curr->GetData());
    }
    double left = RecursiveEval(curr->GetLeft());
    double right = RecursiveEval(curr->GetRight());
    return Operation(left, right, curr->GetData());
}
/**
 * Performs operation with two operands and a string operator
 * @param left operand
 * @param right operand
 * @param sym operator
 * @return result
 */
double Tree::Operation(double left, double right, string sym)const {
    if(!IsOperator(sym))
        return 0.0;
    char s = sym.at(0);
    if(s == '+')
        return left + right;
    if(s == '-')
        return left - right;
    if(s == '*')
        return left * right;
    if(s == '/')
        return left / right;
    if(s  == '^')
        return pow(left, right);
    else
        return 0.0;
}
/**
 * Performs evaluation step by step. If UseLevel is true,
 * a visual representation of the tree will be printed.
 * The conditional can be removed to instead indent the output
 * when useLevel is true
 * @param output stream to output to
 * @param useLevel determine how to output
 */
void Tree::StepByStepEvaluation(ostream& output, bool useLevel)const {
    if(_root == nullptr)
        return;
    if(!useLevel) {
        int root = 0;
        RecursiveOutput(output, _root, root, -1, useLevel, 0);
    }
    else {
        LeveledOutput(output, _root);
    }
}
/**
 * Recursively evaluates expression and outputs each step. Optionally,
 * the output will be indented
 * @param output ostream to output to
 * @param curr treenode to start from
 * @param id id of current node
 * @param parent id of parent node
 * @param useLevel bool determines if output is indented
 * @param currLevel current indenting level
 */
void Tree::RecursiveOutput(ostream& output, TreeNode* curr, int& id, int parent, bool useLevel, size_t currLevel)const {
    //Base case
    if(curr == nullptr) {
        return;
    }
    double value = RecursiveEval(curr);
    string operand;
    char op = curr->GetData().at(0);
    //If operand
    if(!IsOperator(curr->GetData())) {
        operand = "true";
        op = '#';
    }
    else
        operand = "false";
    if(useLevel) {
        //Adds indenting
        for(size_t i = 0; i < currLevel; ++i) {
            output << "        ";
        }
        output << "{\"value\":" << std::fixed << std::setprecision(2) << value << ", \"operator\":\"" << op << "\", \"operand\":" << operand
              << "}" << std::endl;
    }
    else{
        output << "{\"value\":" << std::fixed << std::setprecision(2) << value << ", \"operator\":\"" << op << "\", \"operand\":" << operand
               << ", \"id\":" << id << ", \"parent\":" << parent << "}" << std::endl;
    }

    parent = id;
    id++;
    RecursiveOutput(output, curr->GetLeft(), id, parent, useLevel, currLevel + 1);
    RecursiveOutput(output, curr->GetRight(), id, parent, useLevel, currLevel + 1);
}
/**
 * Sets up parameters for AddLevels which actually
 * adds the data and "branches" and outputs to the ostream
 * @param output ostream of where to print
 * @param curr root node to begin at
 */
void Tree::LeveledOutput(ostream& output, TreeNode* curr)const {
    size_t height = GetHeight(curr);
    int width = static_cast<int>(6 * pow(2, height - 1)) - 1;
    vector<string> levels(2 * height - 1, string(width, ' '));
    AddLevels(curr, levels, 0, width, 0);
    for (const string& level : levels) {
        output << level << std::endl;
    }

}
/**
 * Adds the proper nodes to each level string
 * created in LeveledOutput by recursively going through nodes
 * @param curr current node
 * @param levels vector of level strings
 * @param left lower bound
 * @param right upper bound
 * @param row current row
 */
void Tree::AddLevels(TreeNode* curr, vector<string>& levels, int left, int right, int row)const{
    //Base case
    if(curr == nullptr || left > right)
        return;
    size_t mid = (left + right) / 2;
    stringstream ss;
    //Creating visual node enclosed in ()
    if(IsOperator(curr->GetData())) {
        ss << "(" << setprecision(1) << curr->GetData() << ")";
    }
    else {
        ss << "(" << setprecision(3) << stod(curr->GetData()) << ")";
    }
    size_t dataLen = ss.str().length();
    size_t pos = mid - dataLen / 2;

    levels.at(row).replace(pos, dataLen, ss.str());
    if(curr->GetLeft() != nullptr) {
        //Adding "branch"
        size_t nextMid = (left + mid) / 2;
        nextMid = (mid + nextMid) / 2;
        levels.at(row + 1).replace(nextMid, 1, "/");
        //Recursive call
        AddLevels(curr->GetLeft(), levels, left, mid, row + 2);
    }
    if(curr->GetRight() != nullptr) {
        //Adding "branch"
        size_t nextMid = (right + mid) / 2;
        nextMid = (mid + nextMid) / 2;
        levels.at(row + 1).replace(nextMid + 1, 1, "\\");
        //Recursive call
        AddLevels(curr->GetRight(), levels, mid, right, row + 2);
    }
}
/**
 * Finds height of the tree by recursively searching for leaves
 * @param root the root node to start search at
 * @return height of the tree
 */
size_t Tree::GetHeight(TreeNode* root)const{
    if(root == nullptr)
        return 0;
    size_t leftHeight = GetHeight(root->GetLeft());
    size_t rightHeight = GetHeight(root->GetRight());
    if(leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}