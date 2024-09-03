
#include <iostream>
#include "clsString.h"

int main()
{
    clsString string1;
    string1.SetValue("hesham ELSAYED");
    cout<<clsString::ToUpper("hesham")<<endl;
    cout << string1.Value() << endl;
    cout << string1.CountCapitalLetters() << endl;
    string1.ReverseString();
    cout << string1.Value()<<endl;
    
    

}
