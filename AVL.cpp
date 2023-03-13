#include "ItemNode.cpp"

class AVL
{
public:
    static int getBalanceFactor(T *N);
    static ItemNode* insertItemNode(ItemNode *ItemNode, std::string key,int price);
    int height(T *N);
    int max(int,int);
    static ItemNode* newItemNode(std::string name,int price);
    static T* rightRotate(T*);
    static T* leftRotate(T*);
    static void printTree(T *root, std::string indent, bool last);
    static T* nodeWithMinimumValue(T *node);
    static T* deleteNode(T*,string);
    static ItemNode* updateNode(ItemNode* ,string ,int );
};

int AVL::max(int a, int b) {
  return (a > b) ? a : b;
}

template <typename T>
static int AVL::getBalanceFactor(T *N) {
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

static ItemNode* AVL::insertItemNode(ItemNode* itemNode, std::string key,int price) {
  // Find the correct postion and insert the ItemNode
  if (itemNode == NULL)
    return (newItemNode(key,price));
  if (key < itemNode->key)
    itemNode->left = insertItemNode(itemNode->left, key,price);
  else if (key > itemNode->key)
    itemNode->right = insertItemNode(itemNode->right, key,price);
  else
    return itemNode;

  // Update the balance factor of each ItemNode and
  // balance the tree
  itemNode->height = 1 + max(height(itemNode->left),
               height(itemNode->right));
  int balanceFactor = getBalanceFactor(itemNode);
  if (balanceFactor > 1) {
    if (key < itemNode->left->key) {
      return rightRotate(itemNode);
    } else if (key > itemNode->left->key) {
      itemNode->left = leftRotate(itemNode->left);
      return rightRotate(itemNode);
    }
  }
  if (balanceFactor < -1) {
    if (key > itemNode->right->key) {
      return leftRotate(itemNode);
    } else if (key < itemNode->right->key) {
      itemNode->right = rightRotate(itemNode->right);
      return leftRotate(itemNode);
    }
  }
  return itemNode;
}
template <typename T>
static int AVL::height(T *N) {
  if (N == NULL)
    return 0;
  return N->height;
}
// New node creation
static ItemNode* AVL::newItemNode(std::string name,int price) {
  ItemNode *node = new ItemNode(name,price);
  node->height = 1;
  return (node);
}

// Rotate right
template <typename T>
static T* AVL::rightRotate(T *y) {
  T *x = y->left;
  T *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  return x;
}

// Rotate left
template <typename T>
static T* AVL::leftRotate(T *x) {
  T *y = x->right;
  T *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),height(x->right)) + 1;
  y->height = max(height(y->left),height(y->right)) +1;
  return y;
}
// Print the tree
template <typename T>
static void AVL::printTree(T *root, std::string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    try
    {
      cout << root->key<<" "<<root->price << endl;
    }
    catch(exception e)
    {
      cout <<"anneni siktim" <<endl;
    }
    
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}
template <typename T>
static T* AVL::nodeWithMinimumValue(T *node) {
  T *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}
// Delete a node
template <typename T>
static T* AVL::deleteNode(T *root, string key) {
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
      ItemNode *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      ItemNode *temp = nodeWithMinimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));
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

static ItemNode* AVL::updateNode(ItemNode* root,string key,int updateVal)
{
  if(root->key == key && updateVal ==-1)
  {
    return root;
  }
  else if(root->key == key && updateVal !=-1)
  {
    root->price=updateVal;
    return root;
  }
  if(key < root->key)
  {
    updateNode(root->left,key,updateVal);
  }
  else if(key > root->key)
  {
    updateNode(root->right,key,updateVal);
  }
}
