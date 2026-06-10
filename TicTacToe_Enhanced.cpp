#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

class Account
{
private:
    string username;
    string password;

public:
    void setUsername(string u) { username = u; }
    void setPassword(string p) { password = p; }

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    void saveToFile() const
    {
        ofstream file(username + ".txt");

        if (file.is_open())
        {
            file << username << endl;
            file << password << endl;
            file.close();
            cout << "\nAccount created successfully.\n";
        }
        else
        {
            cout << "\nError saving account.\n";
        }
    }

    bool loadFromFile(string u)
    {
        ifstream file(u + ".txt");

        if (file.is_open())
        {
            getline(file, username);
            getline(file, password);
            file.close();
            return true;
        }

        return false;
    }
};

void mainMenu();
int getValidNumber(int min, int max);
void matchRoom();
void playRound(string playerX, string playerO, int& scoreX, int& scoreO, int& draws, char startingPlayer);
void printDashboard(string playerX, string playerO, int scoreX, int scoreO, int draws);
void printBoard(char board[4][4], int size);
char checkWinner(char board[4][4], int size);

int main()
{
    Account account;
    int choice;

    do
    {
        mainMenu();
        choice = getValidNumber(1, 3);

        if (choice == 1)
        {
            string username, password;

            cout << "\nCreate username: ";
            cin >> username;

            cout << "Create password: ";
            cin >> password;

            account.setUsername(username);
            account.setPassword(password);
            account.saveToFile();
        }
        else if (choice == 2)
        {
            string username, password;

            cout << "\nUsername: ";
            cin >> username;

            cout << "Password: ";
            cin >> password;

            if (account.loadFromFile(username) && password == account.getPassword())
            {
                cout << "\nLogin successful. Welcome, " << username << "!\n";
                matchRoom();
            }
            else
            {
                cout << "\nInvalid username or password.\n";
            }
        }
        else
        {
            cout << "\nGoodbye!\n";
        }

    } while (choice != 3);

    return 0;
}

void mainMenu()
{
    cout << "\n=============================\n";
    cout << "        TIC TAC TOE\n";
    cout << "=============================\n";
    cout << "1. Create Account\n";
    cout << "2. Login and Play\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";
}

int getValidNumber(int min, int max)
{
    int number;

    while (true)
    {
        cin >> number;

        if (cin.fail() || number < min || number > max)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number from " << min << " to " << max << ": ";
        }
        else
        {
            return number;
        }
    }
}

void matchRoom()
{
    string playerX, playerO;
    int scoreX = 0;
    int scoreO = 0;
    int draws = 0;
    char again;
    char startingPlayer = 'X';

    cout << "\nEnter Player X name: ";
    cin >> playerX;

    cout << "Enter Player O name: ";
    cin >> playerO;

    do
    {
        playRound(playerX, playerO, scoreX, scoreO, draws, startingPlayer);

        if (startingPlayer == 'X')
            startingPlayer = 'O';
        else
            startingPlayer = 'X';

        cout << "\nDo you want to play another round with the same players? (Y/N): ";
        cin >> again;

    } while (again == 'Y' || again == 'y');

    cout << "\nFinal Match Result:\n";
    printDashboard(playerX, playerO, scoreX, scoreO, draws);

    if (scoreX > scoreO)
        cout << "Overall winner: " << playerX << "!\n";
    else if (scoreO > scoreX)
        cout << "Overall winner: " << playerO << "!\n";
    else
        cout << "Overall result: Tie!\n";

    cout << "\nReturning to main menu...\n";
}

void printDashboard(string playerX, string playerO, int scoreX, int scoreO, int draws)
{
    cout << "\n========== SCOREBOARD ==========\n";
    cout << playerX << " (X): " << scoreX << " points\n";
    cout << playerO << " (O): " << scoreO << " points\n";
    cout << "Draws: " << draws << endl;
    cout << "================================\n";
}

void playRound(string playerX, string playerO, int& scoreX, int& scoreO, int& draws, char startingPlayer)
{
    int size;

    cout << "\nChoose board size:\n";
    cout << "1. 3 x 3\n";
    cout << "2. 4 x 4\n";
    cout << "Choice: ";

    int boardChoice = getValidNumber(1, 2);

    if (boardChoice == 1)
        size = 3;
    else
        size = 4;

    char board[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = ' ';
        }
    }

    char currentPlayer = startingPlayer;
    int moves = 0;
    int maxMoves = size * size;
    bool gameOver = false;

    while (!gameOver)
    {
        printDashboard(playerX, playerO, scoreX, scoreO, draws);
        printBoard(board, size);

        string currentName;

        if (currentPlayer == 'X')
            currentName = playerX;
        else
            currentName = playerO;

        cout << currentName << " (" << currentPlayer << "), choose a cell from 1 to " << maxMoves << ": ";

        int cell = getValidNumber(1, maxMoves);

        int row = (cell - 1) / size;
        int col = (cell - 1) % size;

        if (board[row][col] != ' ')
        {
            cout << "\nThis cell is already taken. Choose another cell.\n";
            continue;
        }

        board[row][col] = currentPlayer;
        moves++;

        char winner = checkWinner(board, size);

        if (winner != ' ')
        {
            printBoard(board, size);

            if (winner == 'X')
            {
                cout << "\n" << playerX << " wins this round!\n";
                scoreX++;
            }
            else
            {
                cout << "\n" << playerO << " wins this round!\n";
                scoreO++;
            }

            printDashboard(playerX, playerO, scoreX, scoreO, draws);
            gameOver = true;
        }
        else if (moves == maxMoves)
        {
            printBoard(board, size);
            cout << "\nThis round is a draw!\n";
            draws++;
            printDashboard(playerX, playerO, scoreX, scoreO, draws);
            gameOver = true;
        }
        else
        {
            if (currentPlayer == 'X')
                currentPlayer = 'O';
            else
                currentPlayer = 'X';
        }
    }
}

void printBoard(char board[4][4], int size)
{
    cout << "\n";

    int cellNumber = 1;

    for (int i = 0; i < size; i++)
    {
        cout << " ";

        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == ' ')
                cout << cellNumber;
            else
                cout << board[i][j];

            if (j < size - 1)
                cout << " | ";

            cellNumber++;
        }

        cout << endl;

        if (i < size - 1)
        {
            for (int k = 0; k < size; k++)
            {
                cout << "---";

                if (k < size - 1)
                    cout << "+";
            }

            cout << endl;
        }
    }

    cout << endl;
}

char checkWinner(char board[4][4], int size)
{
    for (int i = 0; i < size; i++)
    {
        bool rowWin = true;
        bool colWin = true;

        for (int j = 1; j < size; j++)
        {
            if (board[i][j] != board[i][0] || board[i][0] == ' ')
                rowWin = false;

            if (board[j][i] != board[0][i] || board[0][i] == ' ')
                colWin = false;
        }

        if (rowWin)
            return board[i][0];

        if (colWin)
            return board[0][i];
    }

    bool diagonalOne = true;
    bool diagonalTwo = true;

    for (int i = 1; i < size; i++)
    {
        if (board[i][i] != board[0][0] || board[0][0] == ' ')
            diagonalOne = false;

        if (board[i][size - 1 - i] != board[0][size - 1] || board[0][size - 1] == ' ')
            diagonalTwo = false;
    }

    if (diagonalOne)
        return board[0][0];

    if (diagonalTwo)
        return board[0][size - 1];

    return ' ';
}
