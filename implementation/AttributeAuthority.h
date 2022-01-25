#include <iostream>
#include <string.h>
#include <string>

using namespace std;

struct attributeUniverse
{
    string CGPA;
    string semesterNo;
    string batchNo;
    string section;
    string age;
    string gender;
    string department;
    string favSubj;
    string inchargeTeacher;

    void takeAndsetAttributes(attributeUniverse& a)
    {
        string input;

        cout << "\t\t\t CGPA : ";
        getline(cin, input);

        a.CGPA = input;

        cout << "\t\t\t Semester No : ";
        getline(cin, input);

        a.semesterNo = input;

        cout << "\t\t\t Batch No : ";
        getline(cin, input);

        a.batchNo = input;

        cout << "\t\t\t Section : ";
        getline(cin, input);

        a.section = input;

        cout << "\t\t\t Age : ";
        getline(cin, input);

        a.age = input;

        cout << "\t\t\t Gender : ";
        getline(cin, input);

        a.gender = input;

        cout << "\t\t\t Department : ";
        getline(cin, input);

        a.department = input;

        cout << "\t\t\t Favourite Subject : ";
        getline(cin, input);

        a.favSubj = input;

        cout << "\t\t\t Class incharge : ";
        getline(cin, input);

        a.inchargeTeacher = input;
    }
};

class AttributeAuthority
{
    attributeUniverse allAttributes;

    public:
    void setAttributes(attributeUniverse& attributeStore)
    {
        attributeStore.takeAndsetAttributes(attributeStore);
    }

    
    //for reading attributes
    void readAttributes(attributeUniverse & readIn, string usr , string filename)
    {
        //read from the file and store in each attribute universe
        string registeredUser;
        string previous; //to maintain the previous if previous is $ then check username for next as in rythm

        //will read the file to see
        fstream toRead;

        //opening file in writing mode and append so not to delte the previous stuff
        toRead.open(filename, ios::in);

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
                    do
                    {
                        getline(toRead, registeredUser);

                    }while(!(registeredUser == "?")); //will move to the attribute data

                    //for 9 attributes
                    getline(toRead, registeredUser);
                    readIn.CGPA = registeredUser;

                     getline(toRead, registeredUser);
                    readIn.semesterNo = registeredUser;

                     getline(toRead, registeredUser);
                    readIn.batchNo = registeredUser;

                     getline(toRead, registeredUser);
                    readIn.section = registeredUser;

                     getline(toRead, registeredUser);
                    readIn.age = registeredUser;

                     getline(toRead, registeredUser);
                    readIn.gender = registeredUser;

                     getline(toRead, registeredUser);
                    readIn.department = registeredUser;

                     getline(toRead, registeredUser);
                    readIn.favSubj = registeredUser;


                     getline(toRead, registeredUser);
                    readIn.inchargeTeacher = registeredUser;

                    //data read --- now leave
                    break;
                }
            }

            //saving in previous
            previous = registeredUser;
        }

        toRead.close();


    }

};
