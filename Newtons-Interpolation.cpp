/*
* Myo Aung CS-3010-Numerical Methods and Computing
* Assignment4- Newton's Interpolation Polynomial Algorithm
* 
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

void Coeff(vector<float>& xs, vector<float>& ys, vector<float>& cs) {
    int n = xs.size() - 1;
    for (int i = 0; i <= n; i++) {
        cs[i] = ys[i];
    }
    for (int j = 1; j <= n; j++) {
        for (int i = n; i >= j; i--) {
            cs[i] = (cs[i] - cs[i-1]) / (xs[i] - xs[i-j]);
        }
    }
}

float EvalNewton(vector<float>& xs, vector<float>& cs, float z) {
    float result = cs[xs.size() - 1];
    int n = xs.size() - 1;
    for (int i = n-1; i >= 0; i--) {
        result = result * (z - xs[i]) + cs[i];
    }
    return result;
}

int main() {
    // Test the implementation
    float eval_value;
    int choice, points;
    char q;
    cout << "1) For Defined Data Set." << endl;
    cout << "2) For Random Data Set." << endl;
    cin >> choice;
    if(choice == 1) {
        vector<float> xs {3, 1, 0, 4, 7};
        vector<float> ys {1, 0.12, -0.3, 2, 2.5};
        //vector<float> xs {0, 0.5, 1, 1.5};
        //vector<float> ys {1, 1.3, 1.7, 2.1};
        vector<float> cs(2);
        Coeff(xs, ys, cs);
        while (true) { 
        cout << "Enter the value to evaluate the polynomial: ";
        cin >> eval_value;
        
        cout << "f(" << eval_value << ") = " << EvalNewton(xs, cs, eval_value) << endl;
   
    }
    } else if (choice == 2) {
        cout << "Enter number of points: ";
        cin >> points;
        
       // Create a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        
        // Create a distribution to generate floats between 1 and 10
        std::uniform_real_distribution<float> dist(1.0f, 10.0f);
        
        // Create two vectors to store the random numbers
        vector<float> xcoeff(10);
        vector<float> ycoeff(10);
        vector<float> cs(10);
        // Fill the vectors with random numbers
        for (int i = 0; i < 10; i++) {
            xcoeff[i] = dist(gen);
            ycoeff[i] = dist(gen);
        }
        
        // Print the vectors
        cout << "X-Coefficient:";
        for (auto elem : xcoeff) {
            cout << " " << elem;
        }
        cout << endl;
        
        cout << "Y-Coefficient:";
        for (auto elem : ycoeff) {
            cout << " " << elem;
    }
    cout << endl;
        auto start = chrono::high_resolution_clock::now();
        Coeff(xcoeff, ycoeff, cs);
        cout << "Enter the value to evaluate the polynomial: ";
        cin >> eval_value;
        
        cout << "f(" << eval_value << ") = " << EvalNewton(xcoeff, cs, eval_value) << endl;
        auto end = chrono::high_resolution_clock::now();
        auto time_taken = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time Taken: " << time_taken.count() << "-Microseconds" << endl << endl;
    } else {
        cout << "Enter 1 or 2." << endl;
    }
    
    return 0;
}