/* command to compile: g++ -o jobsearchapp jobsearchapp.cpp
   command to run    : ./jobsearchapp
*/

#include<iostream>
#include <cstdlib>
#include <fstream>
//#include <string>
using namespace std;


class JobSearchAppHome
{
	
	public:
		int invalidLoginCount;

		/* Welcome page section */
		void loadWelcomePage()
		{	
			invalidLoginCount = 0;
			welcomeBanner();
			getLoginDetails();
		}

		void welcomeBanner()
		{
			cout << " ==================================\n";
			cout << "| Welcome to job search appliction |\n";
			cout << " ==================================\n\n";
		}

		void applicationLogo()
		{
			cout << " ===================\n";
			cout << "| Job Search Portel |\n";
			cout << " ===================\n\n";
		}

		void getLoginDetails()
		{
			string registeredUser;
			cout << "Have you registered already? y/n : ";
			cin >> registeredUser;
			if(registeredUser == "y" || registeredUser == "Y")
			{
				authenticateUser(false);
			}
			else
			{
				registerUser();
			}
		}

		void clearScreenAndShowLogo()
		{
			system("clear");
			applicationLogo();
		}

		/* User registration section */
		void registerUser()
		{
			string userName = "", password = "", re_register_flag;
			
			clearScreenAndShowLogo();

			cout << "Please register for login!!\n" << endl;			

			userName = validateUserName();
			if(userName != "y" && userName != "Y")
			{
				password = validatePossword();										
				storeLoginDetails(userName, password);
			}
			else
			{
				cout << endl;
				cout << "Thank you :)" << endl << endl;
			}
			
		}

		string validateUserName()
		{
			string userName;
			bool continueLoop = false;
			do
			{
				cout << "Please enter userName: ";
				cin >> userName;

				if(userName != "y" && userName != "Y")
				{
					if(validateUser(userName) > 0)
					{
						cout << "\nEntered userName already exists. Please enter different name or press \'y\' to exit !!\n\n";
						continueLoop = true;
					}
					else
					{
						continueLoop = false;
					}
				}
				else
				{					
					continueLoop = false;
				}

			}
			while(continueLoop);

			return userName;
		}


		string validatePossword()
		{
			string password, reEnteredPassword;
			bool continueLoop = false;
			do
			{
				cout << "Please enter password: ";
				cin >> password;
			
				cout << "Please re-enter password: ";
				cin >> reEnteredPassword;

				if(password != reEnteredPassword)
				{
					cout << "The password and the re-entered password are mismatching!!\n\n";
					continueLoop = true;
				}
				else
				{
					continueLoop = false;
				}

			}
			while(continueLoop);

			return password;
		}

		void storeLoginDetails(string userName, string password)
		{

			if(userName != "" && password != "")
			{
				string fileName = userName + ".dat";
				writeDataIntoFile(fileName, password);
				cout << "You have registerd successfully! please login again to proceed further.\n";
				authenticateUser(true);
			}
									
		}

		void writeDataIntoFile(string fileName, string dataToWrite)
		{
			ofstream outfile;
   			outfile.open(fileName.c_str());
			outfile << dataToWrite;
			outfile.flush();
			outfile.close();
		}

		

		int validateUser(string userName)
		{
			int fileExistsFlag;
			string fileName = userName + ".dat";
			ifstream inputFileStream(fileName.c_str());
			fileExistsFlag = inputFileStream.good();
			if(fileExistsFlag > 0)
			{
				inputFileStream.close();
			}
			return fileExistsFlag;
			
		}

		/* Login validation section */

		void authenticateUser(bool afterRegistrationFlag)
		{
			string userName, password;
			
			if(!afterRegistrationFlag)
			{
				clearScreenAndShowLogo();
			}
			

			cout << "\n\nPlease enter userName: " << endl;
			cin >> userName;
			
			cout << "Please enter password: " << endl;
			cin >> password;

			validateLoginCredentials(userName, password);
		}

		void validateLoginCredentials(string userName, string password)
		{
			string passwordFromFile = readFile(userName, true);
			if(passwordFromFile == password)
			{
				loadHomeMenu();
			}
			else
			{	
				if(!isInvalidLogin())
				{
					cout << "Please enter valid userName or password.";
					authenticateUser(true);
				}
			}

		}

		bool isInvalidLogin()
		{
			bool loginBock = false;
			if(invalidLoginCount >=2)
			{
				invalidLoginCount = 0;
				cout << endl;
				cout << "Your login has been locked. Please try again after 2 minutes.\n\n";
				cout << "Thank you :)\n";
				loginBock = true;
			}
			else
			{
				invalidLoginCount++;
			}
			return loginBock;			
		}


		string readFile(string fileName, bool firstLine)
		{
			
			string file = fileName + ".dat";			
			string data;

			ifstream inputFileStream(file.c_str());

			if(firstLine)
			{
				inputFileStream >> data;
			}
			else
			{
				while (getline(inputFileStream, data))
				{
					cout << data << endl;
				}
			}
			
			
			inputFileStream.close();
			return data;
		}

		/* Home page after Login */
		void loadHomeMenu()
		{
			string menuOption;
			clearScreenAndShowLogo();
			cout << "-------------------------------------------------------------" << endl;
			cout << "| Job Details (jd) | Update Profile (up) | View Profile (vp) |" << endl;
			cout << "-------------------------------------------------------------" << endl << endl;
			cout << "Please enter you option (jd/up/vp): ";
			cin >> menuOption;
			if(menuOption != "")
			{
				cout << "\nyou have selected : " << menuOption << endl << endl;
				
				if(menuOption == "jd")
				{
					readFile("jobdescription", false);
				}
				else if(menuOption == "up")
				{

				}
				else if(menuOption == "vp")
				{

				}			
			}			
		}

};


int main()
{
	JobSearchAppHome jobSearchAppHomeObj;
	jobSearchAppHomeObj.loadWelcomePage();
	return 0;
}
