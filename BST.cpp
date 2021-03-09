#include "BST.h"

BST::BST(){//constructor

    root = NULL;
}

BST::tree* BST::CreateLeaf(app_info* info) {

    tree* n = new tree;
    n->record.key = info->key;
    n->record.cat = info->cat;
    n->record.units = info->units;
    n->record.version = info->version;
    n->record.size = info->size;
    n->record.price = info->price;

    n->left = NULL;
    n->right = NULL;

    return n;
}

void BST::AddLeaf(app_info* record) {

    AddLeafPrivate(record, root);//so we are able to call private func from main
}

void BST::AddLeafPrivate(app_info* record, tree* ptr) {

    if (root == NULL) { //creates new leaf if empty

        root = CreateLeaf(record);
    }
    else if (ptr->record.key.compare(record->key) > 0) {

        if (ptr->left != NULL)//if not empty traverse left
            AddLeafPrivate(record, ptr->left);
        else
            ptr->left = CreateLeaf(record); //if empty create leaf
    }
    else if (record->key.compare(ptr->record.key) > 0) { //if record is bigger

        if (ptr->right != NULL)
            AddLeafPrivate(record, ptr->right); //if not empty traverse right
        else
            ptr->right = CreateLeaf(record);//if empty create leaf
    }
    else {

        cout << "record: " << record << " has already been added" << endl;

    }


}

void BST::PrintTree() {

    PrintTreePrivate(root);

}

void BST::PrintTreePrivate(tree* ptr) {

    if (root != NULL) {

        if (ptr->left != NULL)
            PrintTreePrivate(ptr->left);


        cout << "\t" << ptr->record.key << " " << endl;

        cout << endl;

        if (ptr->right != NULL)
            PrintTreePrivate(ptr->right);

    }
    else
        cout << "<category> empty" <<  endl;


}


BST::~BST() {

    RemoveSubtree(root);

}

void BST::RemoveSubtree(tree* ptr) {

    if (ptr != NULL) {

        if (ptr->left != NULL) {
            RemoveSubtree(ptr->left);
        }
        if (ptr->right != NULL) {
            RemoveSubtree(ptr->right);
        }

        delete ptr;

    }


}
BST::app_info* BST::getInfoPrivate(){
    app_info *temp = new app_info;

    string App;
    string cat;
    string ver;
    string size;
    string unit;
    string price;

    getline(cin,cat);//cat
    getline(cin, App); //name
    getline(cin,ver);//version
    getline(cin,size);//size
    getline(cin,unit);//unit
    getline(cin,price);//price

    float sizeF;
    stringstream ss;
    ss << size;
    ss >> sizeF;

    float priceF;
    stringstream pp;
    pp << price;
    pp >> priceF;


    temp->cat = cat;
    temp->key = App;
    temp->version = ver;
    temp->units = unit;
    temp->size = sizeF;
    temp->price = priceF;

    return temp;
}


BST::app_info* BST::getInfo(){

    return getInfoPrivate();
}

void BST::addLeafToCat(Hash obj,struct categories *arry, int numOfCat , int numOfApps){
    int j = 0;
    for (int i = 0; i < numOfApps; i++) {

        app_info *record;
        record = arry->root.getInfo();
        if(record->cat != arry[j].category) {
            j = j + 1;
        }
        arry[j].root.AddLeaf(record);
        BST *treePtr = &arry[j].root;
		obj.AddItem(record->key,treePtr);
    }

}
Hash::Hash() {
	//initializing our items in the hash table
	for (int i = 0; i < tableSize; i++) {
		HashTable[i]= new item;
		HashTable[i]->name = "empty";
		HashTable[i]->ptr = NULL;
		HashTable[i]->next = NULL;
	}

}
int Hash::hash(string key) {
	int hash = 0;
	int index;

	//adding up the asciis of the whole string to be our key
	for (int i = 0; i < key.length(); i++)
		hash += (int)key[i];

	index = hash % tableSize; // ascii total mod 100

	return index;
}
void Hash::AddItem(string name,BST* treeptr) {
	int index = hash(name);

	//if index isnt taken
	if (HashTable[index]->name == "empty") {
		HashTable[index]->name = name;
		HashTable[index]->ptr = treeptr;
	}
	else {//if index is taken
		collisions++;
		item* ptr = HashTable[index];
		item* n = new item;
		n->name = name;
		n->ptr = treeptr;
		n->next = NULL;
		while (ptr->next != NULL) {//searching for empty space
			ptr = ptr->next;
		}
		ptr->next = n;//add new item to empty space
	}
}
int Hash::NumberOfItemsInIndex(int index) {
	int count = 0;

	if (HashTable[index]->name == "empty") {
		return count;
	}
	else {
		count++;
		item* ptr = HashTable[index];
		while (ptr->next != NULL) {
			count++;
			ptr = ptr->next;
		}
	}
	return count;
}
void Hash::printTable() {
	int number = 0;
	for (int i = 0; i < tableSize; i++) {

		item* ptr = HashTable[i];
		if (HashTable[i]->name != "empty") {
			cout << "------------------\n";
			cout << "index = " << i << endl;
			cout << "name = " << HashTable[i]->name << endl;
			cout << "------------------\n";
			number++;
		}
		if (NumberOfItemsInIndex(i) > 1) {
			while (ptr->next != NULL) {
				ptr = ptr->next;
				cout << "------------------\n";
				cout << "index = " << i << endl;
				cout << "name = " << ptr->name << endl;

				cout << "------------------\n";
				number++;

			}
		}
	}
	cout << number << endl;
}

void Hash::Find(string name) {

	int index = hash(name);
	bool foundName = false;

	item* ptr = HashTable[index];
	while (ptr != NULL) {

		if (ptr->name == name) {

			foundName = true;
			BST::tree* foundPtr;
			foundPtr = ptr->ptr->ReturnNodePrivate(name,ptr->ptr->root);
			ptr->ptr->printNode(foundPtr);




		}
		ptr = ptr->next;
	}
	if (foundName == false) {
		cout << name << "<" << name << "> not found" <<  endl;
	}

}
void BST::printNode(tree* ptr){

	cout << "Found Application:  <" << ptr->record.key << ">" << endl;
	cout << "\tVersion:  " << ptr->record.version  << endl;
	cout << "\tSize:  " << ptr->record.size  << endl;
	cout << "\tUnits:  " << ptr->record.units << endl;


}
void BST::printCat(struct categories *arry, int numOfCat, string key){
	bool found = false;
	for(int i = 0; i <numOfCat ; i++){
		if(arry[i].category == key){
			found = true;
			cout << "Found Category:  <" << arry[i].category << ">" << endl;
			arry[i].root.PrintTree();
		}

	}
	if(found == false)
		cout << "Category  <" << key << "> not found" << endl;



}
void BST::printFree(struct categories *arry, int numOfCat){

	for(int i = 0; i <numOfCat ; i++){
		bool free;
		cout << "Free Applications in Category: " << "<"<< arry[i].category << ">" << endl;
		bool help;
		help = arry[i].root.PrintFreeLoop(free, arry[i].root.root);


	}


}
bool BST::PrintFreeLoop(bool free, tree* ptr) {

	if (root != NULL) {

		if (ptr->left != NULL)
			PrintFreeLoop(free,ptr->left);

		float zero = 0.00;
		if(ptr->record.price == zero) {
			free = true;
			cout << "\t" << ptr->record.key << " " << endl;
			cout << endl;
		}

		if (ptr->right != NULL)
			PrintFreeLoop(free, ptr->right);

	}
	else
		cout << "Tree Empty" << endl;


	return free;
}
void BST::printPriceRange(struct categories *arry,float low,float high,string category, int numOfCat) {
	cout << "Applications in Price Range (<" << low << ">,<" << high << ">) in Category: " << "<" << category << ">" << endl;
	bool found = false;
	for (int i = 0; i < numOfCat; i++) {
		if (arry[i].category == category) {
			found = true;
			arry[i].root.PrintPriceRangeLoop(arry[i].root.root,low,high);
		}

	}
	if (found == false)
		cout << "Category  <" << category << "> not found" << endl;
}
void BST::PrintPriceRangeLoop(tree* ptr,float low, float high) {

	if (root != NULL) {

		if (ptr->left != NULL)
			PrintPriceRangeLoop(ptr->left,low,high);


		if(ptr->record.price >= low && ptr->record.price <= high) {

			cout << "\t" << ptr->record.key << " " << endl;
			cout << endl;
		}

		if (ptr->right != NULL)
			PrintPriceRangeLoop(ptr->right,low,high);

	}
	else
		cout << "Tree Empty" << endl;



}

void BST::printAppRange(struct categories *arry,char low,char high,string category, int numOfCat) {
	cout << "Applications in Range (<" << low << ">,<" << high << ">) in Category: " << "<" << category << ">" << endl;
	bool found = false;
	for (int i = 0; i < numOfCat; i++) {
		if (arry[i].category == category) {
			found = true;
			arry[i].root.PrintAppRangeLoop(arry[i].root.root,low,high);
		}

	}
	if (found == false)
		cout << "Category  <" << category << "> not found" << endl;
}
void BST::PrintAppRangeLoop(tree* ptr,char low, char high) {

	string hold = ptr->record.key;
	char letter = hold.at(0);
	letter = toupper(letter);

	if (root != NULL) {

		if (ptr->left != NULL)
			PrintAppRangeLoop(ptr->left,low,high);


		if(letter >= low && letter <= high){
			cout <<"\t" << ptr->record.key << " " << endl;
			cout << endl;
		}



		if (ptr->right != NULL)
			PrintAppRangeLoop(ptr->right,low,high);

	}
	else
		cout << "Tree Empty" << endl;



}
BST::tree* BST::ReturnNode(string key) {

	return ReturnNodePrivate(key, root);

}

BST::tree* BST::ReturnNodePrivate(string key, tree* ptr) {

	if (ptr != NULL) {

		if (ptr->record.key == key)
			return ptr;

		else {

			if (key < ptr->record.key)
				return ReturnNodePrivate(key, ptr->left);

			else
				return ReturnNodePrivate(key, ptr->right);

		}
	}
	else
		return NULL;

}

string BST::ReturnRootKey() {

	if (root != NULL)
		return root->record.key;

	else
		return "wrong";

}


string BST::FindSmallest() {

	return FindSmallestPrivate(root);

}

string BST::FindSmallestPrivate(tree* ptr) {

	if (root == NULL) {

		cout << "[tree empty]" << endl;
		return "wrong";

	}
	else {

		if (ptr->left != NULL)
			return FindSmallestPrivate(ptr->left);

		else
			return ptr->record.key;
	}
}

void BST::RemoveNode(string key,string category,struct categories *arry,int numOfCat) {
	bool found = false;
	for (int i = 0; i < numOfCat; i++) {
		if (arry[i].category == category) {
			found = true;
			arry[i].root.RemoveNodePrivate(key, arry[i].root.root);
		}

	}
	if (found == false)
		cout << "Category  <" << category << "> not found" << endl;



}

void BST::RemoveNodePrivate(string key, tree* parent) {

	if (root != NULL) {

		if (root->record.key == key)
			RemoveRootMatch();

		else {

			if (key < parent->record.key && parent->left != NULL) {

				parent->left->record.key == key ?
				RemoveMatch(parent, parent->left, true) :
				RemoveNodePrivate(key, parent->left);

			}
			else if (key > parent->record.key && parent->right != NULL) {

				parent->right->record.key == key ?
				RemoveMatch(parent, parent->right, false) :
				RemoveNodePrivate(key, parent->right);

			}
			else
				cout << "[key not found]" << endl;

		}
	}
	else
		cout << "[tree empty]" << endl;
}

void BST::RemoveRootMatch() {

	if (root != NULL) {

		tree* delptr = root;
		string rootKey = root->record.key;
		string smallRight; //smallest key in right subtree

		//root has 0 children
		if (root->left == NULL && root->right == NULL) {

			root = NULL;
			delete delptr;

		}
			//root has 1 child on the right
		else if (root->left == NULL && root->right != NULL) {

			root = root->right;
			delptr->right = NULL;
			delete delptr;
			cout << "[old root " << rootKey << " deleted]" << endl;
			cout << "[new root is " << root->record.key << "]" << endl;

		}
			//root has 1 child on the left
		else if (root->left != NULL && root->right == NULL) {

			root = root->left;
			delptr->left = NULL;
			delete delptr;
			cout << "[old root " << rootKey << " deleted]" << endl;
			cout << "[new root is " << root->record.key << "]" << endl;

		}
			//root has two children
		else {

			smallRight = FindSmallestPrivate(root->right);
			RemoveNodePrivate(smallRight, root);
			root->record.key = smallRight;
			cout << "[old root " << rootKey << " deleted]" << endl;
			cout << "[new root is " << root->record.key << "]" << endl;

		}
	}
	else
		cout << "[tree empty]" << endl;

}
void BST::RemoveMatch(tree* parent, tree* match, bool left) {

	if (root != NULL) {

		tree* delptr;
		string matchKey = match->record.key;
		string smallRight;

		//match has 0 children
		if (match->left == NULL && match->right == NULL) {

			delptr = match;

			left == true ?
					parent->left = NULL :
					parent->right = NULL;

			delete delptr;
			cout << "[" << matchKey << " removed]" << endl;

		}
			//match has one child
		else if (match->left == NULL && match->right != NULL) {

			left == true ?
					parent->left = match->right :
					parent->right = match->right;
			match->right = NULL;
			delptr = match;
			delete delptr;
			cout << "[" << matchKey << " removed]" << endl;

		}
		else if (match->left != NULL && match->right == NULL) {

			left == true ?
					parent->left = match->left :
					parent->right = match->left;
			match->left = NULL;
			delptr = match;
			delete delptr;
			cout << "[" << matchKey << " removed]" << endl;

		}
			//node has two children
		else {

			smallRight = FindSmallestPrivate(match->right);
			RemoveNodePrivate(smallRight, match);
			match->record.key = smallRight;
		}

	}
	else
		cout << "[tree empty]" << endl;

}
