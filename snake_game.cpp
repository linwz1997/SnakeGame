#include <iostream>
#include <time.h>
#include <string>
#include <unistd.h>  
#include <fcntl.h>
using namespace std;

bool gameOver; // game over flag

int width = 60; // width of game screen
int height = 20; // height of game screen

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
    dir = RIGHT; //Set initial movement as RIGHT
    x = width / 2;
    y = height / 2;
    srand((unsigned) time(0)); // To prevent from the pos always the same in everytime
    fruitX = rand() % width + 1;
    fruitY = rand() % height + 1;
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
    char buf[1];
    system("stty raw"); //stty — set the options for a terminal device interface
                        // If set stty in the raw mode, then no input or output processing is performed.  
                        // All input will just sent straight through. 
    system("stty -echo"); // To hide the input
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK); // To get char without being blocked.
                                                       // if using getchar(), the while(1) loop will be blocked. 
    read(0, buf, 1); // Read 1 byte data from the stdin buffer "buf".
    system("stty cooked"); // The terminal driver is a line-based system. 
                            // Characters are buffered internally until a carriage return (Enter or Return) 
                            // before it is passed to the program - this is called "cooked". 
    
    switch (buf[0])
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
            break;
    }
        
    return;
}

/*Setup the game logic*/
void GameLogic(void)
{
    int prevX, prevY; //Store the previous pos of the snake's head
    int prev2X, prev2Y;
    int i;

    prevX = tailX[0];
    prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;

    for (i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    if (dir)
    {
        switch (dir)
        {
            case LEFT:
                x--;
                dir = LEFT;
                break;
            case RIGHT:
                x++;
                dir = RIGHT;
                break;
            case UP:
                y--;
                dir = UP;
                break;
            case DOWN:
                y++;
                dir = DOWN;
                break;
        }
    }
    
    if (((x > width) || (x < 0)) || (y > height) || (y <= 0))
    {
        cout << "Hit the wall" << endl;
        cout << "Game Over" << endl;
        gameOver = true;
        return;
    }

    for (i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            cout << "Hit the tail" << endl;
            cout << "Game Over" << endl;
            gameOver = true;
            return;
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 1;
        nTail++;
        srand((unsigned) time(0));
        fruitX = rand() % width + 1;
        fruitY = rand() % height + 1;
    }

    if (score <= 3)
    {
        usleep(500000);
    }
    else if (score > 3 && score <= 7)
    {
        usleep(300000);
    }
    else if (score > 7)
    {
        usleep(100000);
    }

    return;
}


int main(void)
{
    init();

    while (1)
    {
        draw();
        Input();
        GameLogic();
        if (gameOver)
        {
            system("stty cooked");
            system("stty echo");
            exit(0);
        }
    }
}
