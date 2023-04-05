#include <stdio.h>

#include<iostream>

#include <list>

#include <string>

#include <sstream>

#include <cmath>

#include <vector>

std::vector < std::string > Email_Adresses;

//Intiger start with 1 = vowel, start with 2 = consonants, start with 3 = digits
std::vector < int > Spam_Traits;

//Averages
////////////////////////////////////////////////////////////////
float SpamVowelAverage = 0, SpamConsonantsAverage = 0, SpamDigitsAverage = 0;
float NonSpamVowelAverage = 0, NonSpamConsonantsAverage = 0, NonSpamDigitsAverage = 0;
////////////////////////////////////////////////////////////


//Convert data into spam traits
///////////////////////////////////////////////////////////
int ConvertData(int Type, int Amount) {
    std::string AmountLength = std::to_string(Amount);
    int AddAmount = std::pow(10, AmountLength.length()) * Type;
    return (AddAmount + Amount);
}
///////////////////////////////////////////////////////////////


//Get first digit of an intiger
/////////////////////////////////////////////////////////////////////

int firstDigit(int n)
{
    // Find total number of digits - 1
    int digits = (int)log10(n);

    // Find first digit
    n = (int)(n / pow(10, digits));

    // Return first digit
    return n;
}


////////////////////////////////////////


//Unconvert data back into the traits amount
///////////////////////////////////////////////////////////
int UnconvertData(int Type, int Amount) {
    std::string AmountLength = std::to_string(Amount);
    int SubtractAmount = (int)(std::pow(10, (AmountLength.length() - 1)) * (float)Type);
    return (int)((float)Amount - (float)SubtractAmount);
}
///////////////////////////////////////////////////////////////



//Detect amount of Vowels, Constonants, and Digits
///////////////////////////////////////////////////////////////////////////////////
void CountTraits(std::string line) 
{
    std::cout << "Email Length" << std::endl;
    std::cout << line.length() << std::endl;

    int vowels = 0, consonants = 0, digits = 0, spaces = 0;

    for (int i = 0; i < line.length(); i++) 
    {   
        digits++;
        if (line[i] == 'a' || line[i] == 'e' || line[i] == 'i' ||
            line[i] == 'o' || line[i] == 'u' || line[i] == 'A' ||
            line[i] == 'E' || line[i] == 'I' || line[i] == 'O' ||
            line[i] == 'U') {
            vowels++;
        }
        else if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))
        {
            consonants++;
        }

    }

    Spam_Traits.push_back(ConvertData(1, vowels));
    Spam_Traits.push_back(ConvertData(2, consonants));
    Spam_Traits.push_back(ConvertData(3, digits));

}
///////////////////////////////////////////////////////////////////////////////////


//Use Functions Above And Get Averages
////////////////////////////////////////////////////////////////////////

int DecodeAndCalculate(int trait)
{

    float TotalVowels = 0;
    float TotalConsonants = 0;
    float TotalDigits = 0;

    for (int i = 0; i < Email_Adresses.size(); i++) {
        CountTraits(Email_Adresses[i]);
    }
    for (int i = 0; i < Spam_Traits.size(); i++) {

        //Get the first digit of an intiger in the traits vector(first digit determines type of data)
        int first_digit = firstDigit(Spam_Traits[i]);
        /////////////////////////////////////////////////
       //If data is for vowels
        if (first_digit == 1) {
            //Vowels
            TotalVowels += UnconvertData(1, Spam_Traits[i]);

        }
        if (first_digit == 2) {
            //Vowels
            TotalConsonants += UnconvertData(2, Spam_Traits[i]);

        }
        if (first_digit == 3) 
        {
            //Digits
            TotalDigits += UnconvertData(3, Spam_Traits[i]);

        }



    }

    if (trait == 1)
    {
        //Get Vowel Average
        return ((float)TotalVowels / (float)Email_Adresses.size());
    }
    if (trait == 2) {
        return ((float)TotalConsonants / (float)Email_Adresses.size());
    }
    if (trait == 3) {
        return ((float)TotalDigits / (float)Email_Adresses.size());
    }

    return 1;
}
////////////////////////////////////


//Calculate if inputed email is spam
/////////////////////////////////////////////////////////////////////////////

bool CalculateIfSpam(std::string)
{
    float EmailCheckVowelAverage = 0;
    float EmailCheckConsonantsAverage = 0;
    float EmailCheckDigitsAverage = 0;

    EmailCheckVowelAverage = DecodeAndCalculate(1);
    EmailCheckConsonantsAverage = DecodeAndCalculate(2);
    EmailCheckDigitsAverage = DecodeAndCalculate(3);

    int AmountTrueSpam = 0;
    int AmountNotSpam = 0;

    //Check to make sure there is a distinct difference between the traits
    if ((SpamVowelAverage / NonSpamVowelAverage) > 1.5 || (SpamVowelAverage / NonSpamVowelAverage) < 0.666f)
    {

        if (std::abs(EmailCheckVowelAverage - SpamVowelAverage) > std::abs(EmailCheckVowelAverage - NonSpamVowelAverage))
        {
            AmountNotSpam++;
        }
        else
        {
            AmountTrueSpam++;
        }
    }
  

    //Check to make sure there is a distinct difference between the traits
    if ((SpamConsonantsAverage / NonSpamConsonantsAverage) > 1.5 || (SpamConsonantsAverage / NonSpamConsonantsAverage) < 0.666f)
    {
        if (std::abs(EmailCheckConsonantsAverage - SpamConsonantsAverage) > std::abs(EmailCheckConsonantsAverage - NonSpamConsonantsAverage))
        {
            AmountNotSpam++;
        }
        else
        {
            AmountTrueSpam++;
        }

    }
  

    //Check to make sure there is a distinct difference between the traits
    if ((SpamDigitsAverage / NonSpamDigitsAverage) > 1.5 || (SpamDigitsAverage / NonSpamDigitsAverage) < 0.666f)
    {
        if (std::abs(EmailCheckDigitsAverage - SpamDigitsAverage) > std::abs(EmailCheckDigitsAverage - NonSpamDigitsAverage))
        {
            AmountNotSpam++;
        }
        else
        {
            AmountTrueSpam++;
        }
    }

    
    
    if (AmountTrueSpam > AmountNotSpam)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
  

   
    return false;
}





//////////////////////////////////////////////////////////////////////////////


int main()
{
    //For Spam Email Calculations
    //////////////////////////////////////////
    //Add the spam email datas
    Email_Adresses.push_back("CVS <email_1fs7fhQ4tokj@ishbgouqenf.loveofglove.com>");
    Email_Adresses.push_back("CVS <info_1fs7fhQF5Wm@msfrlfliszm.grossclassic.com>");
    //Example spam email for checks: T-Mobile <email_1fs7fhQ1E3io@fevdyuftbmd.venicefloridaproperty.com>
    SpamVowelAverage = DecodeAndCalculate(1);
    SpamConsonantsAverage = DecodeAndCalculate(2);
    SpamDigitsAverage = DecodeAndCalculate(3);
    /////////////////////////////////////////////

    //Add Real Email Adress
    ///////////////////////////////////////////////////////// 
    Email_Adresses.clear();
    Spam_Traits.clear();
    Email_Adresses.push_back("info@unity3d.com");
    Email_Adresses.push_back("store-news@amazon.com");
    Email_Adresses.push_back("SoFi@daily.sofi.com");
    Email_Adresses.push_back("inpeckable891@gmail.com");
    NonSpamVowelAverage = DecodeAndCalculate(1);
    NonSpamConsonantsAverage = DecodeAndCalculate(2);
    NonSpamDigitsAverage = DecodeAndCalculate(3);

    //Get User Input
    Spam_Traits.clear();
    std::string Email_To_Check;
    std::cout << "Enter Email To Check: ";
    std::getline(std::cin, Email_To_Check);
    Email_Adresses.clear();
    Email_Adresses.push_back(Email_To_Check);

    if (CalculateIfSpam(Email_To_Check) == 0) 
    {
        std::cout << "Not Spam Email Adress";
    }
    else
    {
        std::cout << "This Is A Spam Email Adress";
    }

}






