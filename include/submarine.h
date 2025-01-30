#pragma once
#include "move.h"
#include <vector>
#include <iostream>

void die();

//PODS style class
class Submarine {
		//This class will need the following member variables:
		//An int holding health, initialized to 100
		int health;
		//An int holding its torpedoes, initialized to 10
		int torpedoes;
		//An int holding its sensors, initialized to 3
		int sensors;
		//Its current position (a Move)
		Move location;
		//A vector of moves called history
		std::vector<Move> history;
	public:
		static const int MAX_HEALTH = 100;
		static const int MAX_TORPEDOES = 6;
		static const int MAX_SENSORS = 3;
		//This function will describe the moves of the sub in terms of north, south, east, etc.
		Submarine(){
			this->set_health(MAX_HEALTH);
			this->set_torpedoes(MAX_TORPEDOES);
			this->set_sensors(MAX_SENSORS);
		}
		Submarine(int health){
			this->set_health(health);
			this->set_torpedoes(MAX_TORPEDOES);
			this->set_sensors(MAX_SENSORS);
		}
		Submarine(int health, int torpedoes){
			this->set_health(health);
			this->set_torpedoes(torpedoes);
			this->set_sensors(MAX_SENSORS);
		}
		Submarine(int health, int torpedoes, int sensors){
			this->set_health(health);
			this->set_torpedoes(torpedoes);
			this->set_sensors(sensors);
		}

		// SETTERS
		void set_health(int health){
			if (health > MAX_HEALTH){
				this->health = MAX_HEALTH;
			} else if (health < 0){
				this->health = 0;
			} else 
				this->health = health;
		}		
		void set_torpedoes(int torpedoes){
			if (torpedoes > MAX_TORPEDOES || torpedoes < 0){
				die();
			}
			this->torpedoes = torpedoes;
		}
		void set_sensors(int sensors){
			if (sensors > MAX_SENSORS || sensors < 0){
				die();
			}
			this->sensors = sensors;
		}
		void set_location(Move location){
			this->location = location;
		}
		void add_location(Move move){
			history.push_back(move);
		}
		void add_health(int health){
			set_health(this->health + health);
		}
		void add_sensors(int sensors){
			set_health(this->sensors + sensors);
		}
		void add_torpedoes(int torpedoes){
			set_health(this->torpedoes + torpedoes);
		}


		// GETTERS
		int get_health() const {
			return this->health;
		}	
		int get_torpedoes() const {
			return this->torpedoes;
		}	
		int get_sensors() const {
			return this->sensors;
		}	
		Move get_location() const {
			return this->location;
		}	

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
