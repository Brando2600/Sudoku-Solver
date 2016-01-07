/*
Made by Brandon Flynn

This program solves sudoku puzzles.


TODO: Consider bringing the conflict detection to the user input phase.

*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Box.h"
#include "Functions.h"
using namespace std;



int main()
{
	//create boxes
	Box box[9][9];
	createGrid(box);
	solve(box);

	//
	std::cin.sync();
	std::cin.get();

	return 0;
}