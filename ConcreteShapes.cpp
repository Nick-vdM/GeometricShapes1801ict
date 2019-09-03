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
    output << "point "
           << xAnchor << " "
           << yAnchor << " "
           << symbol << std::endl;
}

int Point::getXAnchor() const {
    return xAnchor;
}

int Point::getYAnchor() const {
    return yAnchor;
}

char Point::getSymbol() const {
    return symbol;
}

void Point::setXAnchor(int xAnchor) {
    Point::xAnchor = xAnchor;
}

void Point::setYAnchor(int yAnchor) {
    Point::yAnchor = yAnchor;
}

void Point::setSymbol(char symbol) {
    Point::symbol = symbol;
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
    output << "line "
           << xAnchor << " "
           << yAnchor << " "
           << toX << " "
           << toY << " "
           << symbol << std::endl;
}

int Line::getXAnchor() const {
    return xAnchor;
}

int Line::getYAnchor() const {
    return yAnchor;
}

int Line::getToX() const {
    return toX;
}

int Line::getToY() const {
    return toY;
}

char Line::getSymbol() const {
    return symbol;
}

void Line::setXAnchor(int xAnchor) {
    Line::xAnchor = xAnchor;
}

void Line::setYAnchor(int yAnchor) {
    Line::yAnchor = yAnchor;
}

void Line::setToX(int toX) {
    Line::toX = toX;
}

void Line::setToY(int toY) {
    Line::toY = toY;
}

void Line::setSymbol(char symbol) {
    Line::symbol = symbol;
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
    output << "ellipse "
           << xAnchor << " "
           << yAnchor << " "
           << xRadius << " "
           << yRadius << " "
           << symbol << std::endl;
}

int Ellipse::getXAnchor() const {
    return xAnchor;
}

int Ellipse::getYAnchor() const {
    return yAnchor;
}

int Ellipse::getXRadius() const {
    return xRadius;
}

int Ellipse::getYRadius() const {
    return yRadius;
}

char Ellipse::getSymbol() const {
    return symbol;
}

void Ellipse::setXAnchor(int xAnchor) {
    Ellipse::xAnchor = xAnchor;
}

void Ellipse::setYAnchor(int yAnchor) {
    Ellipse::yAnchor = yAnchor;
}

void Ellipse::setXRadius(int xRadius) {
    Ellipse::xRadius = xRadius;
}

void Ellipse::setYRadius(int yRadius) {
    Ellipse::yRadius = yRadius;
}

void Ellipse::setSymbol(char symbol) {
    Ellipse::symbol = symbol;
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
    output << "polygon "
           << xAnchor << " "
           << yAnchor << " "
           << sideCount << " "
           << sideLength << " "
           << symbol << std::endl;
}

int Polygon::getXAnchor() const {
    return xAnchor;
}

int Polygon::getYAnchor() const {
    return yAnchor;
}

int Polygon::getSideCount() const {
    return sideCount;
}

int Polygon::getSideLength() const {
    return sideLength;
}

char Polygon::getSymbol() const {
    return symbol;
}

void Polygon::setXAnchor(int xAnchor) {
    Polygon::xAnchor = xAnchor;
}

void Polygon::setYAnchor(int yAnchor) {
    Polygon::yAnchor = yAnchor;
}

void Polygon::setSideCount(int sideCount) {
    Polygon::sideCount = sideCount;
}

void Polygon::setSideLength(int sideLength) {
    Polygon::sideLength = sideLength;
}

void Polygon::setSymbol(char symbol) {
    Polygon::symbol = symbol;
}

