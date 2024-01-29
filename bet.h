#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class BET
{
    struct BinaryNode // GIVEN IN CLASS
    {
        string element; // the data in the mode
        BinaryNode *left; // left child
        BinaryNode *right; // right child
        
        // GIVEN IN CLASS
        // CONSTRUCTORS - use the member initializer_list to implement the assignments of theElement to element, lt to left, rt to right
        BinaryNode(const string & theElement = string{}, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr) : element{theElement}, left{lt}, right{rt} {}
        BinaryNode(string && theElement, BinaryNode *lt, BinaryNode *rt) : element{std::move(theElement)}, left{lt}, right{rt} {}

        /*
        BinaryNode()
        {
            element = "";
            left = new BinaryNode;
            right = new BinaryNode;
        }
        
        BinaryNode(const string & theElement, BinaryNode *lt, BinaryNode *rt)
        {
            element = theElement;
            left = lt;
            right = rt;
        }
        */
    };

    public:
    BET(); // default zero-parameter constructor, builds an empty tree
    BET(const string& postfix); // one-parameter constructor 
    BET(const BET&); // copy constructor that makes a deep copy of the tree
    ~BET(); // destructor
    bool buildFromPostfix(const string& postfix);
    const BET & operator=(const BET &); // assignment operator
    void printPostfixExpression() const;
    void printInfixExpression() const;
    size_t size() const; // return the number of nodes in the tree
    size_t leaf_nodes() const; // return the number of leaves in the tree
    bool empty() const;
    bool isOperator(string) const; // checks if a token is an operator or not
    int checkPrecedence(string) const; // checks the precedence of each operator

    private:
    BinaryNode *root; // start of the tree
    void printInfixExpression(BinaryNode *n) const;
    void makeEmpty(BinaryNode* &t);
    BinaryNode * clone(BinaryNode *t) const; // clone all nodes in the subtree pointed to by t
    void printPostfixExpression(BinaryNode *n) const;
    size_t size(BinaryNode *t) const;
    size_t leaf_nodes(BinaryNode *t) const;
    stack<BinaryNode*> myStack; // stack of BinaryNodes - the tree!
    
};