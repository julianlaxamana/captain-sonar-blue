#pragma once
#include "move.h"
#include <vector>
#include <iostream>

void die(std::string message);

// ADT style class
class Submarine {
	private:
		//This class will need the following member variables:
		//An int holding health, initialized to 100
		int health = MAX_HEALTH;
		//An int holding its torpedoes, initialized to 10
		int torpedoes = MAX_TORPEDOES;
		//An int holding its sensors, initialized to 3
		int sensors = MAX_SENSORS;
		//Its current position (a Move)
		Move location;
		//A vector of moves called history
		std::vector<Move> history;

	public:
		static const int MAX_HEALTH = 100;
		static const int MAX_TORPEDOES = 6;
		static const int MAX_SENSORS = 3;

		// Default constructor
		Submarine() {
			health = MAX_HEALTH;
			torpedoes = MAX_TORPEDOES;
			sensors = MAX_SENSORS;
		}

		// Getters
		int get_health() { return health; }
		int get_torpedoes() { return torpedoes; }
		int get_sensors() { return sensors; }
		Move get_location() { return location; }
		std::vector<Move> get_history() { return history; }

		// Setters
		void set_health(int new_health) { health = new_health; }
		void set_torpedoes(int new_torpedoes) { torpedoes = new_torpedoes; }
		void set_sensors(int new_sensors) { sensors = new_sensors; }
		void set_location(Move new_location) { location = new_location; }
		void set_history(std::vector<Move> new_history) { history = new_history; }

		//This function will add a move to the history vector
		void add_history(Move new_move) {
			history.push_back(new_move);
		}

		//This function will describe the moves of the sub in terms of north, south, east, etc.
		void report_history() {
			Move current;
			for (int i = 0; i < history.size(); i++) {
				std::cout << "Move " << i+1 << ": ";
				if (i == 0) {
					std::cout << "Start\n";
				}
				else {
					int col_diff = history.at(i).column - current.column; //Positve = east
					int row_diff = current.row - history.at(i).row; //Positive = north
					if (row_diff > 0) std::cout << "North ";
					if (row_diff < 0) std::cout << "South ";
					if (col_diff > 0) std::cout << "East";
					if (col_diff < 0) std::cout << "West";
					if (row_diff == 0 and col_diff == 0) std::cout << "No Movement";
					std::cout << std::endl;
				}
				current = history.at(i);
			}
		}
};
