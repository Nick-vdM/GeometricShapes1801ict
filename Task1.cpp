//
// Created by nick on 26/8/19.
//

#include <iostream>
#include "ConcreteShapes.cpp"
#include "Bunch.cpp"


void printHelp() {
    std::cout << "==============================HELP MENU=================================" << std::endl
              << "To insert a shape type <shapename> <units>." << std::endl
              << "Shapes:" << std::endl
              << "\t point <x> <y> <Symbol>" << std::endl
              << "\t line <startX> <startY> <toX> <toY> <Symbol>" << std::endl
              << "\t ellipse <centreX> <centreY> <xRadius> <yRadius> <Symbol>" << std::endl
              << "\t Polygon <centreX> <centreY> <numberOfSides> <sideLength> <Symbol>" << std::endl
              << "Saving/Loading:" << std::endl
              << "\tsave <saveName>" << std::endl
              << "\tload <loadName>" << std::endl
              << "Note the board is x <- [-20, 20] & y <- [-20, 20]" << std::endl
              << "Type enter 'display' to show the board" << std::endl
              << "Invalid input brings up this screen" << std::endl
              << "Type 'exit' to close the program" << std::endl
              << "======================================================================="
              << std::endl;
}

class BunchOfShapes {
public:
    Bunch<Point> points;
    Bunch<Line> lines;
    Bunch<Ellipse> ellipses;
    Bunch<Polygon> polygons;
    screen board;

    void addPoint(istream &input) {
        Point pointToInsert = getPointFromStream(input);
        pointToInsert.draw(board);
        points.insert(pointToInsert);
    }

    void addLine(istream &input) {
        Line lineToInsert = getLineFromStream(input);
        lineToInsert.draw(board);
        lines.insert(lineToInsert);
    }

    void addEllipse(istream &input) {
        Ellipse ellipseToInsert = getEllipseFromStream(input);
        ellipseToInsert.draw(board);
        ellipses.insert(ellipseToInsert);
    }

    void addPolygon(istream &input) {
        Polygon polygonToInsert = getPolygonFromStream(input);
        polygonToInsert.draw(board);
        polygons.insert(polygonToInsert);
    }

    void loadFromFile(char *path);

    void saveToFile(char *path);

private:
    static Point getPointFromStream(istream &input) {
        char instruction[255];
        input >> instruction;
        int xAnchor = stoi(instruction);
        input >> instruction;
        int yAnchor = stoi(instruction);
        input >> instruction;
        char symbol = instruction[0];
        return Point(xAnchor, yAnchor, symbol);
    }

    static Line getLineFromStream(istream &input) {
        char instruction[255];
        input >> instruction;
        int xAnchor = stoi(instruction);
        input >> instruction;
        int yAnchor = stoi(instruction);
        input >> instruction;
        int toX = stoi(instruction);
        input >> instruction;
        int toY = stoi(instruction);
        input >> instruction;
        char symbol = instruction[0];
        return Line(xAnchor, yAnchor, toX, toY, symbol);
    }

    static Ellipse getEllipseFromStream(istream &input) {
        char instruction[255];
        input >> instruction;
        int xAnchor = stoi(instruction);
        input >> instruction;
        int yAnchor = stoi(instruction);
        input >> instruction;
        int xRadius = stoi(instruction);
        input >> instruction;
        int yRadius = stoi(instruction);
        input >> instruction;
        char symbol = instruction[0];
        return Ellipse(xAnchor, yAnchor, xRadius, yRadius, symbol);
    }

    static Polygon getPolygonFromStream(istream &input) {
        char instruction[255];
        input >> instruction;
        int xAnchor = stoi(instruction);
        input >> instruction;
        int yAnchor = stoi(instruction);
        input >> instruction;
        int sideCount = stoi(instruction);
        input >> instruction;
        int sideLength = stoi(instruction);
        input >> instruction;
        char symbol = instruction[0];
        return Polygon(xAnchor, yAnchor, sideCount, sideLength, symbol);
    }

};

void BunchOfShapes::loadFromFile(char *path) {
    fstream ifs(path);
    if (!ifs) {
        std::cerr << "File failed to open";
        return;
    }
    points.clear();
    lines.clear();
    ellipses.clear();
    polygons.clear();
    board.clear();
    char word[255];
    while (ifs.peek() != EOF) {
        ifs >> word;
        if (strcmp(word, "point") == 0) {
            //Skip 'x y s'
            for (int i = 0; i < 3; i++) ifs >> word;
            addPoint(ifs);
        } else if (strcmp(word, "line") == 0) {
            //Skip 'x y xp yp s'
            for (int i = 0; i < 5; i++) ifs >> word;
            addLine(ifs);
        } else if (strcmp(word, "ellipse") == 0) {
            //skip 'x y a b s'
            for (int i = 0; i < 5; i++) ifs >> word;
            addEllipse(ifs);
        } else if (strcmp(word, "polygon") == 0) {
            //skip 'x y a n l s'
            for (int i = 0; i < 5; i++) ifs >> word;
            addPolygon(ifs);
        }
    }
}

void BunchOfShapes::saveToFile(char *path) {
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

void testConstructors(){
    //VERIFY ME WITH A DEBUGGER (I verified it myself, but I didn't want to flood with prints
    //or make a complicated series of asserts
    //Defaults
    Point pointA{};
    Line lineA{};
    Ellipse ellipseA{};
    Polygon polygonA{};
    //Paramaters
    Point pointP{1, 2, '*'};
    Line lineP{3, 4, 5, 6, '('};
    Ellipse ellipseP{7, 8, 9, 10, '^'};
    Polygon polygonP{11, 12, 13, 14, '!'};
    //Copy ctors
    Point pointB = pointP;
    Line lineB = lineP;
    Ellipse ellipseB = ellipseP;
    Polygon polygonB = polygonP;
    //Move ctors
    Point && pointMC{2, 1, '!'};
    Line && lineMC{2, 3, 4, 1, '@'};
    Ellipse && ellipseMC{5, 3, 1, 5, '#'};
    Polygon && polygonMC{7, 3, 1, 3, '$'};
    //Copy assignment
    pointA = pointB;
    lineA = lineB;
    ellipseA = ellipseB;
    polygonA = polygonB;
    //Move assignment
    pointA = std::move(pointMC);
    lineA = std::move(lineMC);
    ellipseMC = std::move(ellipseMC);
    polygonA = std::move(polygonMC);
    //Destructors
}

void demonstrate() {
    testConstructors(); // Silently check these - you can verify with a debugger
    std::cout << "=================Template Painter by Nick van der Merwe============" << std::endl
              << "This is a small demo of a drawboard using an ASCII board of letters" << std::endl;
    printHelp();
    BunchOfShapes Shapes{};

    char instruction[255];

    bool keepLooping = true;
    while (keepLooping) {
        std::cout << ">>>>";
        std::cin >> instruction;
        for (int i = 0; i < 255 && instruction[i] != '\0'; i++) {
            instruction[i] = ::tolower(instruction[i]);
        }

        if (strcmp("point", instruction) == 0) {
            Shapes.addPoint(std::cin);
        } else if (strcmp("line", instruction) == 0) {
            Shapes.addLine(std::cin);
        } else if (strcmp("ellipse", instruction) == 0) {
            Shapes.addEllipse(std::cin);
        } else if (strcmp("polygon", instruction) == 0) {
            Shapes.addPolygon(std::cin);
        } else if (strcmp("list", instruction) == 0) {
            Shapes.points.display(std::cout);
            Shapes.lines.display(std::cout);
            Shapes.ellipses.display(std::cout);
            Shapes.polygons.display(std::cout);
        } else if (strcmp("display", instruction) == 0) {
            Shapes.board.display();
        } else if (strcmp("save", instruction) == 0) {
            std::cin >> instruction;
            Shapes.saveToFile(instruction);
        } else if (strcmp("load", instruction) == 0) {
            std::cin >> instruction;
            Shapes.loadFromFile(instruction);
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