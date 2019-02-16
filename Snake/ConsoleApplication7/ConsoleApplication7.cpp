#include "pch.h"
#include <iostream>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<ctime>
using namespace std;

COORD position = { 0,0 };
COORD meals = { 0,0 };

int length = 4, check = 0;

enum Direction { LEFT, UP, RIGHT, DOWN };
Direction direction;

void board(int height, int width) {
	system("cls");
	//draws top line
	for (int g = 0; g < width; g++) {
		cout << (char)176;
	}
	cout << endl;
	//draws side lines
	for (int y = 0/*represents y*/; y < height; y++) {
		for (int x = 0/*represents x*/; x < width; x++) {
			if (x == 0) /*left line*/ {
				cout << (char)176;
			}
			else if (x == width - 1)/*right line; w-1 -> because it won't get to width*/ {
				cout << (char)176;
			}
			else { cout << " "; }//to fill board with empty space
		}
		cout << endl;
	}
	//bottom line
	for (int g = 0; g < width; g++) {
		cout << (char)176;
	}
}
//each cell of a snake's body -> it has coordinates and hp(how long it lives until it replaced with other part)
class partOfSnake {
public:
	int hp = 0;
	short int NewX = 0, NewY = 0;
	partOfSnake(int x, int y) {
		NewX = x;
		NewY = y;
	}
};
//it's a snake, obviously
class Snake {
public:
	int newX = 0, newY = 0;
	vector<partOfSnake> snake;//snake consists of cells and each cell has its own position(x,y)
	Snake(int x, int y) {
		newX = x;
		newY = y;
		snake.push_back(partOfSnake(newX, newY));
	}

	void drawSnake() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (auto a : snake) {
			position = { a.NewX, a.NewY };
			SetConsoleCursorPosition(hConsole, position);
			if (a.NewX == snake.back().NewX && a.NewY == snake.back().NewY) cout << (char)2;
			else cout << (char)4;
		}
		position = { meals.X, meals.Y };
		SetConsoleCursorPosition(hConsole, position);
		cout << (char)3;
	}
	void move() {
		if (direction == LEFT) {
			if (stumble(newX - 1, newY)) check = 1;
			newX--;
		}
		if (direction == UP) {
			if (stumble(newX, newY - 1)) check = 1;
			newY--;
		}
		if (direction == RIGHT) {
			if (stumble(newX + 1, newY)) check = 1;
			newX++;
		}
		if (direction == DOWN) {
			if (stumble(newX, newY + 1)) check = 1;
			newY++;
		}
		if (!snake.size() < length) deathOfParts();
		snake.push_back(partOfSnake(newX, newY));
		if (snake.back().NewX == meals.X && snake.back().NewY == meals.Y) {
			dropMeals();
			length++;
		}
	}
	int stumble(int checkX, int checkY) {
		for (auto a : snake) {
			if (checkX == a.NewX && checkY == a.NewY) return 1;
		}
		return 0;
	}
	void deathOfParts() {
		int hp = 0;
		for (auto &a : snake) {
			hp++;
			if (hp >= length) {
				snake.erase(snake.begin(), snake.begin() + 1);
			}
		}
	}
	void dropMeals() {
		meals = position = { rand() % 39, rand() % 19 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
		cout << (char)3;
	}
	bool death() {
		if (snake.back().NewX > 39 || snake.back().NewY > 20 || snake.back().NewX < 1 || snake.back().NewY < 1) return 1;
		if (check) return 1;												
		return 0;
	}
};

int main() {
	srand(time(0));
	int difficulty = 500;
	cout << endl << "Choose what difficulty you'd like to play on" << endl;
	cout << "1000 -> really easy" << endl;
	cout << "500 -> normal" << endl;
	cout << "300 -> somewhat harder" << endl;
	cout << "100 -> fucking crazy" << endl;
	cin >> difficulty;
	Snake ourSnake(5, 5);
	ourSnake.dropMeals();
	while (!ourSnake.death()) {
		system("cls");
		board(20, 40);
		ourSnake.drawSnake();
		if (_kbhit()) {
			char current = _getch();
			if (current == 'w') direction = UP;
			if (current == 'a') direction = LEFT;
			if (current == 's') direction = DOWN;
			if (current == 'd') direction = RIGHT;
		}
		ourSnake.move();
		Sleep(difficulty);
	}
}