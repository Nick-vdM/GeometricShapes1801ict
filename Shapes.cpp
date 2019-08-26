//
// Created by nick on 26/8/19.
//


#include "Shapes.h"

Point::Point() : Point(0, 0, 'S') {}

Point::Point(int pXAnchor, int pYAnchor, char pSymbol) : xAnchor{pXAnchor},
                                                         yAnchor{pYAnchor}, symbol{pSymbol} {}

Point::Point(Point const &that) = default;

Point::Point(Point &&that) noexcept = default;

Point &Point::operator=(Point const &that) = default;

Point &Point::operator=(Point &&that) noexcept = default;

Point::~Point() = default;

void Point::draw(screen s) {
    s.point(xAnchor, yAnchor, symbol);
}

int Point::getXAnchor() {
    return xAnchor;
}

int Point::getYAnchor() {
    return yAnchor;
}

void Point::setYAnchor(int pos) {
    yAnchor = pos;
}

void Point::setXAnchor(int pos) {
    xAnchor = pos;
}

void Point::setAnchors(int xPos, int yPos) {
    xAnchor = xPos;
    yAnchor = yPos;
}

void Point::setSymbol(char pSymbol) {
    symbol = pSymbol;
}

char Point::getSymbol() {
    return symbol;
}

//Line
Line::Line() : Line(0, 0, 1, 1, 'L') {}

Line::Line(int pFromX, int pFromY, int pToX, int pToY, char pSymbol) : Point::Point(pFromX, pFromY, pSymbol),
                                                                       toX{pToX}, toY{pToY} {}

Line::Line(Line const &that) = default;

Line::Line(Line &&that) noexcept = default;

Line &Line::operator=(Line const &that) = default;

Line &Line::operator=(Line &&that) noexcept = default;

Line::~Line() = default;

void Line::draw(screen s) {
    s.line(xAnchor, yAnchor, toX, toY, symbol);
}

void Line::setDest(int xPos, int yPos) {
    toX = xPos;
    toY = yPos;
}

int Line::getXDest() {
    return toX;
}

int Line::getYDest() {
    return toY;
}

void Line::setYDest(int pos) {
    toY = pos;
}

void Line::setXDest(int pos) {
    toX = pos;
}

void Line::setDests(int xPos, int yPos) {
    toX = xPos;
    toY = yPos;
}

Ellipse::Ellipse() : Ellipse(0, 0, 1, 1, 'E') {}

Ellipse::Ellipse(int pXAnchor, int pYAnchor, int pXRadius, int pYRadius, char pSymbol) :
        Point(pXAnchor, pYAnchor, pSymbol), xRadius{pXRadius}, yRadius{pYRadius} {}

Ellipse::Ellipse(Ellipse const &that) = default;

Ellipse::Ellipse(Ellipse &&that) noexcept = default;

Ellipse &Ellipse::operator=(Ellipse const &that) = default;

Ellipse &Ellipse::operator=(Ellipse &&that) noexcept = default;

Ellipse::~Ellipse() = default;

void Ellipse::draw(screen s) {
    s.ellipse(xAnchor, yAnchor, xRadius, yRadius, symbol);
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

int Ellipse::getXRadius() {
    return xRadius;
}

int Ellipse::getYRadius() {
    return yRadius;
}

Polygon::Polygon() : Polygon(0, 0, 3, 1, 't'){}

Polygon::Polygon(int pXAnchor, int pYAnchor, int pSideCount, int pSideLength, char pSymbol) :
        Point(pXAnchor, pYAnchor, symbol), sideCount{pSideCount}, sideLength{pSideLength} {}

Polygon::Polygon(Polygon const &that) = default;

Polygon::Polygon(Polygon &&that) noexcept = default;

Polygon &Polygon::operator=(Polygon const &that) = default;

Polygon &Polygon::operator=(Polygon &&that) noexcept = default;

Polygon::~Polygon() = default;

void Polygon::draw(screen s) {
    s.polygon(xAnchor, yAnchor, sideCount, sideLength, symbol);
}

int Polygon::getSideCount() {
    return 0;
}

void Polygon::setSideCount(int count) {
    sideCount = count;
}

int Polygon::getSideLength() {
    return sideLength;
}

void Polygon::setSideLength(int length) {
    sideLength = length;
}












