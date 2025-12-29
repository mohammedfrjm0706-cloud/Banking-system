#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std; 

struct name 
{
	string full_name; 
	string first_name; 
	string father_name; 
	string grandfather_name; 
	string family_name;
};
struct accounts 
{
	name names;
	int id; 
	float balance; 
};

accounts storage[1000];
void load_from_file();
void save_to_file();
void deposit();
void withdraw();
void add_account();
void view_account_details();
void delete_account();
void transfer_amount();
void split_name(int);
int count=0; 
int main() 
{
	bool flag=true; 
	char choice; 
	load_from_file();
	while(flag)
	{
		cout<<"===Bank==="<<endl; 
	    cout<<"1. Deposit money "<<endl; 
	    cout<<"2. Withdraw money "<<endl; 
	    cout<<"3. Add a new account "<<endl; 
		cout<<"4. View account details "<<endl; 
		cout<<"5. Delete account "<<endl;
		cout<<"6. Transfer money to other account "<<endl;
		cout<<"7. Exit "<<endl; 
	    cout<<"Enter your choice: "; 
	    cin>>choice;
		switch(choice)  
		{
			case '1': 
			deposit();
			save_to_file();
			break; 
			case '3': 
			add_account();
			save_to_file();
			break;
			case '2': 
			withdraw();
			save_to_file();
			break;  
			case '4': 
			view_account_details();
			break;
			case '7': 
			save_to_file();
			cout<<"Thank you of using the program, goodbye "<<endl;
			flag=false; 
			break;
			case '5':
		    delete_account();
		    save_to_file();
		    break; 
		    case '6': 
		    transfer_amount();
		    save_to_file();
		    break;
		    default: 
		    cout<<"Incorrect choice! "<<endl; 
		    break;
		}
	}
	return 0;
}

void save_to_file() 
{
	accounts n;
	ofstream file("auto.txt"); 
	if(file.is_open()) 
	{
		file<<count<<endl;
		for(int i=0 ; i<count ; i++) 
		{
			file<<storage[i].names.full_name<<endl; 
			file<<storage[i].id<<endl; 
			file<<storage[i].balance<<endl; 
		}
	}
	else 
	{
		cout<<"File is not found! "<<endl; 
	}
}
void deposit()
{
	int amount,id;
	accounts n; 
	cin.ignore(); 
	cout<<"Enter the account name: ";
	getline(cin , n.names.full_name);
	cout<<"Enter account id: "; 
	cin>>id; 
	for(int i=0 ; i<count ; i++) 
	{
		if(n.names.full_name==storage[i].names.full_name && id==storage[i].id) 
		{
			cout<<"account with the name "<<n.names.full_name<<" and id number "<<id<<" found! "<<endl;
			cout<<"Enter the added amount: ";
			cin>>amount;
			if(amount<=0) 
			{
				cout<<"Error the amount must be positive! "<<endl; 
				return; 
			}
			cout<<"added the amount successfully! "<<endl; 
			storage[i].balance += amount;
			return; 
		}
	}
	cout<<"Account not found! "<<endl; 
}

void withdraw()
{
	int amount,id;
	accounts e;
	string name; 
	cout<<"Enter the account name: ";
	cin.ignore();
	getline(cin , name);
	cout<<"Enter account id: "; 
	cin>>id; 
	for(int i=0 ; i<count ; i++) 
	{
		if(name==storage[i].names.full_name && id==storage[i].id) 
		{
			cout<<"account with the name "<<name<<" and id number "<<id<<" found! "<<endl;
			cout<<"Enter the taken amount: ";
			cin>>amount;
			if(amount<=0) 
			{
				cout<<"The entered amount is 0! or a negative number"<<endl;
				return;
			}
			if(storage[i].balance<amount || storage[i].balance<=0) 
			{
				cout<<"insufficient balance! "<<endl;
				return; 
			}
			cout<<"Withdrew successfully! "<<endl; 
			storage[i].balance -= amount; 
			return; 
		}
	}
	cout<<"Account not found! "<<endl; 
}

void add_account() 
{
	int id,i;
	cout<<"Enter the account name: "; 
	cin.ignore();
	getline(cin , storage[count].names.full_name); 
	cout<<"Enter the account id: "; 
	cin>>id;
	for(i=0 ; i<count ; i++)  
	{
		if(storage[i].id==id)
		{
			cout<<"id is already used! "<<endl; 
			return;
		}
		else if(count==0) 
		{
			break;
		}
	}
	storage[count].id=id;
	cout<<"Enter the intial balance: "; 
	cin>>storage[count].balance; 
	cout<<"Account added! "<<endl;
	cout<<"Details "<<endl; 
	cout<<"Name: "<<storage[count].names.full_name<<endl;
	cout<<"ID: "<<storage[count].id<<endl;
	cout<<"Initial balance: "<<storage[count].balance<<endl;
	count++;
}

void view_account_details()
{
	int id;
	cout<<"Enter account id: "; 
	cin>>id; 
	for(int i=0 ; i<count ; i++) 
	{
		if(id==storage[i].id) 
		{
			cout<<"Account found! "<<endl; 
			cout<<"Account details below "<<endl;
			split_name(i); 
			cout<<"Account first name: "<<storage[i].names.first_name<<endl; 
			cout<<"Account father name: "<<storage[i].names.father_name<<endl; 
			cout<<"Account grandfather name: "<<storage[i].names.grandfather_name<<endl; 
			cout<<"Account family name: "<<storage[i].names.family_name<<endl; 
			cout<<"Account id "<<storage[i].id<<endl; 
			cout<<"Account balance: "<<storage[i].balance<<endl; 
			return;
		}
	}
	cout<<"Account is not found! "<<endl; 
}

void load_from_file() 
{
	ifstream file("auto.txt"); 
	if(file.is_open()) 
	{
		file>>count;
		for(int i=0 ; i<count ; i++) 
		{
			file.ignore();
			getline(file,storage[i].names.full_name); 
			file>>storage[i].id;
			file>>storage[i].balance; 
		}
	}
	else 
	{
		cout<<"File is not found! "<<endl; 
	}
} 

void delete_account() 
{
	int id;  
	char choice;
	cout<<"Enter the account id: "; 
	cin>>id; 
	for(int i=0 ; i<count ; i++) 
	{
		if(storage[i].id==id) 
		{
			cout<<"The account with the id "<<id<<" found! "<<endl; 
			cout<<"Account details "<<endl; 
			split_name(i); 
			cout<<"Account first name: "<<storage[i].names.first_name<<endl; 
			cout<<"Account father name: "<<storage[i].names.father_name<<endl; 
			cout<<"Account grandfather name: "<<storage[i].names.grandfather_name<<endl; 
			cout<<"Account family name: "<<storage[i].names.family_name<<endl; 
			cout<<"Coniform deletion (Y/N): "; 
			cin>>choice; 
			if(choice=='Y' || choice=='y')
			{
				for(int j=i ; j<count-1 ; j++) 
				{
					storage[j] = storage[j+1]; 
				}
				count--;
				cout<<"Account deleted successfully "<<endl; 
				break;
			}
			else 
			{
				cout<<"Deletion cancelled! "<<endl;
			}
		}
	}
}

void transfer_amount() 
{
	string transfer; 
	int id,transfer_id; 
	float amount;
	accounts n;
	cout<<"Enter your account name: "; 
	cin.ignore(); 
	getline(cin , n.names.full_name);
	cout<<"Enter account id: "; 
	cin>>id; 
	for(int i=0 ; i<count ; i++) 
	{
		if(n.names.full_name==storage[i].names.full_name && id==storage[i].id) 
		{

			cout<<"Account found! "<<endl; 
			if(storage[i].balance<=0) 
			{
				cout<<"insufficient balance! "<<endl; 
				return;
			}
			cout<<"Enter the name of transfer account: "; 
			cin.ignore();
			getline(cin , transfer); 
			cout<<"Enter the id of the transfer: "; 
			cin>>transfer_id;
			for(int j=0 ; j<count ; j++) 
			{
				if(transfer==storage[j].names.full_name && transfer_id==storage[j].id) 
				{
					if(storage[j].id==id) 
					{
						cout<<"That is the same account entered! "<<endl; 
						return;
					}
					cout<<"Transfer account found! "<<endl; 
					cout<<"Transfer account details "<<endl; 
					split_name(j);
					cout<<"Account first name: "<<storage[j].names.first_name<<endl; 
					cout<<"Account father name: "<<storage[j].names.father_name<<endl; 
					cout<<"Account grandfather name: "<<storage[j].names.grandfather_name<<endl; 
					cout<<"Account family name: "<<storage[j].names.family_name<<endl; 
					cout<<"Enter the amount transfer: "; 
					cin>>amount;
					if(amount<=0)
					{
						cout<<"Amount cannot be negative or equal to 0"<<endl; 
						return;
					}
					if(storage[i].balance<amount) 
					{
						cout<<"insufficient balance! "<<endl; 
						return;
					}
					storage[i].balance -= amount; 
					storage[j].balance += amount; 
					cout<<"Transfer successful! "<<endl; 
					return;
				}
			}
		}
	}
	cout<<"Account not found! "<<endl; 
}

void split_name(int i)
{
	stringstream split(storage[i].names.full_name); 
	split>>storage[i].names.first_name>>storage[i].names.father_name>>storage[i].names.grandfather_name>>storage[i].names.family_name;
}


