//
// Created by nick on 26/8/19.
//

//
// Created by Nick van der Merwe on 6/08/2019.
//

#include <iostream>
#include <bits/stdc++.h>

//template<typename T>
//int highestNotZero(int size, T *arr) {
//    //Takes in an array and finds what's the highest index + 1 that isn't a default value
//    T defaultType{};
//    int index = -1;
//    for (int i = 0; i < size; i++) {
//        if (arr[i] != defaultType) {index = i;}
//    }
//    return index + 1;
//}

template<typename T>
class Bunch {
public:
    //Essential methods
    Bunch();

    Bunch(int pSize, T *parr); //p ctors; variety of optional inputs

    Bunch(int pSize, T *parr, bool pSorted);

    Bunch(int pSize, T *parr, bool pSorted, bool pAscending);

    Bunch(Bunch const &that); //Copy ctor

    Bunch(Bunch &&that) noexcept; //Move ctor

    Bunch &operator=(Bunch const &that); //Copy assign

    Bunch &operator=(Bunch &&that) noexcept; //Move assign

    ~Bunch(); //dtor

    //Overload []
    T operator[](int index) const;

    //Functional methods
    int getSize();

    int getTop();

    void shrink(); // Halves the size

    void extend(); // Doubles the size

    bool insert(T toInsert); // Appends the value if unsorted

    bool remove(int toRemove); // Removes the given int

    bool getSorted() const;

    void setSort(bool pSorted); //Sorts the Bunch

    void unsort(); // Disables automatic sorting

    bool getAscend() const;

    void setAscend(bool pAscending);

    int search(T toFind); //Finds the index of the given point

    void display(); //Prints the Bunch to stdout

    //Overriding << operator too for readability despite it not being required
    friend std::ostream &operator<<(std::ostream &os, Bunch<T> const &that);

private:
    int listSize;
    T *arr;
    bool sorted;
    bool ascending;
    int top;
};

template<typename T>
Bunch<T>::Bunch() : Bunch(32, new T[32]{}) {};


template<typename T>
Bunch<T>::Bunch(int pSize, T *parr) : listSize{pSize}, arr{parr}, sorted{false}, ascending{true},
                                      top{0} {}

template<typename T>
Bunch<T>::Bunch(int pSize, T *parr, bool pSorted) : listSize{pSize}, arr{parr}, sorted{pSorted}, ascending{true},
                                                    top{0} {}

template<typename T>
Bunch<T>::Bunch(int pSize, T *parr, bool pSorted, bool pAscending) : listSize{pSize}, arr{parr}, sorted{pSorted},
                                                                     ascending{pAscending},
                                                                     top{0} {}

template<typename T>
Bunch<T>::Bunch(Bunch const &that) : listSize{that.listSize},
                                     arr{new T[listSize]{}},
                                     sorted{that.sorted},
                                     ascending{that.ascending},
                                     top{that.top} {
   for(int i = 0; i < top; i++){
       arr[i] = that.arr[i];
   }
}

template<typename T>
Bunch<T>::Bunch(Bunch &&that) noexcept : listSize{std::move(that.listSize)}, arr{std::move(that.arr)},
                                         sorted{std::move(that.sorted)},
                                         ascending{std::move(that.ascending)}, top{std::move(that.top)} {
    that.arr = nullptr;
}


template<typename T>
Bunch<T> &Bunch<T>::operator=(Bunch const &that) {
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

template<typename T>
Bunch<T> &Bunch<T>::operator=(Bunch &&that) noexcept {
    listSize = std::move(that.listSize);
    arr = std::move(that.arr);
    sorted = std::move(that.sorted);
    ascending = std::move(that.ascending);
    top = std::move(that.top);
    that.arr = nullptr;
    return *this;
}

template<typename T>
Bunch<T>::~Bunch() {
    delete[] arr;
}

//getter
template<typename T>
T Bunch<T>::operator[](int index) const {
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
template<typename T>
int Bunch<T>::getSize() {
    return listSize;
}

template<typename T>
int Bunch<T>::getTop() {
    return top;
}

template<typename T>
void Bunch<T>::shrink() {
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

template<typename T>
void Bunch<T>::extend() {
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

template<typename T>
bool Bunch<T>::insert(T toInsert) {
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

template<typename T>
int Bunch<T>::search(T toFind) {
    for (int i = 0; i < top; i++) {
        if (arr[i] == toFind) {
            return i;
        }
    }
    std::cerr << "Failed to locate item in list. Returning capacity." << std::endl;
    return listSize;
}

template<typename T>
bool Bunch<T>::remove(int toRemove) {
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

template<typename T>
bool Bunch<T>::getSorted() const {
    return sorted;
}

template<typename T>
void Bunch<T>::setSort(bool pSorted) {
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

template<typename T>
void Bunch<T>::unsort() {
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

template<typename T>
void Bunch<T>::setAscend(bool pAscending) {
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


template<typename T>
bool Bunch<T>::getAscend() const {
    return ascending;
}

template<typename T>
void Bunch<T>::display() {
    //Displays the number of elements and the elements in the Bunch
    std::cout << "Integers: " << top << " Items: [";
    for (int i = 0; i < top; i++) {
        std::cout << arr[i];
        if (i != top - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Bunch<T> &that) {
    //NOTE: I would delegate and ONLY have one of display or this, but this
    //isn't actually on the criteria and this seemed significantly neater for demonstrate();
    os << "Integers: " << that.top << " Items: [";
    for (int i = 0; i < that.top; i++) {
        os << that.arr[i];
        if (i != that.top - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

