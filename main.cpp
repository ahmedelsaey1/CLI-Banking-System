#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
enum enChooseMianMenue { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transactions = 6, Exit = 7 };
enum enChooseTransactionsMenue { Deposit = 1, Withdraw = 2, Total_Balances = 3, Main_Menue = 4 };
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0.0;
	bool MarkForDelete = false;
};
void ShowMainMenue();
void ShowTransactionsMenue();
short ReadtrueNumber(string St)
{
	short Num = 0;
	cout << St << " : ";
	cin >> Num;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number , Enter a Valid One : " << endl;
		cin >> Num;
	}

	return Num;
}
vector<string> SplitString(string S1, string Seperetor = "#//#")
{
	short Pos = 0;
	vector<string>vStr;
	string Word = "";
	while ((Pos = S1.find(Seperetor)) != string::npos)
	{
		Word = S1.substr(0, Pos);
		if (Word != "")
		{
			vStr.push_back(Word);
		}
		S1.erase(0, Pos + Seperetor.length());
	}
	if (S1 != "")
	{
		vStr.push_back(S1);
	}
	return vStr;
}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double
	return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		sClient Client;
		string Line;
		while (getline(File, Line))
		{
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				File.close();
				return true;
			}

		}
		File.close();

	}
	return false;
}
void AddDataLineToFile(string FileName, string  stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{

		MyFile << stDataLine << endl;

		MyFile.close();
	}
}
sClient ReadNewClient()
{
	sClient Client;
	cout << "Please Enter Account Number : ";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;

}
void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		//system("cls");
		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintClientRecordLineToTotalBalance(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";
}
void ShowAllClientsScreen()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (sClient Client : vClients)
		{

			PrintClientRecordLine(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void ShowAllClientsScreenToTotalBalance()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (sClient Client : vClients)
		{

			PrintClientRecordLineToTotalBalance(Client);
			cout << endl;
		}


	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double TotalBalance = 0;
	for (sClient& C : vClients)
	{
		TotalBalance += C.AccountBalance;
	}
	cout << "\t\t\t\tTotal Balance = " << TotalBalance << endl;
}
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();

}
void GoBackToTransactionsMenue()
{
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMenue();

}
short ReadMainMenueOpiton(short From = 1, short To = 7)
{
	cout << "Choose what do you want to do? [" << From << " To " << To << "] ? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter Account Number? ";
	cin >> AccountNumber;
	return AccountNumber;

}
bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{

		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}

	}
	return false;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

	for (sClient& C : vClients)
	{

		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}

	}

	return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite

	string DataLine;

	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{

			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.  
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}

		}

		MyFile.close();
	}

	return vClients;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{

		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			//Refresh Clients 
			vClients = LoadCleintsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}
void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}
sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{

		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}
void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);

}
void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients)
{
	char Answer = 'n';

	cout << "Are You Sure You want Preform This Transaction Amount [" << Amount << "] To This Account? y|n ? ";	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\nDone Successfully.\n" << "New Balance Is [" << C.AccountBalance << "]";
				return true;
			}

		}
		return false;
	}
}
void ShowDepositScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";
	string AccountNumber = ReadClientAccountNumber();
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	sClient Client;
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client With [ " << AccountNumber << " ] Does Not Exist.\n\n";
		cout << "Enter True Account Number : ";
		getline(cin >> ws, AccountNumber);
	}
	PrintClientCard(Client);
	double Amount = ReadtrueNumber("Please Enter Debosit Amount ");
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}
void ShowWithdrawScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\Withdraw Screen";
	cout << "\n-----------------------------------\n";
	string AccountNumber = ReadClientAccountNumber();
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	sClient Client;
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client With [ " << AccountNumber << " ] Does Not Exist.\n\n";
		cout << "Enter True Account Number : ";
		getline(cin >> ws, AccountNumber);
	}
	PrintClientCard(Client);
	double Amount = ReadtrueNumber("Please Enter Withdraw Amount ");
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}
void ShowTotalBalancesScreen()
{
	ShowAllClientsScreenToTotalBalance();
}
void PreformMainMenueOpiton(enChooseMianMenue Choose)
{
	switch (Choose)
	{
	case Show:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();

		break;
	case Add:
		system("cls");
		AddNewClients();
		GoBackToMainMenue();
		break;
	case Delete:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	case Update:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	case Find:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case Transactions:
		system("cls");
		ShowTransactionsMenue();
		break;
	case Exit:
		system("cls");
		ShowEndScreen();
		break;
	}
}
void PreformTransactionsMenueOpiton(enChooseTransactionsMenue Choose)
{
	switch (Choose)
	{
	case Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;
	case Withdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionsMenue();
		break;
	case Total_Balances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;
	case Main_Menue:
		ShowMainMenue();
		break;
	}
}
void ShowMainMenue()
{
	system("cls");
	cout << "================================================\n";
	cout << "\t\tMAIN MENUE SCREEN\t\t\n";
	cout << "================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	PreformMainMenueOpiton(enChooseMianMenue(ReadMainMenueOpiton()));
}
void ShowTransactionsMenue()
{
	system("cls");
	cout << "================================================\n";
	cout << "\t\Transactions MENUE SCREEN\t\t\n";
	cout << "================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	PreformTransactionsMenueOpiton(enChooseTransactionsMenue(ReadMainMenueOpiton(1, 4)));
}
int main()
{
	ShowMainMenue();
}