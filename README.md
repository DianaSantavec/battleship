# THE GAME OF SINKING SOCKETS

The game of sinking sockets is a console battleship game for one or two players. Implementation is made for Linux and Windows operating systems and can be played in local network or with a bot.

## Tables and coordinates

The table is 10x10 with columns named 0-9 and rows named A-J.

When opponent's table is displayed, the meanings of symbols are:
- Empty slots (water): tilde symbol (~)
- Targeted fields without a ship: star symbol (*)
- Targeted fields with a ship: 'X' character (X)

When player's table is displayed, the meanings of symbols are:
- All of the above
- Ship's symbols

## Ships

Currently there are 4 types of ships where the longest one takes 4 cells and the smallest one takes 1 cell. A ship can be placed vertically or horizontally (square, 'T', or similar shapes are not allowed yet). Ships and their symbols:
- 4 cells: 'N'
- 3 cells: 'K'
- 2 cells: 'R'
- 1 cell : 'P'

## Ship's placement

Ships can be placed next to each other (in this version) and not one over the other. Ship's placement can be done manually or automatically.
Automatically, placement is done randomly (following the rules).
If users set ships manually, with every ship, start coordinates and direction (horisontally or vertically) must be given.

## Bot

Bot guesses randomly while hit is not scored. After that bot tries to find the rest of the ship and after that it continues random guessing.

