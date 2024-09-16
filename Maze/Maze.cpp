﻿#include <iostream>
#include <Windows.h> // Окрашивание консоли и работа с координатами
#include <conio.h>
using namespace std;

// enumeration - перечисление
// Например, чтобы не запоминать коды клавиш
enum KeyCodes { ENTER = 13, ESCAPE = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, SPACEBAR = 32 };
enum Colors { DARKGREEN = 2, RED = 12, YELLOW = 14, BLUE = 9 };
enum Objects { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3 };
// enum Objects {HALL, WALL, COIN, ENEMY}; // Значения по умолчанию, каждый следующий на 1 больше

// Секция с функциями

bool CoordLevelCompletionCheck(int y, int x, int exit_x, int exit_y) { // 50 13
    if (x == exit_x && y == exit_y) {
        return 1;
    }
    return 0;
}

void ascii_table() { // Table for printing out ASCII symbols
    for (int code = 0; code < 256; code++)
    {
        cout << code << " - " << (char)code << "\n";
    }
}



void level_generation(int HEIGHT, int WIDTH, int location[][50]) {

    for (int y = 0; y < HEIGHT; y++) // перебор строк
    {
        for (int x = 0; x < WIDTH; x++) // перебор столбцов
        {
            location[y][x] = rand() % 4; // 0 1 2 3

            if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1) { // Стены по краям
                location[y][x] = WALL;
            }

            if (x == 0 && y == 2 || x == WIDTH - 1 && y == HEIGHT - 3) { // Вход и выход
                location[y][x] = HALL;
            }

            if (location[y][x] == ENEMY) { // Проверка, если найдена 3 то... поменять
                // Определяется вероятность того, останется враг или нет
                // Допустим, вероятность остаться на уровне - 10%
                int prob = rand() % 10; // 0-9
                if (prob != 0) { // 1 2 3 4 5 6 7 8 9
                    location[y][x] = HALL;
                }

            }

        }
        // cout << "\n";
    }

}


void erase_from_position(HANDLE h, COORD position, int color) { // Стирание ГГ в старой позиции
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << " ";
}

void print_to_position(HANDLE h, COORD position, int color) { // Показ ГГ в новой позиции
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, BLUE);
    cout << (char)1;
}

void cursor_placement_charachter(HANDLE h, COORD position, int color) { // Функция установки курсора в любую точку на экране консоли
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, BLUE);
    cout << (char)1;
}

void cursor_placement_print(HANDLE h, COORD position, int color, string text) { // Функция установки курсора в любую точку на экране консоли
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, BLUE);
    cout << text;
}



// Основная функция main
int main()
{
    system("title Бомбер!"); // Window title
    // Запуск алгоритма случайных чисел
    srand(time(0)); // Random number generator start
    rand();


    // --- Настройки

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Дескриптор окна консоли (порядковый номер окна в системе)

    // Скрыть стандартный мигающий курсор
    // Hiding standart console cursor
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);
    // ---

    // Level settings
    const int WIDTH = 50; // Level settings. X - Horizontal
    const int HEIGHT = 15; // Level settigns. Y - Vertical
    int location[HEIGHT][WIDTH] = {};
    // ---


    // In-game values
    int coins = 0; // Value for collected coins

    // ---


    // Модель локации - числа которые отвечают за определённые состояния
    // 0 - коридоры (пустоты)
    // 1 - стена разрушаемая
    // 2 - Монетки / аптечки / итд
    // 3 - Враги

    // генерация локации
    // Location generation

    /*
    for (int y = 0; y < HEIGHT; y++) // перебор строк
    {
        for (int x = 0; x < WIDTH; x++) // перебор столбцов
        {
            location[y][x] = rand() % 4; // 0 1 2 3

            if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1) { // Стены по краям
                location[y][x] = WALL;
            }

            if (x == 0 && y == 2 || x == WIDTH - 1 && y == HEIGHT - 3) { // Вход и выход
                location[y][x] = HALL;
            }

            if (location[y][x] == ENEMY) { // Проверка, если найдена 3 то... поменять
                // Определяется вероятность того, останется враг или нет
                // Допустим, вероятность остаться на уровне - 10%
                int prob = rand() % 10; // 0-9
                if (prob != 0) { // 1 2 3 4 5 6 7 8 9
                    location[y][x] = HALL;
                }

            }

        }
        // cout << "\n";
    }
    */


    level_generation(HEIGHT, WIDTH, location);


    // ---


    // Показ локации - Представление
    // Printing location - Presentation

    for (int y = 0; y < HEIGHT; y++) // перебор строк
    {
        for (int x = 0; x < WIDTH; x++) // перебор столбцов
        {
            // cout << location[y][x];

            switch (location[y][x]) {
            case HALL: // Коридор
                cout << " ";
                break;
            case WALL: // Стены
                SetConsoleTextAttribute(h, DARKGREEN); // 0-255
                cout << (char)177;
                break;
            case COIN: // Монетки
                SetConsoleTextAttribute(h, YELLOW); // 0-255
                cout << (char)15;
                break;
            case ENEMY: // Враги
                SetConsoleTextAttribute(h, RED); // 0-255
                cout << (char)1;
                break;
            default: // Если вывод цифр - значит какой-то вывод не настроен на символ
                cout << location[y][x];
                break;
            }

        }
        cout << "\n";
    }

    // ---
    // Размещение ГГ

    COORD position;
    position.X = 1;
    position.Y = 2;

    cursor_placement_charachter(h, position, BLUE);

    // Игровой движок (интерактив с пользователем)

    while (true) {
        int code = _getch(); // Функция приостанавливает работу программу, ждёт реакцию пользователя. Получить информацию о нажатой клавише
        // Пользователь может нажать любую кнопку (энтер, эскейп, пробел, стрелочки), после чего вернётся код нажатой клавишы

        if (code == 224) {
            code = _getch(); // Если первый код был 224, то повторный вызов функции вернёт только один (нормальный) код
        }
        // cout << code << "\n";


        erase_from_position(h, position, BLUE);

        switch (code) {
        case ENTER:
            // cout << "Enter\n";
            break;
        case SPACEBAR:
            // cout << "Spacebar\n";
            break;
        case ESCAPE:
            // cout << "Escape\n";
            break;
        case RIGHT:
            if (location[position.Y][position.X + 1] != WALL)
                position.X++;
            break;
        case LEFT:
            // if (position.X > 0 || location[position.Y][position.X - 1] != WALL)
            if (position.X > 0 && location[position.Y][position.X - 1] != WALL)
                position.X--;
            break;
        case UP:
            if (location[position.Y - 1][position.X] != WALL)
                position.Y--;
            break;
        case DOWN:
            if (location[position.Y + 1][position.X] != WALL)
                position.Y++;
            break;
        default:
            cout << code << "\n";
            break;
        }

        print_to_position(h, position, BLUE);

        if (CoordLevelCompletionCheck(position.Y, position.X, 50, 13)) {
            COORD print_coord = { 53, 5 };
            cursor_placement_print(h, print_coord, RED, "Congrats, game over!");
            print_coord = { 53, 7 };
            string text = "Amount of coins: " + coins;
            cursor_placement_print(h, print_coord, RED, text);
            break;
        }

        // Взаимодействие ГГ с другими обьектами в лабиринте

        if (location[position.Y][position.X] == COIN) {
            coins++;
            // cout << coins << "\n";
            // location[position.Y][position.X] = WALL;
            location[position.Y][position.X] = HALL;
        }

    }


}