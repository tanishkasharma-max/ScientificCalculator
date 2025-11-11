#include<iostream>
#include "calculator.hpp"   

using namespace std;



int main()
{
    cout<<"Addition: "<<Calculator().add(5,3)<<endl;
    cout<<"Subtraction: "<<Calculator().subtract(5,3)<<endl;
    cout<<"Multiplication: "<<Calculator().multiply(5,3)<<endl;
    cout<<"Division: "<<Calculator().divide(5,3)<<endl;         

    cout<<"Sine of 30 degrees: "<<Calculator().sin_deg(30)<<endl;
    cout<<"Cosine of 60 degrees: "<<Calculator().cos_deg(60)<<endl;
    cout<<"Tangent of 45 degrees: "<<Calculator().tan_deg(45)<<endl;

    return 0;
}