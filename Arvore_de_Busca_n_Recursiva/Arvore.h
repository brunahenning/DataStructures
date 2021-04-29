#include <iomanip>	///For preetting up the output, uncionally irrelevant
#include "Pilha.h"
#include <vector>	///Temporary

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
	void displayTree(Node<T>* node){ //Output is ugly as hell, too bad
		if(node == nullptr) return;
		pil::Pilha<Node<T>*> pilha;
		len::init(pilha.pilha);

		Node<T>* map = node;
		while(map != nullptr || len::qtd_lista(pilha.pilha) > 0){
			while(true){
				if(map != nullptr){
					pil::push(pilha, map);
					map = map->left;
				}
				else break;
			}
			map = pil::pop(pilha);
			std::cout << map->data << " ";
			map = map->right;
		}
		std::cout << std::endl;
	}

	template<typename T>
	Node<T>* findNode(Node<T>* node, unsigned int key){	///Working
		if(node == nullptr) return nullptr;
	
		Node<T>* map = node;
		while(map != nullptr){
			if(isLeaf(map)) return map;
		
			if(key < map->key){
				if(map->left == nullptr) return map;
				map = map->left;
			}else if(key == map->key){
				return map;
			}else{
				if(map->right == nullptr) return map;
				map = map->right;
			}
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

		pil::Pilha<Node<T>*> pilha;
		len::init(pilha.pilha);
		len::L_Enc<Node<T>*> list_d;
		len::init(list_d);

		Node<T>* map = node;
		while(map != nullptr || len::qtd_lista(pilha.pilha) > 0){
			while(true){
				if(map != nullptr){
					pil::push(pilha, map);
					map = map->left;
				}
				else break;
			}
			map = pil::pop(pilha);
			len::insere_inicio(list_d,map);
			map = map->right;
		}

		while(len::qtd_lista(list_d) > 1){
			auto &del = list_d.inicio;
			len::remove_inicio(list_d);
			std::cout << "Deletando: " << del->data->data << std::endl;
			delete del->data;
		}
	}
	

};
