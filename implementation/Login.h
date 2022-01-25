#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

#include "Register.h"

using namespace std;

//making the class that will help in the login of the user
class Login
{
private:
    string usrName;
    string password;

    bool loginStatus;

    attributeUniverse attributes;

public:
    Login()
    {
        usrName = "";
        password = "";
        loginStatus = 0;
        attributes = {};
    }

    bool getLogin() const
    {
        return loginStatus;
    }

    string getUsr() const
    {
        return usrName;
    }

    void setLogin(string u, bool status)
    {
        usrName = u;
        loginStatus = status;
    }

    void setAttributes(attributeUniverse a)
    {
        attributes = a;
    }

    attributeUniverse getAttributes() const
    {
        return attributes;
    }


    bool checkPassword(string userNametocheck, string enteredPass)
    {

        string registeredPass;
        string previous; //to maintain the previous if previous is $ then check username for next as in rythm

        //will read the file to see
        fstream toRead;

        //opening file in writing mode and append so not to delte the previous stuff
        toRead.open("registered.txt", ios::in);

        //firstly setting it $
        previous = "$";

        while (!toRead.eof())
        {

            getline(toRead, registeredPass);

            if (previous == userNametocheck)
            {
                //if find any that like user then see that passward
                if (enteredPass == registeredPass)
                {
                    return 1;
                }
            }

            //saving in previous
            previous = registeredPass;
        }

        toRead.close();

        return 0; //not found
    }

    //checking whether in data or not
    bool loginSuccessfull(string usr, string pass)
    {
        //to see which was wrong  --- initallay not found
        bool userF = 0;
        bool passF = 0;

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

                //if find any that like user then see that passward
                if (usr == registeredUser)
                {
                    userF = 1; //user name was correct

                    //checking the password for that user
                    if (checkPassword(registeredUser, pass))
                    {
                        passF = 1; //password found
                        return 1;  //the password also matched
                    }
                }
            }

            //saving in previous
            previous = registeredUser;
        }

        toRead.close();

        if (userF == 0)
        {
            cout << "\n\t\t    :::::::: User name was wrong :::::::::" << endl;
        }

        if (passF == 0)
        {
            cout << "\n\t\t    :::::::: Password was wrong :::::::::" << endl;
        }

        return 0; //not found
    }

    void loggingIn()
    {
        char pass[32]; //temprary store of password
        char ch;       //input taking
        int size = 0;  //size of password
        int i = 0;     //will use for indexing

        string uN, p;

        cout << "\n\n\t\t\t Enter The credentials to Login " << endl
             << endl;

        cout << "\n\t\t User-Name : ";
        getline(cin, uN);

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
        p = pass;

        cout << endl;

        if (loginSuccessfull(uN, p))
        {
            //login was successfull , storing data in login class and will aslo make it to behave like a session --
            //having track of the user
            usrName = uN;
            password = p;
            loginStatus = 1;

            cout << "\n\t\t\t ::::::: Logged In ::::::::" << endl;
            Sleep(2000);
            system("cls");
        }
        else
        {
            cout << "\n\t\t ::::::::: Not Logged in --- try again ::::::::: " << endl;
            Sleep(2000);
        }
    }

 
    //will log out
    void logingOut()
    {
        usrName = "";
        password = "";
        loginStatus = 0;

        attributes = {};
    }
};
