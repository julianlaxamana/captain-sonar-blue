#include "../include/map.h"
#include "../include/submarine.h"

using namespace std;

//This function will pause the game until the user hits a key and then enter
void pause() {
	cout << "Please press any key and hit enter to continue.\n";
	string temp;
	cin >> temp;
}

//This function will clear the screen
void clear_screen() {
	system("clear");
}

//Thus function will quit the game with an error message
void die() {
	cout << "Invalid input!\n";
	exit(EXIT_FAILURE);
}

//If cin is in an invalid state, this will fix it
void clear_error() {
	cin.clear();
	string s;
	cin >> s;
}



int main() {
	clear_screen();  //Clear the screen
	splash_screen(); //Display the splash screen

	//Phase 1 - Setup
	cout << "How many people are playing? Minimum 2, Maximum 6:\n";
	int players = 2;
	cin >> players; 
	if (!cin || players < 2 || players > 6) die();
	vector<Submarine> subs(players);
	//Player one suffers a health penalty for going first
	subs.at(0).set_health(75);
	for (int i = 0; i < subs.size(); i++) { //Repeat the setup for each player
		cout << "=== Player " << i+1 << " Setup Phase ===\n";
		cout << "Please sit in front of the computer and shoo the other players away.\n";
		pause();         //Wait for them to admire the screen before clearing it
		clear_screen();
		print_map();
		cout << "Please enter your starting location (for example, 'A11' or 'B6'):\n";
		Move starting_location;
		cin >> starting_location.row >> starting_location.column;
		starting_location.row = toupper(starting_location.row); //Change a 'a' to 'A' for ease of use
		if (!cin) die();
		if (!check_map(starting_location)) die(); //They picked a spot on land our outside the map
		cout << "Starting location accepted.\n";
		subs.at(i).set_location(starting_location); //Save the location 
		subs.at(i).add_location(starting_location); //First entry in the history
		pause();
		clear_screen();
	}

	//Phase 2 - Main Loop
	int current_player = -1; //Will immediately become player 0
	while (true) { 
		current_player = (current_player+1) % subs.size(); //Next player's turn
		cout << "=== Player " << current_player+1 << " Turn ===\n";
		cout << "Please sit in front of the computer and shoo the other players away.\n";
		pause();         
		clear_screen();
		print_map(subs.at(current_player).get_location());
		cout << "=== STATUS ===\n";
		int health = subs.at(current_player).get_health();
		if (health >= 75) 
			cout << RED     << "HEALTH     = " << GREEN << health << endl;
		else if (health >= 50)
			cout << RED     << "HEALTH     = " << YELLOW << health << endl;
		else 
			cout << RED     << "HEALTH     = " << health << endl;
		cout << CYAN    << "TORPEDOES  = " << subs.at(current_player).get_torpedoes() << endl;
		cout << MAGENTA << "SENSORS    = " << subs.at(current_player).get_sensors() << endl;
		cout << YELLOW  << "LOCATION   = " << subs.at(current_player).get_location().row << subs.at(current_player).get_location().column << endl;
		cout << RESET;
		//First they get to move their sub
		while (true) {
			cout << "Please enter your move (it must be within one square horizontal and vertical):\n";
			Move new_location;
			cin >> new_location.row >> new_location.column;
			if (!cin) {
				clear_error();
				continue;
			}
			new_location.row = toupper(new_location.row); //Change a 'a' to 'A' for ease of use
			if (!check_map(new_location)) {
				cout << "That is an invalid location, sorry.\n";
				continue;
			}
			//Check to make sure move is within one square in each direction
			if (abs(subs.at(current_player).get_location().row - new_location.row) > 1 || abs(subs.at(current_player).get_location().column - new_location.column) > 1) {
				cout << "Sorry, that position is more than one space away.\n";
				continue;
			}
			cout << "New location accepted.\n";
			subs.at(current_player).set_location(new_location); //Update location 
			subs.at(current_player).add_location(new_location); //Add it to the history
			break;
		}
		//Second they can take an action
		clear_screen();
		print_map(subs.at(current_player).get_location());
		while (true) {
			cout << "Please enter your bonus command:\n";
			cout << "1) Fire a torpedo (blast radius 3).\n";
			cout << "2) Launch a sensor (sensor radius 5).\n";
			cout << "3) Double move (at the cost of 10 health).\n";
			cout << "4) Resupply gear next to a " << RESUPPLY << " space.\n";
			cout << "5) Repair 10 health next to a " << REPAIR << " space.\n";
			cout << "6) Sonar - spy on movement of enemy sub.\n";
			int choice = 0;
			cin >> choice;
			if (!cin) {
				clear_error();
				continue;
			}
			if (choice < 1 || choice > 6) {
				cout << "Invalid choice. Try again.\n";
				continue;
			}
			if (choice == 1 && subs.at(current_player).get_torpedoes() <= 0) {
				cout << "Sorry, you are out of torpedoes. Please resupply.\n";
				continue;
			}
			if (choice == 2 && subs.at(current_player).get_sensors() <= 0) {
				cout << "Sorry, you are out of sensors. Please resupply.\n";
				continue;
			}
			if (choice == 3 && subs.at(current_player).get_health() <= 10) {
				cout << "Sorry, you are too low on health to double move. Please repair.\n";
				continue;
			}
			if (choice == 4 && !check_near(subs.at(current_player).get_location(),RESUPPLY)) {
				cout << "Sorry, you are not near a resupply station.\n";
				continue;
			}
			if (choice == 5 && !check_near(subs.at(current_player).get_location(),REPAIR)) {
				cout << "Sorry, you are not near a repair station.\n";
				continue;
			}
			if (choice == 1) { //FIRE TORPEDOES
				while (true) {
					cout << "Please enter a water location to nuke:\n";
					Move target;
					cin >> target.row >> target.column;
					target.row = toupper(target.row); //Change a 'a' to 'A' for ease of use
					if (!cin) {
						clear_error();
						continue;
					}
					if (!check_map(target)) {
						cout << "That is an invalid location, sorry.\n";
						continue;
					}
					//See who we hit
					int hits = 0;
					for (int i = 0; i < subs.size(); i++) {
						int y_dist = abs(target.row - subs.at(i).get_location().row);
						int x_dist = abs(target.column - subs.at(i).get_location().column);
						int dist = (x_dist > y_dist) ? x_dist : y_dist;
						if (dist <= 2) {
							cout << "Hit on submarine " << i+1 << ": ";
							hits++;
							int damage = 0;
							if (dist == 0)      damage = 75; //Direct hit
							else if (dist == 1) damage = 50; //One away
							else if (dist == 2) damage = 25; //Two away
							subs.at(i).add_health(-damage);
							cout << damage << " inflicted!\n";
							if (subs.at(i).get_health() <= 0) {
								if (current_player == i) {
									cout << "YOU LOST THE GAME BY BLOWING YOURSELF UP. EVERYONE ELSE WINS.\n";
									exit(0);
								}
								else {
									cout << "YOU HAVE DESTROYED AN ENEMY SUB AND WON THE GAME, A WINNER IS YOU.\n";
									exit(0);
								}
							}
						}
					}
					if (hits == 0) cout << "MISSED!\n";
					subs.at(current_player).add_torpedoes(-1);
					break;
				}
			}
			else if (choice == 2) { //FIRE SENSOR
				while (true) {
					cout << "Please enter a water location to launch a sensor at:\n";
					Move target;
					cin >> target.row >> target.column;
					target.row = toupper(target.row); //Change a 'a' to 'A' for ease of use
					if (!cin) {
						clear_error();
						continue;
					}
					if (!check_map(target)) {
						cout << "That is an invalid location, sorry.\n";
						continue;
					}
					//See who we hit
					int hits = 0;
					for (int i = 0; i < subs.size(); i++) {
						if (i == current_player) continue;
						int y_dist = abs(target.row - subs.at(i).get_location().row);
						int x_dist = abs(target.column - subs.at(i).get_location().column);
						int dist = (x_dist > y_dist) ? x_dist : y_dist;
						if (dist <= 5) {
							cout << "Ping on submarine " << i+1 << ": " << dist << " squares away.\n";
							hits++;
						}
					}
					if (hits == 0) cout << "NO SUBS DETECTED!\n";
					subs.at(current_player).add_sensors(-1);
					break;
				}
			}
			else if (choice == 3) { //DOUBLE MOVE
				subs.at(current_player).add_health(-10); //Damages the sub to move fast
				//Move their sub
				while (true) {
					cout << "Please enter your move (it must be within one square horizontal and vertical):\n";
					Move new_location;
					cin >> new_location.row >> new_location.column;
					if (!cin) {
						clear_error();
						continue;
					}
					new_location.row = toupper(new_location.row); //Change a 'a' to 'A' for ease of use
					if (!check_map(new_location)) {
						cout << "That is an invalid location, sorry.\n";
						continue;
					}
					//Check to make sure move is within one square in each direction
					if (abs(subs.at(current_player).get_location().row - new_location.row) > 1 || abs(subs.at(current_player).get_location().column - new_location.column) > 1) {
						cout << "Sorry, that position is more than one space away.\n";
						continue;
					}
					cout << "New location accepted.\n";
					subs.at(current_player).set_location(new_location); //Update location
					subs.at(current_player).add_location(new_location); //Add it to the history
					break;
				}

			}
			else if (choice == 4) {
				subs.at(current_player).set_torpedoes(Submarine::MAX_TORPEDOES);
				subs.at(current_player).set_sensors(Submarine::MAX_SENSORS);
				cout << "Resupplied to full torpedoes and sensors!\n";
			}
			else if (choice == 5) {
				subs.at(current_player).add_health(10);
				cout << "Repaired to " << subs.at(current_player).get_health() << " health!\n";
			}
			else if (choice == 6) {
				int choice = 0;
				while (true) {
					cout << "Which submarine do you wish to follow?\n";
					cin >> choice;
					if (!cin) {
						clear_error();
						continue;
					}
					choice--; //Adjust for the submarines starting at 1 not 0
					if (choice < 0 || choice >= subs.size()) {
						cout << "Invalid choice, please try again.\n";
						continue;
					}
					if (choice == current_player) {
						cout << "You don't need to track yourself, please try again.\n";
						continue;
					}
					break;
				}
				cout << "Your sonar officer reports the following move history for them:\n";
				subs.at(choice).report_history();
			}
			break;
		}
		cout << "=== END OF TURN ===\n";
		pause();
		clear_screen();
	}
}
