//
// Created by nick on 8/9/19.
//

//##############################################
//#==================SCREEN-===================#
//##############################################

/* Written by M A H Newton on 25.08.2019 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;

/* A class to display 2d graphics in text mode */
/* The screen is a square (-dmin,-dmin) to (dmax,dmax) */
/* The typical screen size is (-20, -20) to (20,20) */
class screen
{
public:
    screen(); 												// default constructor
    screen(screen const & that);							// copy constructor
    screen(screen && that) noexcept;						// move constructor
    screen & operator = (screen const & that); 				// copy assignment
    screen & operator = (screen && that) noexcept;			// move assignment
    ~screen();												// destructor

    int dmin() const;										// getter for dmin
    int dmax() const;										// getter for dmax

    void display() const;									// display screen

    void clear();											// clear the screen
    void axes(char s);										// show both axes using symbol s

    void point(int x, int y, char s);						// plot a point using coordinate (x,y) and symbol s
    void ellipse(int x, int y, int a, int b, char s);		// plot an ellipse using center (x,y), radii a and b, and symbol s
    void polygon(int x, int y, int n, int l, char s);		// plot a polygon using center (x,y), n sides, length l, and symbol s

    void line(int x, int y, int xp, int yp, char s);		// plot a line from (x,y) to (xp, yp) using symbol s

private:

    // low lovel function to plot a single point  since y : x ratio is not 1, x is multiplied if r is true
    void plot(double x, double y, char s);			// plot a point

    int const dim = 20;								// default dimension
    double const ratio = 2.23;						// aspect ratio
    double const pi = acos(-1);						// pi value

    int mWidth, mHeight;							// width and height
    char ** mBoard;									// 2d screen board
};

// default constructor
screen::screen() : mWidth(ratio * dim * 2 + 1), mHeight(dim * 2 + 1)
{
    mBoard = new char * [mHeight];
    for(int j = 0; j < mHeight; ++j)
        mBoard[j] = new char [mWidth]();
}

// destructor
screen::~screen()
{
    for(int j = 0; j < mHeight; ++j)
        delete [] mBoard[j];
    delete [] mBoard;
}

// copy constructor
screen::screen(screen const & that) : mWidth(that.mWidth), mHeight(that.mHeight)
{
    mBoard = new char * [mHeight];
    for(int j = 0; j < mHeight; ++j)
    {
        mBoard[j] = new char [mWidth];
        for (int i = 0; i < mWidth; ++i)
            mBoard[j][i] = that.mBoard[j][i];
    }
}

// move constructor
screen::screen(screen && that) noexcept :
        mWidth(move(that.mWidth)), mHeight(move(that.mHeight)), mBoard(move(that.mBoard))
{
    that.mBoard = nullptr;
    that.mWidth = 0;
    that.mHeight = 0;
}

// copy assignment
screen & screen::operator = (screen const & that)
{
    if (this == &that) return *this;

    if (mHeight != that.mHeight || mWidth != that.mWidth)
    {
        for(int j = 0; j < mHeight; ++j)
            delete [] mBoard[j];
        delete [] mBoard;
        mWidth = that.mWidth;
        mHeight = that.mHeight;
        mBoard = new char * [mHeight];
        for(int j = 0; j < mHeight; ++j)
            mBoard[j] = new char [mWidth]();
    }

    for(int j = 0; j < mHeight; ++j)
        for (int i = 0; i < mWidth; ++i)
            mBoard[j][i] = that.mBoard[j][i];

    return *this;
}

// move constructor
screen & screen::operator = (screen && that) noexcept
{
    mWidth = move(that.mWidth);
    mHeight = move(that.mHeight);
    mBoard = move(that.mBoard);

    that.mBoard = nullptr;
    that.mWidth = 0;
    that.mHeight = 0;

    return *this;
}

// plot a point
void screen::plot(double x, double y, char s)
{
    int yy = static_cast<int>(round(-y + mHeight / 2) );
    int xx = static_cast<int>(round(ratio * x + mWidth / 2 + ratio / 2 ));
    mBoard[yy][xx] = s;
}

// getter for dmax
int screen::dmax() const
{
    return dim;
}

// getter for dmin
int screen::dmin() const
{
    return - dim;
}

// display screen
void screen::display() const
{
    for(int j = 0; j < mHeight; ++j)
    {
        for(int i = 0; i < mWidth; ++i)
            if (mBoard[j][i])
                cout << mBoard[j][i];
            else
                cout << ' ';
        cout << endl;
    }
}

// clear the screen
void screen::clear()
{
    for(int j = 0; j < mHeight; ++j)
        for(int i = 0; i < mWidth; ++i)
            mBoard[j][i] = 0;
}

// show the axes using symbol s
void screen::axes(char s)
{
    // plot x axis
    for(int x = dmin(); x <= dmax(); ++x)
        plot(x,0,s);
    // plot y axis
    for(int y = dmin(); y <= dmax(); ++y)
        plot(0,y,s);
}

// plot a point at (x,y) with symbol s
void screen::point(int x, int y, char s)
{
    plot(static_cast<double>(x), static_cast<double>(y), s);
}

// plot an ellipse using center (xc, yc), radii rx and ry, and symbol s
void screen::ellipse(int xc, int yc, int rx, int ry, char s)
{
    double dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // for region 1
    while (dx < dy)
    {
        // print points based on 4-way symmetry
        plot(x + xc, y + yc, s);
        plot(-x + xc, y + yc, s);
        plot(x + xc, -y + yc, s);
        plot(-x + xc, -y + yc, s);

        // checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
         ((rx * rx) * ((y - 1) * (y - 1))) -
         (rx * rx * ry * ry);

    // plotting points of region 2
    while (y >= 0)
    {
        // print points based on 4-way symmetry
        plot(x + xc, y + yc, s);
        plot(-x + xc, y + yc, s);
        plot(x + xc, -y + yc, s);
        plot(-x + xc, -y + yc, s);

        // checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

// plot a regular polygon with center (x,y), length l, n sides, using symbol s
void screen::polygon(int x, int y, int n, int l, char s)
{
    double * xx = new double [n];
    double * yy = new double [n];
    for(int k = 0; k < n; ++k)
    {
        xx[k] = l * cos(2*pi*k/n);
        yy[k] = l * sin(2*pi*k/n);
    }
    for(int k = 0; k < n; ++k)
        line(x + xx[k], y + yy[k], x + xx[(k+1) % n], y + yy[(k+1) % n],s);
}

// plot a line from (x0,y0) to (x1, y1) using symbol s
void screen::line(int x0, int y0, int x1, int y1, char s)
{
    if (x1 == x0)
    {
        if (y1 > y0)
            for(double y = y0; y <= y1; y++)
                plot(x0, y, s);
        else
            for(double y = y1; y <= y0; y++)
                plot(x0, y, s);
        return;
    }

    if (y1 == y0)
    {
        if (x1 > x0)
            for(double x = x0; x <= x1; x++)
                plot(x, y0, s);
        else
            for(double x = x1; x <= x0; x++)
                plot(x, y0, s);
        return;
    }

    double m = 1.0 * (y1 - y0) / (x1 - x0);
    double c = 1.0 * (y0 * x1 - y1 * x0) / (x1 - x0);

    if (abs(x1-x0) > abs(y1 - y0))
    {
        if (x1 > x0)
            for(double x = x0; x <= x1; x+=1)
                plot(x, m * x + c, s);
        else
            for(double x = x1; x <= x0; x+=1)
                plot(x, m * x + c, s);
    }
    else
    {
        if (y1 > y0)
            for(double y = y0; y <= y1; y+=1)
                plot((y - c)/m, y, s);
        else
            for(double y = y1; y <= y0; y+=1)
                plot((y - c)/m, y, s);
    }
}

// main function
//int main()
//{
//    screen s;
//    //	s.clear();				// clear the screen
//    s.axes('+');				// show axis using +
//    s.point(-20,-20,'+');
//    s.point(-14,-16,'$');		// show point using $
//    s.ellipse(6,6,5,5,'*'); 	// circle since 5 = 5
//    s.ellipse(-10,8,9,5,'*');	// ellipse since 9 != 5
//    s.polygon(-9,-9,6,8,'#');	// show 6-gon with length 8
//    s.line(9,-12, 19,7,'-');	// line from (9,12) to (19,7)
//    s.display();				// display whatever drawn
//
//}

//</editor-fold>

//##############################################
//#===================SHAPES===================#
//##############################################

//<editor-fold desc="SHAPES">

class Shape {
public:
    Shape() : Shape(0, 0, 'S') {}

    Shape(int pXAnchor, int pYAnchor, char pSymbol) : xAnchor{pXAnchor},
                                                      yAnchor{pYAnchor}, symbol{pSymbol} {}

    Shape(Shape const &that) = default;

    Shape(Shape &&that) noexcept = default;

    Shape &operator=(Shape const &that) = default;

    Shape &operator=(Shape &&that) noexcept = default;

    virtual ~Shape() = 0;

    virtual void draw(screen &s) = 0;

    virtual void info(std::ostream &os) = 0;

    int getXAnchor() const {
        return xAnchor;
    }

    int getYAnchor() const {
        return yAnchor;
    }

    void setYAnchor(int pos) {
        yAnchor = pos;
    }

    void setXAnchor(int pos) {
        xAnchor = pos;
    }

    void setAnchors(int xPos, int yPos) {
        xAnchor = xPos;
        yAnchor = yPos;
    }

    void setSymbol(char pSymbol) {
        symbol = pSymbol;
    }

    char getSymbol() const {
        return symbol;
    }


protected:
    int xAnchor;
    int yAnchor;
    char symbol;

};

Shape::~Shape() = default;

class Point : public Shape {
public:
    Point() : Point(0, 0, 'S') {}

    Point(int pXAnchor, int pYAnchor, char pSymbol) : Shape(pXAnchor, pYAnchor, pSymbol) {}

    Point(Point const &that) = default;

    Point(Point &&that) noexcept = default;

    Point &operator=(Point const &that) = default;

    Point &operator=(Point &&that) noexcept = default;

    ~Point() override = default;

    void draw(screen &s) override {
        s.point(xAnchor, yAnchor, symbol);
    }

    void info(std::ostream &os) override {
        //Prints the information to console
        os << "point "
           << xAnchor << " "
           << yAnchor << " "
           << symbol << std::endl;
    }

};

class Line : public Shape {
public:
    Line() : Line(0, 0, 1, 1, 'L') {}

    Line(int pFromX, int pFromY, int pToX, int pToY, char pSymbol) : Shape::Shape(pFromX, pFromY, pSymbol),
                                                                     toX{pToX}, toY{pToY} {}

    Line(Line const &that) = default;

    Line(Line &&that) noexcept = default;

    Line &operator=(Line const &that) = default;

    Line &operator=(Line &&that) noexcept = default;

    ~Line() override = default;

    void draw(screen &s) override {
        s.line(xAnchor, yAnchor, toX, toY, symbol);
    }

    void info(std::ostream &os) override {
        os << "line "
           << xAnchor << " "
           << yAnchor << " "
           << toX << " "
           << toY << " "
           << symbol << std::endl;
    }

    int getToX() const {
        return toX;
    }

    int getToY() const {
        return toY;
    }

    void setToX(int ptoX) {
        toX = ptoX;
    }

    void setToY(int ptoY) {
        ptoY = toY;
    }

private:
    int toX;
    int toY;
};

class Ellipse : public Shape {
public:

    Ellipse() : Ellipse(0, 0, 1, 1, 'E') {}

    Ellipse(int pXAnchor, int pYAnchor, int pXRadius, int pYRadius, char pSymbol) :
            Shape(pXAnchor, pYAnchor, pSymbol), xRadius{pXRadius}, yRadius{pYRadius} {}

    Ellipse(Ellipse const &that) = default;

    Ellipse(Ellipse &&that) noexcept = default;

    Ellipse &operator=(Ellipse const &that) = default;

    Ellipse &operator=(Ellipse &&that) noexcept = default;

    ~Ellipse() override = default;

    void draw(screen &s) override {
        s.ellipse(xAnchor, yAnchor, xRadius, yRadius, symbol);
    }

    void info(std::ostream &os) override {
        os << "ellipse "
           << xAnchor << " "
           << yAnchor << " "
           << xRadius << " "
           << yRadius << " "
           << symbol << std::endl;
    }

    void setRadii(int xPos, int yPos) {
        xRadius = xPos;
        yRadius = yPos;
    }

    void setXRadius(int pos) {
        xRadius = pos;
    }

    void setYRadius(int pos) {
        yRadius = pos;
    }

    int getXRadius() const {
        return xRadius;
    }

    int getYRadius() const {
        return yRadius;
    }

private:
    int xRadius;
    int yRadius;
};

class Polygon : public Shape {
public:
    Polygon() : Polygon(0, 0, 3, 1, 't') {}

    Polygon(int pXAnchor, int pYAnchor, int pSideCount, int pSideLength, char pSymbol) :
            Shape(pXAnchor, pYAnchor, pSymbol), sideCount{pSideCount}, sideLength{pSideLength} {}

    Polygon(Polygon const &that) = default;

    Polygon(Polygon &&that) noexcept = default;

    Polygon &operator=(Polygon const &that) = default;

    Polygon &operator=(Polygon &&that) noexcept = default;

    ~Polygon() override = default;

    void draw(screen &s) override {
        s.polygon(xAnchor, yAnchor, sideCount, sideLength, symbol);
    }

    void info(std::ostream & os) override {
        os << "polygon "
           << xAnchor << " "
           << yAnchor << " "
           << sideCount << " "
           << sideLength << " "
           << symbol << std::endl;
    }

    int getSideCount() const {
        return sideCount;
    }

    void setSideCount(int count) {
        sideCount = count;
    }

    int getSideLength() const {
        return sideLength;
    }

    void setSideLength(int length) {
        sideLength = length;
    }

private:
    int sideCount;
    int sideLength;
};;

//</editor-fold>

//##############################################
//#===================BUNCH====================#
//##############################################

//<editor-fold desc="BUNCH">


template<typename T>
class Bunch {
public:
    //Essential methods
    Bunch() : Bunch(32, new T[32]{}) {};

    Bunch(int pSize, T *parr) : listSize{pSize}, arr{parr}, sorted{false}, ascending{true},
                                top{0} {}

    Bunch(int pSize, T *parr, bool pSorted) : listSize{pSize}, arr{parr}, sorted{pSorted}, ascending{true},
                                              top{0} {}

    Bunch(int pSize, T *parr, bool pSorted, bool pAscending) : listSize{pSize}, arr{parr}, sorted{pSorted},
                                                               ascending{pAscending},
                                                               top{0} {}

    Bunch(Bunch const &that) : listSize{that.listSize},
                               arr{new T[listSize]{}},
                               sorted{that.sorted},
                               ascending{that.ascending},
                               top{that.top} {
        for (int i = 0; i < top; i++) {
            arr[i] = that.arr[i];
        }
    }

    Bunch(Bunch &&that) noexcept : listSize{std::move(that.listSize)}, arr{std::move(that.arr)},
                                   sorted{std::move(that.sorted)},
                                   ascending{std::move(that.ascending)}, top{std::move(that.top)} {
        that.arr = nullptr;
    }

    Bunch &operator=(Bunch const &that) {
        if (this == &that) return *this;
        if (listSize != that.listSize) {
            delete[] arr;
            listSize = that.listSize;
            arr = new T[listSize];
        }
        top = that.top;
        for (int i = 0; i < top; i++) {
            arr[i] = that.arr[i];
        }
        sorted = that.sorted;
        ascending = that.ascending;
        top = that.top;
        return *this;
    }


    Bunch &operator=(Bunch &&that) noexcept {
        listSize = std::move(that.listSize);
        arr = std::move(that.arr);
        sorted = std::move(that.sorted);
        ascending = std::move(that.ascending);
        top = std::move(that.top);
        that.arr = nullptr;
        return *this;
    }


    ~Bunch() {
        delete[] arr;
    }

//getter

    T operator[](int index) const {
        if (index > listSize - 1) {
            std::cerr << "ERROR: Out of bounds operation. Max index is " << listSize - 1 <<
                      " but index " << index << "was requested." <<
                      std::endl;
            exit(EXIT_FAILURE);
        } else {
            return arr[index];
        }
    }

//Functional Methods

    int getSize() {
        return listSize;
    }


    int getTop() {
        return top;
    }


    void shrink() {
        //Halves the size of arr. Note that integer division is being done so
        //listSize = 5 will go to 2
        for (int i = listSize / 2; i < listSize; i++) {
            if (listSize / 2 < top) {
                std::cerr << "ERROR: List would discard information. top = " << top << std::endl;
                return;
            }
        }
        //Generate a new Bunch that contains half the things
        int *firstHalf = new T[listSize / 2]{};
        for (int i = 0; i < listSize / 2; i++) {
            firstHalf[i] = arr[i];
        }
        delete[] arr;
        //Change the pointer & update listSize
        arr = firstHalf;
        listSize /= 2;
    }


    void extend() {
        //Doubles the size of arr
        //make a copy of arr & delete the old one
        int *copy = new T[listSize * 2];
        for (int i = 0; i < listSize; i++) {
            copy[i] = arr[i];
        }
        delete[] arr;
        //Change the pointer to the copy & update listSize
        arr = copy;
        listSize *= 2;
    }


    bool insert(T toInsert) {
        //Returns false if it couldn't be inserted
        //Inserts a new element at top unless its sorted
        if (top >= listSize) {
            std::cerr << "WARNING: failed to insert object. Bunch is full." << std::endl;
            return false;
        }
        //If it isn't sorted put it at the back
        arr[top] = toInsert;
        top++;
        return true;
    }


    int search(T toFind) {
        for (int i = 0; i < top; i++) {
            if (arr[i] == toFind) {
                return i;
            }
        }
        std::cerr << "Failed to locate item in list. Returning capacity." << std::endl;
        return listSize;
    }


    bool remove(int toRemove) {
        //Removes a number if its found
        int index = this->search(toRemove);

        if (index == listSize || index > top) return false;

        if (sorted) {
            //Move everything back
            for (int i = index; i < top - 1; i++) {
                arr[i] = arr[i + 1];
            }
        } else {
            //Grab the item at top and bring it back
            arr[index] = arr[top - 1];
        }
        top--;
        return true;
    }


    bool getSorted() const {
        return sorted;
    }


    void setSort(bool pSorted) {
        //Sorts the Bunch and flicks sorted to true
        if (pSorted) {
            sorted = true;
            //Note ascending = smallest first (at index 0)
            //Descending = biggest first
            if (ascending) {
                std::sort(arr, &arr[top]);
            } else {
                std::sort(arr, &arr[top], std::greater<int>());
            }
        } else {
            //Just flick sorted to false; don't actually unscramble
            sorted = false;
        }
    }

    void unsort() {
        //Must scramble Bunch by swapping each item with another randomly selecter item
        //Using Fisher-Yates shuffle
        srand(time(NULL));
        for (int i = top - 1; i >= 0; i--) {
            int index = rand() % top;
            //Swap index i & j
            T temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
        }
    }

    void setAscend(bool pAscending) {
        ascending = pAscending;
        //Update Bunch if necessary
        if (sorted) {
            if (ascending) {
                std::sort(arr, &arr[top]);
            } else {
                std::sort(arr, &arr[top], std::greater<int>());
            }
        }
    }

    bool getAscend() const {
        return ascending;
    }

    void list(std::ostream &output) {
        for (int i = 0; i < top; i++) {
            arr[i]->info(output);
        }
    }

    void clear() {
        top = 0;
    }

private:
    int listSize;
    T *arr;
    bool sorted;
    bool ascending;
    int top;
};

//</editor-fold>

//##############################################
//#================DEMONSTRATION===============#
//##############################################

//<editor-fold desc="DEMONSTRATION">

void printHelp() {
    std::cout << "==============================HELP MENU=================================" << std::endl
              << "To insert a shape type <shapename> <units>." << std::endl
              << "Shapes:" << std::endl
              << "\t point <x> <y> <Symbol>" << std::endl
              << "\t line <startX> <startY> <toX> <toY> <Symbol>" << std::endl
              << "\t ellipse <centreX> <centreY> <xRadius> <yRadius> <Symbol>" << std::endl
              << "\t Polygon <centreX> <centreY> <numberOfSides> <sideLength> <Symbol>" << std::endl
              << "Type save <filename> or load <filename> to save/load"<< std::endl
              << "Note the board is x <- [-20, 20] & y <- [-20, 20]" << std::endl
              << "Type 'paint shape <index>' to show the board. An index higher" << std::endl
              << "than the number of shapes stored prints everything" << std::endl
              << "Type 'fill' to randomly fill the entire screen" << std::endl
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

    void addPoint(std::istream &input) {
        try {
            Point *pointToInsert = new Point;
            *pointToInsert = getPointFromStream(input);
            pointToInsert->draw(board);
            shapes.insert(pointToInsert);
        } catch (const std::exception &e) {
            std::cout << "ERROR " << e.what() << " INVALID INPUT" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    }

    void addLine(std::istream &input) {
        try {
            Line *lineToInsert = new Line;
            *lineToInsert = getLineFromStream(input);
            lineToInsert->draw(board);
            shapes.insert(lineToInsert);
        } catch (const std::exception &e) {
            std::cout << "ERROR " << e.what() << " INVALID INPUT" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

    }

    void addEllipse(std::istream &input) {
        try {
            Ellipse *ellipseToInsert = new Ellipse;
            *ellipseToInsert = getEllipseFromStream(input);
            ellipseToInsert->draw(board);
            shapes.insert(ellipseToInsert);
        } catch (const std::exception &e) {
            std::cout << "ERROR " << e.what() << " INVALID INPUT" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

    }

    void addPolygon(std::istream &input) {
        try {
            Polygon *polygonToInsert = new Polygon;
            *polygonToInsert = getPolygonFromStream(input);
            polygonToInsert->draw(board);
            shapes.insert(polygonToInsert);
        } catch (const std::exception &e) {
            std::cout << "ERROR " << e.what() << " INVALID INPUT" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

    }


    void loadFromFile(char *path) {
        std::fstream ifs(path);
        if (!ifs) {
            std::cerr << "File failed to open";
            return;
        }
        shapes.clear();
        char word[255];
        while (ifs.peek() != EOF) {
            ifs >> word;
            if (strcmp(word, "point") == 0) {
                addPoint(ifs);
            } else if (strcmp(word, "line") == 0) {
                addLine(ifs);
            } else if (strcmp(word, "ellipse") == 0) {
                addEllipse(ifs);
            } else if (strcmp(word, "polygon") == 0) {
                addPolygon(ifs);
            }
        }
    }

    void saveToFile(char *path) {
        std::ofstream ofs(path);
        if (!ofs) {
            std::cerr << "Failed to open file";
            exit(EXIT_FAILURE);
        }
        shapes.list(ofs);
    }

    void paint() {
        char itemType[256];
        std::cin >> itemType;
        screen board;

        for (int i = 0; i < 255 && itemType[i] != '\0'; i++) {
            itemType[i] = ::tolower(itemType[i]);
        }

        if (strcmp(itemType, "all") == 0) {
            paintAll();
            return;
        }

        int index;
        char indexString[256];
        std::cin >> indexString;
        index = std::stoi(indexString);
        if (strcmp(itemType, "shape") == 0) {
            paintShape(shapes, index);
        }
    }

    void fillScreen() {
        //Generate random shapes and fill the screen
        //Purely for testing purposes
        for (int i = 0; i < shapes.getTop(); i++) {
            delete shapes[i];
        }
        shapes.clear();
        for (int i = 0; i < shapes.getSize(); i++) {
            switch (rand() % 4) {
                case 0:
                    generateRandomPoint();
                    break;
                case 1:
                    generateRandomLine();
                    break;
                case 2:
                    generateRandomEllipse();
                    break;
                case 3:
                    generateRandomPolygon();
                    break;
            }
        }
    }

private:

    template<typename T>
    void paintShape(Bunch<T> &shape, int index) {
        screen board;
        if (shape.getTop() < index) {
            //paint everything
            for (int i = 0; i < shape.getTop(); i++) {
                shape[i]->draw(board);
            }
        } else {
            //paint the index
            shape[index]->draw(board);
        }
        board.display();
    }

    void paintAll() {
        paintShape(shapes, std::numeric_limits<int>::max());
    }

    void generateRandomPoint() {
        Point *pointToInsert = new Point(
                (rand() % 40) - 20,
                (rand() % 40) - 20,
                static_cast<char>((rand() % 57) + 33));
        pointToInsert->draw(board);
        shapes.insert(pointToInsert);
    }

    void generateRandomLine() {
        Line *lineToInsert = new Line(
                (rand() % 40) - 20,
                (rand() % 40) - 20,
                (rand() % 40) - 20,
                (rand() % 40) - 20,
                static_cast<char>((rand() % 57) + 33));
        lineToInsert->draw(board);
        shapes.insert(lineToInsert);
    }

    void generateRandomEllipse() {
        Ellipse *ellipseToInsert = new Ellipse(
                (rand() % 35) - 15,
                (rand() % 35) - 15,
                (rand() % 3) + 2,
                (rand() % 3) + 2,
                static_cast<char>((rand() % 57) + 33));
        ellipseToInsert->draw(board);
        shapes.insert(ellipseToInsert);
    }

    void generateRandomPolygon() {
        Polygon *polygonToInsert = new Polygon(
                (rand() % 28) - 14,
                (rand() % 28) - 14,
                (rand() % 8) + 3,
                (rand() % 8) + 3,
                static_cast<char>((rand() % 57) + 33));
        polygonToInsert->draw(board);
        shapes.insert(polygonToInsert);
    }

    static Point getPointFromStream(std::istream &input) {
        char instruction[255];
        input >> instruction;
        int xAnchor = std::stoi(instruction);
        input >> instruction;
        int yAnchor = std::stoi(instruction);
        input >> instruction;
        char symbol = instruction[0];
        return Point(xAnchor, yAnchor, symbol);
    }

    static Line getLineFromStream(std::istream &input) {
        char instruction[255];
        input >> instruction;
        int xAnchor = std::stoi(instruction);
        input >> instruction;
        int yAnchor = std::stoi(instruction);
        input >> instruction;
        int toX = std::stoi(instruction);
        input >> instruction;
        int toY = std::stoi(instruction);
        input >> instruction;
        char symbol = instruction[0];
        return Line(xAnchor, yAnchor, toX, toY, symbol);
    }

    static Ellipse getEllipseFromStream(std::istream &input) {
        char instruction[255];
        input >> instruction;
        int xAnchor = std::stoi(instruction);
        input >> instruction;
        int yAnchor = std::stoi(instruction);
        input >> instruction;
        int xRadius = std::stoi(instruction);
        input >> instruction;
        int yRadius = std::stoi(instruction);
        input >> instruction;
        char symbol = instruction[0];
        return Ellipse(xAnchor, yAnchor, xRadius, yRadius, symbol);
    }

    static Polygon getPolygonFromStream(std::istream &input) {
        char instruction[255];
        input >> instruction;
        int xAnchor = std::stoi(instruction);
        input >> instruction;
        int yAnchor = std::stoi(instruction);
        input >> instruction;
        int sideCount = std::stoi(instruction);
        input >> instruction;
        int sideLength = std::stoi(instruction);
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
            Shapes.shapes.list(std::cout);
        } else if (strcmp("paint", instruction) == 0) {
            Shapes.paint();
        } else if (strcmp("save", instruction) == 0) {
            std::cin >> instruction;
            Shapes.saveToFile(instruction);
        } else if (strcmp("load", instruction) == 0) {
            std::cin >> instruction;
            Shapes.loadFromFile(instruction);
        } else if (strcmp("fill", instruction) == 0) {
            Shapes.fillScreen();
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

//</editor-fold>
