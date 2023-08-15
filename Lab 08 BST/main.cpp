#include <iostream>
#include <sstream>
#include <fstream>

#include "BST.h"


int main(int argc, char* argv[]) {
	//the usual junk
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	//ok--I'm so fed up with figuring out scope issues.
	//I know there is an easier way to do this by my tired brain got no dice.
	//If you know a better/more efficient way to do this please let me know.
	//I'll highlight the bits I am totally lost on.
	BST<int> intBST;
	BST<std::string> stringBST;

	for (std::string line; getline(in, line);) {
		std::string command, itemToImport;
		if (line.empty()) { continue; }
		std::istringstream iss(line);
		iss >> command;
		out << command;

		//like here--can you reconfigure a templated object? like
		//first tree is an <int>. Can you reassign the same tree to be a <string>?
		//Or do you have to chuck it and make a new one?
		//I ended up just juggling two trees and figuring out which one the person was using at the time.
		//Very inefficiently.
		if (command == "INT") {
			intBST.clearTree();
			stringBST.clearTree();
			out << " true";
		}
		if (command == "STRING") {
			intBST.clearTree();
			stringBST.clearTree();
			out << " true";
		}

		if (command == "add") {
			iss >> itemToImport;
			out << " " << itemToImport;
			if (isdigit(itemToImport.at(0))) { //If the input is a digit
				if (intBST.addNode(stoi(itemToImport))) { out << " true"; } //add it to the int tree
				else { out << " false"; }
			}
			else { //else
				if (stringBST.addNode(itemToImport)) { out << " true"; } //add it to the string tree
				else { out << " false"; }
			}
		} /**In retrospect I'm thinking it would be easier to just have a variable that switches
 * 			depending on whether the current tree is an INT or a STRING.
 * 			That would save a lot of checks.
 * 			Oh well. Too lazy to change it now.*/

		if (command == "remove") {
			iss >> itemToImport;
			out << " " << itemToImport;
			if (isdigit(itemToImport.at(0))) { //same kind of deal--if it's a number, int tree; otherwise string tree
				if (intBST.removeNode(stoi(itemToImport))) { out << " true"; }
				else { out << " false"; }
			}
			else {
				if (stringBST.removeNode(itemToImport)) { out << " true"; }
				else { out << " false"; }
			}
		}

		if (command == "clear") {
			intBST.clearTree(); //Yeah, I'm feeling more stupid by the minute. The INT/STRING variable would've been a lot easier.
			stringBST.clearTree();
			out << " true";
		}

		if (command == "size") {
			int size = intBST.size();
			if (size != 0) { //Sorry you have to read all of these awkward checks
				out << " " << size;
			}
			else {
				out << " " << stringBST.size();
			}
		}

		if (command == "print") {
			out << ":";
			if (intBST.size() != 0) { out << intBST; }
			else if (stringBST.size() != 0) { out << stringBST; }
			else { out << " empty"; }
		}

		if (command == "find") {
			iss >> itemToImport;
			out << " " << itemToImport;
			if (isdigit(itemToImport.at(0))) {
				if (intBST.search(stoi(itemToImport))) { out << " found"; }
				else { out << " not found"; }
			}
			else {
				if (stringBST.search(itemToImport)) { out << " found"; }
				else { out << " not found"; }
			}
		}

		if (command == "tree") {
			out << ":";
			if (intBST.size() != 0) {
				BST<int>::Iterator iter = intBST.begin();
				BST<int>::Iterator endIter = intBST.end();
				while (iter != endIter) { //Oh it looks SO SIMPLE now, does it
					out << " " << *iter;
					++iter;
				}
			}
			else if (stringBST.size() != 0) {
				BST<std::string>::Iterator iter = stringBST.begin(); //like this--do I have to declare an <string> iterator?
				BST<std::string>::Iterator endIter = stringBST.end(); //Or can you reuse the <int> one somehow?
				while (iter != endIter) {
					out << " " << *iter;
					++iter;
				}
			}
			else { out << " empty"; }
		}
		out << std::endl;
	}

	in.close();
	out.close();

	return 0;
}
