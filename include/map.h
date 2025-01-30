#pragma once
#include "move.h"
#include "splash.h"

const char RESUPPLY = '*';
const char REPAIR = '.';
const char PLAYER = 'X';

//A map of Ireland and outlying areas
vector<string> ireland = {
"   00000000011111111112222222222 ",
"   12345678901234567890123456789 ",
"  |-----------------------------|",
"A |                             |",
"B |            .  eer           |",
"C |              ed$'           |",
"D |             -'$$$$$P        |",
"E |             e'$$$$P         |",
"F |             eJ$$$F.         |",
"G |          e   * $$$$$r       |",
"H |        .$$$$  ^$$C$$b       |",
"I |      $ed$$$$     $$$$bb     |",
"J |      $$$$$$F      $$$$$     |",
"K |      J$$$$$*   zee$$$$$P    |",
"L |    -J$$$$$$    $$$$$$$$$$$b |",
"M |    ^'$''     4$$$$$$$$$$$*  |",
"N |                .J$d$$$$$e.  |",
"O |               d$P'$$'''''   |",
"P |                             |",
"  |-----------------------------|"
};

//Displays the above in bright radar green
void print_map(Move cur = {}) {
	cout << GREEN;
	//for (string s : ireland) cerr << s << endl;
	int column = 2+cur.column, row = cur.row-'A'+3; //Adjust the offsets in the map so the coordinates line up
	for (int i = 0; i < ireland.size(); i++) {
		for (int j = 0; j < ireland.at(i).size(); j++) {
			if (cur.row != '@' and i == row and j == column) cout << PLAYER;
			else cout << ireland.at(i).at(j);
		}
		cout << endl;
	}

	cout << RESET;
}

//Checks to see if a spot is land or water
//Returns true if water, false if land
bool check_map(Move test, char test_char = ' ') {
	test.row = toupper(test.row);
	if (test.row < 'A' or test.row > 'P') return false; //Bounds check
	if (test.column < 1 or test.column > 29) return false;
	int column = 2+test.column, row = test.row-'A'+3; //Adjust the offsets in the map so the coordinates line up
	if (ireland.at(row).at(column) == test_char) return true;
	return false;
}

//See if our sub is within one map space of the target character, like a resupply or a repair
bool check_near(Move test, char target) {
	if (!check_map(test)) return false; //Make sure their coordinate is valid
	//Check the nine squares around us
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			Move temp = test;
			temp.column += i;
			temp.row += j;
			if (check_map(temp,target)) return true; //If any of them are a * then we can resupply
		}
	}
	return false;
}
