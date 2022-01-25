#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

//will create a hypothetical cloud service
class StorageServices
{

private:
    string assignmentId;
    string assignmentName;
    string cipherTextpolicy;
    string producer;
    attributeUniverse attributesForfiles;

public:
    StorageServices()
    {
        assignmentId = "";
        assignmentName = "";
        cipherTextpolicy = "";
    }

    //write in storage a hypothetical storage --- folder made
    void moveinStorage()
    {

        fstream write;

        write.open("cloudStore.txt", ios::out | ios::app);
        write << assignmentId << endl;
        write << assignmentName << endl;
        write << cipherTextpolicy << endl;
        write << producer << endl;
        write << "?" << endl;
        write << attributesForfiles.CGPA << endl;
        write << attributesForfiles.semesterNo << endl;
        write << attributesForfiles.batchNo << endl;
        write << attributesForfiles.section << endl;
        write << attributesForfiles.age << endl;
        write << attributesForfiles.gender << endl;
        write << attributesForfiles.department << endl;
        write << attributesForfiles.favSubj << endl;
        write << attributesForfiles.inchargeTeacher << endl;
        write << "$";

        write.close();
    }

    //will show doucuments with their id
    void showStorage()
    {

        cout << "\n\t\t\t    Assignment ID "
             << "  :   "
             << "Assignment Name" << endl
             << endl;

        string id, name;
        string previous;
        fstream read;

        read.open("cloudStore.txt", ios::in | ios::app);

        while (!read.eof())
        {

            getline(read, id);

            if (previous == "$")
            {

                cout << "\t\t\t" << setw(15) << id << "     :   ";

                getline(read, name);

                cout << name << endl;

                //skip ciphertextpolicy
                getline(read, id);
            }

            //saving in previous
            previous = id;
        }

        read.close();
    }

    //and will aslo set the data
    string findcipherPolicyof(string idE)
    {
        string id, name, policy;
        string previous;
        fstream read;

        read.open("cloudStore.txt", ios::in | ios::app);

        while (!read.eof())
        {

            getline(read, id);

            if (previous == "$")
            {
                if (id == idE) //found
                {
                    assignmentId = idE;

                    getline(read, name);

                    assignmentName = name;

                    getline(read, policy);
                    cipherTextpolicy = policy;

                    return policy;
                }
            }

            //saving in previous
            previous = id;
        }

        read.close();

        return "NULL";
    }

    //set data by asking from the user
    void setThings(string i, string n, attributeUniverse c, string ci, string p)
    {
        assignmentId = i;
        assignmentName = n;
        attributesForfiles = c;
        producer = p;
        cipherTextpolicy = ci;
    }

    void setAttribute(attributeUniverse a)
    {
        attributesForfiles = a;
    }

    bool idMatch(string i)
    {
        string registeredPass;
        string previous; //to maintain the previous if previous is $ then check username for next as in rythm

        //will read the file to see
        fstream toRead;

        //opening file in writing mode and append so not to delte the previous stuff
        toRead.open("cloudStore.txt", ios::in);

        //firstly setting it $
        previous = "$";

        while (!toRead.eof())
        {

            getline(toRead, registeredPass);

            if (previous == "$")
            {
                //if find any that like user then see that passward
                if (i == registeredPass)
                {
                    return 1;
                }
            }

            //saving in previous
            previous = registeredPass;
        }

        toRead.close();

        return 0; //not matched
    }

    string filenameFinder(string id)
    {
        string registeredPass;
        string previous; //to maintain the previous if previous is $ then check username for next as in rythm

        //will read the file to see
        fstream toRead;

        //opening file in writing mode and append so not to delte the previous stuff
        toRead.open("cloudStore.txt", ios::in);

        //firstly setting it $
        previous = "$";

        while (!toRead.eof())
        {

            getline(toRead, registeredPass);

            if (previous == "$")
            {
                //if find any that like user then next one is the file name
                if (id == registeredPass)
                {
                    getline(toRead, registeredPass);
                    return registeredPass;
                }
            }

            //saving in previous
            previous = registeredPass;
        }

        toRead.close();

        return NULL; //not matched
    }

    void readAttributes(string id, attributeUniverse &attributeofrequestedfile)
    {
        string registeredPass;
        string previous; //to maintain the previous if previous is $ then check username for next as in rythm

        //will read the file to see
        string file = "cloudStore.txt";

        AttributeAuthority fetchAttribute;

        fetchAttribute.readAttributes(attributeofrequestedfile, id, file);
    }

    //will check current user is owner of that assignment or note
    bool owner(string id, Login user)
    {
        string registeredPass;
        string previous; //to maintain the previous if previous is $ then check username for next as in rythm

        //will read the file to see
        fstream toRead;

        //opening file in writing mode and append so not to delte the previous stuff
        toRead.open("cloudStore.txt", ios::in);

        //firstly setting it $
        previous = "$";

        while (!toRead.eof())
        {

            getline(toRead, registeredPass);

            if (previous == "$")
            {
                //if find any that like assignment
                if (id == registeredPass)
                {
                    getline(toRead, registeredPass); //will take the name
                    getline(toRead, registeredPass); //takes cipherpolicy
                    getline(toRead, registeredPass); //takes producer

                    if (registeredPass == user.getUsr())
                    {
                        return 1; //owner
                    }

                    return 0; //not the owner don't loook whole file
                }
            }

            //saving in previous
            previous = registeredPass;
        }

        toRead.close();

        return 0; //not the owner
    }

    void overrideInmemory(string id, attributeUniverse changeAttribute, string newCipher, Login u)
    {
        // fstream superTemp;
        // superTemp.open("cloudStore.txt", ios::out | ios::app);
        // superTemp << endl;
        // superTemp.close();

        //saving file name
        assignmentName = filenameFinder(id);
        string registeredPass;
        string previous; //to maintain the previous if previous is $ then check username for next as in rythm

        //will read the file to see
        fstream toRead, temp;

        //opening file in writing mode and append so not to delte the previous stuff
        toRead.open("cloudStore.txt", ios::in);

        //copying file not like the cloudstore one
        temp.open("temp.txt", ios::out);

        //firstly setting it $
        previous = "$";

        while (!toRead.eof())
        {

            getline(toRead, registeredPass);

            if (previous == "$")
            {

                //if find any that like user then next one is the file name
                if (id == registeredPass)
                {

                    getline(toRead, registeredPass); //the name
                    getline(toRead, registeredPass); //the policy
                    getline(toRead, registeredPass); //the producer
                    getline(toRead, registeredPass); //the ?
                    //9 attributes
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass);
                    getline(toRead, registeredPass); //the $
                }
                else
                {

                    temp << registeredPass << endl;
                }
            }
            else
            {
                temp << registeredPass << endl;
            }

            //saving in previous
            previous = registeredPass;
        }

        temp.close();
        toRead.close();

        //renaming temp --- without the early data -- and deleteing the cloud storage
        // remove the original file
        remove("cloudStore.txt");

        // rename the file
        rename("temp.txt", "cloudStore.txt");

        //now writing in memory again at bottom
        cipherTextpolicy = newCipher;
        attributesForfiles = changeAttribute;
        assignmentId = id;
        producer = u.getUsr();

        moveinStorage();
    }
};
