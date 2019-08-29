//
// Created by nick on 26/8/19.
//

#ifndef GEOMETRICSHAPES_SHAPES_H
#define GEOMETRICSHAPES_SHAPES_H

#include "screen.cpp"

class Point {
public:
    Point();

    Point(int pXAnchor, int pYAnchor, char pSymbol);

    Point(Point const &that);

    Point(Point &&that) noexcept;

    Point &operator=(Point const &that);

    Point &operator=(Point &&that) noexcept;

    ~Point();

    void draw(screen &s);

    void info(ostream &output);

    int getXAnchor();

    int getYAnchor();

    void setYAnchor(int pos);

    void setXAnchor(int pos);

    void setAnchors(int xPos, int yPos);

    void setSymbol(char pSymbol);

    char getSymbol();

protected:
    int xAnchor;
    int yAnchor;
    char symbol;

};

class Line {
public:
    Line();

    Line(int pXAnchor, int pYAnchor, int pToX, int pToY, char pSymbol);

    Line(Line const &that);

    Line(Line &&that) noexcept;

    Line &operator=(Line const &that);

    Line &operator=(Line &&that) noexcept;

    ~Line();

    void draw(screen &s);

    void info(ostream &output);

    int getXAnchor();

    int getYAnchor();

    void setYAnchor(int pos);

    void setXAnchor(int pos);

    void setAnchors(int xPos, int yPos);

    void setSymbol(char pSymbol);

    char getSymbol();

    void setDest(int xPos, int yPos);

    int getToX();

    int getToY();

    void setToY(int pos);

    void setToX(int pos);

    void setTos(int xPos, int yPos);

private:
    int xAnchor;
    int yAnchor;
    int toX;
    int toY;
    char symbol;
};

class Ellipse {
public:
    Ellipse();

    Ellipse(int pXAnchor, int pYAnchor, int pXRadius, int pYRadius, char pSymbol);

    Ellipse(Ellipse const &that);

    Ellipse(Ellipse &&that) noexcept;

    Ellipse &operator=(Ellipse const &that);

    Ellipse &operator=(Ellipse &&that) noexcept;

    ~Ellipse();

    void draw(screen &s);

    void info(ostream &output);

    int getXAnchor();

    int getYAnchor();

    void setYAnchor(int pos);

    void setXAnchor(int pos);

    void setAnchors(int xPos, int yPos);

    void setSymbol(char pSymbol);

    char getSymbol();

    void setRadii(int xPos, int yPos);

    void setXRadius(int pos);

    void setYRadius(int pos);

    int getXRadius();

    int getYRadius();

public:
    int xAnchor;
    int yAnchor;
    int xRadius;
    int yRadius;
    char symbol;
};

class Polygon {
public:
    Polygon();

    Polygon(int pXAnchor, int pYAnchor, int pSideCount, int pSideLength, char pSymbol);

    Polygon(Polygon const &that);

    Polygon(Polygon &&that) noexcept;

    Polygon &operator=(Polygon const &that);

    Polygon &operator=(Polygon &&that) noexcept;

    ~Polygon();

    void draw(screen &s);

    int getXAnchor();

    int getYAnchor();

    void setYAnchor(int pos);

    void setXAnchor(int pos);

    void setAnchors(int xPos, int yPos);

    void setSymbol(char pSymbol);

    char getSymbol();

    void info(ostream &output);

    int getSideCount();

    void setSideCount(int count);

    int getSideLength();

    void setSideLength(int length);

protected:
    int xAnchor;
    int yAnchor;
    int sideCount;
    int sideLength;
    char symbol;
};

#endif //GEOMETRICSHAPES_SHAPES_H
