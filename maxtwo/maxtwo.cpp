/*******************************************************************************
 * Filename: maxtwo.cpp
 * Author  : Isabel Chen
 * Version : 1.0
 * Date    : September 6, 2023
 * Description: Computes the max of two integers m and n.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm> 
using namespace std;

/* simple max function
int max(int n, int m) {
    if (n > m) {
        return n;
    }
    else {
        return m;
    }
} */

/* ternary operator
int max(int n, int m) {
    return (n > m) ? n : m;
} */

// or just include algorithm and use the function provided by c++


// main function that takes command line arguments
// argv and argc can be renamed; argument count and value 
// argc is an int, argv is an array of strings/pointers
int main(int argc, char* argv[]) {  
    int n, m; // will store the transformed int
    istringstream iss; // an input string stream object that reads data from a string

    // check whether there is the correct number of arguments first
    // requires 2 extra arguments on the command line
    if(argc != 3) { // if argc is not 3, the user typed the wrong number of arguments on the CL
        cerr << "Usage: " << argv[0] << "<int> <int>" << endl;// cerr prints an error message
        // prints out the name of the program in argv[0]
        return 1; // if the program has an error, you want to terminate it with a 1 or -1
    }

    // next, take each command line arguments and transform them into integers one by one
    // input the string into the iss and change into int
    iss.str(argv[1]); // calling the str method and giving it the string in argv[1]
    // iss >> n; // reading the iss object; you can use cin or iss (since it is an input) and puts result in int n (conversion occurs here) **
    // ** problem: what if the user does not type an integer, the conversion will fail; put inside an if test that will return a boolean value

    if(!(iss >> n)) { // attempt to do the conversion; if failed the function will be true and print an error messgae and terminate, if passed, the function will be false and will be ignored
        cerr << "Error: first command line argunent must be an integer" << endl;
        return 1;
    }
    // must clear the iss object in between uses as it was used to convert the first argument otherwise the previous inputs may carry over; or make multiple, seperate iss objects and use one for each
    iss.clear();
    
    // second argument conversion
    iss.str(argv[2]);

    if(!(iss >> m)) {
        cerr << "Error: second command line argument must be an integer" << endl;
        return 1;
    }

    cout << "n is: " << n << endl;
    cout << "m is: " << m << endl;

    // compute the max of two
    cout << "max (" << n << ", " << m << ") is " << max(n, m) << endl;

    return 0; // program terminates successfully
}