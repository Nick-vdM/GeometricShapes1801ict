//
// Created by nick on 26/8/19.
//

#include <iostream>
#include "Shapes.cpp"
#include "Bunch.cpp"

void printHelp() {
    std::cout << "==============================HELP MENU================================="
              << "To insert a shape type <shapename> <units>." << std::endl
              << "Shapes:" << std::endl
              << "\t point <x> <y> <Symbol>" << std::endl
              << "\t line <startX> <startY> <toX> <toY> <Symbol>" << std::endl
              << "\t ellipse <centreX> <centreY> <yRadius> <xRadius> <Symbol>" << std::endl
              << "\t Polygon <centreX> <centreY> <numberOfSides> <sideLength> <Symbol>" << std::endl
              << "Note the board is x <- [-20, 20] & y <- [-20, 20]" << std::endl
              << "Type enter 'display' to show the board" << std::endl
              << "Invalid input brings up this screen" << std::endl
              << "Type 'exit' to close the program" << std::endl
              << "======================================================================="
              << std::endl;
}

void demonstrate() {

    std::cout << "=================Template Painter by Nick van der Merwe============" << std::endl
              << "This is a small demo of a drawboard using an ASCII board of letters" << std::endl;
    printHelp();
    screen board{};
    Bunch<Point> points{};
    Bunch<Line> lines{};
    Bunch<Ellipse> ellipses{};
    Bunch<Polygon> polygons{};

    char instruction[255];

    bool keepLooping = true;
    while (keepLooping) {
        std::cout << ">>>>";
        std::cin >> instruction;
        for (char &i : instruction) {
            i = ::tolower(i);
        }

        if (strcmp("point", instruction) == 0) {
            std::cin >> instruction;
            int xAnchor = atoi(instruction);
            std::cin >> instruction;
            int yAnchor = atoi(instruction);
            std::cin >> instruction;
            char symbol = instruction[0];
            Point toInsert{xAnchor, yAnchor, symbol};
            toInsert.draw(board);
            points.insert(toInsert);
        } else if (strcmp("line", instruction) == 0) {

        } else if (strcmp("ellipse", instruction) == 0) {

        } else if (strcmp("polygon", instruction) == 0) {

        } else if (strcmp("display", instruction) == 0) {
            board.display();
        } else if (strcmp("exit", instruction) == 0) {
            keepLooping = false;
        } else {
            printHelp();
        }
    }
}

int main(int argc, char *argv[]) {
    demonstrate();
    return EXIT_SUCCESS;
}