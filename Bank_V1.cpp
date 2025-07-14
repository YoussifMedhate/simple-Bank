#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string FILENAME = "Clients.txt";
struct sClients
{
	string id;
	string name;
	string pinCode;
	string phoneNumber;
	float balance = 0;
};
enum menus{ showAll = 1 , addUser = 2 , deleteUser = 3 , updateUser = 4 , findUser = 5 , exit_application = 6};
void main_menu();
vector <string> split(string s , string deli = "#///#") 
{
	string Word = "";
	int pos = 0;
	vector <string > v;
	while ((pos = s.find(deli)) != string::npos)
	{
		Word = s.substr(0, pos);
		if (Word != "")
		{
			v.push_back(Word);
		}
		s = s.substr(pos + deli.length() , s.length());
	}
	if (s != "")
	{
		v.push_back(s);
	}
	return v;


}
sClients take_information()
{
	sClients c;
	cout << "Enter Client Id : ";
	getline(cin >> ws , c.id);
	cout << "Enter Client Name : ";
	getline(cin >> ws , c.name);
	cout << "Enter Client Pin Code : ";
	getline(cin >> ws , c.pinCode);
	cout << "Enter Client Phone Number : ";
	getline(cin >> ws , c.phoneNumber);
	cout << "Enter Client balance : ";
	cin >> c.balance;
	return c;
}
void update_information(sClients &c)
{
	cout << "Enter Client Name : ";
	getline(cin >> ws, c.name);
	cout << "Enter Client Pin Code : ";
	getline(cin >> ws, c.pinCode);
	cout << "Enter Client Phone Number : ";
	getline(cin >> ws, c.phoneNumber);
	cout << "Enter Client Balance : ";
	cin >> c.balance;
}
void show_information(sClients& c)
{
	
	cout << "Client Id -> "<<c.id <<"\n";
	cout << "Client Name -> "<<c.name << "\n";
	cout << "Client Pin Code -> "<<c.pinCode <<"\n";
	cout << "Client Phone Number -> "<<c.phoneNumber<<"\n";
	cout << "Client balance -> "<<c.balance<<"\n";

}
string to_line(sClients& c, string deli = "#///#")
{
	string s = c.id + deli + c.name + deli + c.pinCode + deli + c.phoneNumber + deli + to_string(c.balance);
	return s;
}
sClients to_sClient(string& s, string deli = "#///#")
{
	vector <string> v = split(s);
	sClients c;
	c.id = v[0];
	c.name = v[1];
	c.pinCode = v[2];
	c.phoneNumber = v[3];
	c.balance = stof(v[4]);
	return c;
}
void add_line(const string fileName, string line , string deli = "#///#")
{
	fstream file;
	file.open(fileName, ios::app);
	if (file.is_open())
	{
		file << line << endl;
		file.close();
	}
}
void add_line(const string fileName, sClients& c, string deli = "#///#")
{
	string line = to_line(c , deli);
	add_line(fileName, line, deli);
}
vector <sClients> take_lines(string fileName)
{
	vector <sClients > v;
	fstream file;
	string line;
	file.open(fileName, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			v.push_back(to_sClient(line));
		}
	}
	file.close();
	return v;
}
void delete_line(string fileName, string id, string deli = "#///#")
{
	vector <sClients> v = take_lines(fileName);
	fstream file;
	string line;
	file.open(fileName, ios::out);
	if (file.is_open())
	{
		for (sClients& c : v)
		{
			if (c.id != id)
			{
				line = to_line(c, deli);
				file << line << endl;
			}
		}
	file.close();
	}
}
void update_line(string fileName,  sClients &client ,string deli = "#///#")
{
	vector <sClients> v = take_lines(fileName);
	fstream file;
	string line;
	file.open(fileName, ios::out);
	if(file.is_open())
	{
		for (sClients& c : v)
		{
			if (c.id == client.id) c = client;
			line = to_line(c);
			file << line << endl;

		}
		file.close();
	}
}
bool is_exit(string fileName,  sClients &cc,  string deli = "#///#")
{
	vector <sClients> v = take_lines(fileName);
	for (sClients& c : v)
	{
		if (c.id == cc.id)
		{
			cc = c;
			return true;
		}
	}
	return false;
}
void print_one_line(sClients& Client)
{
	cout << "| " << setw(15) << left << Client.id;
	cout << "| " << setw(10) << left << Client.pinCode;
	cout << "| " << setw(20) << left << Client.name;
	cout << "| " << setw(12) << left << Client.phoneNumber;
	cout << "| " << setw(12) << left << Client.balance;
}
void show_all_users(string fileName)
{
	vector<sClients> vClients = take_lines(FILENAME);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________"; 
	cout << "_________________________________________\n" << endl;  
	cout << "| " << left << setw(15) << "Accout Number";   
	cout << "| " << left << setw(10) << "Pin Code";   
	cout << "| " << left << setw(20) << "Client Name"; 
	cout << "| " << left << setw(12) << "Phone";    
	cout << "| " << left << setw(12) << "Balance";  
	cout << "\n_______________________________________________________"; 
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0)      
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
	{
		for (sClients Client : vClients)
		{
			print_one_line(Client);
			cout << endl;
		}
	}
	cout << "\n_______________________________________________________"; 
	cout << "_________________________________________\n" << endl;

}
void add_user()
{
	cout << string(50, '-') << "\n\t\t ADDING CLIENT\n" << string(50, '-') << "\n";
	sClients user;
	cout << "Enter Client ID : ";
	getline(cin >> ws, user.id);
	if (is_exit(FILENAME,  user))
	{
		cout << "\nClient is exist !! \nAnd information is :\n\n";
		show_information(user);
	}
	else
	{
		update_information(user);
		cout << "\n\nClient is added successfully \nAnd information is :\n\n";
		add_line(FILENAME, user);
		show_information(user);
	}

}
void delete_user()
{
	cout << string(50, '-') << "\n\t\t DELETE CLIENT\n" << string(50, '-') << "\n";
	sClients client;
	cout << "Enter Client ID : ";
	getline(cin >> ws, client.id);
	if (is_exit(FILENAME, client))
	{
		char c = 'N';
		cout << "\nAre you sure you want delete (" << client.id << "):\n";
		show_information(client);
		cout << "\nIf you are sure enter [Y / y] : ";
		cin >> c;
		if (c == 'y' || c == 'Y')
		{
			delete_line(FILENAME, client.id);
			cout << "\nClient (" << client.id << ") is deleted successfully \n";
		}
		else
		{
			cout << "\nClient (" << client.id << ") is not deleted \n";
		}
		
	}
	else
	{
		cout << "\nClient(" << client.id << ") is not found in system !!! \n";
	}

}
void update_user()
{
	cout << string(50, '-') << "\n\t\t UPDATE CLIENT\n" << string(50, '-') << "\n";
	sClients client;
	cout << "Enter Client ID : ";
	getline(cin >> ws, client.id);
	if (is_exit(FILENAME, client))
	{
		char c = 'N';
		cout << "\nAre you sure you want update information (" << client.id << "):\n";
		show_information(client);
		cout << "\nIf you are sure enter [Y / y] : ";
		cin >> c;
		if (c == 'y' || c == 'Y')
		{
			update_information(client);
			update_line(FILENAME, client);
			cout << "\nClient (" << client.id << ") is updated successfully \n";
		}
		else
		{
			cout << "\nClient (" << client.id << ") is not updated \n";
		}

	}
	else
	{
		cout << "\nClient(" << client.id << ") is not found in system !!! \n";
	}
}
void find_user()
{
	cout << string(50, '-') << "\n\t\t FIND CLIENT\n" << string(50, '-') << "\n";
	sClients client;
	cout << "Enter Client ID : ";
	getline(cin >> ws, client.id);
	if (is_exit(FILENAME, client))
	{
		cout << "\n";
		show_information(client);
	}
	else
	{
		cout << "\nClient(" << client.id << ") is not found in system !!! \n";
	}
}
void back_main_menu()
{
	cout << "\n\nPress any key to back main menu ......";
	system("pause>0");
	main_menu();
}
int take_choice()
{
	int num;
	do
	{
		cout << "Enter choise : ";
		cin >> num;
	} 
	while (num > 6 || num < 0);
	return num;
}
void exit_app()
{
	cout << "\nThank you for using our Bank\nGood bye :)";
}
void prepare_choise(menus c)
{
	switch (c)
	{
	case (menus::showAll):
	{
		system("cls");
		show_all_users(FILENAME);
		back_main_menu();
		break;
	}
	case (menus::addUser):
	{
		system("cls");
		add_user();
		back_main_menu();
		break;
	}
	case (menus::deleteUser):
	{
		system("cls");
		delete_user();
		back_main_menu();
		break;
	}
	case (menus::updateUser):
	{
		system("cls");
		update_user();
		back_main_menu();
		break;
	}
	case (menus::findUser):
	{
		system("cls");
		find_user();
		back_main_menu();
		break;
	}
	case (menus::exit_application):
	{
		exit_app();
		break;
	}

	}

}
void main_menu()
{
	system("cls");
	cout << string(50, '-') << "\n\t\t MAIN MENU\n" << string(50, '-') << "\n";
	cout << "[1] Show all clients \n";
	cout << "[2] Add client \n";
	cout << "[3] Delete client \n";
	cout << "[4] Update client information \n";
	cout << "[5] Find Client by ID \n";
	cout << "[6] Exit \n";
	int number = take_choice();
	prepare_choise((menus)number);
	
}
int main()
{
	main_menu();
}
