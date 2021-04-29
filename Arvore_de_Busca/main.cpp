#include <iostream>
#include "Arvore.h"
using namespace std;

int main(){

	tree::Tree<string> arvere2;
	tree::init(arvere2);	

	cout << tree::insertNode(arvere2, (unsigned int)1232 , string("1232")) << endl;
	cout << tree::insertNode(arvere2, (unsigned int)3000 , string("3000")) << endl;
	cout << tree::insertNode(arvere2, (unsigned int)567 , string("567")) << endl;
	cout << tree::insertNode(arvere2, (unsigned int)570 , string("570")) << endl;
	cout << tree::insertNode(arvere2, (unsigned int)301 , string("301")) << endl;
	cout << tree::insertNode(arvere2, (unsigned int)350 , string("350")) << endl;
	cout << tree::insertNode(arvere2, (unsigned int)2 , string("2")) << endl;

	if(arvere2.root != nullptr) tree::displayTree(arvere2.root);

	//tree::removeAllFrom(tree::findNode(arvere2.root, 567));
	
	cout << "--------------------------------------------------" << endl;
	//cout << tree::findRootNode(arvere2.root, 1232, arvere2.root)->data << endl;
	cout << tree::deleteNode(arvere2.root, 300) << endl;

	cout << "--------------------------------------------------" << endl;
	if(arvere2.root != nullptr) tree::displayTree(arvere2.root);

	return 0;

}
