#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <forward_list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <memory>
#include <random>
#include <ctime>
#include <cctype>
#include <conio.h>
#include <windows.h>
#include "D:\FMT\include\fmt\format.h"
#include "D:\FMT\include\fmt\ranges.h"
#include "D:\FMT\include\fmt\os.h"
// #include<D:/QinJunyou/C/Eigen3/Eigen/LU>

// #include "HEAD.H"
// #include<D:/QinJunyou/C/Eigen3/Eigen/Eigen>
// using namespace Eigen;


using namespace std;
int main(int argc, char *argv[])
{
/*
    fmt::print("hello,world!\n");
    std::string s = fmt::format("The answer is {}.", 42);
    std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
    fmt::print(s);
    std::vector<int> v{1, 2, 3};
    fmt::print("{}\n", v);
    auto out = fmt::output_file("guide.txt");
    out.print("Don't {}", "Panic");
*/
    // manip();
// float x,y,k0,k1,k2,k3,k4,dx,dy;

// default_random_engine e(time(0));
// normal_distribution<float> w(0,0.005), p(0,0.02);
/* vector<int> vec;
for(int i = 0; i <10; ++i)
    vec.push_back(i);
for(int i = -10; i <5; ++i)
    vec.push_back(i);

    fmt::print("{} ", *max_element(vec.begin(),vec.end()));
 */


/*
    -2.312,0.5027
    2.061,-1.257
    -0.8545,-2.915
    -3.519,-1.156
    2.815,-2.815
 */

    float x[5] = {-2.312, 2.061, -0.8545, -3.519, 2.815};
    float y[5] = {0.5027, -1.257, -2.915, -1.156, -2.815};
    float A[5][5];
    float B[5];
    //A,B
    for(int i = 0; i <5;++i)
    {
        A[i][0] = x[i] * y[i];
        A[i][1] = y[i] * y[i];
        A[i][2] = x[i];
        A[i][3] = y[i];
        A[i][4] = 1;
        B[i] = - x[i] * x[i];
    }
    fmt::print("{}\n", "A = ");
    for(int i = 0; i<5; ++i)
    {
        for(int j = 0; j<5; ++j)
            fmt::print("{: f} ", A[i][j]);
        fmt::print("\n");
    }
    fmt::print("\n");
    fmt::print("{}\n", "B = ");
    for(int i = 0; i<5; ++i)
        fmt::print("{: f} ", B[i]);
    fmt::print("\n\n");
    //求LU
    for(int i = 0; i <5; ++i)
    {
        for(int j = i; j <5; ++j)
        {
            float sum = 0.0;
            for(int k = 0; k < i; ++k)
            {
                sum += A[i][k] * A[k][j];
            }
            A[i][j] = A[i][j] - sum;
            sum = 0.0;
            if(j > i)
            {
                for(int k = 0; k < i; ++k)
                {
                    sum += A[j][k] * A[k][i];
                }
                A[j][i] = (A[j][i] - sum) / A[i][i];
            }
        }
    }
    //输出LU
    fmt::print("{}\n", "L = ");
    for(int i = 0; i<5; ++i)
    {
        for(int j = 0; j<5; ++j)
        {
            if( j == i)
                fmt::print("{: f} ", 1.0);
            if( j > i)
                fmt::print("{: f} ", 0.0);
            if( j < i)
                fmt::print("{: f} ", A[i][j]);
        }
        fmt::print("\n");
    }
    fmt::print("\n");
    fmt::print("{}\n", "U = ");
    for(int i = 0; i<5; ++i)
    {
        for(int j = 0; j<5; ++j)
        {
            if( j >= i)
                fmt::print("{: f} ", A[i][j]);
            if( j < i)
                fmt::print("{: f} ", 0.0);
        }
        fmt::print("\n");
    }
    fmt::print("\n");
    //LY = b
    float Y[5];
    for(int i = 0; i<5; ++i)
    {
        float sum = 0.0;
        for(int j = 0; j<i; ++j)
            sum += A[i][j] * Y[j];
        Y[i] = B[i] - sum;
    }
    //UX = Y
    float X[5];
    for(int i = 4; i>-1; --i)
    {
        float sum = 0.0;
        for(int j = 4; j>i; --j)
            sum += A[i][j] * X[j];
        X[i] = (Y[i] - sum) / A[i][i];
    }
    fmt::print("{}\n", "Result = ");
    for(int i = 0; i<5; ++i)
        fmt::print("{: f} ", X[i]);
    fmt::print("\n\n");





    // fmt::print("{}\n", 1);


    system("pause");
    return 0;
}

