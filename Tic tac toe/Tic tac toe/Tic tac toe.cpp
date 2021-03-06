#include "pch.h"
#include <iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
char board[9];
char win='-';
void fillIn() {
	for (int g = 0; g < 9; g++) {
		board[g] = ' ';
	}
}
void draw() {
	system("cls");
	cout << "Crosses and zeros" << endl;
	cout << "__|__|__" << endl;
	cout << "__|__|__" << endl;
	cout << "  |  |  " << endl;

	cout << "You'll have to choose a number, where you'd like to put your mark: " << endl;
	cout << " 1| 2| 3" << endl;
	cout << " 4| 5| 6" << endl;
	cout << " 7| 8| 9 " << endl;

	cout << "Here we're now:\n" << endl;
	cout << "_" << board[0] << "_" << '|' << "_" << board[1] << "_" << '|' << "_" << board[2] << "_" << endl;
	cout << "_" << board[3] << "_" << '|' << "_" << board[4] << "_" << '|' << "_" << board[5] << "_" << endl;
	cout << "_" << board[6] << "_" << '|' << "_" << board[7] << "_" << '|' << "_" << board[8] << "_" << "\n" << endl;
}
void humanChoice(int num) {
	int cell;
	cout << "Put in the number of the cell";
	cin >> cell;
	while (cell > 9 || cell < 1 || board[cell - 1] == 'O' || board[cell - 1] == 'X')
	cin >> cell;
	cout << "\n";
	if (num == 1) board[cell - 1] = 'X';
	else board[cell - 1] = 'O';
}
char winner() {
	for (int i = 0; i < 3; i++) {
		if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
			return board[i];
		}
		else if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) 
			return board[i]; 
		else if ((board[2] == board[4] && board[4] == board[6]) || (board[0] == board[4] && board[4] == board[8]))
			return board[i];
		return '-';
	}
}
void result() {
		if (win == 'X') {
			cout << "Crosses have won" << endl;
		}
		else if(win == 'O'){
			 cout << "Zeros have won" << endl;
		}
		else {
			cout << "It's a tie";
		}
	}
int main(){
	draw();
	for (int move = 1; move <= 9; move++) {
		if (move % 2) { humanChoice(1); }
		else {humanChoice(2);}
		draw();
		if (move >= 5)
		{
			win = winner();
			if (win != '-')
				break;
		}
	}
	result();
	return 0;
}