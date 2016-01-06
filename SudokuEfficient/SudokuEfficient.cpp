/*
Made by Brandon Flynn

This program solves sudoku puzzles.


TODO: Consider bringing the conflict detection to the user input phase.

*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h> //_getch()
#include "Box.h"
using namespace std;



int main()
{
	//create boxes
	Box box[9][9];
	int input = -5;
	bool loopIt = true;




	//Enter values
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			//Display
			for (int X = 0; X < 9; X++)
			{
				for (int Y = 0; Y < 9; Y++)
				{

					if (x == X && y == Y)
					{
						cout << "x";
						cout << "  ";
					}

					else if (box[X][Y].value != 0)
					{
						cout << box[X][Y].value;
						cout << "  ";

					}

					else if (box[X][Y].value == 0)
					{
						cout << "-";
						cout << "  ";
					}
					if (Y == 2 || Y == 5)
					{
						cout << " | ";
					}
				}
				cout << endl;
				if (X == 2 || X == 5)
				{
					cout << "--------------------------------" << endl;
				}

			}

			cout << "This program assumes that you have entered a valid sudoku puzzle." << endl << endl;;
			cout << "Please fill the puzzle with numbers from 1 to 9" << endl;
			cout << "Use zeros to represent blanks." << endl;
			cout << "Hit backspace to go back" << endl;

			input = _getch() - '0'; //Get user input on key press

			system("cls");

			if (input >= 0 && input <= 9) //If user entered a number
			{
				box[x][y].value = input;
				loopIt = false;
			}

			else if (input == -40) // ASCII -40 is backspace
			{
				loopIt = false;
				if (input == -40 && x == 0 && y == 0) //Do not move back if we are on the first square
				{
					if (y == 0)
					{
						y = 8;
						x--;
					}
					else if (y >= 1 && y < 9)
					{
						y--;
					}
				}
				else
				{
					//This will take us back one square
					if (y == 0)
					{
						y = 7;
						x--;
					}
					else if (y >= 1 && y < 9)
					{
						y--;
						y--;
					}
				}
			}

			else //If invalid input
			{
				if (y == 0)
				{
					y = 8;
					x--;
				}

				else if (y >= 1 && y < 9)
				{
					y--;
				}
			}

			
		}
	}

	//Give boxes a grid value
	for (int x = 0; x <= 9; x++)
	{
		for (int y = 0; y <= 9; y++)
		{

			if (x + 1 <= 3 && y + 1 <= 3)
			{
				box[x][y].grid = 1;
			}

			else if (x + 1 <= 3 && y + 1 < 7 && y + 1 > 3)
			{
				box[x][y].grid = 2;
			}

			else if (x + 1 <= 3 && y + 1 > 6)
			{
				box[x][y].grid = 3;
			}

			else if (x + 1 > 3 && x + 1 < 7 && y + 1 < 4)
			{
				box[x][y].grid = 4;
			}

			else if (x + 1 > 3 && x + 1 < 7 && y + 1 > 3 && y + 1 < 7)
			{
				box[x][y].grid = 5;
			}

			else if (x + 1 > 3 && x + 1 < 7 && y + 1 > 6)
			{
				box[x][y].grid = 6;
			}

			else if (x + 1 > 6 && y + 1 < 4)
			{
				box[x][y].grid = 7;
			}

			else if (x + 1 > 6 && y + 1 < 7 && y + 1 > 3)
			{
				box[x][y].grid = 8;
			}

			else if (x + 1 > 6 && y + 1 > 6)
			{
				box[x][y].grid = 9;
			}
		}
	}

	//Assign blankness or not
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			//If 0, then blank

			if (box[x][y].value == 0)
			{
				box[x][y].blank = true;

				//Also change it to 1, may as well because none of them can end up as zeros.
				box[x][y].value = 1;
			}

			//Else, not blank
			else
			{
				box[x][y].blank = false;
			}
		}
	}

	bool conflict = false;
	bool backing = false;



	//Itterate boxes
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			//Only do all this to the blank boxes
			if (box[x][y].blank == true)
			{

			start:

				//If we are backing and the current value is 9 then we know we have conflict and we need to go back again.
				if (backing == true && box[x][y].value == 9)
				{
					conflict = true;
				}
				else
				{

					if (backing == true)
					{
						box[x][y].value += 1;
					}

					//reset conflict & backing
					conflict = false;
					backing = false;

					//Check for conflict
					//Itterate through boxes VERTICALLY with this one
					for (int X = 0; X < 9; X++)
					{
						if (x != X) //Don't compare a value to itself
						{
							if (!(x < X && box[X][y].blank == true)) //Don't compare with blank boxes below
							{
								if (box[x][y].value == box[X][y].value)
								{
									conflict = true;
									goto VerticalConflict; //used goto because a double break is messy
								}
							}

						}
					}


					//Itterate through boxes HORIZONTALLY with this one
					for (int Y = 0; Y < 9; Y++)
					{
						if (y != Y) //Don't compare a value to itself
						{
							if (!(y < Y && box[x][Y].blank == true)) // Don't compare with the blank boxes after this one
							{
								if (box[x][y].value == box[x][Y].value) //Two numbers are the same 
								{
									conflict = true;
									goto HorizontalConflict; //used goto because a double break is messy
								}
							}
						}
					}

					//Itterate through boxes in the same GRID
					for (int X = 0; X < 9; X++)
					{
						for (int Y = 0; Y < 9; Y++)
						{
							//Don't compare a box to itself
							if (x != X || y != Y)
							{
								//If they are in the same grid...
								if (box[x][y].grid == box[X][Y].grid)
								{//  if compared is before, if compared row is equal but to the left, if 
									if ((x > X) || (x == X && y > Y) || box[X][Y].blank == false) //Don't compare to blank boxes lower than this one and allow comparisons to the left.
										//Compare to all non-blanks
									{
										//...and they have the same value
										if (box[x][y].value == box[X][Y].value)
										{
											conflict = true;
											goto GridConflict;
										}
									}
								}
							}
						}
					}



				}
			VerticalConflict:
			HorizontalConflict :
			GridConflict :
						 //If conflict
						 if (conflict == true)
						 {

							//Go to previous box if the value is 9
							if (box[x][y].value == 9)
							{
								//Set box to 1

								box[x][y].value = 1;

								//Backing = true
								backing = true;


								if (y == 0)
								{
									y = 7;
									x--;
								}

								else if (y >= 1 && y < 9)
								{
									y--;
									y--;
								}
							}
							else
							{
								box[x][y].value += 1;
								goto start;
							}
						 }

			}

			//If we're going backward and land on a non-blank space. We need to go back again.
			else if (backing == true)
			{

				if (y == 0)
				{
					y = 7;
					x--;
				}

				else if (y >= 1 && y < 9)
				{
					y--;
					y--;
				}
			}
		}
	}







	//Display

	cout << "The solution: " << endl;

	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{

			cout << box[x][y].value;
			cout << "  ";
			if (y == 2 || y == 5)
			{
				cout << " | ";
			}
		}
		cout << endl;
		if (x == 2 || x == 5)
		{
			cout << "--------------------------------" << endl;
		}

	}

	//
	std::cin.sync();
	std::cin.get();

	return 0;
}