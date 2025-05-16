Snakes and Ladders Game Implementation
CMSC 341 - Fall 2024 - Project 1
This project implements the classic Snakes and Ladders board game in C++, featuring a linked list structure to represent the game board.
Overview
Snakes and Ladders is a classic board game where players take turns rolling a dice and moving their pieces across a sequentially numbered grid. The objective is to navigate from the starting position to the ending position, using ladders to climb ahead and avoiding snakes that make you slide backward.
Features

Dynamic Board Creation:

Default board generation with predetermined snakes and ladders
Random board generation with customizable number of snakes and ladders
Boards always have perfect square dimensions


Gameplay Mechanics:

Two-player turn-based gameplay
Dice rolling simulation
Automatic snake and ladder traversal
Win condition detection


Memory Management:

Proper memory allocation and deallocation
Deep copy assignment operator


Game Utilities:

Board visualization with colored indicators for snakes and ladders
Game reset functionality
Player position tracking



Game Structure
The game board is represented as a linked list of Cell objects. Each Cell has:

A unique ID (board position number)
A pointer to the next Cell (next board position)
A pointer to a Cell representing a ladder's end (if applicable)
A pointer to a Cell representing a snake's end (if applicable)

How to Play

Create a Snakes object with a board size parameter
The game automatically initializes with both players at the starting position
Players take turns rolling the dice and moving their pieces
If a player lands on a cell with a snake head, they move down to the snake's tail
If a player lands on a cell with a ladder bottom, they climb up to the ladder's top
The first player to reach the final cell wins


Board Rules

Board size must be at least 9 cells
Board size is adjusted to the nearest perfect square
First and last cells cannot have snakes or ladders
Snakes move players backward, ladders move players forward
Players take alternating turns
The game ends when a player reaches the final cell






