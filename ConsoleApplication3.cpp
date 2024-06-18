#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

const int BOARD_SIZE = 5;
const int TIME_LIMIT = 10;

void conditions(int& num1, int& num2, char& op) {
    num1 = rand() % 10 + 1;
    num2 = rand() % 10 + 1;
    int operation = rand() % 3;
    switch (operation) {
    case 0: op = '+'; break;
    case 1: op = '-'; break;
    case 2: op = '*'; break;
    }
}

bool playeranswer(int& playerAnswer, int timelimit) {
    using namespace std::chrono;
    auto start = steady_clock::now();
    std::thread inputThread([&playerAnswer]() {
        std::cin >> playerAnswer;
        });

    bool answered = false;
    for (int i = 0; i < timelimit; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (std::cin.rdbuf()->in_avail() > 0) {
            inputThread.join();
            answered = true;
            break;
        }
    }

    if (!answered) {
        std::cout << "\nTime is up." << std::endl;
        playerAnswer = -2;
        inputThread.detach();
        return false;
    }

    return true;
}

void playground(char board[BOARD_SIZE][BOARD_SIZE], int playerX, int playerY) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == playerX && j == playerY) {
                std::cout << "P ";
            }
            else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void start() {
    srand(time(0));

    char board[BOARD_SIZE][BOARD_SIZE];
    int playerX = 0, playerY = 0;
    int score = 0;
    int num1, num2;
    char op;
    int answer, playerAnswer;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '.';
        }
    }

    while (true) {
        playground(board, playerX, playerY);
        conditions(num1, num2, op);

        switch (op) {
        case '+': answer = num1 + num2; break;
        case '-': answer = num1 - num2; break;
        case '*': answer = num1 * num2; break;
        }

        std::cout << num1 << " " << op << " " << num2 << " = ? (You have " << TIME_LIMIT << " seconds) ";

        if (!playeranswer(playerAnswer, TIME_LIMIT)) {
            if (playerAnswer == -1) {
                break;
            }
            if (playerAnswer == -2) {
                std::cout << "Incorrect. Correct answer: " << answer << std::endl;
                continue;
            }
        }

        if (playerAnswer == answer) {
            std::cout << "Excellent!" << std::endl;
            score++;
            if (playerY < BOARD_SIZE - 1) {
                playerY++;
            }
            else if (playerX < BOARD_SIZE - 1) {
                playerY = 0;
                playerX++;
            }
        }
        else {
            std::cout << "Incorrect. Correct answer: " << answer << std::endl;
        }

        if (playerX == BOARD_SIZE - 1 && playerY == BOARD_SIZE - 1) {
            std::cout << "You win!" << std::endl;
            break;
        }
    }

    std::cout << "Game over. Your score: " << score << std::endl;
}

int main() {
    int choice;

    while (true) {
        std::cout << "Welcome!\nRules:\n1. You need to count fast.\n2. Time limited! But not be afraid you have 10 seconds per task.\n3. You need to answer 25 tasks.\nCreated by Kiva Mykhailo 25 group.\n**************\nPress 1 to start the game.\nPress 0 to exit." << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            start();
        }
        else if (choice == 0) {
            break;
        }
        else {
            std::cout << "Invalid choice, please press 1 to start the game, or 0 to exit." << std::endl;
        }
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}
