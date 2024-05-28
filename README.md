# Expression Tree
Creates a tree from a postfix expression. This was created for an assignment in a data structures course.

## main.cpp
Used to run tests for the tree class and ensure all methods work. This was written entirely by [Carlos Arias Arevalo](https://github.com/arias-spu).

## Example Output:
For an input postfix expression of `7 5 + 5 2 - /`, which in standard notation is: `(7 + 5) / (5 - 2)`. The ouput is as follows.
```
--------------------------------------------------
Input Expression: 7 5 + 5 2 - /
	Traversals
		Your INORDER:        7 + 5 / 5 - 2
		Expected INORDER:    7 + 5 / 5 - 2
		Your PREORDER:       / + 7 5 - 5 2
		Expected PREORDER:   / + 7 5 - 5 2
		Your POSTORDER:      7 5 + 5 2 - /
		Expected POSTORDER:  7 5 + 5 2 - /

	Evaluation
		Your Evaluation:     4.00
		Expected Evaluation: 4.00

	Evaluation Steps
		Your Step:     {"value":4.00, "operator":"/", "operand":false, "id":0, "parent":-1}
		Expected Step: {"value":4.00, "operator":"/", "operand":false, "id":0, "parent":-1}
		Your Step:     {"value":12.00, "operator":"+", "operand":false, "id":1, "parent":0}
		Expected Step: {"value":12.00, "operator":"+", "operand":false, "id":1, "parent":0}
		Your Step:     {"value":7.00, "operator":"#", "operand":true, "id":2, "parent":1}
		Expected Step: {"value":7.00, "operator":"#", "operand":true, "id":2, "parent":1}
		Your Step:     {"value":5.00, "operator":"#", "operand":true, "id":3, "parent":1}
		Expected Step: {"value":5.00, "operator":"#", "operand":true, "id":3, "parent":1}
		Your Step:     {"value":3.00, "operator":"-", "operand":false, "id":4, "parent":0}
		Expected Step: {"value":3.00, "operator":"-", "operand":false, "id":4, "parent":0}
		Your Step:     {"value":5.00, "operator":"#", "operand":true, "id":5, "parent":4}
		Expected Step: {"value":5.00, "operator":"#", "operand":true, "id":5, "parent":4}
		Your Step:     {"value":2.00, "operator":"#", "operand":true, "id":6, "parent":4}
		Expected Step: {"value":2.00, "operator":"#", "operand":true, "id":6, "parent":4}
	Steps passed: 7.00 Total steps: 7
------------------------------------------------------------

--------------------------------------------------
{"value":4.00, "operator":"/", "operand":false, "id":0, "parent":-1}
{"value":12.00, "operator":"+", "operand":false, "id":1, "parent":0}
{"value":7.00, "operator":"#", "operand":true, "id":2, "parent":1}
{"value":5.00, "operator":"#", "operand":true, "id":3, "parent":1}
{"value":3.00, "operator":"-", "operand":false, "id":4, "parent":0}
{"value":5.00, "operator":"#", "operand":true, "id":5, "parent":4}
{"value":2.00, "operator":"#", "operand":true, "id":6, "parent":4}

==================================================

          (/)
        /      \
    (+)         (-)
   /   \       /   \
 (7)   (5)   (5)   (2)
```
