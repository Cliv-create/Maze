#include <iostream>
#include <Windows.h> // Окрашивание консоли и работа с координатами
#include <conio.h>
#include <string>
using namespace std;


// enumeration - перечисление
// Например, чтобы не запоминать коды клавиш
enum KeyCodes { ENTER = 13, ESCAPE = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, SPACEBAR = 32 };
enum Colors { DARKBLUE = 1, DARKGREEN = 2, LIGHTBLUE = 3, ACCENTRED = 4, PURPLE  = 5, ACCENTYELLOW = 6, LIGHTWHITE = 7, GRAY = 8, GREEN = 10, CYAN = 11, ACCENTPURPLE = 13, WHITE = 15, RED = 12, YELLOW = 14, BLUE = 9 };
enum Objects { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3 };
// enum Objects {HALL, WALL, COIN, ENEMY}; // Значения по умолчанию, каждый следующий на 1 больше


// Prototypes


bool CoordCompletionCheck(int y, int x, int point_x, int point_y);
void ascii_table();
void level_generation(int HEIGHT, int WIDTH, int** location);
void erase_from_position(HANDLE h, COORD position, int color);
void print_to_position(HANDLE h, COORD position, int color);
void charachter_placement(HANDLE h, COORD position, int color);
void cursor_placement_print(HANDLE h, COORD position, int color, string text);
void cursor_placement_print(HANDLE h, COORD position, int color, int text);
void cursor_placement_print(HANDLE h, COORD position, int color, double text);
void presentation (HANDLE h, int height, int width, int** location);
void print_win_statistics(HANDLE h, short health, int coins);
void print_no_health_statistics(HANDLE h, short health, int coins);
void color_table(HANDLE h);
int print_menu(HANDLE h);
int main();


// Секция с функциями / Functions


bool CoordCompletionCheck(int y, int x, int point_x, int point_y) { // 49 13
    if (x == point_x && y == point_y) {
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


void level_generation(int height, int width, int** location) {

    // Модель локации - числа которые отвечают за определённые состояния
    // 0 - коридоры (пустоты)
    // 1 - стена разрушаемая
    // 2 - Монетки / аптечки / итд
    // 3 - Враги

    // генерация локации
    // Location generation

    for (int y = 0; y < height; y++) // перебор строк
    {
        for (int x = 0; x < width; x++) // перебор столбцов
        {
            /*
            * Filling a tile with random number
            * 0 - Halls will be printed
            * 1 - Wall will be printed
            * 2 - Money will be printed (For now, 100% coin will be placed)
            * 3 - Bush will be printed (IF with custom probability of that bush being left in tile)
            */
            location[y][x] = rand() % 4; // 0 1 2 3

            if (x == 0 || y == 0 || x == width - 1 || y == height - 1) { // Стены по краям
                location[y][x] = WALL;
            }

            if (x == 0 && y == 2 || x == width - 1 && y == height - 3) { // Вход и выход
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

            /*
            * TODO: Change rand() % 4 to rand() % 5 to generate numbers 0 1 2 3 4
            * Add here a copy of above IF with rand() % 15;
            * This will optionally generate a number 4 with will stand for MEDKIT
            * 
            * MEDKIT will increase players HP by 1.
            * 
            */

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


void charachter_placement(HANDLE h, COORD position, int color) { // Функция установки курсора в любую точку на экране консоли
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, BLUE);
    cout << (char)1;
}


void cursor_placement_print(HANDLE h, COORD position, int color, string text) { // Функция установки курсора в любую точку на экране консоли
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << text;
}


void cursor_placement_print(HANDLE h, COORD position, int color, int text) { // Функция установки курсора в любую точку на экране консоли
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << text;
}


void cursor_placement_print(HANDLE h, COORD position, int color, double text) { // Функция установки курсора в любую точку на экране консоли
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << text;
}


void presentation(HANDLE h, int height, int width, int** location) {
    for (int y = 0; y < height; y++) // перебор строк
    {
        for (int x = 0; x < width; x++) // перебор столбцов
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

            /*
            * TODO: Add 4 option
            * IF number == 4 - generate and show icon of MEDKIT
            * MEDKIT will increase player HP by 1.
            */

        }
        cout << "\n";
    }
}


void print_win_statistics(HANDLE h, short health, int coins) {
    COORD print_coord = { 56, 1 };
    cursor_placement_print(h, print_coord, RED, "|| --- --- ---");

    print_coord = { 56, 2 };
    cursor_placement_print(h, print_coord, RED, "|| Congrats, game over!");

    print_coord = { 56, 3 };
    cursor_placement_print(h, print_coord, RED, "|| Health left: ");

    print_coord = { 72, 3 };
    cursor_placement_print(h, print_coord, YELLOW, health);

    print_coord = { 56, 4 };
    cursor_placement_print(h, print_coord, DARKGREEN, "|| Amount of coins");

    print_coord = { 56, 5 };
    cursor_placement_print(h, print_coord, DARKGREEN, "|| ");

    string text = to_string(coins);
    print_coord = { 59, 5 };
    cursor_placement_print(h, print_coord, YELLOW, text);

    print_coord = { 56, 6 };
    cursor_placement_print(h, print_coord, DARKGREEN, "|| --- --- ---");

    print_coord = { 0, 15 };
    cursor_placement_print(h, print_coord, DARKGREEN, " ");
}


void print_no_health_statistics(HANDLE h, short health, int coins) {
    COORD print_coord = { 56, 1 };
    cursor_placement_print(h, print_coord, RED, "|| --- --- ---");

    print_coord = { 56, 2 };
    cursor_placement_print(h, print_coord, RED, "|| Game over! No health left!");

    print_coord = { 56, 3 };
    cursor_placement_print(h, print_coord, RED, "|| Health left: ");

    print_coord = { 72, 3 };
    cursor_placement_print(h, print_coord, YELLOW, health);

    print_coord = { 56, 4 };
    cursor_placement_print(h, print_coord, DARKGREEN, "|| Amount of coins");

    print_coord = { 56, 5 };
    cursor_placement_print(h, print_coord, DARKGREEN, "|| ");

    string text = to_string(coins);
    print_coord = { 59, 5 };
    cursor_placement_print(h, print_coord, YELLOW, text);

    print_coord = { 56, 6 };
    cursor_placement_print(h, print_coord, DARKGREEN, "|| --- --- ---");

    print_coord = { 0, 15 };
    cursor_placement_print(h, print_coord, DARKGREEN, " ");
}


void color_table(HANDLE h) {
    for (int code = 0; code < 256; code++)
    {
        SetConsoleTextAttribute(h, code);
        cout << "Sample text" << " - Code: " << code << "\n";
    }
}


int print_menu(HANDLE h) {
    system("cls"); // Clear console window

    /*
    * Function return values:
    * 0 - Reserved
    * 1 - Exit the program
    * 2 - Proceed with main() code (game)
    * 3 - Proceed with mirrored difficulty (mirrored_difficulty function)
    */

    /*
    *
    * print_coord = { X, Y };
    *
    *    X
    *   Y0 1 2 3 4 5 6 7 8 9 10
    *    1
    *    2
    *    3
    *    4
    *    5
    *    6
    *    7
    *    8
    *    9
    *    10
    */

    /*

    Background color code: 136

    */


    // Printing background colors
    COORD print_coord = { 0, 0 };

    for (int y = 0; y < 35; y++) // перебор строк
    {
        for (int x = 0; x < 150; x++) // перебор столбцов
        {
            cursor_placement_print(h, print_coord, 136, " ");
            print_coord.X++;
        }
        print_coord.X = 0;
        SetConsoleCursorPosition(h, print_coord);
        print_coord.Y++;
        // cout << "\n";
    }

    // {7, 60}
    // Printing MENU words
    print_coord = { 55,7 };
    cursor_placement_print(h, print_coord, 128, "MENU");

    /*
    * TODO:
    * Add 0 1 2 3 options
    * 0 - Reserved
    * 1 - Exit the program
    * 2 - Proceed with main() code (game)
    * 3 - Proceed with mirrored difficulty (mirrored_difficulty function)
    * At 5 line:
    * Make a FOR cycle (or place cursor and print 5 whitespaces with black background)
    * Place cursor at the beginning of window with black background
    * Set up cursor to show again
    * Initialize CIN in DO WHILE cycle for user to input a number for menu
    */

    return 0;
}


/*
* TODO: Optionally add a difficulty level, where level will be shifted below, and create a mirrored situation.
* Player will not know where he needs to go, because level will be displayed below as a mirror.
* 
* void mirrored_difficulty(HANDLE h)
* // Printing background colors
    COORD print_coord = { 0, 0 };

    for (int y = 0; y < height + 1; y++) // перебор строк
    {
        for (int x = 0; x < width + 1; x++) // перебор столбцов
        {
            cursor_placement_print(h, print_coord, 0, " ");
            print_coord.X++;
        }
        print_coord.X = 0;
        SetConsoleCursorPosition(h, print_coord);
        print_coord.Y++;
        // cout << "\n";
    }
* 
* 
*/


// Основная функция main
int main()
{
    system("title Бомбер!"); // Window title

    // Запуск алгоритма случайных чисел
    srand(time(0)); // Random number generator start
    rand();

    
    // --- Настройки / Settings


    // System window number
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Дескриптор окна консоли (порядковый номер окна в системе)


    // Скрыть стандартный мигающий курсор
    // Hiding standart console cursor
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);
    

    // Menu function call
    // print_menu(h);
    // system("cls");


    // Level settings

    /*
    const int WIDTH = 50; // Level settings. X - Horizontal
    auto p_WIDTH = WIDTH;
    const int HEIGHT = 15; // Level settigns. Y - Vertical
    auto p_HEIGHT = HEIGHT;
    int location[HEIGHT][WIDTH] = {};
    auto ptr_location = location;
    */
    

    // Level array creation
    
    
    int width = 50;
    int height = 15;
    int** location = new int* [height];
    for (int y = 0; y < height; y++) {
        location[y] = new int[width];
    }
    

    // color_table(h);


    // ---


    // In-game values
    int coins = 0; // Value for collected coins
    short health = 3;


    // ---

    // level_generation(height, width, location**);
    level_generation(height, width, location);

    // ---


    // Показ локации - Представление
    // Printing location - Presentation

    // presentation(h, height, width, location**);
    presentation(h, height, width, location);
    

    // ---
    

    // Размещение ГГ

    COORD position;
    position.X = 1;
    position.Y = 2;

    charachter_placement(h, position, BLUE);


    // Game engine / Игровой движок (интерактив с пользователем)

    while (true) {

        /*
        * TODO: Move Game Engine into a function
        * 
        * Prototype:
        * int/void game_engine(HANDLE h, int** location, short health, int coins) {
        *     COORD position = { 1, 2 }; // Starting position
        * 
        *     (Rest of the code here)
        * }
        */

        int code = _getch(); // Функция приостанавливает работу программу, ждёт реакцию пользователя. Получить информацию о нажатой клавише
        // Пользователь может нажать любую кнопку (энтер, эскейп, пробел, стрелочки), после чего вернётся код нажатой клавишы

        if (code == 224) {
            code = _getch(); // Если первый код был 224, то повторный вызов функции вернёт только один (нормальный) код. cout << code << "\n"; для вывода кода
        }


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


        if (CoordCompletionCheck(position.Y, position.X, 49, 12)) {

            print_win_statistics(h, health, coins);

            break;
        }


        // Interacting with other objects / Взаимодействие ГГ с другими обьектами в лабиринте

        if (location[position.Y][position.X] == ENEMY && health > 0) {
            health--;
            // cout << health << "\n";
            location[position.Y][position.X] = HALL;
        }

        if (health == 0) {
            print_no_health_statistics(h, health, coins);
            break;
        }

        /*
        * TODO: Add IF check for MEDKIT here
        * IF position IS MEDKIT
        * health++;
        * OPTIONAL: Generate text message in LOG window (TODO)
        * Found medkit! Health: (health) (Displays last action that is displayed with LOG)
        */

        if (location[position.Y][position.X] == COIN) {
            coins++;
            // cout << coins << "\n";
            location[position.Y][position.X] = HALL;
        }

        /*
        * TODO: Start adding items.
        * Wall breacher - Once every 3 turns
        * Placed with a button, next turn - erases walls in
        * 
        *  #
        * ###
        *  #
        * 
        * Shape
        * 
        * Button interaction must proceed ONLY if (wallbreacher == 3 or wallbreacher > 3) (This if is a counter, that adds after each turn)
        * 
        */
        

        /*
        * Printing HP and COIN to HUD
        * 
        * { 50, Y } - Should be whitespace between HUD and game screen. Statistics can be adjusted in corresponding functions (level filling and presentation).
        * { 51-54, Y } - Positions for printing items into HUD. Example: HP, COIN.
        * { 55, Y } - Should be whitespace between HUD and end-game statistics. Statistics can be adjusted in corresponding functions.
        */
        
        COORD print_coord = { 51, 1 };
        cursor_placement_print(h, print_coord, RED, "HP");

        print_coord = { 51, 2 };
        cursor_placement_print(h, print_coord, ACCENTRED, health);

        print_coord = { 51, 4 };
        cursor_placement_print(h, print_coord, YELLOW, "COIN");

        print_coord = { 51, 5 };
        cursor_placement_print(h, print_coord, ACCENTYELLOW, coins);

        // HP
        // (number)
        // { 51, 1 }
        // { 51, 2 }
        // 
        // COIN
        // (number)
        // 51, 4
        // 51, 5
    }

    // Clearing dynamic array
    // delete[] location;

}