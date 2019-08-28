# Geometric Shapes #

This is a small project done for 1810ICT with the requirements 
in project3.pdf. In short, the screen.cpp file is used to display a 
variety of classes. Its main purpose is to exercise inheritance and 
polymorphism.

The proposed structure to solve it is as follows:

## Part 2.2 - My Template Painter ##
The basic classes and functions being made here are:
### 1. Shapes and properties ###
Question: Given that these are all just 
attributes, would it be convention to use
structures?
#### Point ####
* x and y

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
