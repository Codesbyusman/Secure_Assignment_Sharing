#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>


#include "AttributeAuthority.h"

using namespace std;

//making the class that will help in the registration of the user
class Register
{

private:
    string name;
    string userName; //will be unique -- so can be used for identification
    string password;

    attributeUniverse myAttributes; //will contain arrtibutes

public:
    Register()
    {
        userName = "";
        password = "";
        name = "";

        myAttributes = {};
    }

    //making the setters and getters
    string getName() const
    {
        return name;
    }

    string getUsername() const
    {
        return userName;
    }

    string getPass() const
    {
        return password;
    }
    
    attributeUniverse getAttribute() const
    {
        return myAttributes;
    }

    bool uniqueUsername(string tempUser)
    {
        string registeredUser;
        string previous; //to maintain the previous if previous is $ then check username for next as in rythm

        //will read the file to see
        fstream toRead;

        //opening file in writing mode and append so not to delte the previous stuff
        toRead.open("registered.txt", ios::in);

        //firstly setting it $
        previous = "$";

        while (!toRead.eof())
        {

            getline(toRead, registeredUser);

            if (previous == "$")
            {
                //if find any that like user name then will return 0
                if (tempUser == registeredUser)
                {
                    return 0;
                }
            }

            //saving in previous
            previous = registeredUser;
        }

        toRead.close();

        return 1;
    }

    //taking the data
    void takeCredentials()
    {
        int a = 0;

        string input = "";

        //to store the password
        char pass[32];
        int i = 0;

        //to check the size of pass
        int size = 0;

        //temp storag of the character
        char ch;

        cout << "\n\t\t Enter Name : ";
        getline(cin, input);

        name = input;

        a = 0;

        do
        {
            if (a == 0)
            {
                //taking the user name
                cout << "\t\t Enter user-name : ";
                getline(cin, input);
            }
            else
            {

                if (name == input)
                {
                    cout << "\n\t\t      ::::: Name and User Name must be different ::::" << endl
                         << endl;
                }
                else
                {
                    cout << "\n\t\t      ::: Try anyother already registered by this :::" << endl
                         << endl;
                }

                //taking the user name
                cout
                    << "\t\t Enter user-name again : ";
                getline(cin, input);
            }

            a++;

        } while (!((uniqueUsername(input)) && (input != name))); //will take again and again to have the unique user name

        userName = input;

        cout << "\t\t Enter password :  ";

        //making infinite loop will break when enter is pressed
        while (1)
        {

            //taking the character without displaying
            ch = _getch();

            //if backspace is entered then remove the display //bonus
            if (ch == 8 && i > 0)
            {

                //remove the space and the character
                cout << "\b\b ";

                //remove the character
                pass[i] = ' ';

                //moving back to override next time on the space
                i--;
            }

            //if enter character or return carriage '\r' is entered break with adding null character
            if (ch == 13)
            {
                pass[i] = '\0';
                //assiginging the size
                size = i;
                i++;
                break;
            }

            //if the characters are special characters numbers or characters then save other wise no input for arrow like that
            if (ch >= 32 && ch <= 126)
            {
                //assiging the password characters
                pass[i] = ch;

                //in display remove and print *
                cout << "\b* ";
                i++;
            }
        }

        //storing in class
        password = pass;
    }

    //taking the attributes
    void setYourAttributes()
    {
        cout << "\n\n\t Note : If you don't want to enter any attribute enter NULL " << endl;
        cout << "\t But remember incomplete file will let you to face problems in accessing the material :) " << endl
             << endl;

        AttributeAuthority attributesManagement;

        attributesManagement.setAttributes(myAttributes);
    }

    //will save data in a text file
    void saveData(fstream &writeInfile)
    {
        //opening file in writing mode and append so not to delte the previous stuff
        writeInfile.open("registered.txt", ios::out | ios::app);

        //writing the data and will store in a rythm
        writeInfile << userName << endl;
        writeInfile << password << endl;
        writeInfile << name << endl;
        writeInfile << "?" << endl; //starting of attributes
        writeInfile << myAttributes.CGPA << endl;
        writeInfile << myAttributes.semesterNo << endl;
        writeInfile << myAttributes.batchNo << endl;
        writeInfile << myAttributes.section << endl;
        writeInfile << myAttributes.age << endl;
        writeInfile << myAttributes.gender << endl;
        writeInfile << myAttributes.department << endl;
        writeInfile << myAttributes.favSubj << endl;
        writeInfile << myAttributes.inchargeTeacher << endl;
        writeInfile << "$" << endl; //one data end

        //closing the file
        writeInfile.close();
    }
};