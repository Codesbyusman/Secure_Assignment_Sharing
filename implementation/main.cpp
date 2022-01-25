//including the stuff needed
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>

#include <cstdlib>
#include <fstream>
#include <time.h>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

#include "encryptionLibrary/encrypt.h"

#include "Login.h"
#include "StorageServices.h"

using namespace std;

class EncryptionDecryption_Service
{
private:
	string encryptedMsg;
	string decryptedMsg;

public:
	EncryptionDecryption_Service()
	{
		encryptedMsg = "";
		decryptedMsg = "";
	}

	//will encrypt whole file
	void encryptAssignment(string fileName, string attributeSpecified)
	{
		//whole assignment reading in one string
		string AssignmentData;
		string readLine;

		fstream toencrypt;

		//for reading
		toencrypt.open(fileName, ios::in);

		while (!toencrypt.eof())
		{
			getline(toencrypt, readLine);
			AssignmentData += readLine;
		}

		toencrypt.close();

		//now encrypting the data
		encryptedMsg = encrypt(AssignmentData, attributeSpecified);

		//writing the encrypted msg in file
		toencrypt.open(fileName, ios::out);

		toencrypt << encryptedMsg;

		toencrypt.close();

		AssignmentData = "";

		//for distracting the attacker if attacked the encryption/decryption services
		encryptedMsg = "qwye@hheu3333hvfh hfyfuy 3hu33i238 hj3hg38 u389";
		decryptedMsg = "Failed to access the data of SAS illegally";
	}

	//will decrypt the whole file
	void decryptAssignment(string fileName, string key)
	{
		//whole assignment reading in one string
		string AssignmentData; //decryted one
		string readLine;

		fstream todecrypt;

		//for reading
		todecrypt.open(fileName, ios::in);

		while (!todecrypt.eof())
		{
			getline(todecrypt, readLine);
			AssignmentData += readLine;
		}

		todecrypt.close();

		//now decrypting the data
		decryptedMsg = decrypt(AssignmentData, key);

		//will not save will only show on terminal --- because unable to maintain users storages as hypthetical storage is being done
		cout << decryptedMsg << endl;

		AssignmentData = "";

		//for distracting the attacker if attacked the encryption/decryption services
		encryptedMsg = "qwye@hheu3333hvfh hfyfuy 3hu33i238 hj3hg38 u389";
		decryptedMsg = "Failed to access the data of SAS illegally";
	}
};

//will have keys and will be stored in encrypted form by a key developed by the SAS --- only Known o them
class KeyManagement_Authority
{
private:
	string compKey; //will be runtime always a change
	string userAttributeKey;
	string cipherPolicykey;

public:
	KeyManagement_Authority()
	{
		compKey = "";
		userAttributeKey = "";
		cipherPolicykey = "";
	}

	void generateCompkey()
	{
		string key = "d3crytion$ervice@@@@3bvc123!we@reb!nd";
		compKey = encrypt(key, key);
	}

	//will generate users key on the basis of his request
	void generateUserkey(attributeUniverse attributes, Login user)
	{
		attributeUniverse dummyOfuser;
		dummyOfuser = user.getAttributes();

		string tempKey;

		//any null in required will make user attribute null
		//check if any of attribute is not the requirement then making that null
		if (attributes.CGPA == "NULL" || attributes.CGPA == "Null" || attributes.CGPA == "null")
		{
			dummyOfuser.CGPA = "null";
		}

		if (attributes.age == "NULL" || attributes.age == "Null" || attributes.age == "null")
		{
			dummyOfuser.age = "null";
		}

		if (attributes.batchNo == "NULL" || attributes.batchNo == "Null" || attributes.batchNo == "null")
		{

			dummyOfuser.batchNo = "null";
		}

		if (attributes.department == "NULL" || attributes.department == "Null" || attributes.department == "null")
		{
			dummyOfuser.department = "null";
		}

		if (attributes.favSubj == "NULL" || attributes.favSubj == "Null" || attributes.favSubj == "null")
		{
			dummyOfuser.favSubj = "null";
		}

		if (attributes.gender == "NULL" || attributes.gender == "Null" || attributes.gender == "null")
		{
			dummyOfuser.gender = "null";
		}

		if (attributes.inchargeTeacher == "NULL" || attributes.inchargeTeacher == "Null" || attributes.inchargeTeacher == "null")
		{
			dummyOfuser.inchargeTeacher = "null";
		}

		if (attributes.section == "NULL" || attributes.section == "Null" || attributes.section == "null")
		{
			dummyOfuser.section = "null";
		}

		if (attributes.semesterNo == "NULL" || attributes.semesterNo == "Null" || attributes.semesterNo == "null")
		{
			dummyOfuser.semesterNo = "null";
		}

		//making a collective string of all this with < after every attribute
		tempKey = dummyOfuser.CGPA + ">" + dummyOfuser.semesterNo + ">" + dummyOfuser.batchNo + ">" + dummyOfuser.section + ">" + dummyOfuser.age + ">" + dummyOfuser.gender + ">" + dummyOfuser.department + ">" + dummyOfuser.favSubj + ">" + dummyOfuser.inchargeTeacher + ">";

		//encrypt with company key and save in the user key
		userAttributeKey = encrypt(tempKey, compKey);

		tempKey = "";
	}

	//generate the ciphertext policies based key of a file
	void generatecypherKey(attributeUniverse attributeOffile)
	{
		string tempKey;

		//making a collective string of all this with < after every attribute
		tempKey = attributeOffile.CGPA + ">" + attributeOffile.semesterNo + ">" + attributeOffile.batchNo + ">" + attributeOffile.section + ">" + attributeOffile.age + ">" + attributeOffile.gender + ">" + attributeOffile.department + ">" + attributeOffile.favSubj + ">" + attributeOffile.inchargeTeacher + ">";

		//encryting with company key and saving
		cipherPolicykey = encrypt(tempKey, compKey);

		tempKey = "";
	}

	string getCompkey() const
	{
		return compKey;
	}

	string getUserkey() const
	{
		return userAttributeKey;
	}

	string getPolicykey() const
	{
		return cipherPolicykey;
	}

	void revoke(Login &user, AttributeAuthority &attributes, StorageServices &store)
	{
		
		char option;
		attributeUniverse changeAttribute;
		string id;

			store.showStorage();

			system("pause");

			//will take all the attributes again
			cout << "\n\t\t Enter id of the assignment : ";
			getline(cin, id);

			//and is owner of that file
			if (store.idMatch(id) && store.owner(id, user))
			{
				//firstly decryting the data from previous key and then will again encrypt with new key
				string oldCipher = store.findcipherPolicyof(id);
				string f = store.filenameFinder(id);
				string originalData = "";

				//overriding original in the file
				fstream temp;
				string tempS;

				temp.open(f , ios::in);
				
					while(!temp.eof())
					{
						getline(temp, tempS);
						originalData+=tempS;
					}

				temp.close();

				originalData = decrypt(originalData, oldCipher);
			

				cout << "\n\t\t Enter the new attributes for file " << endl
					 << endl;

				attributes.setAttributes(changeAttribute);

				user.setAttributes(changeAttribute);

				//writing the new in the storage
				store.setAttribute(changeAttribute);

				//now will assign the key again --- the cyphierpolicy
				generateCompkey();
				generatecypherKey(changeAttribute);

				string tempT = getPolicykey();
				string temk = getCompkey();

				string newCipher = encrypt(tempT, temk);

				//decryting file with new cipher
				string encryptMsg = encrypt(originalData, newCipher);

				temp.open(f , ios::out);
				temp << encryptMsg <<endl;
				temp.close();

				store.overrideInmemory(id, changeAttribute, newCipher, user);

				

				originalData = "";
				encryptMsg = "";

			}
			else
			{
				if (!store.owner(id, user))
				{
					cout << "\n\t :::::::: Not the onwer of this file :::::::::" << endl;
				}

				if (!store.idMatch(id))
				{
					cout << "\n\t\t Entered ID not found " << endl
						 << endl;
				}
			}
		
	
	}
};

//functions prototype ---- of a program
bool registerLogin_Menu();

int main()
{

	while (registerLogin_Menu())
		;
	return 0;
}

bool registerLogin_Menu()
{
	//will use for registering and logging in
	Login loginUser;
	Register registerUser;
	AttributeAuthority attributeMangement;
	StorageServices storeData;
	KeyManagement_Authority KMA;
	EncryptionDecryption_Service EDS;

	//company key generation
	KMA.generateCompkey(); //will use to protect the data

	fstream dataRecord;

	//will be use for processing the data
	char optionForprocessing = 0;

	//to check logedin first time as from registration
	//at starting not for first time
	bool checkLogtime = 0;

	int option = 0;
	int a = 0;

	cout << "\n\t\t\t ::::::::: Secure Assignment Sharing :::::::::" << endl
		 << endl;

	do
	{
		if (a == 0)
		{
			cout << "\n\t\t\t\t    For Registering Enter 1  " << endl;
			cout << "\t\t\t\t    For Login       Enter 2 " << endl;
			cout << "\t\t\t\t    For Exiting     Enter 0 " << endl;
			cout << "\n\n\t\t\t\t   Entered Desired Option : ";
			cin >> option;
		}
		else
		{

			cout << "\n\t\t\t :::: Invalid ---- Enter valid option ::::" << endl;

			cout << "\n\t\t\t\t    For Registering Enter 1  " << endl;
			cout << "\t\t\t\t    For Login       Enter 2 " << endl;
			cout << "\t\t\t\t    For Exiting     Enter 0 " << endl;
			cout << "\n\n\t\t\t\t   Entered Desired Option : ";
			cin >> option;
		}

		a++;

	} while (!(option == 0 || option == 1 || option == 2));

	cin.ignore();

	//switch statements
	switch (option)
	{
	//exiting
	case 0:
	{

		return 0;
	}

	//registration
	case 1:
	{
		//will take credentials for registering the user
		registerUser.takeCredentials();

		//will ask for the attributes to setup the profile
		cout << "\n\n\t\t :::::::::: Setup Your profile :::::::::::" << endl;
		registerUser.setYourAttributes();

		//saving data in  a text file
		registerUser.saveData(dataRecord);

		//looging in from registration
		checkLogtime = 1;
	}

	//login
	default:
	{

		//if is from registration
		if (checkLogtime)
		{
			//the data is being assigned to login to save current session
			loginUser.setLogin(registerUser.getUsername(), true);
			loginUser.setAttributes(registerUser.getAttribute()); //same as entered in registration
			cout << "\n\t\t ---- Registered Successfull :::: logging you -----" << endl;
			Sleep(2000);
		}

		if (!loginUser.getLogin()) //login user if not will display a msg
		{
			loginUser.loggingIn();
		}

		//if successfully login other functions will be done
		//if not will display the same menu
		//if logen in login status will be 1
		if (loginUser.getLogin())
		{
			//clearing the screen
			system("cls");

			string file = "registered.txt";

			attributeUniverse tempAttribute;

			//reading the attributes from the file
			attributeMangement.readAttributes(tempAttribute, loginUser.getUsr(), file);

			//now saving in logined user's attribute
			loginUser.setAttributes(tempAttribute);

			//displaying userName on the top to show loged in and msg of welcome
			cout << "\n\t\t\t :::::::: Welcome " << loginUser.getUsr() << " ::::::::" << endl
				 << endl;

		menu:

			cout << "\n\t\t :::: Secure Assignment Sharing provides you following ::::" << endl;

			cout << "\n\t\t\t Enter 1 to see list of documents uploaded in SAS " << endl;
			cout << "\t\t\t Enter 2 to upload your assignment in SAS " << endl;
			cout << "\t\t\t Enter 3 to redifine (revoke) attributes of your assignment in SAS " << endl;
			cout << "\t\t\t Enter 0 to Logout from SAS " << endl;
			cout << "\t\t\t Enter any other character to access assignment  in SAS " << endl;

			cout << "\n\t\t\t     Enter Your desired option : ";
			cin >> optionForprocessing;

			cin.ignore();

			//switch for the furthure processing
			switch (optionForprocessing)
			{

			//logout
			case '0':
			{

				cout << "\n\t\t\t :::::::: See you soon " << loginUser.getUsr() << " :) ::::::::" << endl;
				loginUser.logingOut(); //will logout erase the session info

				//giving pauses
				Sleep(2000);

				system("cls");
				break;
			}

			//revoking
			case '3':
			{
					cout<<"\n\t\t :::::::: Revoking --- Redifining attributes ::::::::"<<endl;

					KMA.revoke(loginUser, attributeMangement , storeData);

					cout<<"\n\t ::::::::::::::::::::::::::::::::::::::::::::: "<<endl;
					Sleep(2000);
					
					system("cls");

					goto menu;

			}

			//to upload
			case '2':
			{
				string filename;
				string data;
				attributeUniverse fileTobeaccesedby;
				fstream makeFile;
				string storeCipherPolicy;
				string id;

				string temptxt;
				string tempkey;

				cout << "\n\t\t :::: Upload Your Stuff in completely Secure manner ::::" << endl;

				cout << "\n\t\t Enter the name of file (with extension) : ";
				getline(cin, filename);

				a = 0;

				do
				{
					if (a == 0)
					{
						cout << "\t\t Enter a 4 digit code for assignment --- must be unique : ";
						getline(cin, id);
					}
					else
					{
						cout << "\n\t\t ::::::::::: Invalid --- already exist ::::::::::\n"
							 << endl;
						cout << "\t\t Enter a 4 digit code again for assignment --- must be unique : ";
						getline(cin, id);
					}

					a++;

				} while (storeData.idMatch(id));

				cout << "\n\t\t     ::::: Creating file of " << filename << " ::::::" << endl;
				Sleep(1000);

				makeFile.open(filename, ios::out);

				cout << "\n\t Enter data : ";
				getline(cin, data);

				//writing in the assignment file created
				makeFile << data << endl;

				makeFile.close();

				cout << "\n\t\t ::::: Enter the attributes you want to specify with the file :::::" << endl;
				cout << "\t\t ::::::: Something not allowed can be done by entering NULL :::::::" << endl
					 << endl;

				attributeMangement.setAttributes(fileTobeaccesedby);

				cout << "\n\t\t\t :::::: Saving File ::::::::" << endl;
				//Sleep(2000);

				//policy key based on attributes
				KMA.generatecypherKey(fileTobeaccesedby);

				temptxt = KMA.getPolicykey();
				tempkey = KMA.getCompkey();

				storeCipherPolicy = encrypt(temptxt, tempkey);

				storeData.setThings(id, filename, fileTobeaccesedby, storeCipherPolicy, loginUser.getUsr());
				
				//inserting a new line when entering the data
				fstream superTemp;
				superTemp.open("cloudStore.txt", ios::out | ios::app);
				superTemp << endl;
				superTemp.close();

				storeData.moveinStorage();

				//doing the encryption of the created file
				EDS.encryptAssignment(filename, storeCipherPolicy);

				cout << "\n\t\t ::::: Encrypted form of " << filename << " is saved in storage :::::" << endl;

				Sleep(2000);

				cout << "\n\t\t :::::::::::::::::::::::::::::::::::::::::::::::::::::: \n"
					 << endl;

				int option1;
				a = 0;

				do
				{
					if (a == 0)
					{
						cout << "\n\t Enter 1 to see main menu again" << endl;
						cout << "\t Enter 0 to logout " << endl;

						cout << "\n\t Enter desired option : ";
						cin >> option1;
					}
					else
					{
						cout << "\n\t\t ::::::: Invalid entry :::::::" << endl;
						cout << "\n\t Enter 1 to see see main menu again" << endl;
						cout << "\t Enter 0 to logout " << endl;

						cout << "\n\t Enter desired option : ";
						cin >> option1;
					}

					a++;
				} while (!(option1 == 0 || option1 == 1));

				//using switch accordingly
				switch (option1)
				{
				case 0:
				{
					cout << "\n\t\t\t :::::::: See you soon " << loginUser.getUsr() << " :) ::::::::" << endl;
					loginUser.logingOut(); //will logout erase the session info

					//giving pauses
					Sleep(2000);

					system("cls");
					return 1;
				}

				default:
				{
					//go to main menu label again
					goto menu;
				}
				}
			}

			//see list
			case '1':
			{

				cout << "\n\t\t :::::::: SAS have the following Assignments in storage ::::::::" << endl;
				storeData.showStorage();
				cout << endl
					 << endl;
				system("pause");
				//will go automaticallay to access the material
			}

			//for accessing
			default:
			{
				string id;

				string tempT;
				string tempK;

				string decryptKey;
				string theKeyoffile;

				string fn;

			//can be use for the accessing
			//creating user key on the runtime after he decides to see the specific assignment
			takeIdagain:
				cout << "\n\n\t\t Enter the assignment code u want to see : ";
				getline(cin, id);

				if (storeData.idMatch(id))
				{
					//attributes of specified file
					attributeUniverse finding;

					//saving the attributes of requested
					storeData.readAttributes(id, finding);

					//making the user key on the basis of the request generated
					KMA.generateUserkey(finding, loginUser);

					//now making the generated key as encrypted
					tempT = KMA.getUserkey();
					tempK = KMA.getCompkey();

					//will encrypt the key
					decryptKey = encrypt(tempT, tempK);

					fn = storeData.filenameFinder(id);

					//if is owner of file
					if(storeData.owner(id, loginUser))
					{
						cout<<"\n\t\t ::::: You are the owner of this file ::::: "<<endl;
						string key = storeData.findcipherPolicyof(id);
						string file = storeData.filenameFinder(id);

						cout << "\n\t\t ::::::: Decrypted File is  :::::::: \n\t\t\t" << endl;
						EDS.decryptAssignment(fn, key);
						
						cout << endl
							 << endl;

						system("pause");
						
						system("cls");

						goto menu;
					}

					//will decrypt the data
					if (storeData.findcipherPolicyof(id) == decryptKey)
					{
						cout << "\n\a\t\t ::::::: Accessed Successfully ::::::::" << endl;

						cout << "\n\t\t ::::::: Decrypted File is  :::::::: \n\t\t\t" << endl;

						EDS.decryptAssignment(fn, decryptKey);

						cout << endl
							 << endl;

						system("pause");
					}
					else
					{
						cout << "\n\a\t\t ::::::: Access Denied ::::::::" << endl;

						cout << "\n\t\t ::::::: Encrypted File is  :::::::: \n\t\t\t" << endl;
						//making key more puzzled
						decryptKey += "111@@####jhfjfh{{{{}}}}";

						EDS.decryptAssignment(fn, decryptKey);

						cout << endl
							 << endl;

						system("pause");
					}
				}
				else
				{
					char opt;

					cout << "\n\t\t ::::: Invalid Entry ::::: " << endl;
					cout << "\n\t :::::: No assignment found in storage :::::" << endl;

					cout << "\n\t Enter any character to enter Id again to exit enter 0 : ";
					cin >> opt;

					if (opt != '0')
					{
						goto takeIdagain;
					}
				}

				goto menu;
			}
			}
		}
	}

		return 1;
	}
}

