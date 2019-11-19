#include "pch.h"
#include <iostream>
#include"conio.h"
using namespace std;
const int MazeHeight = 11;
const int MazeWidth = 11;
char Maze[MazeHeight][MazeWidth + 1] =
{
	"# #########",
	"#  #      #",
	"# ## #### #",
	"#    #    #",
	"# ## ## ###",
	"# ##  #   #",
	"# ### ### #",
	"# # # # # #",
	"#   # # # #",
	"# ###   # #",
	"######### #"
};
const char Wall = '#';
const char Free = ' ';
const char SomeDude = '*';
class COORD
{
public:
	int X;
	int Y;
	COORD(int x = 0, int y = 0) { X = x, Y = y; }
	COORD(const COORD &coord) { X = coord.X; Y = coord.Y; }
};
COORD StartingPoint(0, 1);
COORD EndingPoint(10, 9);
void clear_coord()
{
	for (int Y = 0; Y < MazeHeight; Y++)
		for (int X = 0; X < MazeWidth + 1; X++)
			if (Maze[Y][X] == SomeDude) Maze[Y][X] = Free;
}

void PrintDaMaze()
{
	for (int Y = 0; Y < MazeHeight; Y++)
	{
		cout << Maze[Y] << endl;
	}
	cout << endl;
}


bool check(COORD You)
{
	if (Maze[You.X - 1][You.Y] != Free &&
		Maze[You.X + 1][You.Y] != Free &&
		Maze[You.X][You.Y - 1] != Free &&
		Maze[You.X][You.Y + 1] != Free)
	{
		cout << "you are in deadlock" << endl;
		return true;
	}
	else { cout << "Choose free side" << endl; return false; }
}

bool Solve(int X, int Y)
{
	// Make the move (if it wrong, we will backtrack later.
	Maze[X][Y] = SomeDude;
	// If you want progressive update, uncomment these lines...
	PrintDaMaze();
	// Check if we have reached our goal.
	if (X == EndingPoint.X && Y == EndingPoint.Y)
	{
		return true;
	}
	// Recursively search for our goal.
	if (X > 0 && Maze[X - 1][Y] == Free && Solve( X - 1,Y))
	{
		return true;
	}
	if (X < MazeWidth && Maze[X + 1][Y] == Free && Solve(X + 1,Y))
	{
		return true;
	}
	if (Y > 0 && Maze[X][Y - 1] == Free && Solve( X,Y-1))
	{
		return true;
	}
	if (Y < MazeHeight && Maze[X][Y + 1] == Free && Solve( X,Y + 1))
	{
		return true;
	}
	// Otherwise we need to backtrack and find another solution.
	Maze[Y][X] = Free;
	return false;
}

int main()
{
	COORD You = StartingPoint;
	char step;
	bool b = true, exit = false;
	Maze[You.X][You.Y] = SomeDude;
	cout << "Choose the side which you want to go:" << endl;
	cout << "'w' - up, 'a' - left,'s' - down, 'd'-right" << endl;
	cout << "If you wanna restart enter r" << endl;
	while (b && !exit)
	{
		system("cls");
		PrintDaMaze();
		step=_getch();//cin>>step;(Без нажанитя Enter)
		switch (step)
		{
		case 'r': {clear_coord(); You = StartingPoint; Maze[You.X][You.Y] = SomeDude; } break;
		case 'a':
			if (You.Y > 0 && Maze[You.X][You.Y - 1] == Free)
			{
				You.Y -= 1;
				Maze[You.X][You.Y] = SomeDude;
			}
			else if (You.X == EndingPoint.X&&You.Y == EndingPoint.Y)
			{
				cout << "Exit is founded! Congratulations!!" << endl;
				exit = true;
			}
			else if (check(You)) { cout << "Enter r to reset the game " << endl; }

			else cout << "You can't go to the left, go to the other side" << endl;
			break;
		case 'w':
			if (You.X > 0 && Maze[You.X - 1][You.Y] == Free)
			{
				You.X -= 1;
				Maze[You.X][You.Y] = SomeDude;
			}
			else if (You.X == EndingPoint.X&&You.Y == EndingPoint.Y)
			{
				cout << "Exit is founded! Congratulations!!" << endl;
				exit = true;
			}
			else if (check(You)) { cout << "Enter r to reset the game " << endl; }

			else cout << "You can't go to the up, go to the other side" << endl;
			break;
		case's':
			if (You.X < MazeHeight && Maze[You.X + 1][You.Y] == Free)
			{
				You.X += 1;
				Maze[You.X][You.Y] = SomeDude;
			}
			else if (You.X == EndingPoint.X&&You.Y == EndingPoint.Y)
			{
				cout << "Exit is founded! Congratulations!!" << endl;
				exit = true;
			}
			else if (check(You)) { cout << "Enter r to reset the game " << endl; }

			else cout << "You can't go to the down, go to the other side" << endl;
			break;
		case 'd':
			if (You.Y < MazeWidth && Maze[You.X][You.Y + 1] == Free)
			{
				You.Y += 1;
				Maze[You.X][You.Y] = SomeDude;
			}
			else if (You.X == EndingPoint.X&&You.Y == EndingPoint.Y)
			{
				cout << "Exit is founded! Congratulations!!" << endl;
				exit = true;
			}
			else if (check(You)) { cout << "Enter r to reset the game " << endl; }
			else cout << "You can't go to the right, go to the other side" << endl;
			break;
		}//end switch
	}//end while
	if (exit)
	{
		cout << "Your Maze :" << endl;
		PrintDaMaze();
	}
	else if (!b) cout << "You loser! Try again" << endl;
	/*
	if (Solve(StartingPoint.X, StartingPoint.Y))
	{
		cout << "Success!" << endl;
		PrintDaMaze();
	}
	else
	cout << "Failed!" << endl;
	*/
	return 0;
}
