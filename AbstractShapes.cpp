//
// Created by nick on 29/8/19.
//

#include "AbstractShapes.h"

Shape::Shape() : Shape(0, 0, 'S') {}

Shape::Shape(int pXAnchor, int pYAnchor, char pSymbol) : xAnchor{pXAnchor},
                                                         yAnchor{pYAnchor}, symbol{pSymbol} {}

Shape::Shape(Shape const &that) = default;

Shape::Shape(Shape &&that) noexcept = default;

Shape &Shape::operator=(Shape const &that) = default;

Shape &Shape::operator=(Shape &&that) noexcept = default;

Shape::~Shape() = default;

int Shape::getXAnchor() const {
    return xAnchor;
}

int Shape::getYAnchor() const {
    return yAnchor;
}

void Shape::setYAnchor(int pos) {
    yAnchor = pos;
}

void Shape::setXAnchor(int pos) {
    xAnchor = pos;
}

void Shape::setAnchors(int xPos, int yPos) {
    xAnchor = xPos;
    yAnchor = yPos;
}

void Shape::setSymbol(char pSymbol) {
    symbol = pSymbol;
}

char Shape::getSymbol() const {
    return symbol;
}


Point::Point() : Point(0, 0, 'S') {}

Point::Point(int pXAnchor, int pYAnchor, char pSymbol) : Shape::Shape(pXAnchor, pYAnchor, pSymbol) {}

Point::Point(Point const &that) = default;

Point::Point(Point &&that) noexcept = default;

Point &Point::operator=(Point const &that) = default;

Point &Point::operator=(Point &&that) noexcept = default;

Point::~Point() = default;

void Point::draw(screen &s) {
    s.point(xAnchor, yAnchor, symbol);
}

void Point::info() {
    //Prints the information to console
    std::cout << "point x y s \t\t"
              << xAnchor << " "
              << yAnchor << " "
              << symbol << std::endl;
}


Line::Line() : Line(0, 0, 1, 1, 'L') {}

Line::Line(int pFromX, int pFromY, int pToX, int pToY, char pSymbol) : Shape::Shape(pFromX, pFromY, pSymbol),
                                                                       toX{pToX}, toY{pToY} {}

Line::Line(Line const &that) = default;

Line::Line(Line &&that) noexcept = default;

Line &Line::operator=(Line const &that) = default;

Line &Line::operator=(Line &&that) noexcept = default;

Line::~Line() = default;

void Line::draw(screen &s) {
    s.line(xAnchor, yAnchor, toX, toY, symbol);
}

void Line::info() {
    std::cout << "line x y xp yp s \t\t"
              << xAnchor << " "
              << yAnchor << " "
              << toX << " "
              << toY << " "
              << symbol << std::endl;
}

int Line::getToX() const {
    return toX;
}

int Line::getToY() const {
    return toY;
}

void Line::setToX(int toX) {
    Line::toX = toX;
}

void Line::setToY(int toY) {
    Line::toY = toY;
}

Ellipse::Ellipse() : Ellipse(0, 0, 1, 1, 'E') {}

Ellipse::Ellipse(int pXAnchor, int pYAnchor, int pXRadius, int pYRadius, char pSymbol) :
        Shape(pXAnchor, pYAnchor, pSymbol), xRadius{pXRadius}, yRadius{pYRadius} {}

Ellipse::Ellipse(Ellipse const &that) = default;

Ellipse::Ellipse(Ellipse &&that) noexcept = default;

Ellipse &Ellipse::operator=(Ellipse const &that) = default;

Ellipse &Ellipse::operator=(Ellipse &&that) noexcept = default;

Ellipse::~Ellipse() = default;

void Ellipse::draw(screen &s) {
    s.ellipse(xAnchor, yAnchor, xRadius, yRadius, symbol);
}

void Ellipse::info() {
    std::cout << "ellipse x y a b s \t\t"
              << xAnchor << " "
              << yAnchor << " "
              << xRadius << " "
              << yRadius << " "
              << symbol << std::endl;
}

void Ellipse::setRadii(int xPos, int yPos) {
    xRadius = xPos;
    yRadius = yPos;
}

void Ellipse::setXRadius(int pos) {
    xRadius = pos;
}

void Ellipse::setYRadius(int pos) {
    yRadius = pos;
}

int Ellipse::getXRadius() const {
    return xRadius;
}

int Ellipse::getYRadius() const {
    return yRadius;
}

Polygon::Polygon() : Polygon(0, 0, 3, 1, 't') {}

Polygon::Polygon(int pXAnchor, int pYAnchor, int pSideCount, int pSideLength, char pSymbol) :
        Shape(pXAnchor, pYAnchor, pSymbol), sideCount{pSideCount}, sideLength{pSideLength} {}

Polygon::Polygon(Polygon const &that) = default;

Polygon::Polygon(Polygon &&that) noexcept = default;

Polygon &Polygon::operator=(Polygon const &that) = default;

Polygon &Polygon::operator=(Polygon &&that) noexcept = default;

Polygon::~Polygon() = default;

void Polygon::draw(screen &s) {
    s.polygon(xAnchor, yAnchor, sideCount, sideLength, symbol);
}

void Polygon::info() {
    std::cout << "polygon x y n l s \t\t"
              << xAnchor << " "
              << yAnchor << " "
              << sideCount << " "
              << sideLength << " "
              << symbol << std::endl;
}

int Polygon::getSideCount() const {
    return sideCount;
}

void Polygon::setSideCount(int count) {
    sideCount = count;
}

int Polygon::getSideLength() const {
    return sideLength;
}

void Polygon::setSideLength(int length) {
    sideLength = length;
}