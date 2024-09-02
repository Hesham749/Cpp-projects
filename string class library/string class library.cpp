
#include <iostream>
#include "clsString.h"

int main()
{
    clsString string1;
    string1.SetValue("hesham");
    cout<<clsString::ToUpper("hesham")<<endl;
    cout << string1.Value() << endl;
    string1.ToUpper();
    cout << string1.Value() << endl;
    cout<<clsString::LetterCount("hesham",'h')<<endl;
    cout<<string1.LetterCount('e')<<endl;


    cout<<string1.CountVowel()<<endl;
    cout<<clsString::CountVowel("hesham  elsayed ahmed")<<endl;

}
