#include <iostream>  // Biblioteca estándar para entrada y salida
#include <conio.h>   // Biblioteca para detección de teclas (no estándar, pero común en Windows)
#include <windows.h> // Biblioteca para la función Sleep(), usada para ralentizar el juego
using namespace std;

// Variables globales para el estado del juego
bool gameOver; // Indica si el juego ha terminado
const int width = 20; // Ancho del tablero
const int height = 20; // Altura del tablero
int x, y; // Posición actual de la cabeza de la serpiente
int fruitX, fruitY; // Posición de la fruta
int score; // Puntuación del jugador
int tailX[100], tailY[100]; // Arreglos para almacenar las posiciones del cuerpo de la serpiente
int nTail; // Tamaño actual de la cola de la serpiente
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Direcciones posibles
eDirection dir; // Dirección actual de la serpiente

// Configuración inicial del juego
void Setup() {
    gameOver = false; // El juego no ha terminado
    dir = STOP; // La serpiente está inicialmente detenida
    x = width / 2; // Posición inicial de la cabeza de la serpiente (centro del tablero)
    y = height / 2;
    fruitX = rand() % width; // Genera una posición aleatoria para la fruta en el eje X
    fruitY = rand() % height; // Genera una posición aleatoria para la fruta en el eje Y
    score = 0; // La puntuación comienza en 0
}

// Función para dibujar el tablero del juego
void Draw() {
    system("cls"); // Limpia la pantalla para redibujar el tablero
    // Dibuja la pared superior
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Dibuja el tablero y los elementos del juego
    for (int i = 0; i < height; i++) { // Recorre las filas del tablero
        for (int j = 0; j < width; j++) { // Recorre las columnas
            if (j == 0) cout << "#"; // Dibuja la pared izquierda
            if (i == y && j == x)
                cout << "O"; // Dibuja la cabeza de la serpiente
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Dibuja la fruta
            else {
                bool print = false; // Variable para determinar si hay que dibujar un segmento de cola
                for (int k = 0; k < nTail; k++) { // Recorre el cuerpo de la serpiente
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Dibuja un segmento de la cola
                        print = true;
                    }
                }
                if (!print) cout << " "; // Espacio vacío si no hay nada
            }
            if (j == width - 1) cout << "#"; // Dibuja la pared derecha
        }
        cout << endl;
    }

    // Dibuja la pared inferior
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Muestra la puntuación del jugador
    cout << "Score: " << score << endl;
}

// Función para procesar la entrada del jugador
void Input() {
    if (_kbhit()) { // Comprueba si se ha presionado una tecla
        switch (_getch()) { // Lee la tecla presionada
        case 'a': // Tecla 'a' para mover a la izquierda
            dir = LEFT;
            break;
        case 'd': // Tecla 'd' para mover a la derecha
            dir = RIGHT;
            break;
        case 'w': // Tecla 'w' para mover hacia arriba
            dir = UP;
            break;
        case 's': // Tecla 's' para mover hacia abajo
            dir = DOWN;
            break;
        case 'x': // Tecla 'x' para salir del juego
            gameOver = true;
            break;
        }
    }
}

// Función que implementa la lógica principal del juego
void Logic() {
    // Actualiza las posiciones de la cola de la serpiente
    int prevX = tailX[0]; // Almacena la posición previa de la cabeza en X
    int prevY = tailY[0]; // Almacena la posición previa de la cabeza en Y
    int prev2X, prev2Y; // Variables para el intercambio de posiciones
    tailX[0] = x; // La nueva posición de la cabeza se convierte en la primera parte de la cola
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) { // Recorre cada segmento de la cola
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX; // Actualiza la posición del segmento actual
        tailY[i] = prevY;
        prevX = prev2X; // Pasa a la siguiente posición
        prevY = prev2Y;
    }

    // Actualiza la posición de la cabeza según la dirección
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Termina el juego si la serpiente toca los límites del tablero
    if (x < 0 || x >= width || y < 0 || y >= height) {
        gameOver = true;
    }

    // Comprueba si la cabeza colisiona con la fruta
    if (x == fruitX && y == fruitY) {
        score += 10; // Incrementa la puntuación
        fruitX = rand() % width; // Genera una nueva posición para la fruta
        fruitY = rand() % height;
        nTail++; // Incrementa el tamaño de la cola
    }
}

// Función principal del programa
int main() {
    Setup(); // Configura el juego
    while (!gameOver) { // Bucle principal del juego
        Draw(); // Dibuja el estado actual del juego
        Input(); // Procesa la entrada del jugador
        Logic(); // Ejecuta la lógica del juego
        Sleep(100); // Pausa para ralentizar el juego (100 ms)
    }
    cout << "Game Over! Final Score: " << score << endl; // Muestra la puntuación final
    return 0; // Finaliza el programa
}
