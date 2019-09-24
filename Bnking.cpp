#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string hashing(string passwd)
{
	char aux;
	for(int i = 0; i < passwd.length() / 2 - 1; i++)
	{
		aux = passwd[passwd.length() - i - 1];
		passwd[passwd.length() - i] = passwd[i];
		passwd[i] = aux;
	}
	
	for(int i = 0; i < passwd.length(); i++)
		if(i % 2 == 0)
			passwd[i]--;
		else passwd[i]++;

	return passwd;
}

class balance
{
private:
	double sold;
public: 
	int currentSold()
	{
		return sold;
	}

	void setSold(double cash)
	{
		sold = cash;
	}
	void withDraw(double cash)
	{
		if(sold < cash)
				cout << "!ERROR!, Not enough money!" << endl;
		else sold -= cash;
	}

	void addSold(double cash)
	{
		sold += cash;
	}

	void exchange(string currency, double cash)
	{
		if(currency == "EURO")
		{
			if(sold < cash * 4.73)
			{
				cout << "!ERROR!, Not enoughtt money!" << endl;
				return;
			}
			sold -= cash * 4.73;
		}
		else if(currency == "USD")
		{
			if(sold < cash * 4.03)
			{
				cout << "!ERROR!, Not enoughtt money!" << endl;
				return;
			}
			sold -= cash * 4.03;
		}
		else if(currency == "GBP")
		{
			if(sold < cash * 5.55)
			{
				cout << "!ERROR!, Not enoughtt money!" << endl;
				return;
			}
			sold -= cash * 5.55;
		}
	}
};

struct dateOfBirth
{
	int month, day, year;
};

struct adress
{
	string city, street, county;
	int nr;
};

class Human
{
protected:
	string fullName;
	dateOfBirth dateBirth;
	adress adress;
	long long int ID;
	long long int CNP;
	balance BL;
	string hashedPasswd;

public:
	// virtual ~Human()
	// {
	// 	ofstream f(to_string(ID));
	// 	f << "HUMAN" << endl;
	// 	f << fullName << endl;
	// 	f << dateBirth.day << " " << dateBirth.month << " " << dateBirth.year << endl;
	// 	f << CNP << endl;
	// 	f << hashedPasswd << endl;
	// 	f << BL.currentSold();
	// 	f.close();
	// }

	virtual void PrintOptions() = 0;

	virtual void Menu() = 0;

	void newPsswd(string passwd)
	{
		hashedPasswd = hashing(passwd);
	}

	void Add(long long id)
	{
		string aux;
		ID = id;
		cout << "@Add new user with id: " << id << endl;
		cout << "*Enter full name with '_': " << endl;
		cout << "  - ";
		cin >> fullName;
		cout << "*Enter date of birth:" << endl;
		cout << "  - Day: ";
		cin >> dateBirth.day;
		cout << "  - Month: ";
		cin >> dateBirth.month;
		cout << "  - Year: ";
		cin >> dateBirth.year;
		cout << "Give CNP: " << endl;
		cin >> CNP;
		cout << "Give account password: " << endl;
		cout << "  - ";
		cin >> aux;
		hashedPasswd = hashing(aux);
		BL.setSold(0.0);
	}

	void printInfo()
	{
		cout << fullName << " " << dateBirth.day << "/" << dateBirth.month << "/"  << dateBirth.year << " " << CNP << " " << BL.currentSold() << endl;
	}
};

class Client : public Human
{
public:
	Client(){};

	Client(long long _id)
	{
		string s = to_string(_id);
		ifstream f(s);
		if(!f)
			return;
		string aux;
		f >> aux;
		f >> fullName;
		f >> dateBirth.day >> dateBirth.month >> dateBirth.year;
		ID = _id;
		f >> CNP;
		f >> hashedPasswd;
		double aux2;
		f >> aux2;
		BL.setSold(aux2);
		f.close();
	}

	~Client()
	{
		saveToFile();
	}

	void saveToFile()
	{
		ofstream f(to_string(ID));
		f << "CLIENT" << endl;
		f << fullName << endl;
		f << dateBirth.day << " " << dateBirth.month << " " << dateBirth.year << endl;
		f << CNP << endl;
		f << hashedPasswd << endl;
		f << BL.currentSold();
		f.close();
	}

	void PrintOptions()
	{
		cout << " @ You are a client with ID: " << ID << endl;
		cout << "  1 - Show balance" << endl;
		cout << "  2 - Withdraw" << endl;
		cout << "  3 - Add sold" << endl;
		cout << "  4 - Exchange" << endl;
		cout << "  5 - Change password" << endl;
		cout << "  0 - Exit" << endl;
		cout << "!Type your request!" << endl;
	}

	void Menu()
	{	
		int option = 100;
		double aux;
		string aux2;

		cout << " @ You are a client with ID: " << ID << endl;
		cout << "Give the password" << endl;
		cin >> aux2;
		getchar();
		if(hashing(aux2) != hashedPasswd)
		{
			cout << "WRONG PASSWORD" << endl;
			cout << "PRESS ENTER TO CONTINUE" << endl;
			getchar();
			return;
		}

		while(option != 0)
		{
			system("cls");
			PrintOptions();
			cin >> option;
			if(option < 0 || option > 5)
			{
				cout << "!!!WRONG OPTION!!!" << endl;
				cout << "Press enter to continue" << endl;
				getchar();
			}
			switch(option)
			{
				case 1:	cout << "Your current sold is: " << BL.currentSold() << " RON" << endl;
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						break;

				case 2: cout << "Your current sold is: " << BL.currentSold() << "RON" << endl;
						cout << "Type what ammount of money(RON) you want to withdraw: " << endl;
						cin >> aux;
						BL.withDraw(aux);
						cout << "You have withdrawed " << aux << "RON, you new sold is: " << BL.currentSold() << endl;
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						saveToFile();
						break;

				case 3:	cout << "Your current sold is: " << BL.currentSold() << "RON" << endl;
						cout << "Type what ammount you want to add to your sold:" << endl;
						cin >> aux;
						BL.addSold(aux);
						cout << "You have added " << aux << " RON to you account, and you new sold is: " << BL.currentSold() << endl;
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						saveToFile();
						break;

				case 4:	cout << "Type what currency you want to exchange" << endl;
						cout << "EUR/USD/GBP" << endl;
						cin >> aux2;
						cout << "Type what amount you want to exchange" << endl;
						cin >> aux;
						BL.exchange(aux2, aux);
						cout << "You have exchanged " << aux << " " << aux2 << " you new sold is: " << BL.currentSold() << endl;
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						saveToFile();
						break;

				case 5: cout << "Type your old password" << endl;
						cin >> aux2;
						if(hashing(aux2) != hashedPasswd)
						{
							cout << "   !!WRONG PASSWORD!!" << endl;
							cout << "Press enter to continue" << endl;
							getchar();
							getchar();
							saveToFile();
							break;
						}
						cout << "Type your new password" << endl;
						cin >> aux2;
						hashedPasswd = hashing(aux2);
						cout << "You have changed your password" << endl;
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						saveToFile();
						break;
			}
		}
	}

};

class Staff : public Human
{
public:
	Staff(){};

	Staff(long long _id)
	{
		string s = to_string(_id);
		ifstream f(s);
		string aux;
		f >> aux;
		f >> fullName;
		f >> dateBirth.day >> dateBirth.month >> dateBirth.year;
		ID = _id;
		f >> CNP;
		f >> hashedPasswd;
		double aux2;
		f >> aux2;
		BL.setSold(aux2);
		f.close();
	}
	~Staff()
	{
		saveToFile();
	}

	void saveToFile()
	{
		ofstream f(to_string(ID));
		f << "STAFF" << endl;
		f << fullName << endl;
		f << dateBirth.day << " " << dateBirth.month << " " << dateBirth.year << endl;
		f << CNP << endl;
		f << hashedPasswd << endl;
		f << BL.currentSold();
		f.close();
	}

	void PrintOptions()
	{
		cout << " @ You are a client with ID: " << ID << endl;
		cout << "  1 - List all users" << endl;
		cout << "  2 - Add user" << endl;
		cout << "  3 - Change exchange rate" << endl;
		cout << "  4 - Add a currency" << endl;
		cout << "  5 - Remove client" << endl;
		cout << "  6 - Change password" << endl;
		cout << "  7 - Change client password" << endl;
		cout << "  0 - Exit" << endl;
		cout << "!Type your request!" << endl;
	}

	void listAllClients()
	{
		int nr;
		string aux;
		ifstream f("bank.txt");
			if(f)
				f >> nr;
		f.close();
		for(long long int i = 1; i <= nr; i++)
		{
			ifstream in(to_string(i));
			in >> aux;
			cout << i << " - ";
			if(aux == "CLIENT")
			{
				in.close();
				Client x(i);
				x.printInfo();
			} else if(aux == "STAFF")
				{
					in.close();
					cout << "Staff Account" << endl;
				}	else cout << "DELETED" << endl;
		}

	}

	void Menu()
	{	
		int option = 100;
		double aux;
		string aux2;

		cout << " @ You are a staff with ID: " << ID << endl;
		cout << "Give the password" << endl;
		cin >> aux2;
		getchar();
		if(hashing(aux2) != hashedPasswd)
		{
			cout << "WRONG PASSWORD" << endl;
			cout << "PRESS ENTER TO CONTINUE" << endl;
			getchar();
			return;
		}

		while(option != 0)
		{
			system("cls");
			PrintOptions();
			cin >> option;
			if(option < 0 || option > 7)
			{
				cout << "!!!WRONG OPTION!!!" << endl;
				cout << "Press enter to continue" << endl;
				getchar();
			}
			switch(option)
			{
				case 1:	cout << "ID - NAME - BIRTH - CNP - ID - BALANCE(RON)" << endl;
						listAllClients();
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						break;

				case 2:{ifstream f("bank.txt");
						long long int aux3;
						f >> aux3;
						aux3++;
						f.close();
						ofstream g("bank.txt");
						g << aux3;
						g.close();
						cout << "You are adding client with ID: " << aux3 << endl;
						Client cl(aux3);
						cl.Add(aux3);
						cl.~Client();
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						break;
						}

				case 3:{ifstream f("exchange_rate.txt");
						if(!f)
						{
							cout << "EXCHANGE RATE NOT AVAILABLE AT THE MOMENT" << endl;
						}
						else
						{
							cout << "Current exchange rate:" << endl;
							vector<string> data;
							vector<string> v;
							int i = 0;
							while(f >> aux2)
							{
								cout << i + 1 << " - " << aux2 << " ";
								data.push_back(aux2);
								f >> aux2;
								cout << aux2 << endl;
								v.push_back(aux2);
								i++;
							}
							f.close();
							int x;
							cout << "Type the id of the currency you want to change:" << endl;
							cin >> x;
							cout << "Type the new value for " << data[x - 1] << endl;
							cout << data[x - 1] << " - ";
							cin >> aux2;
							v[x - 1] = aux2;
							ofstream g("exchange_rate.txt");
							for(int j = 0; j < i; j++)
								g << data[j] << " " << v[j] << endl;
							g.close();
							cout << "You have succesefully edited the selected currency" << endl;
						}
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						break;
					   }

				case 4:{ifstream f("exchange_rate.txt");
						if(!f)
						{
							cout << "EXCHANGE RATE NOT AVAILABLE AT THE MOMENT" << endl;
						}
						else
						{
							vector<string> data;
							vector<string> v;
							int i = 0;
							while(f >> aux2)
							{
								data.push_back(aux2);
								f >> aux2;
								v.push_back(aux2);
								i++;
							}
							f.close();
							cout << "Type the currency you want to add" << endl;
							cin >> aux2;
							getchar();
							data.push_back(aux2);
							cout << "Type the value of the new currency" << endl;
							cin >> aux2;
							v.push_back(aux2);
							ofstream g("exchange_rate.txt");
							for(int j = 0; j <= i; j++)
								g << data[j] << " " << v[j] << endl;
							g.close();
							cout << "You have succesfully added the new currency" << endl;
						}
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						break;
					   }


				case 5:{cout << "You are removing a client" << endl;
						cout << "Type the ID of the client you want to remove" << endl;
						long long int aux3;
						cin >> aux3;
						ifstream f(to_string(aux3));
						if(!f)
							cout << "THIS ID DOES NOT EXIST" << endl;
						else
						{
							f >> aux2;
							if(aux2 == "STAFF")
							{
								cout << "YOU CAN'T DELETE A STAFF ACCOUNT" << endl;
								f.close();
							}
							else if(aux2 == "DELETED")
							{
								f.close();
								cout << "THIS USER HAS ALLREADY BEEN DELETED" << endl;
							}
							else 
							{
								ofstream g(to_string(aux3));
								g << "DELETED" << endl;
								g.close();
								f.close();
								cout << "You have succesefully deleted the account with ID: " << aux3 << endl;
							}
						}
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						break;
					   }

				case 6: cout << "Type your old password" << endl;
						cin >> aux2;
						if(hashing(aux2) != hashedPasswd)
						{
							cout << "   !!WRONG PASSWORD!!" << endl;
							cout << "Press enter to continue" << endl;
							getchar();
							getchar();
							saveToFile();
							break;
						}
						cout << "Type your new password" << endl;
						cin >> aux2;
						hashedPasswd = hashing(aux2);
						cout << "You have changed your password" << endl;
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						saveToFile();
						break;

				case 7: cout << "Type the ID of the user you want to change the password of:" << endl;
						long long int aux3;
						cin >> aux3;
						ifstream f(to_string(aux3));
						if(!f)
							cout << "THIS ID DOES NOT EXIST" << endl;
						else
						{
							f >> aux2;
							if(aux2 == "STAFF")
							{
								cout << "YOU CAN'T CHANGE THE PASSWORD TO A STAFF ACOUNT" << endl;
								f.close();
							}
							else 
							{
								f.close();
								Client cl(aux3);
								cout << "Give the new password for client with ID: " << aux3 << endl;
								cin >> aux2;
								cl.newPsswd(aux2);
								cl.~Client();
								cout << "You have succesefully changed the password of the account with ID: " << aux3 << endl;
							}
						}
						cout << "Press enter to continue" << endl;
						getchar();
						getchar();
						break;
			}
		}
	}
	

};


class Bank
{
private:
	long long int id;
	Bank(){};

	~Bank()
	{
		ofstream f("bank.txt");
		f << id;
		f.close();
	}

	// long long int hashing(string passwd)
	// {
	// 	int hash = 0;
	// 	for(int i = 0; i < passwd.length(); i++)
	// 		hash += passwd[i];
	// 	return hash;
	// }

public:
	static Bank& Instance()
	{
		static Bank bank;
		return bank;
	}

	void PrintOptions()
	{
		cout << " !You are in the main Bank Menu!" << endl;
		cout << "   @This bank has got " << id << " users@" << endl;
		cout << " 1 - Show exchange rate" << endl;
		cout << " 2 - Log in" << endl;
		cout << " 0 - Exit" << endl;
		cout << "*Type your request*" << endl;
	}

	void showExchangeRate()
	{
		cout << endl;
		ifstream f("exchange_rate.txt");
		if(!f)
		{
			cout << "Exchange rate not available at the moment" << endl << endl;
			return;
		}
		cout << endl;
		string aux;
		while(f >> aux)
		{
			cout << aux << " ";
			f >> aux;
			cout << aux << endl;
			cout << endl;
		}
		f.close();
		cout << endl;
	}

	void MainMenu()
	{
		string aux2;
		long long int aux = 0;
		int option = 100;
		while(option != 0)
		{
			ifstream f("bank.txt");
			if(f)
				f >> id;
			else id = 0;
			f.close();
			system("cls");
			PrintOptions();
			cin >> option;
			getchar();
			switch(option)
			{
				case 0: return;
				
				case 1:	showExchangeRate();
						cout << "Press enter to continue" << endl;
						getchar();
						break;

				case 2: cout << "Give the ID" << endl;
						cin >> aux;
						ifstream in(to_string(aux));
						if(in)
							{
								in >> aux2;
								if(aux2 == "CLIENT")
								{
									in.close();
									Client x(aux);
									x.Menu();
								}
								else if(aux2 == "STAFF")
								{
									in.close();
									Staff x(aux);
									x.Menu();
								}
								else if(aux2 == "DELETED")
								{
									cout << "THIS ID HAS BEEN REMOVED" << endl;
									cout << "PRESS ENTER TO CONTINUE" << endl;
									getchar();
								}
								else 
								{
									cout << "THIS ID NEVER EXISTED" << endl;
									cout << "PRESS ENTER TO CONTINUE" << endl;
									getchar();
								}
							}
								break;
				

			}
		}
	}


};

int main()
{
	Bank& bank = Bank::Instance();
	bank.MainMenu();
	return 0;
}
