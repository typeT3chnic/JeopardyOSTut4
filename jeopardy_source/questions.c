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
#include <strings.h>
#include "questions.h"

char categories[NUM_CATEGORIES][MAX_LEN] = {
    "programming", 
    "algorithms", 
    "databases"
};

question questions[NUM_QUESTIONS];

// Initializes the array of questions for the game
void initialize_game(void)
{
    int index = 0;

    // -------- Programming --------
    strcpy(questions[index].category, "programming");
    strcpy(questions[index].question, "What keyword is used to define a function in C that does not return a value?");
    strcpy(questions[index].answer, "void");
    questions[index].value = 100;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "programming");
    strcpy(questions[index].question, "What symbol is used to access a pointer's value?");
    strcpy(questions[index].answer, "*");
    questions[index].value = 200;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "programming");
    strcpy(questions[index].question, "What header file is required for printf?");
    strcpy(questions[index].answer, "stdio.h");
    questions[index].value = 300;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "programming");
    strcpy(questions[index].question, "What loop is guaranteed to run at least once?");
    strcpy(questions[index].answer, "do while");
    questions[index].value = 400;
    questions[index].answered = false;
    index++;

    // -------- Algorithms --------
    strcpy(questions[index].category, "algorithms");
    strcpy(questions[index].question, "What is the time complexity of binary search?");
    strcpy(questions[index].answer, "O(log n)");
    questions[index].value = 100;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "algorithms");
    strcpy(questions[index].question, "What data structure uses FIFO?");
    strcpy(questions[index].answer, "queue");
    questions[index].value = 200;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "algorithms");
    strcpy(questions[index].question, "What sorting algorithm repeatedly swaps adjacent elements?");
    strcpy(questions[index].answer, "bubble sort");
    questions[index].value = 300;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "algorithms");
    strcpy(questions[index].question, "What traversal uses a stack implicitly?");
    strcpy(questions[index].answer, "depth first search");
    questions[index].value = 400;
    questions[index].answered = false;
    index++;

    // -------- Databases --------
    strcpy(questions[index].category, "databases");
    strcpy(questions[index].question, "What does SQL stand for?");
    strcpy(questions[index].answer, "structured query language");
    questions[index].value = 100;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "databases");
    strcpy(questions[index].question, "What SQL command is used to retrieve data?");
    strcpy(questions[index].answer, "select");
    questions[index].value = 200;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "databases");
    strcpy(questions[index].question, "What key uniquely identifies a record?");
    strcpy(questions[index].answer, "primary key");
    questions[index].value = 300;
    questions[index].answered = false;
    index++;

    strcpy(questions[index].category, "databases");
    strcpy(questions[index].question, "What clause filters results?");
    strcpy(questions[index].answer, "where");
    questions[index].value = 400;
    questions[index].answered = false;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    printf("\n%-15s %-15s %-15s\n",
           categories[0],
           categories[1],
           categories[2]);

    for (int value = 100; value <= 400; value += 100)
    {
        for (int c = 0; c < NUM_CATEGORIES; c++)
        {
            bool found = false;

            for (int i = 0; i < NUM_QUESTIONS; i++)
            {
                if (strcmp(questions[i].category, categories[c]) == 0 &&
                    questions[i].value == value)
                {
                    if (!questions[i].answered)
                        printf("%-15d", value);
                    else
                        printf("%-15s", "X");

                    found = true;
                }
            }

            if (!found)
                printf("%-15s", " ");
        }
        printf("\n");
    }
}

//Validates if the category entered by the user is valid
bool valid_category(char *category)
{
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (strcasecmp(categories[i], category) == 0)
            return true;
    }
    return false;
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 &&
            questions[i].value == value)
        {
            printf("\nQuestion for %s - $%d:\n",
                   category, value);
            printf("%s\n", questions[i].question);
            return;
        }
    }

    printf("Question not found.\n");
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 &&
            questions[i].value == value)
        {

            // Tokenize the user input
            char temp[MAX_LEN];
            strcpy(temp, answer);

            char *token = strtok(temp, " ");
            if (token == NULL)
                return false;

            // Check first word: "what" or "who"
            if (strcasecmp(token, "what") != 0 &&
                strcasecmp(token, "who") != 0)
                return false;

            // Check second word: "is"
            token = strtok(NULL, " ");
            if (token == NULL || strcasecmp(token, "is") != 0)
                return false;

            // The rest is the actual answer - get everything after "what is " or "who is "
            char *actual_answer = strtok(NULL, "\0");
            if (actual_answer == NULL)
                return false;

            // Trim leading/trailing whitespace from actual_answer
            while (*actual_answer == ' ') actual_answer++;
            int len = strlen(actual_answer);
            while (len > 0 && actual_answer[len-1] == ' ') len--;
            actual_answer[len] = '\0';

            if (strcasecmp(questions[i].answer, actual_answer) == 0)
            {
                questions[i].answered = true;
                return true;
            }
            else {
                questions[i].answered = true;
                return false;
            }
        }
    }



    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 &&
            questions[i].value == value)
        {
            return questions[i].answered;
        }
    }
    return false;
}
