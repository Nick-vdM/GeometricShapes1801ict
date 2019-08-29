# Geometric Shapes #

This is a small project done for 1801ICT with the requirements 
in project3.pdf. In short, the screen.cpp file is used to display a 
variety of classes. Its main purpose is to exercise inheritance and 
polymorphism.

The proposed structure to solve it is as follows:

## Task 1 - My Template Painter ##
The basic classes and functions being made here are:
### 1. properties ###
* Note everything needs a display & draw method
#### Point ####
* x, y and symbol

#### Line ####
* Two points; source & target

#### Ellipse ####
* anchor point
* a = x-radius
* b = y-radius 
* if a = b: becomes circle

#### Polygon ####
* n number of sides
* length of each side
* Will need overriding the essential methods so that a dynamic
number of sides can be used

### 2. Template class Bunch ### 
* 32 items
* Overload [] operator
* Add method to end of array
* In short, the integer class from project 2 can be 
copy pasted with a template

### 3. Main function ###
* Four bunch objects: one for each shape
* Provide a menu to draw all of the shapes
* Function to list all the objects that have been painted

#### 3.1. Saving shapes ####
* Save and load from files using stream direction to 
simplify it

## Task 2. My Polymorphic Painter ##
Essentially, we're turning point into an abstract
shape class and letting everything inherit it here
### 1. Abstract Classes ###
* Make draw & info pure virtual
* Destructor should be pure virtual - using
abstract class pointers (look into them)
### 2. Main Console ###
* Essentially the same, but only use a bunch<Shape*>
* Ensure memory allocation is properly done
* No down casting or switches for drawing - call
polymorphic methods using shape pointer
