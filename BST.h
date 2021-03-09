#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;
#include <string>
#include <sstream>
#define CAT_NAME_LEN 25
#define APP_NAME_LEN 50
#define VERSION_LEN 10
#define UNIT_SIZE 3


class Hash;

class BST {

public:
    struct app_info {
        string cat;
        string key;
        string version;
        float size;
        string units;
        float price;
    };
    struct tree {

        app_info record;
        tree* left;
        tree* right;
    };



    tree* root;

    void AddLeafPrivate(app_info *record, tree* ptr);
    void PrintTreePrivate(tree* ptr);
    tree* ReturntreePrivate(int record, tree* ptr);
    tree* CreateLeaf(app_info* info);
    tree* Returntree(int record);
    app_info* getInfoPrivate();
    app_info* getInfo();
    BST(); //constructor
    ~BST();//deconstructor
    void AddLeaf(app_info* record);
    void PrintTree();
    int ReturnRootrecord();
    void PrintChildren(int record);
    void Removetree(int record);
    void addLeafToCat(Hash obj,struct categories *arry, int numOfCat , int numOfApps);
	void printNode(tree* ptr);
	void printCat(struct categories *arry, int numOfCat, string key);
	void printFree(struct categories *arry, int numOfCat);
	bool PrintFreeLoop(bool free ,tree* ptr);
	void printPriceRange(struct categories *arry,float low,float high,string category,int numOfCat);
	void PrintPriceRangeLoop(tree* ptr,float low, float high);
	void printAppRange(struct categories *arry,char low,char high,string category, int numOfCat);
	void PrintAppRangeLoop(tree* ptr,char low, char high);
	tree* ReturnNode(string key);
	tree* ReturnNodePrivate(string key, tree* ptr);
	string ReturnRootKey();
	string FindSmallest();
	string FindSmallestPrivate(tree* ptr);
	void RemoveNode(string key,string category,struct categories *arry,int numOfCat);
	void RemoveNodePrivate(string key, tree* parent);
	void RemoveRootMatch();
	void RemoveMatch(tree* parent, tree* match, bool left);
	void RemoveSubtree(tree* ptr);
};
struct categories {
    string category; // Name of category
    BST root; // Pointer to root of search tree for this category
};

class Hash {
private:
	int collisions = 0;

	static const int tableSize = 233;

	struct item { // what we are putting into the table
		string name;
		BST* ptr;
		item* next;
	};

	item* HashTable[tableSize];

public:
	Hash();//constructor
	int hash(string key);//creating key value from string
	void AddItem(string name, BST* ptr);
	int NumberOfItemsInIndex(int index);
	void printTable();
	void printCollisions();
	void Find(string name);

};

#endif