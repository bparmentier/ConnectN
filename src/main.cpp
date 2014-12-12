#include <iostream>
#include <string>
#include "ConnectN.h"
#include "Player.h"
#include "libs/keyboard.hpp"

using namespace std;


/*!
 * \brief Print ConnectN logo
 */
void printLogo()
{
    cout << "   ____                            _   _   _ " << endl;
    cout << "  / ___|___  _ __  _ __   ___  ___| |_| \\ | |" << endl;
    cout << " | |   / _ \\| '_ \\| '_ \\ / _ \\/ __| __|  \\| |" << endl;
    cout << " | |__| (_) | | | | | | |  __/ (__| |_| |\\  |" << endl;
    cout << "  \\____\\___/|_| |_|_| |_|\\___|\\___|\\__|_| \\_|" << endl;
    cout << "                             Bruno Parmentier" << endl;
    cout << endl;
}

/*!
 * \brief Main program
 * \return 0 if everything went fine
 */
int main()
{
    ConnectN game;
    unsigned power;
    unsigned line;
    unsigned column;
    unsigned columnIn;
    char customGame;
    string namePlayer1;
    string namePlayer2;

    printLogo();

    try {
        cout << "Choose game size? (y/[N]) ";
        customGame = nvs::lineFromKbd<char>();
    } catch (const nvs::bad_string_convert) {
        customGame = 'N';
    }

    if (customGame == 'y' || customGame == 'Y') {
        /* Number of pieces */
        do {
            cout << "Number of pieces? (3-10) ";
            try {
                power = nvs::lineFromKbd<unsigned>();
            } catch (const nvs::bad_string_convert &e) {
                cout << e.what() << endl;
            }
        } while (power < ConnectN::MIN_POWER || power > ConnectN::MAX_POWER);

        /* Number of lines */
        do {
            cout << "Number of lines? (" << power << "-" << power + 10 << ") ";
            try {
                line = nvs::lineFromKbd<unsigned>();
            } catch (const nvs::bad_string_convert &e) {
                cout << e.what() << endl;
            }
        } while (line < power || line > power + 10);

        /* Number of columns */
        do {
            cout << "Number of columns? (" << power << "-" << power + 10 << ") ";
            try {
                column = nvs::lineFromKbd<unsigned>();
            } catch (const nvs::bad_string_convert &e) {
                cout << e.what() << endl;
            }
        } while (column < power || column > power + 10);

        /* Custom game initialization */
        game = ConnectN(power, line, column);
    } else {
        /* Default game initialization */
        //game = ConnectN();
    }

    /* Player1 name */
    do {
        try {
            cout << "Name of player 1 : ";
            namePlayer1 = nvs::lineFromKbd<string>();
        } catch (const nvs::bad_string_convert &e) {
            cout << "Please enter a name" << endl;
        }
    } while (namePlayer1.empty());

    /* Player2 name */
    do {
        try {
            cout << "Name of player 2 : ";
            namePlayer2 = nvs::lineFromKbd<string>();
        } catch (const nvs::bad_string_convert &e) {
            cout << "Please enter a name" << endl;
        }
    } while (namePlayer2.empty());

    Player player1 { namePlayer1.c_str() };
    Player player2 { namePlayer2.c_str() };

    /* Enroll the two players */
    game.enroll(&player1);
    game.enroll(&player2);

    /* Game is started */
    while (!(game.finished())) {
        try {
            cout << endl;
            cout << "You are playing a Connect" << game.power() << endl << endl;
            cout << game << endl;
            cout << game.activePlayer()->name() << "'s turn";
            cout << " (" << game.color(game.activePlayer()) << "): ";
            columnIn = nvs::lineFromKbd<unsigned>();
            try {
                game.play(columnIn);
            } catch (const std::out_of_range &e) {
                cout << e.what() << endl;
            } catch (const std::logic_error &e) {
                cout << e.what() << endl;
            }
        } catch (const nvs::bad_string_convert &e) {
            cout << e.what() << endl;
        }
    }

    cout << endl;
    cout << game << endl;

    if (game.winner() != nullptr) {
        cout << "Winner: " << game.winner()->name();
        cout << " (" << game.color(game.winner()) << ")" << endl;
    } else {
        cout << "No winner!" << endl;
    }

    return 0;
}

