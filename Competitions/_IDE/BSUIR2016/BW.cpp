#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
char input_code[4] = {0,}; //Code which needs to be cracked
char g_code[4] = {0,}; //code guessed by user or algorithm
char a_code[4] = {0,}; //code guessed by user or algorithm
char solution[4] = {(char) 255,}; //Holds the correct solutions
char checked[4] = {0,}; //With bits, holds information which color has been checked in corresponding slot
char incorrect[4] = {(char) 255,}; //Hold information which color was misplaced
char randNum; //just random number variable

//----------------------------------------------------------
// Function for returning the results of guess
//    0 - incorrect
//    1 - correct
//    2 - misplaced
//----------------------------------------------------------
void checkIfCorrect(char guess[], char result[], char code[])
{

    result[0] = 0;
    result[1] = 0;
    char blacks[4] = {0};
    char whites[4] = {0};


    for(int i=0; i<4; i++)
    {
        if(guess[i] == code[i])
            blacks[i]=1;
        else
            blacks[i]=0;
    }

    for(int i=0; i<4; i++)
    {
        if(blacks[i]!=1)
        {
            for(int f=0; f<4; f++)
            {
                if(f==i) continue;
                if((guess[i] == code[f] && blacks[f] != 1))
                    if(whites[f] == 0)
                    {
                        whites[f]=1;
                        break;
                    }
            }
        }
    }

    for(int i=0; i<4; i++)
    {
        result[0] += blacks[i];
        result[1] += whites[i];
    }

}


int scoreCalculator(int black, int white)
{
    if(black == 0 && white == 0) return 0;
    if(black == 0 && white == 1) return 1;
    if(black == 1 && white == 0) return 2;
    if(black == 0 && white == 2) return 3;
    if(black == 1 && white == 1) return 4;
    if(black == 2 && white == 0) return 5;
    if(black == 0 && white == 3) return 6;
    if(black == 1 && white == 2) return 7;
    if(black == 2 && white == 1) return 8;
    if(black == 3 && white == 0) return 9;
    if(black == 0 && white == 4) return 10;
    if(black == 1 && white == 3) return 11;
    if(black == 2 && white == 2) return 12;
    if(black == 4 && white == 0) return 13;
}

void base10counter (char *num)
{
    num[3]++;
    if(num[3] == 10)
    {
        num[2]++;
        if(num[2] == 10)
        {
            num[1]++;
            if(num[1] == 10)
            {
                num[0]++;
                if(num[0]==10) num[0] = 0;
                num[1] = 0;
            }
            num[2] = 0;
        }
        num[3] = 0;
    }
}

int main()
{
    srand(time(NULL));

    //memset(g_code,0,4);
    memset(solution,255,4);
    memset(checked,0,4);
    memset(incorrect, 255, 4);
    cout << "Put 4 number code in with values from 0 to 5! (with spaces)" << endl << "For example: 0 3 4 2" << endl;
    scanf("%d%d%d%d", &input_code[0], &input_code[1], &input_code[2], &input_code[3]);

    int guesses = 0;
    char result[] = {0, 0};

    g_code[0] = 0; g_code[1] = 0; g_code[2] = 1; g_code[3] = 1;
    a_code[0] = 0; a_code[1] = 0; a_code[2] = 1; a_code[3] = 1;
    char previous_answers[12][4];
    char previous_scores[12];
    while(guesses < 15)
    {
        guesses++;


        cout << "Code: ";
        //scanf("%d%d%d%d", &g_code[0], &g_code[1], &g_code[2], &g_code[3]);
        printf("%d %d %d %d",g_code[0],g_code[1],g_code[2],g_code[3]);
        //reset the misplaced variables

        checkIfCorrect(g_code, result, input_code); //Check how if the guess was correct
        int score = scoreCalculator(result[0],result[1]);

        previous_answers[guesses-1][0] = g_code[0];
        previous_answers[guesses-1][1] = g_code[1];
        previous_answers[guesses-1][2] = g_code[2];
        previous_answers[guesses-1][3] = g_code[3];

        previous_scores[guesses-1] = score;

        if(result[0] == 4)
            break;

        bool anySolutions = true;

        while(anySolutions)
        {
            bool consistent = true;
            for(int i=0; i<guesses; i++)
            {
                checkIfCorrect(a_code, result, previous_answers[i]);
                int test_score = scoreCalculator(result[0],result[1]);
                if(test_score != previous_scores[i])
                {
                    consistent = false;
                    break;
                }
            }
            if(consistent)
                break;

            base10counter (a_code);
            if(a_code[0] == 0 && a_code[1] == 0 && a_code[2] == 1 && a_code[3] == 1)
            {
                anySolutions = false;
                printf("ERROR: No solution possible!\n");
            }
        }


        g_code[0] = a_code[0];
        g_code[1] = a_code[1];
        g_code[2] = a_code[2];
        g_code[3] = a_code[3];

        printf("\n[ %d ; %d ]  ----  My best guess: [%d %d %d %d]\n", result[0],result[1],a_code[0],a_code[1],a_code[2],a_code[3]);

        if(guesses == 8)
            printf("\n-- %d %d %d %d -- \n",input_code[0],input_code[1],input_code[2],input_code[3]);


    }

    if(result[0] == 4)
    {
        cout << "\n\nI won the game, in " << guesses << " turns!" << endl << "Your code was: ";
        printf("[%d %d %d %d]\n", g_code[0],g_code[1],g_code[2],g_code[3]);
    }
    else
        cout << "\n\nI\'m are crap in this game!" << endl;

    return 0;
}