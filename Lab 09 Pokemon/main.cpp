#include <iostream>
#include <fstream>
#include <sstream>

#include "HashMap.h"

int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	//declarations
	Set<std::string> set;
	HashMap<std::string, std::string> pokemon;
	HashMap<std::string, std::string> moves;
	HashMap<std::string, Set<std::string>> effectivities;
	HashMap<std::string, Set<std::string>> ineffectivities;

	//command input
	for (std::string line; getline(in, line);) {
		std::string command, itemToImport;
		if (line.empty()) { continue; }
		std::istringstream iss(line);
		iss >> command;
		try {
			if (command == "Set:") {
				out << line;
				set.clear();
				std::stringstream output;
				while (iss >> itemToImport) {
					set.insert(itemToImport);
				}
				out << std::endl;
				out << "  [" << set << "]" << std::endl;
			}
			if (command == "Pokemon:") {
				out << line;
				iss >> itemToImport;
				std::string first = itemToImport;
				iss >> itemToImport;
				std::string second = itemToImport;
				pokemon[first] = second;
			}
			if (command == "Pokemon") {
				out << std::endl;
				out << "Pokemon: " << pokemon.size() << "/" << pokemon.max_size() << std::endl;
				out << pokemon;
			}
			if (command == "Move:") {
				out << line;
				iss >> itemToImport;
				std::string first = itemToImport;
				iss >> itemToImport;
				std::string second = itemToImport;
				moves[first] = second;
			}
			if (command == "Moves") {
				out << std::endl;
				out << "Moves: " << moves.size() << "/" << moves.max_size() << std::endl;
				out << moves;
			}
			if (command == "Effective:") {
				out << line;
				iss >> itemToImport;
				std::string first = itemToImport;
				while (iss >> itemToImport) {
					std::string second = itemToImport;
					effectivities[first].insert(second);
				}
			}
			if (command == "Effectivities") {
				out << std::endl;
				out << "Effectivities: " << effectivities.size() << "/" << effectivities.max_size() << std::endl;
				out << effectivities;
			}
			if (command == "Ineffective:") {
				out << line;
				iss >> itemToImport;
				std::string first = itemToImport;
				while (iss >> itemToImport) {
					std::string second = itemToImport;
					ineffectivities[first].insert(second);
				}
			}
			if (command == "Ineffectivities") {
				out << std::endl;
				out << "Ineffectivities: " << ineffectivities.size() << "/" << ineffectivities.max_size() << std::endl;
				out << ineffectivities;
			}
			if (command == "Battle:") {
				out << line << std::endl;
				std::string firstPokemon, secondPokemon, firstMove, secondMove;
				iss >> firstPokemon >> firstMove >> secondPokemon >> secondMove;
				out << "  " << firstPokemon << " (" << firstMove << ") vs " << secondPokemon << " (" << secondMove << ")" << std::endl;

				out << "  " << firstPokemon << " is a " << pokemon[firstPokemon] << " type Pokemon." << std::endl;
				out << "  " << secondPokemon << " is a " << pokemon[secondPokemon] << " type Pokemon." << std::endl;
				out << "  " << firstMove << " is a " << moves[firstMove] << " type move." << std::endl;
				out << "  " << secondMove << " is a " << moves[secondMove] << " type move." << std::endl;


				out << "  " << firstMove << " is super effective against [" << effectivities[moves[firstMove]] << "] type Pokemon." << std::endl;
				out << "  " << firstMove << " is ineffective against [" << ineffectivities[moves[firstMove]] << "] type Pokemon." << std::endl;
				int damageOnSecond = effectivities[moves[firstMove]].count(pokemon[secondPokemon]) - ineffectivities[moves[firstMove]].count(pokemon[secondPokemon]);
				if (damageOnSecond == 0) { out << "  " << firstPokemon << "'s " << firstMove << " is effective against " << secondPokemon << std::endl; }
				if (damageOnSecond == 1) { out << "  " << firstPokemon << "'s " << firstMove << " is super effective against " << secondPokemon << std::endl;}
				if (damageOnSecond == -1) { out << "  " << firstPokemon << "'s " << firstMove << " is ineffective against " << secondPokemon << std::endl;}

				out << "  " << secondMove << " is super effective against [" << effectivities[moves[secondMove]] << "] type Pokemon." << std::endl;
				out << "  " << secondMove << " is ineffective against [" << ineffectivities[moves[secondMove]] << "] type Pokemon." << std::endl;
				int damageOnFirst = effectivities[moves[secondMove]].count(pokemon[firstPokemon]) - ineffectivities[moves[secondMove]].count(pokemon[firstPokemon]);
				if (damageOnFirst == 0) { out << "  " << secondPokemon << "'s " << secondMove << " is effective against " << firstPokemon << std::endl; }
				if (damageOnFirst == 1) { out << "  " << secondPokemon << "'s " << secondMove << " is super effective against " << firstPokemon << std::endl;}
				if (damageOnFirst == -1) { out << "  " << secondPokemon << "'s " << secondMove << " is ineffective against " << firstPokemon << std::endl;}

				if ((damageOnFirst - damageOnSecond) == 0) {
					out << "  The battle between " << firstPokemon << " and " << secondPokemon << " is a tie." << std::endl;
				}
				if ((damageOnFirst - damageOnSecond) > 0) {
					out << "  In the battle between " << firstPokemon << " and " << secondPokemon << ", " << secondPokemon << " wins!" << std::endl;
				}
				if ((damageOnFirst - damageOnSecond) < 0) {
					out << "  In the battle between " << firstPokemon << " and " << secondPokemon << ", " << firstPokemon << " wins!" << std::endl;
				}
			}
		}
		catch (std::string e) { out << " " << e; }
		out << std::endl;

	}

	return 0;
}
