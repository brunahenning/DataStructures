#include <iomanip>	///For preetting up the output, uncionally irrelevant

template<typename T>
struct Node{
	unsigned int key;
	T data;
	Node<T> *left;
	Node<T> *right;
};

namespace tree{

	template<typename T>
	struct Tree{
		Node<T> *root;
	};

	template<typename T>
	void init(Tree<T> &tree){
		tree.root = nullptr;
	}

	template<typename T>
	bool isLeaf(Node<T>* node){
		if(node->right == nullptr && node->left == nullptr) return 1;
		return 0;
	}

	template<typename T>
	void displayTree(Node<T>* node, unsigned int indent = 0){
		if(node == nullptr) return;

		displayTree(node->right, indent + 4);
		if(indent > 0) std::cout << std::setw((int)indent) << " ";
		std::cout << node->data << std::endl;
		displayTree(node->left, indent + 4);

	}

	template<typename T>
	Node<T>* findNode(Node<T>* node, unsigned int key){	///Working
		if(node == nullptr) return nullptr;
		if(isLeaf(node)) return node;	///Trying never to return null

		if(key < node->key){
			if(node->left == nullptr) return node;
			return findNode(node->left , key);
		}else if(node->key == key){
			return node;
		}else{
			if(node->right == nullptr) return node;
			return findNode(node->right, key);
		}

	}

	template<typename T>
	Node<T>* findRootNode(Node<T>* node, unsigned int key, Node<T>* backUpNode){	///Working
		if(node == nullptr) return nullptr;
		if(isLeaf(node) && (node->key == key)){
			return backUpNode;
		}else if( isLeaf(node) && (node->key != key)){
			return nullptr;
		}


		if(key < node->key){
			if(node->left == nullptr) return backUpNode;
			return findRootNode(node->left , key, node);
		}else if(node->key == key){
			return backUpNode;
		}else{
			if(node->right == nullptr) return backUpNode;
			return findRootNode(node->right, key, node);
		}

	}

	template<typename T>
	bool insertNode(Tree<T>& tree, unsigned int key, T data){

		
		Node<T>* newNode = new Node<T>;
		newNode->key = key;
		newNode->data = data;
		newNode->left = nullptr;
		newNode->right = nullptr;

		if(tree.root == nullptr){
			tree.root = newNode;
			return 1;	
		}

		Node<T>* foundNode = findNode(tree.root, key);
		if(foundNode == nullptr){
			std::cerr << "Node not found" << std::endl;
			return 0;
		}

		if(key < foundNode->key){
			foundNode->left = newNode;
		}else if(foundNode->key == key){
			return 0;	///Cant replace like that
		}else{
			foundNode->right = newNode;
		}
		return 1;

	}

	template<typename T>
	void removeAllFrom(Node<T>* node){
		if(node == nullptr) return;

		if(node->left != nullptr){
			removeAllFrom(node->left);
			delete node->left;
		}

		if(node->right != nullptr){
			removeAllFrom(node->right);
			delete node->right;
		}

	}

	template<typename T>
	bool deleteNode(Node<T>* treeNode, unsigned int key){
		if(treeNode == nullptr) return 0;

		if(treeNode->key == key){
			if(treeNode->left != nullptr){
				std::cout << "left\n";
				treeNode = treeNode->left;
				return 1;
			}
			if(treeNode->right != nullptr){
				std::cout << "right\n";
				treeNode = treeNode->right;
				return 1;
			}
		}

		Node<T>* rootNode = findRootNode(treeNode, key, treeNode);
		///Has root node, but no idea wich way to go
		if(rootNode == nullptr) return 0;

		std::cout << "rootNode: " << rootNode->data << std::endl;

		Node<T>* problemNode;
		if(rootNode->left->key == key){
			problemNode = rootNode->left;
			if(problemNode->left != nullptr){
				rootNode->left = problemNode->left;
			}else{
				rootNode->left = problemNode->right;
			}	
		}else if(rootNode->right->key == key){
			problemNode = rootNode->right;
			if(problemNode->left != nullptr){
				rootNode->right = problemNode->left;
			}else{
				rootNode->right = problemNode->right;
			}	
		}
			
		delete problemNode;
		return 1;
	}
	

};
