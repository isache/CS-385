/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Isabel Chen
 * Date        : September 20, 2023
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);
    
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve(); 
    static int num_digits(int num);

    int count_primes() const;
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

int PrimesSieve::count_primes() const {
    int counter = 0;
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i] == true) {
            counter++;
        }
    }
    return counter;
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    cout << endl << "Number of primes found: " << count_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    int counter = 0;
    for (int i = 2; i <= limit_; i++) {

        if (is_prime_[i]) {
            if(counter > 0) {
                cout << " ";
            }

            if(num_primes() > primes_per_row) {
                cout << setw(max_prime_width) << i;
            } else {
                cout << i;
            }

            if (primes_per_row == ++counter) {
                cout << endl;
                counter = 0;
            }
        }
    }
}

void PrimesSieve::sieve() { 
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.

    for (int i = 2; i <= limit_; i++) {
        is_prime_[i] = true;
    }

    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i] == true) {
            for (int j = i * i; j <= limit_ + 1; j += i) {
                is_prime_[j] = false;
            }
        }
    }
    for (int i = 2; i <= limit_ + 1; i++) {
        if (is_prime_[i] == true) {
            max_prime_ = i;
        }
    }
    num_primes_ = count_primes();

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.

    int digits;
    while(num/10 > 0) { 
        num /= 10;
        digits ++;
    }
    return digits + 1;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve s = PrimesSieve(limit);
    s.display_primes();

    return 0;
}