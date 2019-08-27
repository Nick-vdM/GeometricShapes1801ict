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

    virtual void draw(screen & s);

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

class Line : public Point {
public:
    Line();

    Line(int pFromX, int pFromY, int pToX, int pToY, char pSymbol);

    Line(Line const &that);

    Line(Line &&that) noexcept;

    Line &operator=(Line const &that);

    Line &operator=(Line &&that) noexcept;

    ~Line();

    void draw(screen & s) override;

    void setDest(int xPos, int yPos);

    int getXDest();

    int getYDest();

    void setYDest(int pos);

    void setXDest(int pos);

    void setDests(int xPos, int yPos);

private:
    int toX;
    int toY;
};

class Ellipse : public Point {
public:
    Ellipse();

    Ellipse(int pXAnchor, int pYAnchor, int pXRadius, int pYRadius, char pSymbol);

    Ellipse(Ellipse const &that);

    Ellipse(Ellipse &&that) noexcept;

    Ellipse &operator=(Ellipse const &that);

    Ellipse &operator=(Ellipse &&that) noexcept;

    ~Ellipse();

    void draw(screen & s) override;

    void setRadii(int xPos, int yPos);

    void setXRadius(int pos);

    void setYRadius(int pos);

    int getXRadius();

    int getYRadius();

public:
    int xRadius;
    int yRadius;
};

class Polygon : public Point {
public:
    Polygon();

    Polygon(int pXAnchor, int pYAnchor, int pSideCount, int pSideLength, char pSymbol);

    Polygon(Polygon const &that);

    Polygon(Polygon &&that) noexcept;

    Polygon &operator=(Polygon const &that);

    Polygon &operator=(Polygon &&that) noexcept;

    ~Polygon();

    void draw(screen & s) override;

    int getSideCount();

    void setSideCount(int count);

    int getSideLength();

    void setSideLength(int length);

protected:
    int sideCount;
    int sideLength;
};

#endif //GEOMETRICSHAPES_SHAPES_H
