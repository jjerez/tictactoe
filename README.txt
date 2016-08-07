Jeffrey Jerez, Bradley Shiver
COP 4930 - Intro to AI Spring 2015
Final Project
Tic Tac Toe Using the Minimax Algorithm

/--- Included

tictactoe.cpp 						// source code
jjerez_bshiver_project report.docx 	// final report
README.txt

/--- How to run

In a linux environment, type:
	~/g++ tictactoe.cpp -o ttt
	~/./ttt
	
Follow the prompts to play the game. We assume that all input is correct (i.e. no letters are input when asked for a number).


/--- The game

It is a simple, coordinate-based 3x3 grid game of tic-tac-toe. The computer player will never lose, the game will either always end in a win for the computer or a draw for both players. If pitted against itself, the computer will draw forever, using the same set of moves (not implemented). It is implemented using the minimax algorithm. 