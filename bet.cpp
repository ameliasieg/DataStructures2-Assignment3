#include "bet.h"
#include <iostream>
using namespace std; 

BET::BET() // Default constructor
{
    root = new BinaryNode;
}

BET::BET(const string& postfix) // GIVEN IN CLASS
{
    root = new BinaryNode;
    if(buildFromPostfix(postfix) == true)
    {
        cout << "Successfully built the tree given" << endl;
        buildFromPostfix(postfix);
        //cout << "Successfully built the tree given" << endl;
    }
    // else
    // {
    //     cout << "Errors encountered" << endl;
    // }
}

BET::BET(const BET& copy) // Copy constructor
{
    root = clone(copy.root);
    // myStack.push(root);
}

BET::~BET() // Destructor
{ 
	makeEmpty(root);
}

    
bool BET::buildFromPostfix(const string& postfix)
{
    if(!empty())
    {
        makeEmpty(root);
        root = new BinaryNode();
    }

    // Tokenizing - turning string of elements into tokens
    string token = ""; // Setting an empty string
    vector<string> tokenVector;
    
    for(int i = 0; i < postfix.length(); i++)
    {
        if(!isspace(postfix[i]))
        {
            token.push_back(postfix[i]);
        }
        else
        {
            tokenVector.push_back(token);
            token = "";
        }

        if(i == postfix.length() - 1) // account for the last element
        {
            tokenVector.push_back(token);
        }
    }
    
    // int operatorCount = 0;
    // int operandCount = 0;
    
    // for(int i = 0; i < tokenVector.size(); i++)
    // {
    //     if(isOperator(tokenVector[i])) operatorCount++;
    //     else operandCount++;
    // }

    // Prints elements individually
    // for(int i = 0; i < tokenVector.size(); i++)
    // {
    //     cout << tokenVector[i] << " " << endl;
    // }

    // Builidng tree
    for(int i = 0; i < tokenVector.size(); i++)
    {
        if(!isOperator(tokenVector[i]))
        {
            BinaryNode *temp = new BinaryNode(tokenVector[i], nullptr, nullptr);
            myStack.push(temp);
        }

        else // if this IS an operator
        {
            if(myStack.size() < 2)
            {
                return false;
            }

            BinaryNode* rightChild = myStack.top();
            myStack.pop();

            BinaryNode* leftChild = myStack.top();
            myStack.pop();

            BinaryNode *temp = new BinaryNode(tokenVector[i], leftChild, rightChild);
            myStack.push(temp);
        }
    }
   
    if(myStack.size() != 1)
    {
        return false;
    }

    else
    {
        root = myStack.top(); // now tree is actually saved
        myStack.pop(); // obtain - after we pop, it has to be empty
        return true;
    }


    // // Error checking
    // if(!myStack.empty())
    // {
    //     cout << "Inside false empty" << endl;
    //     return false;
    // }

    // if(operandCount == operandCount+1) return true;
    // else return false;

}

const BET & BET::operator=(const BET & opr) // Assignment operator
{
    makeEmpty(root);
	root = clone(opr.root);
	return *this;
}

void BET::printInfixExpression() const // print infix form (use private recursive function to help)
{
	printInfixExpression(root);
	cout << endl;
}

void BET::printPostfixExpression() const// print postfix form (use private recursive function to help)
{
	printPostfixExpression(root);
	cout << endl;
}

size_t BET::size() const // return the number of nodes in the tree
{
	return (size(root));
}

size_t BET::leaf_nodes() const // Return the number of leaves in the tree
{
    return leaf_nodes(root);
}

bool BET::empty() const // return true if the tree is empty, else false
{ 
	if(root == nullptr) // if its an empty tree return true
	{
        return true;
    }

	return false;
}

bool BET::isOperator(string x) const
{
    if (x == "+" || x == "-" || x == "/" || x == "*")
    {
        return true;
    }

    else
    {
        return false;
    }
}

// check precedence? YES
int BET::checkPrecedence(string string) const // checks the precedence of given string
{
	if(string == "("|| string == ")")
	{
        return (3);
    }
	
    else if(string == "*" || string == "/")
	{
        return (2);
    }
	
    else if(string == "+" || string == "-")
	{
        return (1);
    }
	
    else
	{
        return 0;
    }
}

void BET::printInfixExpression(BinaryNode *n) const
{
    bool parentheses = false;

    if (n == nullptr)
    {
        cout << "Binary Expression Tree is EMPTY!";
    }

    else
    {
        if(n->left != nullptr)
        {
            if(isOperator(n->left->element) && (checkPrecedence(n->element) > checkPrecedence(n->left->element)))
            {
                cout << "( ";
                parentheses = true;
            }
            
            printInfixExpression(n->left);
            
            if(parentheses == true)
            {
                cout << ") ";
                parentheses = false;
            }
            
            cout << n->element << " ";
            
            if(isOperator(n->right->element) && (checkPrecedence(n->element) >= checkPrecedence(n->right->element)))
            {
                cout << "( ";
                parentheses = true;
            }
            
            printInfixExpression(n->right);

            if(parentheses == true)
            {
                cout << ") ";
                parentheses = false;
            }
        }
        
        else
        {
            cout << n->element << " ";
        }
    }
}

void BET::makeEmpty(BinaryNode* &t) // deletes all nodes in subtree pointed to by t
{
	if(t != nullptr) // if it isn't empty, then empty it
    { 
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
}

BET::BinaryNode * BET::clone(BinaryNode *t) const
{
    if(t == nullptr)
    {
        return nullptr;
    }

    else
    {
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
}

void BET::printPostfixExpression(BinaryNode *n) const // print postfix expression
{
    if(n != nullptr) // prevent segfault on empty tree
    {
		printPostfixExpression(n->left); // print left nodes first
		printPostfixExpression(n->right); // print right nodes next
		cout << n->element << " "; // print the data of the node
	}

    /*else if(root->left == nullptr && root->right == nullptr)
		cout << root->element << endl;*/
}

// Return the number of nodes in the subtree pointed to by t
size_t BET::size(BinaryNode *t) const // GIVEN IN CLASS
{
    if (t == nullptr)
    {
        return 0;
    }
    
    else if(t != nullptr)
    {
        return (1 + size(t->left) + size(t->right));
    }
}

// GIVEN IN CLASS
size_t BET::leaf_nodes(BinaryNode *t) const // Return the number of leaf nodes in the subtree pointed to by t
{
    if (t != nullptr && t->left == nullptr && t->right == nullptr)
    {
        return 1;
    }

    else if (t != nullptr)
    {
        return leaf_nodes(t->left) + leaf_nodes(t->right);
    }

    return 0;
}

// void BET::printInfixExpression(BinaryNode *n)// const // print infix expression (needs to handle adding parentheses)
// {
//     // Check if its an operator first
//     /*

//     If it is an operator, 
//     If node is not null, you can print it

//     if(isOperator(n))
//     {
//         if(isOperator(n->left)) printInfixExpression(n->left);
//         else if(n->left != null)
//             cout << n->left.element << n.element;

//         if(isOperator(n->right)) printInfixExpression(n->right);
//         else if(n->right != null)
//             cout << n->right.element;

//     }
    
//     */

//     bool closeParentheses = false;

//     if(n != nullptr) // prevent segfault on empty tree
//         {
//             printPostfixExpression(n->left); // print left nodes first
            
//             if(checkPrecedence(n->element) != 0 && checkPrecedence(n->left->element) != 0)
//                 {	// test for operator. print right side first
//                     if(n->left != nullptr)
//                     {
//                         if(checkPrecedence(n->element) >= checkPrecedence(n->left->element))
//                         {
//                             if(checkPrecedence(n->element) == 2)
//                             {
//                                 cout << "( ";
//                                 closeParentheses = true;
//                             }
//                         }
//                     }
//                 }
            
//             cout << n->element << " "; // print the data of the node
//             printPostfixExpression(n->right); // print right nodes next
        
//         if(closeParentheses == true)
//                     cout << ") ";
//                 closeParentheses = false; // set closeParentheses back to false
//         }

//     /*
//     bool closeParentheses = false;
	
//     if(n != nullptr)
//     {
//         if(n->left == nullptr && n->right == nullptr) // if start node is valid, but has no children then just print it without any parentheses
//             cout << n->element << " ";
        
//         else
//         {
//             if(checkPrecedence(n->element) != 0 && checkPrecedence(n->right->element) != 0)
//             {	// test for operator. print right side first
//                 if(checkPrecedence(n->element) >= checkPrecedence(n->right->element))
//                 {
// 					if(checkPrecedence(n->element) == 2)
//                     {
// 						cout << "( ";
// 						closeParentheses = true;
// 					}
// 				}
//             }
            
//             printInfixExpression(n->right);
			
//             if(closeParentheses == true)
// 				cout << ") ";
//             closeParentheses = false; // set closeParentheses back to false
            
//             cout << n->element << " ";
//             if(checkPrecedence(n->element) != 0 && checkPrecedence(n->left->element) != 0)
//             {	// test for operator. print left side next
// 				if(checkPrecedence(n->element) >= checkPrecedence(n->left->element))
//                 {
// 				    cout << "( ";
// 					closeParentheses = true;
// 				}
//             }
            
//             printInfixExpression(n->left);
//             if(closeParentheses == true)
// 				cout << ") ";
// 			closeParentheses = false; // set closeParentheses back to false
//         }
//     } */
// }