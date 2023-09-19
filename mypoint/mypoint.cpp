/*******************************************************************************
 * Filename: mypointers.cpp
 * Author  : Isabel Chen
 * Version : 1.0
 * Date    : September 11, 2023
 * Description: Introduction to classes.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// class with the name MyPoint
class MyPoint { 
// public section, declares everything within this block public, no need to specify every method/instance var
public: 
    // constructor that uses an initializer list, same name as the class
    MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} {
        // usually here in java you would have this.x = x, this.y = y etc
        // in c++, "this" is a pointer, so you must use pointer dereference
        // in practice, you can leave it empty and use an initializer list : x_{x} meaning instance var x_ is initialized using x (x_ = x)
    }

    // methods that do not modify member variables should be declared const
    void print_coords() const {
        cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed << setprecision(2) << z_ << ")" << endl;
    }
    // mutator (setter), cannot be const as it modifies the method
    void set_x(int x) {
        x_ = x;
    }
    // accressor (getter), declared const: calling the method will not change the object meaning ..., optional but good for practice
    int get_x() const {
        // ... inside the code you cannot do x_ = 5
        return x_;
    }
// private section
private:
    // member variables (fields), using the trailing _ for these variables
    // underscore tells you that it is an instance variable of an object, rather than a method or an argument or a local variable
    // instance var are private, rest of code usually public
    int x_, y_;
    float z_;

}; // semicolon required at the end of the class

// pass by reference, and using an iterator (which is an object that can be used essentially as if it were a pointer):
void display_points(const vector<MyPoint> &points) {
    for(auto it = points.cbegin(); it != points.cend(); it++) { // it: is the iterator object, do not care about the type: auto, cbegin method creates an interator object, cend method returns a value telling the iterator to stop when you reached the end of the vector, it++ operator specific to this iterator
        it -> print_coords(); // same as pointer dereference operator (*it).print_coords();, looks like a pointer but is an object
        // arrow operator, start from the iterator, go from the corresponding object, and call the print_coords method on the corresponding object
    }
}

void display_points_v2(const vector<MyPoint> &points) {
    for(size_t i = 0; i < points.size(); i++) { // int does not work when looping over a vector, the size type/method is not an int
    // size_t is a standard c++ type, always big enough to count anything
        points[i].print_coords();
    }
}

int main() {
    // local variables, integers allocated on the stack (will be automatically deallocated from the stack when the current function returns)
    int x, y; 
    
    // in c++ you can use new or create object as local variables
    // local objects allocated on the stack:
    // the only way to delete these objects would be to return from the main function
    MyPoint point1(5, 7, 1.9823412);
    MyPoint point2(1, 2, 3);
    MyPoint point3(4, 5, 6);
    point2.print_coords();

    // arraylist in java, an array but you can grow and shrink it automatically
    // local vector object, generic in c++
    vector<MyPoint> points; // empty
    points.push_back(point1); // push_back method adds a new object to the end of the vector
    points.push_back(point2);
    points.push_back(point3);

    // define another local vector, different name but same type
    vector<MyPoint> points_above_two;
    // for each loop (using a reference so there is no copy)
    for(const auto &point : points) { // &point (& is a reference, just a new name for an existing element to avoid copying) is the variable name for the current element in the vector that we are processing in the loop, points is the vector of which we want to loop
    // type auto, normally a type would be in place or MyPoint, good practice allowing the compiler to compute the type for you
        if(point.get_x() > 2) {
            points_above_two.push_back(point);
            // will not contain point2 since x > 2
        }
    }

    // dynamic memory allocation to create objects using new, 33:45
    // function
    display_points(points_above_two);

    // practice using a standard in (STDIN)
    cout << "Input x: ";
    cin >> x;

    cout << "Input y: ";
    cin >> y;

    // object allocated on the heap (must be explicitly deallocated in your code using "delete" when you do not need to object anymore)
    // the new object here does not have a name, there must be a pointer to remember where it is in the heap
    // the pointer point4 itself is a local variable in the stack
    MyPoint *point4 = new MyPoint(x, y, 7); // new object created dynamically with inputs

    // !! for objects, the name of the pointer is just the name, you cannot use it as the name of the object, unlike the array !!
    // calling the method using the pointer to the object
    // remember point4 is the name of the pointer to the object not the object, must use arrow notation
    point4 -> print_coords(); // same as: (*point4).print_coords(); dereferencing the pointer to go from the pointer to the object, then you can use a normal method call .print_coords()

    // deallocating the object from the heap (this does not change the pointer itself which is a local variable on the stack)
    // for every "new" in your code, there must be a corresponding "delete", to make sure the heap is properly managed
    delete point4;

    return 0;

    /*  using valgrind to detect memory leaks

    ./mypoint
    val
    valgrind --leak-check=full ./mypoint

    in use at exit: bytes in blocks (how much memory you lost from forgetting to delete)
    main (mypoint.cpp: line number) (tells you where memory that is leaking is allocated, which object that you forgot to delete)

    */

   // in ubuntu vm, int and floats are 4 bytes each
}
