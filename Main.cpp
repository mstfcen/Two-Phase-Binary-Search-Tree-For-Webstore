#include "CategoryNode.cpp"
#include "ItemNode.cpp"
#include <iostream>
#include <string>
#include "FileReader.cpp"
#include <vector>
#include <fstream>
#include <typeinfo>
using namespace std;

int main(int argc, char const *argv[])
{
    freopen(argv[2],"w",stdout);
    CategoryNode* categoryRoot = nullptr;
    vector<string> inputs = FileReader::readFile(argv[1]);
    for (int i = 0; i < inputs.size(); i++)
    {
        if(inputs[i]=="insert")
        {
            /*
            look if category node exists
            if True:
            insert new item to itemitemRoot and itemRoota eşitle
            if False:
            insert a category node and then insert itemNode in it 
            */
            string categoryName = inputs[++i];
            string itemName = inputs[++i];
            int itemPrice = stoi(inputs[++i]);
            if(CategoryNodeAvl::getNode(categoryRoot,categoryName)==NULL)
           {
                categoryRoot = CategoryNodeAvl::insertCategoryNode(categoryRoot,categoryName);
                CategoryNode* categoryNode = CategoryNodeAvl::getNode(categoryRoot,categoryName);
                categoryNode->itemRoot = ItemNodeAvl::insertItemNode(categoryNode->itemRoot,itemName,itemPrice);
           }
           else
           {
                CategoryNode* categoryNode = CategoryNodeAvl::getNode(categoryRoot,categoryName);
                categoryNode->itemRoot =  ItemNodeAvl::insertItemNode(categoryNode->itemRoot,itemName,itemPrice);
           }
           
        }
        else if(inputs[i]=="remove")
        {
            CategoryNode* categoryNode = CategoryNodeAvl::getNode(categoryRoot,inputs[++i]);
            categoryNode->itemRoot = ItemNodeAvl::deleteNode(categoryNode->itemRoot,inputs[++i]);
        }
        else if(inputs[i]=="printAllItems")
        {
            cout << "command:"<<inputs[i]<<endl<<"{"<<endl;
            /*
            Print all items 
            */
           CategoryNodeAvl::printTree(categoryRoot,"",true);
        }
        else if(inputs[i]=="printAllItemsInCategory")
        {
            cout << "command:"<<inputs[i];
            /*
            get category node and print all items in itemRoot
            */
            string categoryName = inputs[++i];
            cout << " " << categoryName <<endl<<"{"<<endl;
            CategoryNode* categoryNode = CategoryNodeAvl::getNode(categoryRoot,categoryName);
            cout << categoryNode->key << ":"<<endl;
            if(categoryNode->itemRoot==NULL){cout <<"{}"<<endl<<"}"<<endl;}
            else
            {
                ItemNodeAvl::printTree(categoryNode->itemRoot,"",true);
            }
        }
        else if(inputs[i]=="printItem" | inputs[i]=="find")
        {
            cout << "command:"<<inputs[i];
            /*
            get category node and look for item in category node 
            and then print it
            */
           string categoryName = inputs[++i];
           string itemName = inputs[++i];
           cout <<" "<<categoryName<<" "<<itemName<<endl<<"{"<<endl;
           CategoryNode* categoryNode = CategoryNodeAvl::getNode(categoryRoot,categoryName);
           if(categoryNode ==  NULL){cout << "{}" <<endl<<"}"<<endl;}
           else{
            ItemNode* itemNode = ItemNodeAvl::getNode(categoryNode->itemRoot,itemName);
           
           if(itemNode == NULL){cout << "{}" <<endl<<"}"<<endl;}
           else{
            cout << categoryName << ":"<< endl;
            cout << "\t\t"<<itemNode->key <<" " <<itemNode->price<<endl<<"}"<<endl;}}
        }
        else if(inputs[i]=="updateData")
        {
            //get corresponding category node and find corresponding item and then update its price
            CategoryNode* categoryNode = CategoryNodeAvl::getNode(categoryRoot,inputs[++i]);
            ItemNode* itemNode = ItemNodeAvl::getNode(categoryNode->itemRoot,inputs[++i]);
            itemNode->price = stoi(inputs[++i]);
        }
    }
    return 0;
}

