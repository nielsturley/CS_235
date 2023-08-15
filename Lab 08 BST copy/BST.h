#ifndef LAB_09_POKEMON_BST_H
#define LAB_09_POKEMON_BST_H

#include "Stack.h"

template<typename T>
class BST {
private:

	struct Node {
		Node(T d) : data(d), leftChild(nullptr), rightChild(nullptr) {}
		~Node() {}
		T data;
		Node* leftChild;
		Node* rightChild;
	};
	Node* root_;
public:
	BST() { this->root_ = nullptr; }
	~BST() { clearTree(); }

	class Iterator {
	private:
		Stack<Node*> stack;
	public:
		Iterator(Node* root) {
			Node* curr = root;
			while (curr != nullptr) {
				stack.push(curr);
				curr = curr->leftChild;
			}
		}
		~Iterator() {}

		bool operator!= (const Iterator& rhs) const {
			if (stack.top() != rhs.stack.top()) { return true; }
			else { return false; }
		}

		void operator++() {
			Node* curr = stack.top()->rightChild;
			stack.pop();
			while (curr != nullptr) {
				stack.push(curr);
				curr = curr->leftChild;
			}
		}

		T operator*() const {
			if (!stack.empty()) { return stack.top()->data; }
			else { throw std::string("Stack is empty!"); }
		}

		std::string toString() const {
			if (!stack.empty()) { return stack.top()->data; }
			else { throw std::string("Stack is empty!"); }
		}
		friend std::ostream& operator<< (std::ostream& os, const Iterator& iter) {
			os << iter.toString();
			return os;
		}
		bool isEnd() const { return stack.empty(); }
	};

	/**return the leftmost node*/
	Iterator begin() const {
		Node* node = root_;
		return Iterator(node);
	}

	/**recursively add a node to the right spot in the tree*/
	bool addNode(const T& data) {
		return recAddNode(root_, data);
	}
	bool recAddNode(Node*& node, const T& data) {
		if (node == nullptr) {
			node = new Node(data);
			return true;
		}
		if (data == node->data) { return false; }
		if (data < node->data) { return recAddNode(node->leftChild, data); }
		if (data > node->data) { return recAddNode(node->rightChild, data); }
		return false;
	}

	/**recursively find the node with the data you want to remove*/
	bool removeNode(const T& data) {
		return recRemoveNode(root_, data);
	}
	bool recRemoveNode(Node*& node, const T& data) {
		if (node == nullptr) { return false; }
		if (data < node->data) { return recRemoveNode(node->leftChild, data); }
		if (data > node->data) { return recRemoveNode(node->rightChild, data); }

		Node* oldNode = node;
		if (node->leftChild == nullptr) { node = node->rightChild; }
		else if (node->rightChild == nullptr) { node = node->leftChild; }
		else {
			Node *inOrderPredecessor = node->leftChild;
			while (inOrderPredecessor->rightChild != nullptr) {
				inOrderPredecessor = inOrderPredecessor->rightChild;
			}
			std::swap(node->data, inOrderPredecessor->data);
			recRemoveNode(node->leftChild, data);
			return true;
		}
		delete oldNode;
		return true;
	}

	/**search for a data value, true if found*/
	bool search(const T& data) {
		bool found = false;
		recSearch(root_, data, found);
		return found;
	}
	void recSearch(Node*& node, const T& data, bool& found) {
		if (found) { return; }
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
		if (node == nullptr) { return; }
		recClearTree(node->leftChild);
		recClearTree(node->rightChild);
		delete node;
		node = nullptr;
	}

	/**return int size of the tree*/
	int size() const {
		return recSize(root_);
	}
	int recSize(Node* node) const {
		if (node == nullptr) { return 0; }
		else {
			return (recSize(node->leftChild) + 1 + recSize(node->rightChild));
		}
	}

	/**output each level of the tree*/
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
#endif
