//
// Created by nick on 29/8/19.
//

#ifndef GEOMETRICSHAPES_ABSTRACTSHAPES_H
#define GEOMETRICSHAPES_ABSTRACTSHAPES_H

#include "screen.cpp"

class Shape {
public:
    Shape();
    
    Shape(int pXAnchor, int pYAnchor, char pSymbol);

    Shape(Shape const &that);

    Shape(Shape &&that) noexcept;

    Shape &operator=(Shape const &that);

    Shape &operator=(Shape &&that) noexcept;

    virtual ~Shape() = 0;

    virtual void draw(screen & s) = 0;

    virtual void info() = 0;

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

class Point : public Shape{
public:
    Point();

    Point(int pXAnchor, int pYAnchor, char pSymbol);

    Point(Point const &that);

    Point(Point &&that) noexcept;

    Point &operator=(Point const &that);

    Point &operator=(Point &&that) noexcept;

    ~Point();

    void draw(screen &s) override;

    void info() override;
};

class Line : public Shape {
public:
    Line();

    Line(int pFromX, int pFromY, int pToX, int pToY, char pSymbol);

    Line(Line const &that);

    Line(Line &&that) noexcept;

    Line &operator=(Line const &that);

    Line &operator=(Line &&that) noexcept;

    ~Line();

    void draw(screen &s) override;

    void info() override;

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

class Ellipse : public Shape {
public:
    Ellipse();

    Ellipse(int pXAnchor, int pYAnchor, int pXRadius, int pYRadius, char pSymbol);

    Ellipse(Ellipse const &that);

    Ellipse(Ellipse &&that) noexcept;

    Ellipse &operator=(Ellipse const &that);

    Ellipse &operator=(Ellipse &&that) noexcept;

    ~Ellipse();

    void draw(screen &s) override;

    void info() override;

    void setRadii(int xPos, int yPos);

    void setXRadius(int pos);

    void setYRadius(int pos);

    int getXRadius();

    int getYRadius();

private:
    int xRadius;
    int yRadius;
};

class Polygon : public Shape {
public:
    Polygon();

    Polygon(int pXAnchor, int pYAnchor, int pSideCount, int pSideLength, char pSymbol);

    Polygon(Polygon const &that);

    Polygon(Polygon &&that) noexcept;

    Polygon &operator=(Polygon const &that);

    Polygon &operator=(Polygon &&that) noexcept;

    ~Polygon();

    void draw(screen &s) override;

    void info() override;

    int getSideCount();

    void setSideCount(int count);

    int getSideLength();

    void setSideLength(int length);

private:
    int sideCount;
    int sideLength;
};

#endif //GEOMETRICSHAPES_ABSTRACTSHAPES_H
