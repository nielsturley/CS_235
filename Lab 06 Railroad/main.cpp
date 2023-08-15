#include <iostream>
#include <fstream>
#include <sstream>

#include "Car.h"
#include "Station.h"

//I love how this lab is all about reusing code and efficiency, and it still took me just as long to finish
int main(int argc, char* argv[]) {
	//all the usual stuff--open files, read files, do the comman
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
	Station<Car> station;
    std::string line, command;
    while (getline(in, line)) {
        try {
            if (line.size() == 0) continue;
            out << line;
            std::istringstream iss(line);
            iss >> command;
            if (command.find("Add") != std::string::npos) {
            	if (command.find("station") != std::string::npos) { //I'm using the "find" command because it works. I'm kinda a sucker for things that work.
            		std::string id;
            		iss >> id;
            		station.addStation(Car(stoi(id))); //Wow. All to get that stupid unsigned int into the station
            	}                                               //Ever feel like you are trying to put a square peg in a round hole for this class?
            	else if (command.find("queue") != std::string::npos) {
					station.addQueue();
	            }
            	else if (command.find("stack") != std::string::npos) {
					station.addStack();
	            }
                out << " OK";
            }
            else if (command.find("Remove") != std::string::npos) {
            	if (command.find("station") != std::string::npos) {
            		station.addTrain();
            	}
            	else if (command.find("queue") != std::string::npos) {
            		station.removeQueue();
            	}
            	else if (command.find("stack") != std::string::npos) {
            		station.removeStack();
            	}
                out << " OK";
            }
            else if (command.find("Top") != std::string::npos) {
            	if (command.find("station") != std::string::npos) {
            		out << " " << station.topStation();
            	}
	            else if (command.find("queue") != std::string::npos) {
	            	out << " " << station.topQueue();
	            }
	            else if (command.find("stack") != std::string::npos) {
	            	out << " " << station.topStack();
	            }
            }
            else if (command.find("Size") != std::string::npos) {
	            if (command.find("queue") != std::string::npos) {
	            	out << " " << station.sizeQueue();
	            }
	            else if (command.find("stack") != std::string::npos) {
	            	out << " " << station.sizeStack();
	            }
	            else if (command.find("train") != std::string::npos) {
	            	out << " " << station.sizeTrain();
	            }
            }
            else if (command == "Queue") {
            	out << station.queue();
            }
            else if (command == "Stack") {
                out << station.stack();
            }
            else if (command == "Train") {
                out << station.train();
            }
            else if (command == "Find") {
	            std::string id;
	            iss >> id;
	            Car newCar = Car(stoi(id));
	            out << " " << station.find(newCar);
            }
        }
        catch (std::string& e) {
        	if (e.find("Deque") != std::string::npos) {             //My deque class throws the errors usually, so I wasn't sure how to make it specifically "stack" or "queue"
        		if (command.find("queue") != std::string::npos) {   //ended up just using the actual command and inferring the error from there
        			out << " Queue empty!";
        		}
        		else if (command.find("stack") != std::string::npos) {
        			out << " Stack empty!";
        		}
        	}
        	else {
		        out << " " << e; //all other errors (i.e. "Turntable empty!") come out here
        	}
        }
        out << std::endl;
    }

    in.close();
    out.close();

    return 0;
}
