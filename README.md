# THE GAME OF SINKING SOCKETS

Is a console battleship game for one or two players. Implementation is made for Linux and Windows operating systems and can be played in local network or with bot.

## Tables and coordinates

The table is 10x10 with columns named 0-9 and rows named A-J.

When opponents table is displayed, meaning of symbols are:
- empty slots (water): tilde symbol (~)
- Targeted fields without ship: star symbol (*)
- Targeted fields with ship: 'X' character (X)

When players table is displayed, meaning of symbols are:
- all above
- ships symbols

## Ships

Currently there are 4 types of ships, where the longest takes 4 cells and the smallest 1 cell. Ship can be placed vertically or horisontally (square, 'T', or similar shapes are not allowed yet). Ships and their symbols:
- 4 cells: 'N'
- 3 cells: 'K'
- 2 cells: 'R'
- 1 cell: 'P'

## Ships placement

Ships can be placed next to each other (in this version) and not one over the other. Ships placement can be done manually or automatically.
Automatically placement is done randomly (following rules).
If users sets ships manually, with every ship start coordinates and direction (horisontally or vertically) must be given.

## Bot

Bot guesses randomly while hit is not scored. After that bot tries to find rest of the ship and after that continues random guessing.

