#include <iostream>
#include <sstream>
#include <fstream>

#include "BST.h"


int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	enum TreeSetting { INT, STRING };

	int currentTree;
	BST<int> intBST;
	BST<std::string> stringBST;

	for (std::string line; getline(in, line);) {
		std::string command, itemToImport;
		if (line.empty()) { continue; }
		std::istringstream iss(line);
		iss >> command;
		out << command;

		try {
			if (command == "INT") {
				currentTree = INT;
				intBST.clearTree();
				stringBST.clearTree();
				out << " true";
			}
			if (command == "STRING") {
				currentTree = STRING;
				intBST.clearTree();
				stringBST.clearTree();
				out << " true";
			}

			if (command == "add") {
				iss >> itemToImport;
				out << " " << itemToImport;
				if (currentTree == INT) { //If we are working on int trees now
					if (intBST.addNode(stoi(itemToImport))) { out << " true"; } //add it to the int tree
					else { out << " false"; }
				}
				if (currentTree == STRING) { //If we are working on string trees now
					if (stringBST.addNode(itemToImport)) { out << " true"; } //add it to the string tree
					else { out << " false"; }
				}
			}

			if (command == "remove") {
				iss >> itemToImport;
				out << " " << itemToImport;
				if (currentTree == INT) {
					if (intBST.removeNode(stoi(itemToImport))) { out << " true"; }
					else { out << " false"; }
				}
				if (currentTree == STRING) {
					if (stringBST.removeNode(itemToImport)) { out << " true"; }
					else { out << " false"; }
				}
			}

			if (command == "clear") {
				if (currentTree == INT) {
					intBST.clearTree();
				}
				if (currentTree == STRING) {
					stringBST.clearTree();
				}
				out << " true";
			}

			if (command == "size") {
				if (currentTree == INT) {
					out << " " << intBST.size();
				}
				if (currentTree == STRING) {
					out << " " << stringBST.size();
				}
			}

			if (command == "print") {
				out << ":";
				if (currentTree == INT) {
					if (intBST.size() != 0) { out << intBST; }
					else { out << " empty"; }
				}
				if (currentTree == STRING) {
					if (stringBST.size() != 0) { out << stringBST; }
					else { out << " empty"; }
				}
			}

			if (command == "find") {
				iss >> itemToImport;
				out << " " << itemToImport;
				if (currentTree == INT) {
					if (intBST.search(stoi(itemToImport))) { out << " found"; }
					else { out << " not found"; }
				}
				if (currentTree == STRING) {
					if (stringBST.search(itemToImport)) { out << " found"; }
					else { out << " not found"; }
				}
			}

			if (command == "tree") {
				out << ":";
				if (currentTree == INT) {
					if (intBST.size() != 0) {
						BST<int>::Iterator iter = intBST.begin();
						while (!iter.isEnd()) {
							out << " " << *iter;
							++iter;
						}
					}
					else { out << " empty"; }
				}
				if (currentTree == STRING) {
					if (stringBST.size() != 0) {
						BST<std::string>::Iterator iter = stringBST.begin();
						while (!iter.isEnd()) {
							out << " " << *iter;
							++iter;
						}
					}
					else { out << " empty"; }
				}
			}
		}
		catch (std::string e) { out << " " << e; }
		out << std::endl;
	}

	in.close();
	out.close();

	return 0;
}
