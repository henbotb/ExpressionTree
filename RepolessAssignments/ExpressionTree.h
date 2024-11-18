#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <string> // string, stoi (string -> int), strlen
#include <iostream> // ostream
#include <cctype> // isdigit
#include <cmath> // pow

class ExpressionTree {
private:
    struct Node;
    Node* root;
    std::string expr;

    // helper methods

    // destructor
    void deleteTree(Node*);

    // making/evaluating/copy expression tree
    void buildTree(Node*&, size_t);
    int evaluateTree(Node*);
    Node* copyTree(Node*);

    // output
    void postOrder(std::ostream&, Node*);
    void inOrder(std::ostream&, Node*);
public:
    // constructors
    ExpressionTree();
    ExpressionTree(std::string);

    // copy constructors
    ExpressionTree(const ExpressionTree&);
    ExpressionTree& operator=(const ExpressionTree&);

    // destructor
    ~ExpressionTree();

    // setter / getter
    void setExpression(std::string);
    int getResult();

    // output
    std::ostream& printParseTreeInOrder(std::ostream&);
    std::ostream& printParseTreePostOrder(std::ostream&);
};

struct ExpressionTree::Node {
    Node* left;
    Node* right;
    std::string data;

    Node() : left(nullptr), right(nullptr), data("") {}
    Node(std::string val) : left(nullptr), right(nullptr), data(val) {}
    Node(Node* l, Node* r, std::string val) : left(l), right(r), data(val) {}
};

ExpressionTree::ExpressionTree() : expr(""), root(nullptr) {}

ExpressionTree::ExpressionTree(std::string expr) : expr(expr), root(nullptr) {
    if (!expr.empty()) {
        root = new Node;
        buildTree(root, 0);
    }
}

ExpressionTree::ExpressionTree(const ExpressionTree& bt) {
    deleteTree(root);
    root = copyTree(bt.root);
}

ExpressionTree& ExpressionTree::operator=(const ExpressionTree& bt) {
    if (this != &bt) { // self check
        deleteTree(root);
        root = copyTree(bt.root);
    }
    return *this;
}

ExpressionTree::~ExpressionTree() {
    // call delete tree with root node
    deleteTree(root);
}

void ExpressionTree::setExpression(std::string expr) {
    deleteTree(root); // delete tree
    root = nullptr;
    this->expr = expr;
    if(!expr.empty()) buildTree(root, 0);
    
}

int ExpressionTree::getResult() {
    return evaluateTree(root);
}

std::ostream& ExpressionTree::printParseTreeInOrder(std::ostream& out) {
    if (root != nullptr) inOrder(out, root);
    return out;
}

std::ostream& ExpressionTree::printParseTreePostOrder(std::ostream& out) {
    if (root != nullptr) postOrder(out, root);
    return out;
}

// helper methods

ExpressionTree::Node* ExpressionTree::copyTree(Node* other) {
    if (other == nullptr) return nullptr;
    return new Node(copyTree(other->left), copyTree(other->right), other->data);
}

void ExpressionTree::deleteTree(Node* curr) {
    if (curr == nullptr) return; // base case
    deleteTree(curr->left); // recursively delete all of left and right branch
    deleteTree(curr->right);
    delete curr; // delete current node after previous branch cleared
}

void ExpressionTree::postOrder(std::ostream& out, Node* curr) {
    if (!curr) return;
    if (curr->data == "") return;
    postOrder(out, curr->left);
    postOrder(out, curr->right);
    out << (curr == root ? "" : " ") << curr->data;
}

void ExpressionTree::inOrder(std::ostream& out, Node* curr) {
    if (!curr) return;
    if (curr->data == "") return;
    inOrder(out, curr->left);
    out << (curr == root ? "" : " ") << curr->data;
    inOrder(out, curr->right);
    
}

void ExpressionTree::buildTree(Node*& curr, size_t ndx) {
    if (ndx > expr.length()) return;

    char currVal = expr[ndx];
    if (currVal == '(') {
        curr->left = new Node;
        ndx++;
        buildTree(curr->left, ndx);
    }
    else if (std::isdigit(currVal)) {
        std::string tempNum = "";
        while (std::isdigit(expr[ndx]) && ndx < expr.length()) {
            tempNum += expr[ndx++];
        }

        curr = new Node(tempNum);
        return;
    }
    else if (
        currVal == '+' ||
        currVal == '-' ||
        currVal == '/' ||
        currVal == '*' ||
        currVal == '^'
        ) {
        curr->data = currVal;''
        ndx++;
        curr->right = new Node;
        buildTree(curr->right, ndx);
    }
    else if (currVal == ')') {
        ndx++;
        return;
    }
}

int ExpressionTree::evaluateTree(Node* curr) {
    if (curr == nullptr) return 0; // base case
    if (curr->left == nullptr && curr->right == nullptr) return std::stoi(curr->data); // if not operator, return value

    // if not value or nullptr, return the operator on the values
    int leftVal = evaluateTree(curr->left);
    int rightVal = evaluateTree(curr->right);

    switch (curr->data[0]) {
    case '+': return leftVal + rightVal;
    case '-': return leftVal - rightVal;
    case '/': 
        if (rightVal == 0) throw std::runtime_error("Divison by zero");
        return leftVal / rightVal;
    case '*': return leftVal * rightVal;
    case '^': return std::pow(leftVal, rightVal);
    default: throw std::logic_error("Invalid operator type");
    }
}

#endif