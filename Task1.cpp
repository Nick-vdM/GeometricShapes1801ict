//
// Created by nick on 26/8/19.
//

#include <iostream>
#include "Shapes.cpp"
#include "Bunch.cpp"
#include <fstream>

Point getPointFromStream(istream &input) {
    char instruction[255];
    input >> instruction;
    int xAnchor = atoi(instruction);
    input >> instruction;
    int yAnchor = atoi(instruction);
    input >> instruction;
    char symbol = instruction[0];
    return Point(xAnchor, yAnchor, symbol);
}

Line getLineFromStream(istream &input) {
    char instruction[255];
    input >> instruction;
    int xAnchor = atoi(instruction);
    input >> instruction;
    int yAnchor = atoi(instruction);
    input >> instruction;
    int toX = atoi(instruction);
    input >> instruction;
    int toY = atoi(instruction);
    input >> instruction;
    char symbol = instruction[0];
    return Line(xAnchor, yAnchor, toX, toY, symbol);
}

Ellipse getEllipseFromStream(istream &input) {
    char instruction[255];
    input >> instruction;
    int xAnchor = atoi(instruction);
    input >> instruction;
    int yAnchor = atoi(instruction);
    input >> instruction;
    int xRadius = atoi(instruction);
    input >> instruction;
    int yRadius = atoi(instruction);
    input >> instruction;
    char symbol = instruction[0];
    return Ellipse(xAnchor, yAnchor, xRadius, yRadius, symbol);
}

Polygon getPolygonFromStream(istream &input) {
    char instruction[255];
    input >> instruction;
    int xAnchor = atoi(instruction);
    input >> instruction;
    int yAnchor = atoi(instruction);
    input >> instruction;
    int sideCount = atoi(instruction);
    input >> instruction;
    int sideLength = atoi(instruction);
    input >> instruction;
    char symbol = instruction[0];
    return Polygon(xAnchor, yAnchor, sideCount, sideLength, symbol);
}

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

class groupOfBunches {
public:
    Bunch<Point> points;
    Bunch<Line> lines;
    Bunch<Ellipse> ellipses;
    Bunch<Polygon> polygons;

    void loadFromFile(char *path, screen board);

    void saveToFile(char *path);
};

void groupOfBunches::loadFromFile(char *path, screen board) {
    fstream ifs(path);
    if (!ifs) {
        std::cerr << "File failed to open";
        return;
    }
    points.clear();
    lines.clear();
    ellipses.clear();
    polygons.clear();
    char word[255];
    while (ifs.peek() != EOF) {
        ifs >> word;
        if (strcmp(word, "point") == 0) {
            //Skip 'x y s'
            for (int i = 0; i < 3; i++) ifs >> word;
            Point pointToInsert = getPointFromStream(ifs);
            pointToInsert.draw(board);
            points.insert(pointToInsert);
        } else if (strcmp(word, "line") == 0) {
            //Skip 'x y xp yp s'
            for (int i = 0; i < 5; i++) ifs >> word;
            Line lineToInsert = getLineFromStream(ifs);
            lineToInsert.draw(board);
            lines.insert(lineToInsert);
        } else if (strcmp(word, "ellipse") == 0) {
            //skip 'x y a b s'
            for (int i = 0; i < 5; i++) ifs >> word;
            Ellipse ellipseToInsert = getEllipseFromStream(ifs);
            ellipseToInsert.draw(board);
            ellipses.insert(ellipseToInsert);
        } else if (strcmp(word, "polygon") == 0) {
            //skip 'x y a n l s'
            for (int i = 0; i < 5; i++) ifs >> word;
            Polygon polygonToInsert = getPolygonFromStream(ifs);
            polygonToInsert.draw(board);
            polygons.insert(polygonToInsert);
        }
    }
}

void groupOfBunches::saveToFile(char *path) {
    ofstream ofs(path);
    if (!ofs) {
        std::cerr << "Failed to open file";
        exit(EXIT_FAILURE);
    }
    points.display(ofs);
    lines.display(ofs);
    ellipses.display(ofs);
    polygons.display(ofs);
}

void demonstrate() {

    std::cout << "=================Template Painter by Nick van der Merwe============" << std::endl
              << "This is a small demo of a drawboard using an ASCII board of letters" << std::endl;
    printHelp();
    screen board{};
    groupOfBunches Shapes{};

    char instruction[255];

    bool keepLooping = true;
    while (keepLooping) {
        std::cout << ">>>>";
        std::cin >> instruction;
        for (int i = 0; i < 255 && instruction[i] != '\0'; i++) {
            instruction[i] = ::tolower(instruction[i]);
        }

        if (strcmp("point", instruction) == 0) {
            Point pointToInsert = getPointFromStream(std::cin);
            pointToInsert.draw(board);
            Shapes.points.insert(pointToInsert);
        } else if (strcmp("line", instruction) == 0) {
            Line lineToInsert = getLineFromStream(std::cin);
            lineToInsert.draw(board);
            Shapes.lines.insert(lineToInsert);
        } else if (strcmp("ellipse", instruction) == 0) {
            Ellipse ellipseToInsert = getEllipseFromStream(std::cin);
            ellipseToInsert.draw(board);
            Shapes.ellipses.insert(ellipseToInsert);
        } else if (strcmp("polygon", instruction) == 0) {
            Polygon polyToInsert = getPolygonFromStream(std::cin);
            polyToInsert.draw(board);
            Shapes.polygons.insert(polyToInsert);
        } else if (strcmp("list", instruction) == 0) {
            Shapes.points.display(std::cout);
            Shapes.lines.display(std::cout);
            Shapes.ellipses.display(std::cout);
            Shapes.polygons.display(std::cout);
        } else if (strcmp("display", instruction) == 0) {
            board.display();
        } else if (strcmp("save", instruction) == 0) {
            std::cin >> instruction;
            Shapes.saveToFile(instruction);
        } else if (strcmp("load", instruction) == 0) {
            std::cin >> instruction;
            Shapes.loadFromFile(instruction, board);
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