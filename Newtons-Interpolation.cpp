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

void Coeff(vector<float> &xs, vector<float> &ys, vector<float> &cs)
{
    int n = xs.size() - 1;
    for (int i = 0; i <= n; i++)
    {
        cs[i] = ys[i];
    }
    for (int j = 1; j <= n; j++)
    {
        for (int i = n; i >= j; i--)
        {
            cs[i] = (cs[i] - cs[i - 1]) / (xs[i] - xs[i - j]);
        }
    }
}

float EvalNewton(vector<float> &xs, vector<float> &cs, float z)
{
    float result = cs[xs.size() - 1];
    int n = xs.size() - 1;
    for (int i = n - 1; i >= 0; i--)
    {
        result = result * (z - xs[i]) + cs[i];
    }
    return result;
}

int main()
{
    float eval_value, input;
    int choice, points;
    char q;
    cout << "1) For Defined Data Set." << endl;
    cout << "2) For Random Data Set." << endl;
    cin >> choice;
    if (choice == 1)
    {
        vector<float> xs{3, 1, 0, 4, 7};         // Exercise 1 & 2
        vector<float> ys{1, 0.12, -0.3, 2, 2.5}; // Exercise 1 & 2
        // vector<float> xs {0, 0.5, 1, 1.5};
        // vector<float> ys {1, 1.3, 1.7, 2.1};
        auto start = chrono::high_resolution_clock::now();
        vector<float> cs(2);
        Coeff(xs, ys, cs);
        while (true)
        {
            char quit;
            cout << "Enter the value to evaluate the polynomial: ";
            cin >> eval_value;
            cout << "f(" << eval_value << ") = " << EvalNewton(xs, cs, eval_value) << endl;
            auto end = chrono::high_resolution_clock::now();
            auto time_taken = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Time Taken: " << time_taken.count() << "-Milliseconds" << endl;
            cout << "Continue Yes(y)/Quit(q) : ";
            cin >> quit;
            if (quit == 'q')
            {
                break;
            }
            else if (quit == 'y')
            {
                true;
            }
        }
    }
    else if (choice == 2)
    {
        cout << "Enter number of points: ";
        cin >> points;
        std::random_device rd; // Create a random number generator
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(1.0f, 4.0f); // Create a distribution to generate floats between 1 and 10
        vector<float> xcoeff(points);                           // Create two vectors to store the random numbers
        vector<float> ycoeff(points);
        vector<float> cs(points);

        for (int i = 0; i < points; i++)                        // Fill the vectors with random numbers
        {
            xcoeff[i] = dist(gen);
            ycoeff[i] = dist(gen);
        }
        cout << "X-Coefficient:";
        for (auto elem : xcoeff)
        {
            cout << " " << setprecision(23) << elem;
        }
        cout << endl;

        cout << "Y-Coefficient:";
        for (auto elem : ycoeff)
        {
            cout << " " << setprecision(23) << elem;
        }
        cout << endl;
        auto start = chrono::high_resolution_clock::now();
        Coeff(xcoeff, ycoeff, cs);
        cout << "Enter the value to evaluate the polynomial: ";
        cin >> eval_value;

        cout << "f(" << eval_value << ") = " << setprecision(23) << EvalNewton(xcoeff, cs, eval_value) << endl;
        auto end = chrono::high_resolution_clock::now();
        auto time_taken = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Time Taken: " << time_taken.count() << "-Milliseconds" << endl;
    }
    else
    {
        cout << "Enter 1 or 2." << endl;
    }

    return 0;
}