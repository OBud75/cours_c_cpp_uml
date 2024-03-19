#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> maze;
int playerX, playerY;

bool loadMaze(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        maze.push_back(line);
    }
    file.close();

    for (size_t y = 0; y < maze.size(); y++) {
        for (size_t x = 0; x < maze[y].size(); x++) {
            if (maze[y][x] == 'P') {
                playerX = x;
                playerY = y;
                return true;
            }
        }
    }

    std::cerr << "Position du joueur introuvable dans le fichier." << std::endl;
    return false;
}

void printMaze() {
    system("cls");
    for (const auto& line : maze) {
        std::cout << line << '\n';
    }
    std::cout << "Deplacez-vous avec 'z' (haut), 's' (bas), 'q' (gauche), 'd' (droite). Appuyez sur 'x' pour quitter.\n";
}

bool movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (maze[newY][newX] == ' ' || maze[newY][newX] == 'S') {
        maze[playerY][playerX] = ' ';
        playerX = newX;
        playerY = newY;

        if (maze[playerY][playerX] == 'S') {
            std::cout << "Bravo ! Vous avez trouve la sortie !" << std::endl;
            std::cout << "Appuyez sur n'importe quelle touche pour quitter." << std::endl;
            _getch();
            return false;
        }

        maze[playerY][playerX] = 'P';
        return true;
    }
    return false;
}

int main() {
    if (!loadMaze("labyrinthe.txt")) {
        return -1;
    }

    printMaze();
    bool running = true;
    while (running) {
        if (_kbhit()) {
            char key = _getch();
            bool moved = false;

            switch (key) {
                case 'z': moved = movePlayer(0, -1); break;
                case 's': moved = movePlayer(0, 1); break;
                case 'q': moved = movePlayer(-1, 0); break;
                case 'd': moved = movePlayer(1, 0); break;
                case 'x': running = false; break;
            }

            if (moved) {
                if (maze[playerY][playerX] == 'S') {
                    running = false;
                } else {
                    printMaze();
                }
            }
        }
    }
    return 0;
}
