#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h> //_getch()
#include "Box.h"

void createGrid(Box box[9][9]) //Here the user creates the grid
{
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
						std::cout << "x";
						std::cout << "  ";
					}

					else if (box[X][Y].value != 0)
					{
						std::cout << box[X][Y].value;
						std::cout << "  ";

					}

					else if (box[X][Y].value == 0)
					{
						std::cout << "-";
						std::cout << "  ";
					}
					if (Y == 2 || Y == 5)
					{
						std::cout << " | ";
					}
				}
				std::cout << std::endl;
				if (X == 2 || X == 5)
				{
					std::cout << "--------------------------------" << std::endl;
				}

			}

			std::cout << "This program assumes that you have entered a valid sudoku puzzle." << std::endl << std::endl;;
			std::cout << "Please fill the puzzle with numbers from 1 to 9" <<std::endl;
			std::cout << "Use zeros to represent blanks." <<std::endl;
			std::cout << "Hit backspace to go back" << std::endl;

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
}

void solve(Box box[9][9])
{
	//Determine weight of the puzzle to see if/how it should be rotated. Why? Because the puzzle will solve faster if the bulk of the weight is at the top.

	int topFive = 0;
	int rightFive = 0;
	int leftFive = 0;
	int bottomFive = 0;

	int rotationCounter = 0;


	//Top 5 - do not rotate
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (box[x][y].value != 0)
			{
				topFive++;
			}
		}
	}

	//Right 5 - rotate once
	for (int x = 0; x < 9; x++)
	{
		for (int y = 5; y < 9; y++)
		{
			if (box[x][y].value != 0)
			{
				rightFive++;
			}
		}
	}

	//Left 5 - rotate 3 times
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (box[x][y].value != 0)
			{
				leftFive++;
			}
		}
	}

	//Bottom 5 - rotate twice
	for (int x = 5; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (box[x][y].value != 0)
			{
				bottomFive++;
			}
		}
	}

	//Rotate counter clockwise, to get the most efficient puzzle 
	for (int i = 0; i < rotationCounter; i++)
	{

		int n = 9;
		int tmp;
		for (int i = 0; i < 9 / 2; i++)
		{
			for (int j = i; j < n - i - 1; j++)
			{
				tmp = box[i][j].value;
				box[i][j].value = box[j][n - i - 1].value;
				box[j][n - i - 1].value = box[n - i - 1][n - j - 1].value;
				box[n - i - 1][n - j - 1].value = box[n - j - 1][i].value;
				box[n - j - 1][i].value = tmp;
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

	//Un-rotate grid
	int a = 0;
	int b = 0;
	if (rotationCounter == 1)
	{
		a = 3;
	}
	else if (rotationCounter == 2)
	{
		a = 2;
	}
	else if (rotationCounter == 3)
	{
		a = 3;
	}

	for (b = 0; b < a; b++)
	{
		int n = 9;
		int tmp;
		for (int i = 0; i < 9 / 2; i++)
		{
			for (int j = i; j < n - i - 1; j++)
			{
				tmp = box[i][j].value;
				box[i][j].value = box[j][n - i - 1].value;
				box[j][n - i - 1].value = box[n - i - 1][n - j - 1].value;
				box[n - i - 1][n - j - 1].value = box[n - j - 1][i].value;
				box[n - j - 1][i].value = tmp;
			}
		}
	}
}


void display(Box box[9][9])
{
	//Display

	std::cout << "The solution: " << std::endl;

	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{

			std::cout << box[x][y].value;
			std::cout << "  ";
			if (y == 2 || y == 5)
			{
				std::cout << " | ";
			}
		}
		std::cout << std::endl;
		if (x == 2 || x == 5)
		{
			std::cout << "--------------------------------" << std::endl;
		}

	}
}