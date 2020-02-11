//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.

#ifndef TIC_H
#define TIC_H

/**********************************
 * CONFIGURATION
 **********************************/

enum BoardSize
{
    /* The number of fields on the X axis of the board */
    SIZE_X_AXIS = 3,
    /* The number of fields on the Y axis of the board */
    SIZE_Y_AXIS = 3,
};

/**********************************
 * ENUMS
 **********************************/

/* Constants for our Symbols */
enum Symbol
{
    CROSS = 1,
    CIRCLE = -1,
    NONE = 0,
    FULL = 2
};

/* Errors */
enum Error
{
    NO_ERROR,
    MOVE_OUTOFBOUNDS,
    MOVE_OCCUPIED,
    UNKNOWN_INPUT,
    CANNOT_BE_UNDONE,
};

/**********************************
 * STRUCTURES
 **********************************/

/* Structure to store a single game "state" */
struct Board
{
    /* The fields of the board */
    char fields[SIZE_X_AXIS][SIZE_Y_AXIS];
};

/* Structure to store our Game */
struct Game
{
    /* Store the current Board */
    struct Board board;
    /* Store each move in the game */
    struct Board moves[SIZE_X_AXIS * SIZE_Y_AXIS];
    /* Current move */
    unsigned int current_move;
};




#endif /* TIC_H */