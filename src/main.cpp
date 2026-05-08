#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void x3Game();
void x4Game();
void menu();

class Player
{
    private:
    string name;
    string password;
    int score;

    public:
    void setName(string);
    void setPassword(string);
    void setScore(int);
    string getName() const;
    string getPassword() const;
    int getScore() const;
    void print() const;
};

void Player::setName(string n)
{
    name=n;
}

void Player::setPassword(string p)
{
    password=p;
}

void Player::setScore(int s)
{
    score=s;
}

string Player::getName() const
{
    return name;
}

string Player::getPassword() const
{
    return password;
}

int Player::getScore() const
{
    return score;
}

void Player::print() const
{
    string ans;
    cout<<"The name of the player is: "<<name<<endl;
    cout<<"Player's score is: "<<score<<endl;
    cout<<"Do you want to view your password?"<<endl;
    cin>>ans;
    if (ans=="yes")
    {
        cout<<"The password is: "<<password<<endl;
    }
}

int main() 
{
    Player X, O;
    int choice;
    string playerName, ans, name, password;

    do {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                cout << "Enter your username: ";
                cin >> name;
                X.setName(name);
                cout << "Enter your password: ";
                cin >> password;
                X.setPassword(password);
                playerName = name;
                cout << "Account saved in file successfully." << endl;
                cout << "The Tic-Tac-Toe Rules are: " << endl;
                cout << "---------------------------------------------------------------------------------------------" << endl;
                cout << "1. A player can put only a single letter X or O in the 3 x 3 or 4 x 4 grid in each chance." << endl;
                cout << "2. Both players will get chances alternatively one after another till someone wins or draws." << endl;
                cout << "3. To win this game, the player must create a horizontal, vertical";
                cout << "or diagonal line consisting of three same letters." << endl;
                cout << "The game is drawn, if all grids are filled with X or O letters but no line is made." << endl;
                cout << "Game Started!!" << endl;
                cout << "Would you like to play 3x3 or 4x4? ";
                cin >> ans;
                while (ans != "3x3" && ans != "4x4") 
                {
                    cout << "Invalid choice. Please enter 3x3 or 4x4: ";
                    cin >> ans;
                }
                if (ans == "3x3") 
                {
                    x3Game();
                } else if (ans == "4x4") 
                {
                    x4Game();
                }
                break;
            }

            case 2: 
            {
                string name, password;
                cout << "------------------" << endl;
                cout << "    Login in: " << endl;
                cout << "------------------" << endl;
                cout << "Enter your username: ";
                cin >> name;
                cout << "Enter your password: ";
                cin >> password;
                playerName = name;
                if (name == X.getName() && password == X.getPassword()) 
                {
                    cout << "Logged in Successfully. Welcome back, " << playerName << endl;
                    cout << "Would you like to play 3x3 or 4x4? ";
                    cin >> ans;
                    while (ans != "3x3" && ans != "4x4") 
                    {
                        cout << "Invalid choice. Please enter 3x3 or 4x4: ";
                        cin >> ans;
                    }
                    if (ans == "3x3") 
                    {
                        x3Game();
                    } 
                    else if (ans == "4x4") 
                    {
                        x4Game();
                    }
                } 
                else 
                {
                    cout << "Invalid username or password. Please try again." << endl;
                }
                break;
            }

            case 3: 
            {
                cout << "Exiting the game! Bye Bye." << endl;
                break;
            }

            default: 
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 3);
    return 0;
}

void menu()
{
    cout<<"  Main Menu "<<endl;
    cout<<"--------------"<<endl;
    cout<<"1. Login" <<endl;
    cout<<"2. Continue Saved Games" <<endl;
    cout<<"3. Exit" <<endl;
    cout<<"--------------"<<endl;
}

void printBoard(char board[3][3]) 
{ 
    cout << "-------------\n"; 
    for (int i = 0; i < 3; i++) 
    { 
        cout << "| "; 
        for (int j = 0; j < 3; j++) 
        { 
            cout << board[i][j] << " | "; 
        } 
        cout << "\n-------------\n"; 
    } 
} 

char checkWin(char board[3][3]) 
{
    for (int i = 0; i < 3; ++i) 
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];
    return ' ';
}

void x3Game() 
{
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char currentPlayer = 'X';
    int moves = 0;

    while (moves < 9) 
    {
        cout << "Current board:" << endl;
        printBoard(board);

        int row, col;
        cout << "Player " << currentPlayer << ", enter row and column (0-2): ";
        cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') 
        {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row][col] = currentPlayer;
        ++moves;

        char winner = checkWin(board);
        if (winner != ' ') 
        {
            cout << "Player " << winner << " wins!" << endl;
            printBoard(board);
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    if (moves == 9) 
    {
        cout << "It's a draw!" << endl;
        printBoard(board);
    }
}

void printBoard(char board[4][4]) 
{ 
    cout << "-----------------\n"; 
    for (int i = 0; i < 4; i++) 
    { 
        cout << "| "; 
        for (int j = 0; j < 4; j++) 
        { 
            cout << board[i][j] << " | "; 
        } 
        cout << "\n-----------------\n"; 
    } 
} 

char checkWin(char board[4][4]) 
{
    for (int i = 0; i < 4; ++i) 
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] == board[i][3] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] == board[3][i] && board[0][i] != ' ')
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] == board[3][3] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][3] == board[1][2] && board[1][2] == board[2][1] && board[2][1] == board[3][0] && board[0][3] != ' ')
        return board[0][3];
    return ' ';
}

void x4Game() 
{
    char board[4][4] = {{' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}};
    char currentPlayer = 'X';
    int moves = 0;

    while (moves < 16) 
    {
        cout << "Current board:" << endl;
        printBoard(board);

        int row, col;
        cout << "Player " << currentPlayer << ", enter row and column (0-3): ";
        cin >> row >> col;

        if (row < 0 || row > 3 || col < 0 || col > 3 || board[row][col] != ' ') 
        {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row][col] = currentPlayer;
        ++moves;

        char winner = checkWin(board);
        if (winner != ' ') 
        {
            cout << "Player " << winner << " wins!" << endl;
            printBoard(board);
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    if (moves == 16) 
    {
        cout << "It's a draw!" << endl;
        printBoard(board);
    }
}
