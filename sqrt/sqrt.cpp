/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Isabel Chen
 * Version : 1.0
 * Date    : September 14, 2023
 * Description: Computes the square root of a double using Newton's method.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <limits> // limits header
#include <iomanip> // input/output manipulation
#include <sstream>
using namespace std;

double sqrt(double num, double epsilon) {
    double lastGuess = num;
    double nextGuess = (lastGuess + num / lastGuess) / 2;

    if(num < 0) {
        return numeric_limits<double>::quiet_NaN();
    } 
    if (num == 0 || num == 1) {
        return num;
    }
    else {
        while(abs((lastGuess - nextGuess) >= epsilon)) {
            lastGuess = nextGuess;
            nextGuess = (lastGuess + num / lastGuess) / 2;
            }
            return nextGuess;
    }

}

int main(int argc, char* argv[]) {
    istringstream iss;
    double x, y = 1e-7;
    
    if(argc != 2) { 
        if(argc == 3) {
            iss.str(argv[2]);
            if(!(iss >> y) || y <= 0) { 
                cerr << "Error: Epsilon argument must be a positive double." << endl;
                return 1;
            }
        }
        else {
            cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
            return 1;
        }
    }
    iss.clear();

    iss.str(argv[1]);
    if(!(iss >> x)) { 
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }

    // fixed notation output
    cout << fixed << setprecision(8) << sqrt(x, y) << endl;
    return 0;
}
