/*******************************************************************************
 * Filename: pointers.cpp
 * Author  : Isabel Chen
 * Version : 1.0
 * Date    : September 8, 2023
 * Description: Introduction to pointers.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
using namespace std;

// k is a copy of x, changing k does not change x
void pass_by_value(int k) {
    k = 10;
}

void pass_by_pointer(int *k) {
    *k = 10; // same as x = 10
}

// & is not the "address of" operator here, it is just a notation to indicate that k is passed by reference
// a reference is just a new name for something that already exists
// changing k changes x
void pass_by_reference(int &k) {
    k = 10;
}
// internally, the complier rewrites all the code with pass by pointers

// the array parameter is in fact a pointer but we can use it as if it were the name of the array itself
void display_array(int array[], int length) {
    for(int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// the array parameter is a pointer and we used pointer arthmetic
void display_array_ptr(int *array, int length) {
    for(int *p = array; p < array + length; p++) { // creates a new pointer p, pointer p copies the pointer array, there is now 2 pointers, p will then point to the next element in the array +8
        cout << *p << " ";
    }
    cout << endl;
}

int main() {
    int x; // type integer
    x = 5; // stores the int 5 into x
    int *z; // type pointer (* means pointer) to integer; pointer is a normal var where you store the address
    z = &x; // a pointer stores the address of integer x into z
    // int x = 5, *z = &x; shorter version of the above

    cout << x << " " << &x << " " << z << " " << &z << endl;
    // 5 (x) 0xffffc675def0 (address of x) 0xffffc675def0 (value of z) 0xffffc675def8 (address of z in memory)
    // prints out x itself, x in memory, address of x, the content of z is the same as the address, and memory of z
    
    // dereference operator: starting from z, looks at the address contained in z, which is the address of x, then jumps to x itself; follows the arrow from z to x
    // pointer dereference: if z == &x then *z is the same as x itself since z points to x
    // do not confuse the * dereference operator and the * pointer type.
    cout << "*z is: " << *z << endl;
    *z = 7; // same as x = 7
    cout << x << " " << &x << " " << z << " " << &z << endl;
    cout << "*z is: " << *z << endl; // now x and *z = 7 but the addresses remain the same, x and z has not moved in memory

    // why use *z when you can just use x? 
    // later on, it is useful in identifying a pointer that points at something without a name, here we have 2 separate name x and z

    // DO NOT do this: never change pointers
    // z += 30000;
    // cout << "*z is: " << *z << endl; // dereferencing is not allowed, garbage or no memory, throws a segmentation fault, now z points to somewhere else, unknown?
    // z is not *z which is not equal to x, you will be changing the address stored in z, making it point to a completely different place in memory
    // segmentation fault: trying to access memory that is not there
    // note: when you get a segmentation fault, you can use gdb from the command line to find the source of the problem
        // gdb debugger
        // gdb ./pointer
        // run: tells gdb to run your code, line of code where you have a segmentation fault
        // quit when done

    // summary
    // computer uses addresses to find the data we store in a variable in memory
    // *z is the variable that stores the address of x
    // z knows where x is in memory, z points to x

    x = 5;
    // k (see the function definition) is a copy of x, changing k does not change the value of x; this function call is useless
    pass_by_value(x); // calls the function defined at the top, when this is called, the value of x or 5 is copied to int k, but they are two different int in memory, x is only visible in main and k only exists in the pass by value function
    // ref above, changing k does not change x, reaching at the end of the function call, k changes back to 10
    cout << "x is: " << x << endl; // prints out x

    // k (see func def) is a copy of &x, so k points at x; *k is then the same as x, so changing *k also changes x
    // you will be able to change x even though x is defined in main
    // instead of giving the value of (x), we are now giving the address of x (&x)
    pass_by_pointer(&x); // above, k is now a pointer to integer x, *k is now equal to x, x just cannot be used in the function above as it is only visible in main
    cout << "x is: " << x << endl; // prints out x = 10

    x = 5;
    // k (see func def) is an alias for x, so changing k changes x
    // internally the compiler implements pass by reference by rewriting your code to use a pointer (pass by pointer), so pass by reference is just for the convenience of the programmer
    pass_by_reference(x); // when passed by ref, we keep the name x of the function and the argument &k above just becomes a new name for the existing x
    cout << "x is: " << x << endl; // modifying k also modifies x, x is 10

    // dynamic memory allocation
    // pointer to an anonymous variable lengeth array which is dynamically allocated on the heap (as variable length arrays must be)
    // the pointer is a local variable which is allocated from the stack
    // new operator and name of a class creates an object in memory, dynamically allocates new memory for your program while running, comes from the heap
    // in c++, you can use new to allocate anything, and int or an array etc
    // here we are allocating an array of integers with a dynamic size, else just define as a local variable if the size is known int y[10]
    // the size is determined at run time, allocates an array of x integers in the heap of the program
    // the array itself does not have a name, anonymous in memory, x is the name for the size, to use the array, we need a pointer to the array, which is stored in the pointer *values that points to the beginning of the array
    int *values = new int[x]; 

    // you can use the name of the pointer as if it is the name of the array
    for(int i = 0; i <x; i++) {
        // using the pointer as if it were the name of the array: 
        values[i] = i; // the normal array notation
        // or using pointer arithmetic (which is what the CPU really does):
        *(values + i) = i; // pointer addition that does everything manually in code, 40:30 for explanation

    }

    // using the pointer as if it were the name of the array:
    display_array(values, x);
    display_array_ptr(values, x);
    // deleting the array from the heap (the pointer remains on the stack because it is a local variable, and it is not modified):
    delete [] values; // required in c++ to manually delete the memory, deleting the array pointed at the pointer values
    // does not delete the pointer as it is a local variable and will still point to where the array use to be, only what it points to, follows it to the array
    // for every new, there must be a corresponding delete
    return 0;
}