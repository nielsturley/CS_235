#ifndef LAB_08_BST_BST_H
#define LAB_08_BST_BST_H

#include "BSTInterface.h"

//You know, I thought linked lists were kinda tough.
//But I lied. I'd take a linked list over BST any day.
template<typename T>
class BST : public BSTInterface<T> {
private:
	//I feel like we are family now, me and my nodes.
	//We've been through a lot together.
	struct Node {
		Node(T d, Node* p) : data(d), parent(p), leftChild(nullptr), rightChild(nullptr) {}
		~Node() {}
		T data;
		Node* parent; //you will notice this lovely addition of a parent pointer. I'll explain in the operator++ iterator function.
		Node* leftChild;
		Node* rightChild;
	};
	Node* root_;
public:
	BST() { this->root_ = nullptr; }
	~BST() { clearTree(); }

	//Joke: how are iterators like your ex?
	//Answer: because after you get over IT, YUR HATE HER
	class Iterator {
	private:
		Node* root;
		Node* iNode;
	public:
		Iterator(Node* node) : iNode(node) {}
		Iterator(Node* node, Node* root_) {
			iNode = node;
			root = root_;//sometimes, you just want a root_ passed in.
							//because NESTED CLASSES can't access PRIVATE VARIABLES unless they are STATIC
							//DUH
		}
		~Iterator() {}

		bool operator!= (const Iterator& rhs) const {
			if (iNode != rhs.iNode) { return true; }
			else { return false; }
		}

		Iterator& operator++() { //oooo how I hated this one.
			if (iNode == nullptr) {
				//Go left as far as you can from the root
				iNode = root;
				while (iNode->leftChild != nullptr) {
					iNode = iNode->leftChild;
				}
			}
			else {
				if (iNode->rightChild != nullptr) {
					//Go right, then go left as far as you can
					iNode = iNode->rightChild;
					while (iNode->leftChild != nullptr) {
						iNode = iNode->leftChild;
					}
				}
				else {
					/**Introducing the parent pointer:
					 * Apparently the only way to iterate in-order is either to have a stack
					 * (to keep track of where you have been before) or a parent pointer
					 * (so you can go back up the tree). I spent a ~very~ ~long~ time without this
					 * piece of information. It was not pleasant.*/
					Node* par = iNode->parent;
					while (par != nullptr && iNode == par->rightChild) { //if you can go back up the tree and the node is a right child
						iNode = par; //scoot up
						par = par->parent;
					}
					iNode = par; //now you are one the next branch to go down.
				}
			}
			return *this;
		}

		T operator*() const { return iNode->data; }

		std::string toString() const {
			return iNode->data;
		}
		friend std::ostream& operator<< (std::ostream& os, const Iterator& iter) {
			os << iter.toString();
			return os;
		}
	};

	/**return the leftmost node*/
	Iterator begin() const {
		Node* node = root_;
		if (node != nullptr) {
			if (node->leftChild != nullptr) {
				while (node->leftChild != nullptr) {
					node = node->leftChild;
				}
			}
		}
		return Iterator(node, root_);
	}
	/**return nullptr to signify the end*/
	Iterator end() const {
		return Iterator(nullptr);
	}

	/**recursively add a node to the right spot in the tree*/
	bool addNode(const T& data) {
		return recAddNode(root_, nullptr, data);
	}
	bool recAddNode(Node*& node, Node* par, const T& data) { //recursion makes my head hurt
		if (node == nullptr) {
			node = new Node(data, par); //I hate new. I always get memory leaks and it's all because of this guy.
			return true;
		}
		if (data == node->data) { return false; }
		if (data < node->data) { return recAddNode(node->leftChild, node, data); }
		if (data > node->data) { return recAddNode(node->rightChild, node, data); }

		return false;
	}

	/**recursively find the node with the data you want to remove
	 * hate this one too*/
	bool removeNode(const T& data) {
		return recRemoveNode(root_, data);
	}
	bool recRemoveNode(Node*& node, const T& data) {
		if (node == nullptr) { return false; }
		if (data < node->data) { return recRemoveNode(node->leftChild, data); }
		if (data > node->data) { return recRemoveNode(node->rightChild, data); }
		if (node->leftChild == nullptr && node->rightChild == nullptr) { //has no children
			//see how easy this is? I wonder what kind of political statement that makes.
			//Maybe AIs will decide that children are pointless.
			//Get it? POINTless
			//Like, deleting the POINTer
			//I'll leave now
			delete node;
			node = nullptr;
			return true;
		}
		if (node->leftChild != nullptr && node->rightChild == nullptr) { //has left child
			//become the left child
			//This is kind of like cannibalism
			Node* tempNode = node;
			node->data = node->leftChild->data;
			node->rightChild = node->leftChild->rightChild;
			node->leftChild = node->leftChild->leftChild;
			delete tempNode;
			return true;
		}
		if (node->rightChild != nullptr && node->leftChild == nullptr) { //has right child
			//become the right child
			Node* tempNode = node;
			node->data = node->rightChild->data;
			node->leftChild = node->rightChild->leftChild;
			node->rightChild = node->rightChild->rightChild;
			delete tempNode;
			return true;
		}
		//has two children
		Node* inOrderPredecessor = node->leftChild;
		while (inOrderPredecessor->rightChild != nullptr) {
			inOrderPredecessor = inOrderPredecessor->rightChild;
		}
		T tempData = node->data;
		node->data = inOrderPredecessor->data;
		inOrderPredecessor->data = tempData; //switch data with inorder processor
		return recRemoveNode(node->leftChild, data); //and do it again!
	}

	/**search for a data value, true if found*/
	bool search(const T& data) {
		bool found = false; //? Why didn't you just make the recSearch function return a bool?
		recSearch(root_, data, found);
		return found; //Answer: Because it wasn't working. And I didn't know how to fix it. So I did this instead
	}                   //and now it works. You judging?
	void recSearch(Node*& node, const T& data, bool& found) {
		if (found) { return; } //because it's FOUND dang it. Hate recursion.
		if (node == nullptr) { return; }
		if (node->data == data) {
			found = true;
			return;
		}
		if (data < node->data) { recSearch(node->leftChild, data, found); }
		if (data > node->data) { recSearch(node->rightChild, data, found); }

	}

	/**empty the tree*/
	bool clearTree() {
		recClearTree(root_);
		root_ = nullptr;
		return true;
	}
	void recClearTree(Node*& node) {
		if (node != nullptr) {
			if (node->leftChild != nullptr) { recClearTree(node->leftChild); }
			if (node->rightChild != nullptr) { recClearTree(node->rightChild); }
			delete node;
		}
	}

	/**return int size of the tree
	 * first time the iterators proved mildly useful*/
	int size() const {
		return recSize(root_);
	}
	int recSize(Node* node) const {
		if (node == nullptr) { return 0; }
		else {
			return (recSize(node->leftChild) + 1 + recSize(node->rightChild));
		}
	}

	/**output each level of the tree
	 * being honest here, I have only the faintest idea what is going on*/
	bool outLevel(Node* node, int level, std::stringstream& out) const {
		if (node == nullptr) { return false; }
		if (level == 1) {
			out << " " << node->data;
			if ((node->leftChild != nullptr) || (node->rightChild != nullptr)) { return true; }
			return false;
		}
		if ((level == 2) && (node->leftChild == nullptr) && (node->rightChild != nullptr)) { out << " _"; }
		bool left = outLevel(node->leftChild, level - 1, out);
		bool right = outLevel(node->rightChild, level - 1, out);
		if ((level == 2) && (node->leftChild != nullptr) && (node->rightChild == nullptr)) { out << " _"; }
		return left || right;
	}

	std::string toString() const {
		std::stringstream out;
		int level = 0;
		do {
			out << std::endl << "  " << ++level << ":";
		}
		while (outLevel(root_, level, out));
		return out.str();
	}

	friend std::ostream& operator<< (std::ostream& os, const BST& bst) {
		os << bst.toString();
		return os;
	}
};
#endif //LAB_08_BST_BST_H
