#include <iostream>
#include <stdio.h>
#include <string>
//#include "function.h"
using namespace std;

class Polynomial{
public:
    Polynomial();
    Polynomial(const int , const int [51]);
    Polynomial add( const Polynomial) const; // add function
    Polynomial subtract( const Polynomial ) const; // subtract function
    Polynomial multiplication( const Polynomial ) const; // multiplication function
    void output() const;
private:
    int coefficients[101]; // integer coefficients
    int greatestPower; // integer greatestPower
}; // end class Polynomial

Polynomial::Polynomial(){}

Polynomial::Polynomial(const int gp, const int coe[51]){
    this->greatestPower = gp;
    for(int i = gp ; i >= 0; i--)
        coefficients[i] = coe[i];
}

Polynomial Polynomial::add(const Polynomial b) const{
    Polynomial ans;

    if(greatestPower >= b.greatestPower){
        ans.greatestPower = greatestPower;
        for(int i = greatestPower; i >= 0; i--)
            if(i > b.greatestPower)
                ans.coefficients[i] = coefficients[i];
            else
                ans.coefficients[i] = coefficients[i] + b.coefficients[i];
    }
    else{
        ans.greatestPower = b.greatestPower;
        for(int i = b.greatestPower; i >= 0; i--)
            if(i > greatestPower)
                ans.coefficients[i] = b.coefficients[i];
            else
                ans.coefficients[i] = coefficients[i] + b.coefficients[i];
    }

    return ans;
}

Polynomial Polynomial::subtract(const Polynomial b) const{
    Polynomial ans;

    if(greatestPower >= b.greatestPower){
        ans.greatestPower = greatestPower;
        for(int i = greatestPower; i >= 0; i--)
            if(i > b.greatestPower)
                ans.coefficients[i] = coefficients[i];
            else
                ans.coefficients[i] = coefficients[i] - b.coefficients[i];
    }
    else{
        ans.greatestPower = b.greatestPower;
        for(int i = b.greatestPower; i >= 0; i--)
            if(i > greatestPower)
                ans.coefficients[i] = 0 - b.coefficients[i];
            else
                ans.coefficients[i] = coefficients[i] - b.coefficients[i];
    }

    return ans;
}

Polynomial Polynomial::multiplication(const Polynomial b) const{
    Polynomial ans;
    int tmp[110] = {0};

    ans.greatestPower = greatestPower + b.greatestPower;

    for(int i = 0; i <= greatestPower; i++){
        for(int j = 0; j <= b.greatestPower; j++){
            tmp[i+j] += coefficients[i] * b.coefficients[j];
        }
    }

    for(int i = 0; i <= ans.greatestPower; i++)
        ans.coefficients[i] = tmp[i];

    return ans;
}

void Polynomial::output() const{
    for(int i = greatestPower; i >= 0; i--)
        if(i != 0)
            printf("%d ", coefficients[i]);
        else
            printf("%d", coefficients[i]);
}

int main()
{
    int greatestPower1, greatestPower2;
    int coefficient1[51], coefficient2[51];
    Polynomial ans;

    cin>>greatestPower1;
    for(int i = greatestPower1 ; i >= 0; i--)
    {
        cin>>coefficient1[i];
    }
    cin>>greatestPower2;
    for(int i = greatestPower2 ; i >= 0 ; i--)
    {
        cin>>coefficient2[i];
    }

    Polynomial a(greatestPower1, coefficient1);
    //a.output();
    Polynomial b(greatestPower2, coefficient2);
    //b.output();

    ans = a.add( b );
    ans.output();
    cout << endl;

    ans = a.subtract( b );
    ans.output();
    cout << endl;

    ans = a.multiplication( b );
    ans.output();
    cout << endl;

} // end main

