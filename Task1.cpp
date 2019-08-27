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
              << "\t ellipse <centreX> <centreY> <xRadius> <yRadius> <Symbol>" << std::endl
              << "\t Polygon <centreX> <centreY> <numberOfSides> <sideLength> <Symbol>" << std::endl
              << "Note the board is x <- [-20, 20] & y <- [-20, 20]" << std::endl
              << "Type enter 'display' to show the board" << std::endl
              << "Invalid input brings up this screen" << std::endl
              << "Type 'exit' to close the program" << std::endl
              << "======================================================================="
              << std::endl;
}

Point getPointFromUser() {
    char instruction[255];
    std::cin >> instruction;
    int xAnchor = atoi(instruction);
    std::cin >> instruction;
    int yAnchor = atoi(instruction);
    std::cin >> instruction;
    char symbol = instruction[0];
    return Point(xAnchor, yAnchor, symbol);
}

Line getLineFromUser() {
    char instruction[255];
    std::cin >> instruction;
    int xAnchor = atoi(instruction);
    std::cin >> instruction;
    int yAnchor = atoi(instruction);
    std::cin >> instruction;
    int toX = atoi(instruction);
    std::cin >> instruction;
    int toY = atoi(instruction);
    std::cin >> instruction;
    char symbol = instruction[0];
    return Line(xAnchor, yAnchor, toX, toY, symbol);
}

Ellipse getEllipseFromUser() {
    char instruction[255];
    std::cin >> instruction;
    int xAnchor = atoi(instruction);
    std::cin >> instruction;
    int yAnchor = atoi(instruction);
    std::cin >> instruction;
    int xRadius = atoi(instruction);
    std::cin >> instruction;
    int yRadius = atoi(instruction);
    std::cin >> instruction;
    char symbol = instruction[0];
    return Ellipse(xAnchor, yAnchor, xRadius, yRadius, symbol);
}

Polygon getPolygonFromUser() {
    char instruction[255];
    std::cin >> instruction;
    int xAnchor = atoi(instruction);
    std::cin >> instruction;
    int yAnchor = atoi(instruction);
    std::cin >> instruction;
    int sideCount = atoi(instruction);
    std::cin >> instruction;
    int sideLength = atoi(instruction);
    std::cin >> instruction;
    char symbol = instruction[0];
    return Polygon(xAnchor, yAnchor, sideCount, sideLength, symbol);
}

void printInsertedShapes(Bunch<Point> points, Bunch<Line> lines,
                         Bunch<Ellipse> ellipses, Bunch<Polygon> polygons) {
    if (points.getTop() > 0)
        std::cout << "------Points------" << std::endl
                  << "xAnchor\tyAnchor\tSymbol" << std::endl;
    for (int i = 0; i < points.getTop(); i++) {
        std::cout << points[i].getXAnchor() << "\t"
                  << points[i].getYAnchor() << "\t"
                  << points[i].getSymbol() << std::endl;
    }
    if (lines.getTop() > 0)
        std::cout << "------Lines------" << std::endl
                  << "xCentre\tyCentre\txTo\ttoY\tSymbol" << std::endl;
    for (int i = 0; i < lines.getTop(); i++) {
        std::cout << lines[i].getXAnchor() << "\t"
                  << lines[i].getYAnchor() << "\t"
                  << lines[i].getXDest() << "\t"
                  << lines[i].getYDest() << "\t"
                  << lines[i].getSymbol() << std::endl;
    }
    if (ellipses.getTop() > 0)
        std::cout << "------Ellipses------" << std::endl
                  << "xCentre\tyCentre\txRadius\tyRadius\tSymbol" << std::endl;
    for (int i = 0; i < ellipses.getTop(); i++) {
        std::cout << ellipses[i].getXAnchor() << "\t"
                  << ellipses[i].getYAnchor() << "\t"
                  << ellipses[i].getXRadius() << "\t"
                  << ellipses[i].getYRadius() << "\t"
                  << ellipses[i].getSymbol() << std::endl;
    }
    if (polygons.getTop() > 0)
        std::cout << "------Polygons------" << std::endl
                  << "xCentre\tyCentre\tsideCount\tsideLength\tSymbol" << std::endl;
    for (int i = 0; i < polygons.getTop(); i++) {
        std::cout << polygons[i].getXAnchor() << "\t"
                  << polygons[i].getYAnchor() << "\t"
                  << polygons[i].getSideCount() << "\t"
                  << polygons[i].getSideLength() << "\t"
                  << polygons[i].getSymbol() << std::endl;
    }
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
        for (int i = 0; i < 255 && instruction[i] != '\0'; i++) {
            instruction[i] = ::tolower(instruction[i]);
        }

        if (strcmp("point", instruction) == 0) {
            Point pointToInsert = getPointFromUser();
            pointToInsert.draw(board);
            points.insert(pointToInsert);
        } else if (strcmp("line", instruction) == 0) {
            Line lineToInsert = getLineFromUser();
            lineToInsert.draw(board);
            lines.insert(lineToInsert);
        } else if (strcmp("ellipse", instruction) == 0) {
            Ellipse ellipseToInsert = getEllipseFromUser();
            ellipseToInsert.draw(board);
            ellipses.insert(ellipseToInsert);
        } else if (strcmp("polygon", instruction) == 0) {
            Polygon polyToInsert = getPolygonFromUser();
            polyToInsert.draw(board);
            polygons.insert(polyToInsert);
        } else if (strcmp("list", instruction) == 0) {
            printInsertedShapes(points, lines, ellipses, polygons);
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