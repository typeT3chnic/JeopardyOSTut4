/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Copyright (C) 2026, <GROUP NUMBER>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    int index = 0;
    char *token = strtok(input, " ");

    while (token != NULL) {
        tokens[index++] = token;
        token = strtok(NULL, " ");
    }

    tokens[index] = NULL; //end of list
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    //sort players by score descending
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = 0; j < num_players - i -1; j++) {
            if (players[j].score < players[j+1].score) {
                player temp = players[j];
                players [j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }

    printf("\nFinal Results:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%d. %s - $%d\n", i + 1, players[i].name, players[i].score);
    }
}


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    
    // initialize each of the players in the array

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files

        // Execute the game until all questions are answered

        // Display the final results and exit
    }
    return EXIT_SUCCESS;
}
