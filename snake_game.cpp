#include <iostream>
#include <time.h>
#include <string>
using namespace std;

bool gameOver; // game over flag

int width = 60; // width and height of game screen
int height = 20;

int x, y; // represent current position of the snake
int fruitX, fruitY; // represent the pos that the snake is going to eat
int score; // scores that player got

int tailX[100], tailY[100]; // arrays to store the pos of the snake's tail
int nTail; // records the length of the snake's tail

string fruit = "*"; // represents the mark of the fruit

enum Direction { // all possible directions that the snake will move
    STOP = 0,
    LEFT,
    RIGHT, 
    UP,
    DOWN
};
Direction dir;

void init(void)
{
    gameOver = false; 
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

/*Draw boundary for the game*/
void draw(void)
{
    int i; // represents the coordinate on the vertical axis
    int j; // represents the coordinate on the horizontal axis
    int k;
    bool print;

    system("clear"); // clears the console

    for (i = 0; i < width + 2; i++) // prints the top border of the game screen
    {
        cout << "#";
    }
    cout << endl;
    
    for (i = 1; i <= height; i++) // iterates each row of the game screen
    {
        for (j = 0; j < width + 2; j++) // iterates each col of the game screen
        {
            if (j == 0 || j == width) // prints the left-side and right-side border
            {
                cout << "#";
            }

            if (i == y && j == x) // print "o" if current pos matches the snake's head at (x, y)
            {
                cout << "o";
            }
            else if (i == fruitY && j == fruitX) // print "*" if current pos matches the fruit's pos
            {
                cout << fruit;
            }
            else 
            {
                print = false;
                for (k = 0; k < nTail; k++) 
                {
                    if (tailY[k] == i && tailX[k] == j) // if current pos matches any segment of the snake's tail, it will print "o" to present the snake's tail
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) // if current pos is not the snake and fruit exist, it will display empty
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    for (i = 0; i < width + 2; i++) // prints the bottom border of the game screen
    {
        cout << "#";
    }
    cout << endl;
    cout << "score:" << score << endl; // prints the score that the player got
}

/*Handling User Input in the game*/
void Input(void)
{
    int c = 0;
    
    while (1)
    {
        system("stty raw"); //stty — set the options for a terminal device interface
                            // If set stty in the raw mode, then no input or output processing is performed.  
                            // All input will just sent straight through. 
        system("stty -echo"); // To hide the input
        c = getchar();
        system("stty cooked"); // The terminal driver is a line-based system. 
                               // Characters are buffered internally until a carriage return (Enter or Return) 
                               // before it is passed to the program - this is called "cooked". 
        switch (c)
        {
            case 'w':
                dir = UP;
                //cout << "UP" << endl;
                break;
            case 'a':
                dir = LEFT;
                //cout << "LEFT" << endl;
                break;
            case 's':
                dir = DOWN;
                //cout << "DOWN" << endl;
                break;
            case 'd':
                dir = RIGHT;
                //cout << "RIGHT" << endl;
                break;
            case 'x':
                gameOver = true;
                cout << "Game Over" << endl;
                system("stty cooked");
                system("stty echo"); // Stop hiding the input
                exit(0);
                break;
        }
    }
    return;
}


int main(void)
{
    init();
    draw();
    Input();
}
