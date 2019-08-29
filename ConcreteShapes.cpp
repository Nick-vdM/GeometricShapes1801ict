//
// Created by nick on 26/8/19.
//


#include "ConcreteShapes.h"

Point::Point() : Point(0, 0, 'S') {}

Point::Point(int pXAnchor, int pYAnchor, char pSymbol) : xAnchor{pXAnchor},
                                                         yAnchor{pYAnchor}, symbol{pSymbol} {}

Point::Point(Point const &that) = default;

Point::Point(Point &&that) noexcept = default;

Point &Point::operator=(Point const &that) = default;

Point &Point::operator=(Point &&that) noexcept = default;

Point::~Point() = default;

void Point::draw(screen &s) {
    s.point(xAnchor, yAnchor, symbol);
}

void Point::info(ostream &output) {
    //Prints the information to console
    output << "point x y s \t\t"
           << xAnchor << " "
           << yAnchor << " "
           << symbol << std::endl;
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


Line::Line() : Line(0, 0, 1, 1, 'L') {}

Line::Line(int pXAnchor, int pYAnchor, int pToX, int pToY, char pSymbol) : xAnchor{pXAnchor}, yAnchor{pYAnchor},
                                                                           toX{pToX}, toY{pToY}, symbol{pSymbol} {}

Line::Line(Line const &that) = default;

Line::Line(Line &&that) noexcept = default;

Line &Line::operator=(Line const &that) = default;

Line &Line::operator=(Line &&that) noexcept = default;

Line::~Line() = default;

void Line::draw(screen &s) {
    s.line(xAnchor, yAnchor, toX, toY, symbol);
}

void Line::info(ostream &output) {
    output << "line x y xp yp s \t\t"
           << xAnchor << " "
           << yAnchor << " "
           << toX << " "
           << toY << " "
           << symbol << std::endl;
}

int Line::getXAnchor() {
    return xAnchor;
}

int Line::getYAnchor() {
    return yAnchor;
}

void Line::setYAnchor(int pos) {
    yAnchor = pos;
}

void Line::setXAnchor(int pos) {
    xAnchor = pos;
}

void Line::setAnchors(int xPos, int yPos) {
    xAnchor = xPos;
    yAnchor = yPos;
}

void Line::setSymbol(char pSymbol) {
    symbol = pSymbol;
}

char Line::getSymbol() {
    return symbol;
}

void Line::setDest(int xPos, int yPos) {
    toX = xPos;
    toY = yPos;
}

int Line::getToX() {
    return toX;
}

int Line::getToY() {
    return toY;
}

void Line::setToY(int pos) {
    toY = pos;
}

void Line::setToX(int pos) {
    toX = pos;
}

void Line::setTos(int xPos, int yPos) {
    toX = xPos;
    toY = yPos;
}

Ellipse::Ellipse() : Ellipse(0, 0, 1, 1, 'E') {}

Ellipse::Ellipse(int pXAnchor, int pYAnchor, int pXRadius, int pYRadius, char pSymbol) :
        xAnchor{pXAnchor}, yAnchor{pYAnchor}, xRadius{pXRadius}, yRadius{pYRadius}, symbol{pSymbol} {}

Ellipse::Ellipse(Ellipse const &that) = default;

Ellipse::Ellipse(Ellipse &&that) noexcept = default;

Ellipse &Ellipse::operator=(Ellipse const &that) = default;

Ellipse &Ellipse::operator=(Ellipse &&that) noexcept = default;

Ellipse::~Ellipse() = default;

void Ellipse::draw(screen &s) {
    s.ellipse(xAnchor, yAnchor, xRadius, yRadius, symbol);
}

void Ellipse::info(ostream &output) {
    output << "ellipse x y a b s \t\t"
           << xAnchor << " "
           << yAnchor << " "
           << xRadius << " "
           << yRadius << " "
           << symbol << std::endl;
}

int Ellipse::getXAnchor() {
    return xAnchor;
}

int Ellipse::getYAnchor() {
    return yAnchor;
}

void Ellipse::setYAnchor(int pos) {
    yAnchor = pos;
}

void Ellipse::setXAnchor(int pos) {
    xAnchor = pos;
}

void Ellipse::setAnchors(int xPos, int yPos) {
    xAnchor = xPos;
    yAnchor = yPos;
}

void Ellipse::setSymbol(char pSymbol) {
    symbol = pSymbol;
}

char Ellipse::getSymbol() {
    return symbol;
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

Polygon::Polygon() : Polygon(0, 0, 3, 1, 't') {}

Polygon::Polygon(int pXAnchor, int pYAnchor, int pSideCount, int pSideLength, char pSymbol) :
        xAnchor{pXAnchor}, yAnchor{pYAnchor}, sideCount{pSideCount}, sideLength{pSideLength}, symbol{pSymbol} {}

Polygon::Polygon(Polygon const &that) = default;

Polygon::Polygon(Polygon &&that) noexcept = default;

Polygon &Polygon::operator=(Polygon const &that) = default;

Polygon &Polygon::operator=(Polygon &&that) noexcept = default;

Polygon::~Polygon() = default;

void Polygon::draw(screen &s) {
    s.polygon(xAnchor, yAnchor, sideCount, sideLength, symbol);
}

void Polygon::info(ostream &output) {
    output << "polygon x y n l s \t\t"
           << xAnchor << " "
           << yAnchor << " "
           << sideCount << " "
           << sideLength << " "
           << symbol << std::endl;
}

int Polygon::getXAnchor() {
    return xAnchor;
}

int Polygon::getYAnchor() {
    return yAnchor;
}

void Polygon::setYAnchor(int pos) {
    yAnchor = pos;
}

void Polygon::setXAnchor(int pos) {
    xAnchor = pos;
}

void Polygon::setAnchors(int xPos, int yPos) {
    xAnchor = xPos;
    yAnchor = yPos;
}

void Polygon::setSymbol(char pSymbol) {
    symbol = pSymbol;
}

char Polygon::getSymbol() {
    return symbol;
}

int Polygon::getSideCount() {
    return sideCount;
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












