//Bradley Shiver and Jeffrey Jerez

#include <iostream>
#include <vector>

using namespace std;

//holds the value of a state with a 3x3 2D array
class state{
public:
	state();
	int values[3][3];
};

//state constructor
state::state(){
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			values[i][j] = 0;
		}
	}

	return;
}

class TicTacToe{
public:
	TicTacToe();
	void displayState(const state);
	int winTest(const state);
	int minimaxAlgorithm(state, int, int);
	void compTurn();
	void displayMarking(int);
	state currState;
	int playerNumber;
};

//constructor
TicTacToe::TicTacToe(){
	// initialize the currState array to zeroes
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			currState.values[i][j] = 0;
		}
	}

	cout << "Do you want to be player 1 or 2? ";
	cin >> playerNumber;

	//input validation to choose only player 1 or 2
	while (playerNumber > 2 || playerNumber < 1){
		cout << "Please enter 1 or 2: ";

		cin >> playerNumber;
	}

	return;
}

//takes the integer value of the player and outputs the marking
void TicTacToe::displayMarking(int player){
	//if mark is the user's
	if (player == -15){
		if (playerNumber == 1) cout << "x";
		if (playerNumber == 2) cout << "o";
	}

	//if the mark is the computer's
	if (player == 15){
		if (playerNumber == 1) cout << "o";
		if (playerNumber == 2) cout << "x";
	}

	//if space is empty print a space
	if (player == 0) cout << " ";
}

//output the grid with X's for player 1 and O's for player 2
void TicTacToe::displayState(state grid){
	cout << endl;
	cout << "\t\t\t\t    ";
	displayMarking(grid.values[0][0]); 
	cout << " | ";
	displayMarking(grid.values[0][1]);
	cout << " | ";
	displayMarking(grid.values[0][2]);
	cout << endl << "\t\t\t\t   -----------\n";
	cout << "\t\t\t\t    ";
	displayMarking(grid.values[1][0]); 
	cout << " | ";
	displayMarking(grid.values[1][1]); 
	cout << " | ";
	displayMarking(grid.values[1][2]);
	cout << endl << "\t\t\t\t   -----------\n";
	cout << "\t\t\t\t    ";
	displayMarking(grid.values[2][0]); 
	cout << " | ";
	displayMarking(grid.values[2][1]); 
	cout << " | ";
	displayMarking(grid.values[2][2]);
	cout << endl << endl;
}

//checks if the inputted grid contains a win for either player
//returns the integer value that has 3 in a row, or 0 if none exist
int TicTacToe::winTest(const state grid){

	for (int i = 0; i < 3; ++i){
		//check each column for win
		if (grid.values[0][i] != 0 && grid.values[0][i] == grid.values[1][i] 
			&& grid.values[0][i] == grid.values[2][i]){
			return grid.values[0][i];
		}
		//check each row for win
		if (grid.values[i][0] != 0 && grid.values[i][0] == grid.values[i][1] 
			&& grid.values[i][0] == grid.values[i][2]){
			return grid.values[i][0];
		}
	}

	//check diagonals for win
	if (grid.values[0][0] != 0 && grid.values[0][0] == grid.values[1][1] 
		&& grid.values[0][0] == grid.values[2][2]){
		return grid.values[0][0];
	}
	if (grid.values[0][2] != 0 && grid.values[0][2] == grid.values[1][1] 
		&& grid.values[0][2] == grid.values[2][0]){
		return grid.values[0][2];
	}

	return 0;
}

//finds the best path from the state specified through recursion of future moves
int TicTacToe::minimaxAlgorithm(state grid, int player, int depth){
	if (winTest(grid) != 0) {
		return winTest(grid) * player;
	}

	//set marking coordinates to arbitrary low values
	int markingI = -1000;
	int markingJ = -1000;
	int maxScore = -1000;

	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			if (grid.values[i][j] == 0){
				//mark the spot [i][j] with the player's value/mark
				grid.values[i][j] = player;
				//recursively call minimax for next player to find score
				int tempScore = -minimaxAlgorithm(grid, -player, depth+1);
				//change current state back
				grid.values[i][j] = 0;
				//if this path leads to a better score, replace the best score
				if (tempScore > maxScore){
					maxScore = tempScore;
					markingI = i;
					markingJ = j;
				}
			}
		}
	}

	//if marking coordinates did not change, return 0 (for tie)
	if (markingI == -1000 || markingJ == -1000) return 0;
	//else return score of this path
	return maxScore - depth;
}

//starts the minimax algorithm and makes the move that returns the best path
void TicTacToe::compTurn(){
	int markingI = -1000;
	int markingJ = -1000;
	int maxScore = -1000;

	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			if (currState.values[i][j] == 0){
				//mark the spot [i][j] with the computer's value/mark
				currState.values[i][j] = 15;
				//recursively call minimax for player to find score
				int tempScore = -minimaxAlgorithm(currState, -15, 0);
				//change current state back
				currState.values[i][j] = 0;
				//if this path leads to a better score, replace the best score
				if (tempScore > maxScore){
					maxScore = tempScore;
					markingI = i;
					markingJ = j;
				}
			}
		}
	}

	//mark the spot on the grid that leads to the path with the best score
	currState.values[markingI][markingJ] = 15;
}

//main game that takes turns between computer and player, changing the state for each
int main(){

	//output dope ascii art
	cout << " _______  ___   _______    _______  _______  _______    _______  _______  _______ " << endl;
	cout << "|       ||   | |       |  |       ||   _   ||       |  |       ||       ||       |" << endl;
	cout << "|_     _||   | |      _|  |_     _||  |_|  ||      _|  |_     _||   _   ||    ___|" << endl;
	cout << "  |   |  |   | |     |      |   |  |       ||     |      |   |  |  | |  ||   |___ " << endl;
	cout << "  |   |  |   | |     |      |   |  |       ||     |      |   |  |  |_|  ||    ___|" << endl;
	cout << "  |   |  |   | |     |_     |   |  |   _   ||     |_     |   |  |       ||   |___ " << endl;
	cout << "  |___|  |___| |_______|    |___|  |__| |__||_______|    |___|  |_______||_______|" << endl;
	cout << "                                                                           v.1.00 " << endl; 
	
	//output key for tic tac toe coordinates
	cout << "\n\t\t\t\ty\n\n";
	cout << "\t\t\t\t3  ";
	cout << "   | ";
	cout << "  | ";
	cout << endl << "\t\t\t\t   -----------\n";
	cout << "\t\t\t\t2  ";
	cout << "   | ";
	cout << "  | ";
	cout << endl << "\t\t\t\t   -----------\n";
	cout << "\t\t\t\t1  ";
	cout << "   | ";
	cout << "  | ";
	cout << "\n\n\t\t\t\t    1   2   3  x\n\n";

	TicTacToe game;
	int coords[2];
	cout << endl;

	int turn = 1;
	while (game.winTest(game.currState) == 0 && turn <= 9){
		//if player goes first
		if (game.playerNumber == 1){
			//player's turn
			cout << "Enter a move (x y): ";
			cin >> coords[0];
			cin >> coords[1];

			//input validation to ensure it's in the grid
			while (game.currState.values[3 - coords[1]][coords[0] - 1] != 0
				|| coords[0] > 3 || coords[1] > 3 || coords[0] < 0 || coords[1] < 0){
				cout << "Please enter an empty space (x y): ";
				cin >> coords[0];
				cin >> coords[1];
			}

			//inserts player mark into grid
			game.currState.values[3 - (coords[1])][coords[0] - 1] = -15;
			++turn;
			game.displayState(game.currState);
			if (game.winTest(game.currState) == -15){
				cout << "You win!\n";
				return 0;
			}

			//computer's turn
			game.compTurn();
			++turn;
			game.displayState(game.currState);
			if (game.winTest(game.currState) == 15){
				cout << "You lose!\n";
				return 0;
			}
		}

		//if player goes second
		if (game.playerNumber == 2){
			//computer's turn
			game.compTurn();
			++turn;
			game.displayState(game.currState);
			if (game.winTest(game.currState) == 15){
				cout << "You lose!\n";
				return 0;
			}
			if (turn >= 9){
				cout << "It's a tie!\n\n";
				return 0;
			}

			//player's turn
			cout << "Enter a move (x y): ";
			cin >> coords[0];
			cin >> coords[1];

			//input validation to ensure it's in the grid
			while (game.currState.values[3 - coords[1]][coords[0] - 1] != 0
				|| coords[0] > 3 || coords[1] > 3 || coords[0] < 0 || coords[1] < 0){
				cout << "Please enter an empty space (x y): ";
				cin >> coords[0];
				cin >> coords[1];
			}

			//inserts player mark into grid
			game.currState.values[3 - coords[1]][coords[0] - 1] = -15;
			game.displayState(game.currState);
			if (game.winTest(game.currState) == -15){
				cout << "You win!\n";
				return 0;
			}
			++turn;
		}
	}

	cout << "It's a tie!\n\n";

	return 0;
}