#include <string>
#include <iostream>
#include "ItemNode.cpp"
using namespace std;
class CategoryNode
{
public:
    std::string key;
    CategoryNode* left;
    CategoryNode* right;
    int height;
    ItemNode* itemRoot;
    CategoryNode(std::string);
    ~CategoryNode();
};

CategoryNode::CategoryNode(std::string name)
{
    this->key = name;
    this->left = NULL;
    this->right = NULL;
    this->itemRoot = NULL;
}

CategoryNode::~CategoryNode()
{
}

class CategoryNodeAvl
{

public:
    CategoryNode* root;
    CategoryNodeAvl();
    CategoryNodeAvl(CategoryNode*);
    static int getBalanceFactor(CategoryNode *N);
    static CategoryNode* insertCategoryNode(CategoryNode *CategoryNode, std::string key);
    static int height(CategoryNode *N);
    static int max(int,int);
    static CategoryNode* newCategoryNode(std::string name);
    static CategoryNode* rightRotate(CategoryNode*);
    static CategoryNode* leftRotate(CategoryNode*);
    static void printTree(CategoryNode *root, std::string indent, bool last);
    static CategoryNode *nodeWithMinimumValue(CategoryNode *node);
    static CategoryNode* deleteNode(CategoryNode*,string);
    static CategoryNode* getNode(CategoryNode*,string);
};
 CategoryNodeAvl::CategoryNodeAvl()
{
    root=NULL;
}
CategoryNodeAvl::CategoryNodeAvl(CategoryNode* item)
{
    root=item;
}
int CategoryNodeAvl::max(int a, int b) {
  return (a > b) ? a : b;
}

int CategoryNodeAvl::getBalanceFactor(CategoryNode *N) {
  if (N == NULL)
    return 0;
  return height(N->left) -height(N->right);
}

CategoryNode* CategoryNodeAvl::insertCategoryNode(CategoryNode *CategoryNode, std::string key) {
  // Find the correct postion and insert the CategoryNode
  if (CategoryNode == NULL)
    {
    return (newCategoryNode(key));
    }
  if (key < CategoryNode->key)
    {
    CategoryNode->left = insertCategoryNode(CategoryNode->left, key);
    }
  else if (key > CategoryNode->key)
  {
    CategoryNode->right = insertCategoryNode(CategoryNode->right, key);
    }
  else
  {
    return CategoryNode;
  }
  // Update the balance factor of each CategoryNode and
  // balance the tree
  CategoryNode->height = 1 + max(height(CategoryNode->left), height(CategoryNode->right));
  int balanceFactor = getBalanceFactor(CategoryNode);
  if (balanceFactor > 1) 
  {
    if (key < CategoryNode->left->key) 
    {
      return rightRotate(CategoryNode);
    } 
    else if (key > CategoryNode->left->key) 
    {
      CategoryNode->left = leftRotate(CategoryNode->left);
      return rightRotate(CategoryNode);
    }
  }
  if (balanceFactor < -1) {
    if (key > CategoryNode->right->key) 
    {
      return leftRotate(CategoryNode);
    } 
    else if (key < CategoryNode->right->key) 
    {
      CategoryNode->right = rightRotate(CategoryNode->right);
      return leftRotate(CategoryNode);
    }
  }
  return CategoryNode;
}
int CategoryNodeAvl::height(CategoryNode *N) {
  if (N == NULL)
    return 0;
  return N->height;
}
// New node creation
CategoryNode * CategoryNodeAvl::newCategoryNode(std::string name) {
  CategoryNode *node = new CategoryNode(name);
  node->height = 1;
  return (node);
}

// Rotate right
CategoryNode* CategoryNodeAvl::rightRotate(CategoryNode *y) {
  CategoryNode *x = y->left;
  CategoryNode *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) +1;
  return x;
}

// Rotate left
CategoryNode* CategoryNodeAvl::leftRotate(CategoryNode *x) {
  CategoryNode *y = x->right;
  CategoryNode *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),height(x->right)) + 1;
  y->height = max(height(y->left),height(y->right)) +1;
  return y;
}
// Print the tree
void CategoryNodeAvl::printTree(CategoryNode *root, std::string indent, bool last) {
  if (root != NULL) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << root->key<<"  " << endl;
    ItemNodeAvl::printTree(root->itemRoot,indent,true);
    
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}
CategoryNode* CategoryNodeAvl::nodeWithMinimumValue(CategoryNode *node) {
  CategoryNode *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}
// Delete a node
CategoryNode* CategoryNodeAvl::deleteNode(CategoryNode *root, string key) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) || (root->right == NULL)) 
    {
      CategoryNode *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      CategoryNode *temp = nodeWithMinimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left), height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}
CategoryNode* CategoryNodeAvl::getNode(CategoryNode* root,string categoryName)
{
  CategoryNode* temp = root;
  if(root==NULL)return NULL;
  while(temp->key!=categoryName)
  {
    if (temp->key < categoryName)
    {
      if(temp->right== NULL)return NULL;
    
      temp=temp->right;
    }
    else if(temp->key > categoryName)
    {
      if(temp->left== NULL)return NULL;
      temp=temp->left;
    }
  }
  return temp;
}