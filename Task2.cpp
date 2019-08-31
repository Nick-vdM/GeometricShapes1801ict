//
// Created by nick on 26/8/19.
//

#include <iostream>
#include "AbstractShapes.cpp"
#include "Bunch.cpp"


void printHelp() {
    std::cout << "==============================HELP MENU=================================" << std::endl
              << "To insert a shape type <shapename> <units>." << std::endl
              << "Shapes:" << std::endl
              << "\t point <x> <y> <Symbol>" << std::endl
              << "\t line <startX> <startY> <toX> <toY> <Symbol>" << std::endl
              << "\t ellipse <centreX> <centreY> <xRadius> <yRadius> <Symbol>" << std::endl
              << "\t Polygon <centreX> <centreY> <numberOfSides> <sideLength> <Symbol>" << std::endl
              << "THERE IS NO SAVING IN TASK 2" << std::endl
              << "Note the board is x <- [-20, 20] & y <- [-20, 20]" << std::endl
              << "Type enter 'display' to show the board" << std::endl
              << "Invalid input brings up this screen" << std::endl
              << "Type 'exit' to close the program" << std::endl
              << "======================================================================="
              << std::endl;
}

class BunchOfShapes {
public:
    Bunch<Shape *> shapes;
    screen board;

    BunchOfShapes() = default;

    BunchOfShapes(BunchOfShapes &that) = default;

    BunchOfShapes(BunchOfShapes &&that) = default;

    BunchOfShapes &operator=(BunchOfShapes const &that) = default;

    BunchOfShapes &operator=(BunchOfShapes &&that) noexcept = default;

    ~BunchOfShapes() {
        for (int i = 0; i < shapes.getTop(); i++) {
            delete shapes[i];
        }
    }

    void addPoint(istream &input) {
        Point *pointToInsert = new Point;
        *pointToInsert = getPointFromStream(input);
        pointToInsert->draw(board);
        shapes.insert(pointToInsert);
    }

    void addLine(istream &input) {
        Line *lineToInsert = new Line;
        *lineToInsert = getLineFromStream(input);
        lineToInsert->draw(board);
        shapes.insert(lineToInsert);
    }

    void addEllipse(istream &input) {
        Ellipse *ellipseToInsert = new Ellipse;
        *ellipseToInsert = getEllipseFromStream(input);
        ellipseToInsert->draw(board);
        shapes.insert(ellipseToInsert);
    }

    void addPolygon(istream &input) {
        Polygon *polygonToInsert = new Polygon;
        *polygonToInsert = getPolygonFromStream(input);
        polygonToInsert->draw(board);
        shapes.insert(polygonToInsert);
    }

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

void testConstructors() {
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
    Point &&pointMC{2, 1, '!'};
    Line &&lineMC{2, 3, 4, 1, '@'};
    Ellipse &&ellipseMC{5, 3, 1, 5, '#'};
    Polygon &&polygonMC{7, 3, 1, 3, '$'};
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
            Shapes.shapes.display();
        } else if (strcmp("display", instruction) == 0) {
            Shapes.board.display();
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