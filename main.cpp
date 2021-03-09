#include "BST.h"


void PrintCatArray(int numOfCat, struct categories *arry){

    for(int i = 0; i< numOfCat; i++){
        cout << arry[i].category << endl;

    }

}


int main() {

    //test values
    int numOfCat;
    cin >> numOfCat;

    cin.ignore();
    struct categories app_categories [numOfCat];

    for(int i = 0; i < numOfCat; i++){

        string str;
        getline(cin, str);

        app_categories[i].category = str;

        BST tree; //creating tree

        app_categories[i].root = tree;

    }



    BST treeMain;
	Hash obj;

    int numApps;
    cin >> numApps;
    cin.ignore();

    //create a tree of all apps including cats
    //then go through cat array adding each leaf of that cat
    //for (int i = 0; i < numApps; i++) {
    //    treeMain.AddLeaf(treeMain.getInfo());
    //}

    treeMain.addLeafToCat(obj,app_categories, numOfCat, numApps);


	string query;
	getline(cin,query);

	int querys;
	stringstream qq;
	qq << query;
	qq >> querys;

	for(int i = 0; i < querys; i++){
		string hold;
		getline(cin,hold);
		string input = hold;
		string firstWord = input.substr(0, input.find(" "));
		if(firstWord == "find"){
			input=input.substr(input.find_first_of(" \t")+1);
			firstWord = input.substr(0, input.find(" "));
			if(firstWord == "app"){
				input=input.substr(input.find_first_of(" \t")+1);
				obj.Find(input);
				cout << endl;
				cout << endl;
			}
			if(firstWord == "category"){
				input=input.substr(input.find_first_of(" \t")+1);
				treeMain.printCat(app_categories,numOfCat,input);
				cout << endl;
				cout << endl;
			}
			if(firstWord == "price"){
				treeMain.printFree(app_categories,numOfCat);
				cout << endl;
				cout << endl;
			}
		}
		if(firstWord == "range"){
			input=input.substr(input.find_first_of(" \t")+1);
			string category;
			category = input.substr(0, input.find(" "));
			input=input.substr(input.find_first_of(" \t")+1);
			firstWord = input.substr(0, input.find(" "));
			if(firstWord == "app"){
				string lowHold;
				string highHold;
				input=input.substr(input.find_first_of(" \t")+1);
				lowHold = input.substr(0, input.find(" "));
				input=input.substr(input.find_first_of(" \t")+1);
				highHold = input.substr(0, input.find(" "));
				char low = lowHold[0];
				char high = highHold[0];
				treeMain.printAppRange(app_categories,low,high,category,numOfCat);
				cout << endl;
				cout << endl;
			}
			if(firstWord == "price"){
				string lowHold;
				string highHold;
				input=input.substr(input.find_first_of(" \t")+1);
				lowHold = input.substr(0, input.find(" "));
				input=input.substr(input.find_first_of(" \t")+1);
				highHold = input.substr(0, input.find(" "));
				float low;
				stringstream ll;
				ll << lowHold;
				ll >> low;
				float high;
				stringstream hh;
				hh << highHold;
				hh >> high;
				treeMain.printPriceRange(app_categories,low,high,category,numOfCat);
				cout << endl;
				cout << endl;

			}
		}
		if(firstWord == "delete"){
			string category;
			input=input.substr(input.find_first_of(" \t")+1);
			category = input.substr(0, input.find(" "));
			string name = input=input.substr(input.find_first_of(" \t")+1);
			treeMain.RemoveNode(name, category, app_categories, numOfCat);
			cout << endl;
			cout << endl;
		}
		if(firstWord == "report"){
			cout << "number of categories in array: " << numOfCat << endl;
			cout << "number of apps in hash table and BST: " << numApps << endl;
		}


	}



    return 0;
}