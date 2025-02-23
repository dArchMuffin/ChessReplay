# Chess Replay Program

## Overview

This project is a Chess Replay Program written in C. It reads a text file formatted according to the Lichess.org database model and simulates the game move by move, displaying the board state after each move. The program also provides additional information such as move evaluations and comments, provided by the txt file.

## Features

- **Game Parsing**: Reads a chess game from a text file in Lichess format.
- **Board Simulation**: Simulates the game move by move, updating the board state.

## How It Works

The program consists of several modules:

1. **read_game.c**: Reads the game file and parses the moves and headers.
2. **parse_move.c**: Parses individual moves and extracts relevant information.
3. **update_board.c**: Updates the chess board based on the moves.
4. **write_move.c**: Writes the move details to the console.
5. **print_board.c**: Prints the current state of the chess board.
6. **main.c**: The main driver program that orchestrates the reading, parsing, and simulation of the game.
7. etc.

## Usage

To run the program, compile the source files. 
To tweak the display speed, provide as argument the interval time in seconds : 

```bash
make
./chess 1
```
This will compile the program, and run it with 1 second of delay between each move.
Edit the read_game function in the read_game.c line to open any txt file formatted according to the Lichess.org database model

## Example Output

The program will display the initial board state and then simulate each move, showing the updated board and move details:

```
  ||  a |  b |  c |  d |  e |  f |  g |  h ||
==++====+====+====+====+====+====+====+====++==
8 ||  R |  N |  B |  Q |  K |  B |  N |  R || 8	
--++----+----+----+----+----+----+----+----++--	[White "VR1H"]
7 ||  P |  P |  P |  P |  P |  P |  P |  P || 7	[Black "Pericles44"]
--++----+----+----+----+----+----+----+----++--	[Result "1/2-1/2"]
6 ||    |    |    |    |    |    |    |    || 6	[UTCDate "2014.07.01"]
--++----+----+----+----+----+----+----+----++--	[UTCTime "09:54:51"]
5 ||    |    |    |    |    |    |    |    || 5	[WhiteElo "2083"]
--++----+----+----+----+----+----+----+----++--	[BlackElo "1942"]
4 ||    |    |    |    |    |    |    |    || 4	[WhiteRatingDiff "-22"]
--++----+----+----+----+----+----+----+----++--	[BlackRatingDiff "+3"]
3 ||    |    |    |    |    |    |    |    || 3	[ECO "A52"]
--++----+----+----+----+----+----+----+----++--	[Opening "Budapest Defense: Rubinstein Variation"]
2 ||  p |  p |  p |  p |  p |  p |  p |  p || 2	[TimeControl "60+1"]
--++----+----+----+----+----+----+----+----++--	[Termination "Normal"]
1 ||  r |  n |  b |  q |  k |  b |  n |  r || 1	
==++====+====+====+====+====+====+====+====++==	
  ||  a |  b |  c |  d |  e |  f |  g |  h ||
mMl
                                     +----------+
====================================<| Turn #1 |>====================================
                                     +----------+

White pawn moves to d4.	#0 : [d4]
	

  ||  a |  b |  c |  d |  e |  f |  g |  h ||
==++====+====+====+====+====+====+====+====++==
8 ||  R |  N |  B |  Q |  K |  B |  N |  R || 8	
--++----+----+----+----+----+----+----+----++--	[White "VR1H"]
7 ||  P |  P |  P |  P |  P |  P |  P |  P || 7	[Black "Pericles44"]
--++----+----+----+----+----+----+----+----++--	[Result "1/2-1/2"]
6 ||    |    |    |    |    |    |    |    || 6	[UTCDate "2014.07.01"]
--++----+----+----+----+----+----+----+----++--	[UTCTime "09:54:51"]
5 ||    |    |    |    |    |    |    |    || 5	[WhiteElo "2083"]
--++----+----+----+----+----+----+----+----++--	[BlackElo "1942"]
4 ||    |    |    |  p |    |    |    |    || 4	[WhiteRatingDiff "-22"]
--++----+----+----+----+----+----+----+----++--	[BlackRatingDiff "+3"]
3 ||    |    |    |    |    |    |    |    || 3	[ECO "A52"]
--++----+----+----+----+----+----+----+----++--	[Opening "Budapest Defense: Rubinstein Variation"]
2 ||  p |  p |  p |    |  p |  p |  p |  p || 2	[TimeControl "60+1"]
--++----+----+----+----+----+----+----+----++--	[Termination "Normal"]
1 ||  r |  n |  b |  q |  k |  b |  n |  r || 1	
==++====+====+====+====+====+====+====+====++==	
  ||  a |  b |  c |  d |  e |  f |  g |  h ||

...
...
...

====================================<| Turn #48 |>====================================
                                     +----------+

White king moves to d3.	#94 : [Kd3]
	

  ||  a |  b |  c |  d |  e |  f |  g |  h ||
==++====+====+====+====+====+====+====+====++==
8 ||    |    |    |    |    |    |    |    || 8	
--++----+----+----+----+----+----+----+----++--	[White "VR1H"]
7 ||    |    |    |    |    |    |    |    || 7	[Black "Pericles44"]
--++----+----+----+----+----+----+----+----++--	[Result "1/2-1/2"]
6 ||    |    |    |    |    |    |    |    || 6	[UTCDate "2014.07.01"]
--++----+----+----+----+----+----+----+----++--	[UTCTime "09:54:51"]
5 ||    |  P |    |  K |    |    |    |    || 5	[WhiteElo "2083"]
--++----+----+----+----+----+----+----+----++--	[BlackElo "1942"]
4 ||    |  p |    |    |    |    |    |    || 4	[WhiteRatingDiff "-22"]
--++----+----+----+----+----+----+----+----++--	[BlackRatingDiff "+3"]
3 ||    |    |    |  k |    |    |    |    || 3	[ECO "A52"]
--++----+----+----+----+----+----+----+----++--	[Opening "Budapest Defense: Rubinstein Variation"]
2 ||    |    |    |    |    |    |    |    || 2	[TimeControl "60+1"]
--++----+----+----+----+----+----+----+----++--	[Termination "Normal"]
1 ||    |    |    |    |    |    |    |    || 1	
==++====+====+====+====+====+====+====+====++==	
  ||  a |  b |  c |  d |  e |  f |  g |  h ||




Draw.	#95 : [1/2]
	

  ||  a |  b |  c |  d |  e |  f |  g |  h ||
==++====+====+====+====+====+====+====+====++==
8 ||    |    |    |    |    |    |    |    || 8	
--++----+----+----+----+----+----+----+----++--	[White "VR1H"]
7 ||    |    |    |    |    |    |    |    || 7	[Black "Pericles44"]
--++----+----+----+----+----+----+----+----++--	[Result "1/2-1/2"]
6 ||    |    |    |    |    |    |    |    || 6	[UTCDate "2014.07.01"]
--++----+----+----+----+----+----+----+----++--	[UTCTime "09:54:51"]
5 ||    |  P |    |  K |    |    |    |    || 5	[WhiteElo "2083"]
--++----+----+----+----+----+----+----+----++--	[BlackElo "1942"]
4 ||    |  p |    |    |    |    |    |    || 4	[WhiteRatingDiff "-22"]
--++----+----+----+----+----+----+----+----++--	[BlackRatingDiff "+3"]
3 ||    |    |    |  k |    |    |    |    || 3	[ECO "A52"]
--++----+----+----+----+----+----+----+----++--	[Opening "Budapest Defense: Rubinstein Variation"]
2 ||    |    |    |    |    |    |    |    || 2	[TimeControl "60+1"]
--++----+----+----+----+----+----+----+----++--	[Termination "Normal"]
1 ||    |    |    |    |    |    |    |    || 1	
==++====+====+====+====+====+====+====+====++==	
  ||  a |  b |  c |  d |  e |  f |  g |  h ||

```

## Requirements

- C Compiler (e.g., GCC)
- Standard C Library

## Future Improvements

- **GUI Integration**: Add a graphical user interface to visualize the board and moves.
- **Fully playable chess game**: Allow users to interactively play through the game.

---

Feel free to contribute to this project by submitting issues or pull requests. Enjoy replaying your chess games!
