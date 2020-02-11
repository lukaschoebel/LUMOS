//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.

/**********************************
 * INCLUDES
 **********************************/

#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

/**********************************
 * DEFINES
 **********************************/

#define DEBUG 0

/**********************************
 * FUNCTIONS
 **********************************/

/**
 * display_board
 *
 * Print the given board to the screen.
 *
 * @param b The board to print
 */
void display_board(struct Board b)
{
    int x, y = x = 0;
    
    // Loop over Y
    for (y = 0; y < SIZE_Y_AXIS * 5; y += 1)    // y_axis = 3 --> continue till y < 15
    {
        printf("\t");
        
        // Loop over X
        for (x = 0; x < SIZE_X_AXIS; x += 1)
        {
            switch (y % 5)                      // max_y = 15 --> creates cases 0,1,2,3,4
            {
                case 0:
                    /*fallthrough*/
                case 4:
                    printf(" --- ");
                    break;
                case 1:
                    /*fallthrough*/
                case 3:
                    printf("|   |");
                    break;
                case 2:
                    printf("| ");
                    if (b.fields[x][y/5] == CIRCLE)
                        printf("o");
                    else if (b.fields[x][y/5] == CROSS)
                        printf("X");
                    else
                        printf(" ");
                    printf(" |");
            }
        }
        
        printf("\n");
    }
}

/**
 * print_help
 *
 * Print a help message.
 */

void print_help(void)
{
    printf("\nHELP\n");
    printf("----\n");
    printf("A simple Tic Tac Toe game. To conduct a move ");
    printf("simply type the number of the field you want ");
    printf("to occupy. The first field has the number one.\n");
    printf("Example: The input '6' would set the last field ");
    printf("in the second row on a 3x3 Tic Tac Toe board.\n\n");
    printf("Further options:\n");
    printf("\t'u' - undo you last move\n");
    printf("\t'h' - print this message\n\n");
}

/**
 * print_error
 *
 * Print the given error message.
 *
 * @param e The error that should be printed
 */
void print_error(enum Error e)
{
    printf("\nError:\n");
    switch(e)
    {
        case MOVE_OUTOFBOUNDS:
            printf("Cannot conduct the given move as it outside ");
            printf("of the current board!\n");
            break;
        case MOVE_OCCUPIED:
            printf("The specified field has already been set!\n");
            break;
        case UNKNOWN_INPUT:
            printf("Unkown command! Type 'h' for help!\n");
            break;
        case CANNOT_BE_UNDONE:
            printf("The are no more moves to undo!\n");
            break;
        default:
            printf("Unknown error!\n");
            break;
    }
    
    printf("\n");
}


/**
 * print_winner
 *
 * Print the winner of the game.
 *
 * @param s The symbol that won.
 */

void print_winner(enum Symbol s)
{
    printf("\nGAME OVER!\n");
    
    switch(s){
        case CROSS:
            printf("The winner is *drum roll*: Cross!\n\n");
            break;
        case CIRCLE:
            printf("The winner is *drum roll*: Circle!\n\n");
            break;
        case FULL:
            printf("Draw - There is no winner\n\n");
        default:
            break;
    }
}


/**
 * initialize_board
 *
 * Initialize the given board by setting all its fields
 * to "NONE".
 *
 * @param b The board to initialize
 * @return The initialized board
 */

struct Board initialize_board(struct Board b)
{
    int x, y = x = 0;
    
    for (y = 0; y < SIZE_Y_AXIS; y += 1)
        for (x = 0; x < SIZE_X_AXIS; x += 1)
            b.fields[x][y] = NONE;
            
            return b;
}


/**
 * initialize_game
 *
 * Initialize the given game.
 *
 * @param g The game to initialize
 * @return The initialized game
 */

struct Game initialize_game(struct Game g)
{
    g.board = initialize_board(g.board);
    g.current_move = 0;
    
    return g;
}


/**
 * ask_for_move
 *
 * Ask the user for a move.
 *
 * @return The command of the user.
 */

char ask_for_move(void)
{
    char input = 0;
    
    do
    {
        printf("\nType 'h' for help.\n");
        printf("move> ");
        input = getchar();
        getchar();
    }
    while (input < '0' || (input > '9' && input != 'h' && input != 'u'));
    
    return input;
}


/**
 * validate_move
 *
 * Check whether the move of the user is valid.
 *
 * @param g The game to test the move on.
 * @param move The move conducted by the user.
 * @return NO_ERROR if the move is possible, the respective
 *         error otherwise (e.g. MOVE_OCCUPIED)
 */

enum Error validate_move(struct Game g, int move)
{
    int x = (move - 1) % SIZE_Y_AXIS;
    int y = (move - 1) / SIZE_X_AXIS;
    
    if (x > SIZE_X_AXIS - 1 || y > SIZE_Y_AXIS - 1 || x < 0 || y < 0)
        return MOVE_OUTOFBOUNDS;
    else if (g.board.fields[x][y] != NONE)
        return MOVE_OCCUPIED;
    else
        return NO_ERROR;
}


/**
 * conduct_move
 *
 * Conduct the given move for the given game.
 *
 * @param g     The game the move should be made in
 * @param move  The move to conduct
 * @param s     The symbol that should be used for the move
 * @return      The updated game containing the move
 */

struct Game conduct_move(struct Game g, int move, enum Symbol s)
{
    int x = (move - 1) % SIZE_Y_AXIS;
    int y = (move - 1) / SIZE_X_AXIS;
    
    g.moves[g.current_move] = g.board;
    g.current_move += 1;
    g.board.fields[x][y] = s;
    
    return g;
}


/**
 * undo_moves
 *
 * Undo the given number of moves in the given game.
 *
 * @param g The game the move should be undone in
 * @param number The number of moves to undo
 * @return The reverted game
 */

struct Game undo_moves(struct Game g, unsigned int number)
{
    if (number > g.current_move)
    {
        print_error(CANNOT_BE_UNDONE);
        return g;
    }
    
    g.current_move -= number;
    g.board = g.moves[g.current_move];
    return g;
}


/**
 * game_over
 *
 * Check whether there is a winner in the given game.
 *
 * @param g The game to check
 * @return The winning symbol or NONE if there is
 *         currently no winner
 */

enum Symbol game_over(struct Game g)
{
    int x, y = x = 0;
    int full = 0;
    
    for (y = 0; y < SIZE_Y_AXIS; y += 1)
    {
        for (x = 0; x < SIZE_X_AXIS; x += 1)
        {
            if (g.board.fields[x][y] == NONE)
                full++;
            else if (x < SIZE_X_AXIS - 2 &&
                     g.board.fields[x][y] == g.board.fields[x+1][y] &&
                     g.board.fields[x][y] == g.board.fields[x+2][y])
                return g.board.fields[x][y];
            else if (y < SIZE_Y_AXIS - 2 &&
                     g.board.fields[x][y] == g.board.fields[x][y+1] &&
                     g.board.fields[x][y] == g.board.fields[x][y+2])
                return g.board.fields[x][y];
            else if (x < SIZE_X_AXIS - 2 && y < SIZE_Y_AXIS - 2 &&
                     g.board.fields[x][y] == g.board.fields[x+1][y+1] &&
                     g.board.fields[x][y] == g.board.fields[x+2][y+2])
                return g.board.fields[x][y];
            else if (x >= 2 && y < SIZE_Y_AXIS - 2 &&
                     g.board.fields[x][y] == g.board.fields[x-1][y+1] &&
                     g.board.fields[x][y] == g.board.fields[x-2][y+2])
                return g.board.fields[x][y];
        }
    }
    if (full == 0)
        return FULL;
    return NONE;
}


/*
 * miniMAX
 *
 * Implementation of the miniMAX algorithm that searches with a brute-force approach
 * every possible step in the game and values certain moves.
 * If I win --> +10
 * If I lose --> -10
 * draw --> +0
 *
 * @param g       Game state (as defined in the lecture)
 * @param player  Player to find the best move for.
 * @return        best possible score
 */

int miniMAX(struct Game g, enum Symbol player)
{
    int bestScore = 0;
    int Xscore = 0;
    int Oscore = 0;
    int x = 0;
    int y = 0;
    // Assuming the AI is CROSS - CROSS wants to win the game/CIRCLE should lose the game
    
    // initialize bestScore...
    if (player == CROSS)
        bestScore = -42424242;      // ... with an low value if the player is CROSS
    else
        bestScore = 42424242;       // ... with a high value if the player is CIRCLE
    
    
    // check game_over and if someone got a winning strike --> return +-10 or 0
    switch (game_over(g))
    {
        case CROSS:                 // if CROSS/AI wins --> good move --> return +10
            return 10;
            break;
            
        case CIRCLE:                // if CIRCLE wins/AI loses --> dumb --> return -10
            return -10;
            
        case FULL:                  // if it is going to be a tie --> smart ass opponent --> 0
            return 0;
            
        default:                    // just in case a default case..
            break;
    }
    
    for (y = 0; y < SIZE_Y_AXIS; y++)
    {
        for (x = 0; x < SIZE_X_AXIS; x++)
        {
            if (g.board.fields[x][y] == NONE)           // check all not-occupied fields
            {
                switch (player)
                {
                    case CROSS:
                        g.board.fields[x][y] = CROSS;   // brute-force: set field[x][y] equal to CROSS
                        Xscore = miniMAX(g, CIRCLE);    // call miniMAX on CIRCLE and save the value in Xscore
                        break;
                        
                    case CIRCLE:
                        g.board.fields[x][y] = CIRCLE;  // brute-force: set field[x][y] equal to CIRCLE
                        Oscore = miniMAX(g, CROSS);
                        break;
                        
                    default:
                        break;
                }
                
                g.board.fields[x][y] = NONE;                        // make your steps invisible
            
                if ((Xscore > bestScore) && (player == CROSS))      // high Xscores --> good for AI
                    bestScore = Xscore;
                if ((Oscore < bestScore) && (player == CIRCLE))     // low Oscores  --> good for AI
                    bestScore = Oscore;
                
#if (DEBUG == 1)
                printf("[DEBUG] Current bestScore: %d\n", bestScore);
#endif
            }
        }
    }
    
    return bestScore;
}

/*
 * nextMove
 * 
 * Function that calculates the best move for the player 'player' - given
 * the current game state 'g'.
 *
 * @param   g           Game state (as defined in the lecture)
 * @param   player      Player to find the best move for.
 * @return  nextMove    Index of field for the suggested move.
 */

int nextMove(struct Game g, enum Symbol player)
{
    int x = 0;                  // define counter variables
    int y = 0;
    
    int Xscore = -42424242;     // define scores for CIRCLE/CROSS
    int Oscore = 42424242;
    
    int Xscore_tmp = 0;         // define temporary variables to store certain X and O scores
    int Oscore_tmp = 0;
    
    int nextMove_X = 1;         // define the e
    int nextMove_O = 1;
    
    for (y = 0; y < SIZE_Y_AXIS; y++)               // iterates from y = 0 to y = 2 --> y in {0, 2}
    {
        for (x = 0; x < SIZE_X_AXIS; x++)           // iterates from x = 0 to x = 2 --> x in {0, 2}
        {
            if (g.board.fields[x][y] == NONE)       // check all non-occupied fields
            {
                switch (player)
                {
                    case CROSS:
                        g.board.fields[x][y] = CROSS;       // brute-force set field[x][y] equal to cross
                        Xscore_tmp = miniMAX(g, CIRCLE);    // call miniMAX on CIRCLE
                        
                        #if (DEBUG == 1)
                        printf("%d\n", miniMAX(g, CROSS));
                        #endif
                        
                        // Assuming the AI is CROSS, higher values will be good
                        if (Xscore_tmp > Xscore)            // If the minimax(CIRCLE) is greater than Xscore...
                        {
                            Xscore = Xscore_tmp;            // ...set Xscore to the temporary Xscore
                            nextMove_X = (y*3) + (x+1);     // ex.: if the bestMove will be 3 --> iteration y = 0, x = 2 --> 3 = 0*3+2+1
                        }
                        break;
                        
                    case CIRCLE:
                        g.board.fields[x][y] = CIRCLE;      // brute-force set field[x][y] equal to circle
                        Oscore_tmp = miniMAX(g, CROSS);     // call miniMAX to CIRCLE
                        
                        #if (DEBUG == 1)
                        printf("%d\n", miniMAX(g, CIRCLE));
                        #endif
                        
                        // Assuming the AI is CROSS, smaller values will be good
                        if (Xscore_tmp < Oscore)            // If the minimax(CROSS) is less than Oscore...
                        {
                            Oscore = Oscore_tmp;            // ...set Oscore to the temporary Oscore
                            nextMove_O = (y*3) + (x+1);
                        }
                        break;
                        
                    default:
                        print_error(NO_ERROR);
                        exit(-1);
                        break;
                }
                
                g.board.fields[x][y] = NONE;                // make your iteration steps invisible
            }
        }
    }
    
    switch (player)
    {
        case CROSS:
#if (DEBUG == 1)
            printf("[DEBUG] Next Move for X will be: %d\n", nextMove_X);
#endif
            return nextMove_X;
            break;
            
        case CIRCLE:
#if (DEBUG == 1)
            printf("[DEBUG] Next Move for O will be: %d\n", nextMove_O);
#endif
            return nextMove_O;
            break;
            
        default:
            break;
    }
    
    return -1;
}

int main(void)
{
    struct Game g;
    char move = 0;
    enum Error e;

    enum Symbol current = CIRCLE;       // decides the beginner
    enum Symbol computer = CIRCLE;      // decides the symbol of the computer
    
    // Initialize the game
    g = initialize_game(g);
    
    // Game Loop
    do
    {
        display_board(g.board);
        
        if (current == computer)
        {
            move = nextMove(g, current) + '0';
        }else{
            move = ask_for_move();
        }
        
        //move = ask_for_move();
        
        if (move == 'u')
            g = undo_moves(g, 1);
        else if (move == 'h')
            print_help();
        else
        {
            e = validate_move(g, move - '0');
            
            if (e == NO_ERROR)
            {
                g = conduct_move(g, move - '0', current);
                
                if (current == CROSS)
                    current = CIRCLE;
                else
                    current = CROSS;
            }
            else
                print_error(e);
        }
        
#if (DEBUG == 3)
        // check the algorithm
        if (game_over(g) == NONE)
        {
            g = conduct_move(g, nextMove(g, current), current);
            
            if (current == CROSS)
                current = CIRCLE;
            else
                current = CROSS;
        }
#endif
    } while (game_over(g) == NONE);
    
    // Print the winner
    display_board(g.board);
    print_winner(game_over(g));
}