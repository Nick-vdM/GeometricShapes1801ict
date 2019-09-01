//
// Created by nick on 26/8/19.
//

#ifndef GEOMETRICSHAPES_CONCRETESHAPES_H
#define GEOMETRICSHAPES_CONCRETESHAPES_H

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

    int getXAnchor() const;

    int getYAnchor() const;

    char getSymbol() const;

    void setXAnchor(int xAnchor);

    void setYAnchor(int yAnchor);

    void setSymbol(char symbol);

private:
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

    int getXAnchor() const;

    int getYAnchor() const;

    int getToX() const;

    int getToY() const;

    char getSymbol() const;

    void setXAnchor(int xAnchor);

    void setYAnchor(int yAnchor);

    void setToX(int toX);

    void setToY(int toY);

    void setSymbol(char symbol);

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

    int getXAnchor() const;

    int getYAnchor() const;

    int getXRadius() const;

    int getYRadius() const;

    char getSymbol() const;

    void setXAnchor(int xAnchor);

    void setYAnchor(int yAnchor);

    void setXRadius(int xRadius);

    void setYRadius(int yRadius);

    void setSymbol(char symbol);


private:
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

    void info(ostream &output);

    int getXAnchor() const;

    int getYAnchor() const;

    int getSideCount() const;

    int getSideLength() const;

    char getSymbol() const;

    void setXAnchor(int xAnchor);

    void setYAnchor(int yAnchor);

    void setSideCount(int sideCount);

    void setSideLength(int sideLength);

    void setSymbol(char symbol);

private:
    int xAnchor;
    int yAnchor;
    int sideCount;
    int sideLength;
    char symbol;

};

#endif //GEOMETRICSHAPES_CONCRETESHAPES_H
