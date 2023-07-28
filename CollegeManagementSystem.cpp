#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;
void gen();
class student{
public:
    int roll;
    char name[80];
    vector<string> course;
    float gpa;
    char branch[4];
    vector<string> club;
    void input(){
			cout<<"\n Enter name: ";
			fflush(stdin);
			gets(name);
			cout<<"\n Enter roll no: ";
			fflush(stdin);
			cin>>roll;
			cout<<"\n Enter gpa: ";
			fflush(stdin);
			cin>>gpa;
			cout<<"\n Enter Branch: ";
			fflush(stdin);
			gets(branch);
			int n;
			cout<<"\n Enter number of clubs joined: ";
			cin>>n;
			for(int i=0;i<n;i++){
                string temp; cin>>temp;
                club.push_back(temp);
			}
			cout<<"\n Enter number of courses enrolled in: ";
			cin>>n;
			for(int i=0;i<n;i++){
                string temp; cin>>temp;
                course.push_back(temp);
			}
		}
    void display()
		{
			system("CLS");
			cout<<"\t\tDisplay Records";
			cout<<"\n";
			cout<<"\n Name - "<<name;
			cout<<"\n Reg no. - "<<roll;
			cout<<"\n gpa: "<<gpa;
			cout<<"\n Branch - "<<branch;
			cout<<"\n Club List:\n ";
			for(auto &it:club)
            cout<<it<<" ";
            cout<<"\n Course List: \n ";
            for(auto &it:course)
            cout<<it<<" ";
            cout<<endl;
			system("PAUSE");
			system("CLS");
		}
    void disC(){
        cout<<"\n Course List: \n";
            for(auto &it:course)
                cout<<it<<" ";
            cout<<endl;
			system("PAUSE");
			system("CLS");
    }
    void disClub(){
        cout<<"\n Club List: \n";
            for(auto &it:club)
                cout<<it<<" ";
            cout<<endl;
			system("PAUSE");
			system("CLS");
    }
    void tt(){
        cout<<"==========================================================================================================\n";
        cout<<"|DAY/TIME|8:00-9:00|9:00-10:00|10:00-11:00|11:00-12:00|12:00-1:00|1:00-2:00|2:00-3:00|3:00-4:00|4:00-5:00|"<<endl;
        cout<<"|========================================================================================================|"<<endl;
        cout<<"|MON     |         |          |AME        |           |PF        |         |ES LAB   |         |AME Tut. |"<<endl;
        cout<<"|TUES    |         |AME       |EDA        |IIOT       |          |         |         |         |IIOT LAB |"<<endl;
        cout<<"|WED     |         |PF        |ES         |IIOT       |EDA       |         |         |AME tut. |PF       |"<<endl;
        cout<<"|THURS   |         |PF        |EVS        |AME        |ES        |         |EDA LAB  |         |EDA LAB  |"<<endl;
        cout<<"|FRI     |         |IIOT      |ES         |EDA        |EVS       |         |PF LAB   |         |IIOT LAB |"<<endl;
        cout<<"==========================================================================================================\n";
        system("PAUSE");
			system("CLS");
    }
    void getgpa(){
        cout<<" \ngpa is: "<<gpa<<"\n ";
        system("PAUSE");
        system("CLS");
    }
};

void passwd(char *ar,int Max)
    {
        char ch;
        int x=0;
        while(1)
        {
            ch=getch();
            if(ch==13)                  //13 ascii code of enter or vertical tab
            {
                ar[x]='\0';
                break;
            }
            if(ch==8 && x!=0)           //8 ascii code of back space
            {
                cout<<"\b \b";
                if(x<=Max && x>0)
                    x--;
            }
            else if(x<Max && ch!=8)
            {
                cout<<"*";
                ar[x]=ch;
                x++;
            }
        }
    }


vector <student>v;
int search_reg(long int roll,int &i);
void get_file(){
	student x;
	int i=0;
	fstream f;
	f.open("clog.txt",ios::in);
	if(f)
	{
		f.read((char *) &x,sizeof(class student));
		while(!f.eof())
		{
			v.push_back(x);
			f.read((char *) &x,sizeof(class student));
		}
	}
	else
		;
	f.close();
}
void bubblesort()
{
	int i,j;
	student x;
	for(i=0;i<v.size();i++)
		for(j=0;j<v.size()-i-1;j++)
			if(v[j].roll>v[j+1].roll)
			{
				x=v[j];
				v[j]=v[j+1];
				v[j+1]=x;
			}
}
void insert_new()
{
	char ch='y';
	int ta;
	while(ch=='y')
	{
		fflush(stdin);
		student x;
		x.input();
		if(search_reg(x.roll,ta)==0)
			v.push_back(x);
		else
			cout<<"\nTHE REGISTRATION NO. ALREADY EXIST!!!\nCANNOT ADD";
		cout<<"\n Press [Y] to enter more: ";
		cin>>ch;
		fflush(stdin);
	}
}
void write_file()
{
	bubblesort();
	fstream f;
	f.open("clog.txt",ios::out);
	for(int i=0;i<v.size();i++)
	{
		student x=v[i];
		f.write((char *) &x,sizeof(class student));
	}
	f.close();
}
int search_reg(long int roll,int &i)
{
	int ta=0;
	for(i=0;i<v.size();i++)
		if(v[i].roll==roll){
			ta=1;
			break;
		}
	return ta;
}
int search_name(string name,vector<int> &vi){
	int i,ta=0;
	for(i=0;i<v.size();i++)
		if(v[i].name==name)
		{
			ta=1;
			vi.push_back(i);
		}
	return ta;
}
int search_branch(string branch,vector<int> &vj){
	int i,ta=0;
	for(i=0;i<v.size();i++)
		if(v[i].branch==branch){
			ta=1;
			vj.push_back(i);
		}
	return ta;
}
void search_and_show()
{
	int ch,i,ta=0;
	char name[80],branch[50];
	vector <int>vi;
	vector <int>vj;
	long int reg;
	poi:
	cout<<"\n1.Press to search reg no."
	<<"\n2.Press to search name"
	<<"\n3.Press to search branch\n ";
	cin>>ch;
	switch(ch)
	{
		case 1:
			cout<<"\nEnter reg no.: ";
			cin>>reg;
			if(search_reg(reg,i)==1)
				v[i].display();
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		case 2:
			cout<<"\nEnter name: ";
			fflush(stdin);
			gets(name);
			if(search_name(name,vi)==1)
			{
				for(int j=0;j<vi.size();j++)
					v[vi[j]].display();
			}
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		case 3:
			cout<<"\nEnter branch: ";
			fflush(stdin);
			gets(branch);
			if(search_branch(branch,vj)==1)
			{
				for(int j=0;j<vj.size();j++)
					v[vj[j]].display();
			}
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		default:
			cout<<"\nWrong CHOICE!!!";
			system("PAUSE");
			goto poi;
	}
}
void showtt(){
    system("CLS");
    student x;
    x.tt();
}
void showCourse(){

int ch,i,ta=0;
	char name[80],branch[50];
	vector <int>vi;
	vector <int>vj;
	long int reg;
	poi:
	cout<<"\n1.Press to search reg no."
	<<"\n2.Press to search name\n Enter Choice: ";
	cin>>ch;
	switch(ch){
		case 1:
			cout<<"\nEnter reg no.: ";
			cin>>reg;
			if(search_reg(reg,i)==1)
				v[i].disC();
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		case 2:
			cout<<"\nEnter name: ";
			fflush(stdin);
			gets(name);
			if(search_name(name,vi)==1)
			{
				for(int j=0;j<vi.size();j++)
					v[vi[j]].disC();
			}
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		default:
			cout<<"\nWrong CHOICE!!!";
			goto poi;
	}
}
bool passcheck(char arr[5]){
    if(arr[0]=='a'&&arr[1]=='d'&&arr[2]=='m'&&arr[3]=='i'&&arr[4]=='n')
        return 1;
    return 0;
}
void show(){
   // system("CLS");
	int i;
	for(i=0;i<v.size();i++)
		v[i].display();
   // system("PAUSE");
   // system("CLS");
}
void delete_data(){
	int i,j;
	long int reg;
	vector <student>::iterator p=v.begin();
	cout<<"\nEnter Reg. no.: ";
	cin>>reg;
	if(search_reg(reg,i)==1){
		student x=v[i];
		cout<<"\nThe following data is being deleted";
		x.display();
		p+=i;
		v.erase(p,p+1);
	}
}
void showGPA(){

int ch,i,ta=0;
	char name[80],branch[50];
	vector <int>vi;
	vector <int>vj;
	long int reg;
	poi:
	cout<<"\n1.Press to search reg no."
	<<"\n2.Press to search name\n Enter Choice: ";
	cin>>ch;
	switch(ch){
		case 1:
			cout<<"\nEnter reg no.: ";
			cin>>reg;
			if(search_reg(reg,i)==1)
				v[i].getgpa();
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		case 2:
			cout<<"\nEnter name: ";
			fflush(stdin);
			gets(name);
			if(search_name(name,vi)==1)
			{
				for(int j=0;j<vi.size();j++)
					v[vi[j]].getgpa();
			}
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		default:
			cout<<"\nWrong CHOICE!!!";
			goto poi;
	}
}
void edit_data()
{
	int i,j;
	long int reg;
	vector <student>vi;
	cout<<"\nEnter Reg. no.: ";
	cin>>reg;
	if(search_reg(reg,i)==1)
	{
		cout<<"\nEnter new data:";
		fflush(stdin);
		v[i].input();
	}
}
void admin(){
    system("CLS");
    passi:
    char pass[10];
    cout<<" Enter Admin password: ";
    passwd(pass,10);
   // cin>>pass;
    if(passcheck(pass)){
            adminscr:
    system("CLS");
	int i;
        system("CLS");
        cout<<"\t\t\t=========================================\n";
		cout<<"\t\t\t|       College Management System       |\n";
		cout<<"\t\t\t=========================================\n";
		cout<<"\t\t\t|                                       |";
		cout<<"\n\t\t\t| Enter <1> to Add new student          |"
			<<"\n\t\t\t| Enter <2> to Display all student      |"
			<<"\n\t\t\t| Enter <3> to Remove student           |"
			<<"\n\t\t\t| Enter <4> to Edit student             |"
			<<"\n\t\t\t| Enter <5> to Search student           |"
			<<"\n\t\t\t| Enter <0> to Exit                     |"
			<<"\n\t\t\t|                                       |"
			<<"\n\t\t\t=========================================\n";
		cout<<"\n\n\t\t\tEnter Your Choice:";
		cin>>i;
		switch(i)
		{
			case 1 :
				insert_new();
                goto adminscr;
				break;
			case 2 :
				show();
			goto	adminscr;
				break;
			case 3 :
				delete_data();
				write_file();
				goto adminscr;
				break;
			case 4 :
				edit_data();
				goto adminscr;
				break;
			case 5 :
				search_and_show();
				goto adminscr;
				break;

			case 0 :
			    write_file();
				gen();
			//    goto adminscr;
			//	terminate();
				break;
			default :
				cout<<"\nWRONG CHOICE!!!\nTRY AGAIN";
		}}
		else{
            cout<<"\n Wrong password!!!\n ";
            goto passi;
		}
}
void clubList(){
    int ch,i,ta=0;
	char name[80],branch[50];
	vector <int>vi;
	vector <int>vj;
	long int reg;
	poi:
	cout<<"\n1.Press to search reg no."
	<<"\n2.Press to search name\n Enter Choice: ";
	cin>>ch;
	switch(ch){
		case 1:
			cout<<"\nEnter reg no.: ";
			cin>>reg;
			if(search_reg(reg,i)==1)
				v[i].disClub();
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		case 2:
			cout<<"\nEnter name: ";
			fflush(stdin);
			gets(name);
			if(search_name(name,vi)==1)
			{
				for(int j=0;j<vi.size();j++)
					v[vi[j]].disClub();
			}
			else
				cout<<"\nRecord NOT FOUND!!!";
			break;
		default:
			cout<<"\nWrong CHOICE!!!";
			goto poi;
	}
}
void stu(){
    stuscr:
	int i;
        system("CLS");
        cout<<"\t\t\t===========================================\n";
		cout<<"\t\t\t|        College Management System        |\n";
		cout<<"\t\t\t===========================================\n";
		cout<<"\t\t\t|                                         |";
		cout<<"\n\t\t\t| Enter <1> View Subject List             |"
			<<"\n\t\t\t| Enter <2> Display Time Table            |"
			<<"\n\t\t\t| Enter <3> Display Club List             |"
			<<"\n\t\t\t| Enter <4> Display Academic Performance  |"
            <<"\n\t\t\t| Enter <0> to Exit                       |"
			<<"\n\t\t\t|                                         |"
			<<"\n\t\t\t===========================================";
		cout<<"\n\n\t\t\tEnter Your Choice:";
		cin>>i;
		switch(i)
		{
			case 1 :
				showCourse();
				goto stuscr;
				break;
			case 2 :
				showtt();
				goto stuscr;
				break;
			case 3 :
				clubList();
				goto stuscr;
				break;
			case 4 :
				showGPA();
				goto stuscr;
				break;
			case 0 :
			//	write_file();
				gen();
				break;
			default :
				cout<<"\nWRONG CHOICE!!!\nTRY AGAIN";
				system("PAUSE");
				break;
		}
}
void gen(){
     int i;
		system("CLS");
		cout<<"\t\t\t=========================================\n";
		cout<<"\t\t\t|       College Management System       |\n";
		cout<<"\t\t\t=========================================\n";
		cout<<"\t\t\t|                                       |";
		cout<<"\n\t\t\t| Enter <1> Admin Login                 |"
			<<"\n\t\t\t| Enter <2> Student view                |"
		//	<<"\n\t\t\t| Enter <0> to Exit                     |"
			<<"\n\t\t\t|                                       |"
			<<"\n\t\t\t=========================================\n";
		cout<<"\n\n\t\t\tEnter Your Choice:";
		cin>>i;
		switch(i){
			case 1 :
				admin();
				break;
			case 2 :
				stu();
				break;
		/*	case 0 :
				write_file();
				//terminate();
				break;*/
			default :
				cout<<"\nWRONG CHOICE!!!\nTRY AGAIN";
		}
}
int main()
{
	get_file();
	while(1)
	{
        gen();
	}
	return 0;
}
