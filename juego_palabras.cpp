#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

// Estructura para representar una palabra en la pantalla
struct FallingWord {
    string word;
    int position;
    int y; // Altura actual de la palabra
};

// Constantes del juego
const int SCREEN_WIDTH = 50;
const int SCREEN_HEIGHT = 20;

// Función para generar una palabra aleatoria
string generateWord() {
    vector<string> words = {"apple", "banana", "cherry", "dragon", "elephant", "flower", "grape", "house", "island", "jungle"};
    return words[rand() % words.size()];
}

// Función para imprimir el estado del juego
void printScreen(const vector<FallingWord>& fallingWords, int score) {
    system("clear"); // Limpia la pantalla (usa "cls" en Windows)

    vector<string> screen(SCREEN_HEIGHT, string(SCREEN_WIDTH, ' '));

    for (const auto& word : fallingWords) {
        if (word.y < SCREEN_HEIGHT) {
            for (size_t i = 0; i < word.word.size(); ++i) {
                if (word.position + i < SCREEN_WIDTH) {
                    screen[word.y][word.position + i] = word.word[i];
                }
            }
        }
    }

    for (const auto& line : screen) {
        cout << line << endl;
    }

    cout << "\nScore: " << score << endl;
    cout << "Type the words to catch them!" << endl;
}

// Función para mostrar el menú y obtener la velocidad seleccionada
int showMenu() {
    int speedOption;
    cout << "Welcome to Falling Words!" << endl;
    cout << "Choose difficulty level:" << endl;
    cout << "1. Easy (Slow)" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard (Fast)" << endl;
    cout << "Enter your choice: ";
    cin >> speedOption;

    switch (speedOption) {
        case 1: return 500; // Easy
        case 2: return 300; // Medium
        case 3: return 150; // Hard
        default: return 300; // Default to Medium
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<FallingWord> fallingWords;
    int score = 0;
    bool running = true;

    // Mostrar el menú y obtener la velocidad
    int SPEED = showMenu();

    // Hilo separado para capturar entrada del usuario
    thread inputThread([&]() {
        while (running) {
            string input;
            cin >> input;

            // Verificar si el input coincide con alguna palabra en pantalla
            for (auto it = fallingWords.begin(); it != fallingWords.end(); ++it) {
                if (it->word == input) {
                    score += 10;
                    fallingWords.erase(it);
                    break;
                }
            }
        }
    });

    while (running) {
        // Agregar nuevas palabras aleatorias
        if (rand() % 3 == 0) {
            FallingWord newWord = {generateWord(), rand() % (SCREEN_WIDTH - 10), 0};
            fallingWords.push_back(newWord);
        }

        // Actualizar la posición de las palabras
        for (auto& word : fallingWords) {
            word.y += 1;
            if (word.y >= SCREEN_HEIGHT) {
                running = false; // Termina el juego si una palabra toca el fondo
            }
        }

        // Imprimir el estado actual
        printScreen(fallingWords, score);

        // Esperar un poco antes de la siguiente actualización
        this_thread::sleep_for(chrono::milliseconds(SPEED));
    }

    // Finalizar el hilo de entrada
    running = false;
    inputThread.join();

    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}
