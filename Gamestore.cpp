#include<conio.h>	
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<string.h>


int itno;
class game
{
 char gname[100];
 int gno;
 float gprice;
 public:
	void getdata()
	{
	 cout<<"\n\nGame Name:";
	 gets(gname);
	 cout<<"\nGame serial No:";
	 cin>>gno;
	 cout<<"\nPrice of game:";
	 cin>>gprice;
	}

	char* returnname()
	{
	 return gname;
	}

	int getitem_no()
	{
	 return gno;
	}

	float getprice()
	{
	 return gprice;
	}

	void modifyprice(float p)
	{
	 gprice=p;
	}

	void putdata()
	{
	 cout<<"\n Game Name:";
	 cout<<gname;
	 cout<<"\n Game serial Number:";
	 cout<<gno;
	 cout<<"\n Price of game:";
	 cout<<gprice<<endl;
	 cout<<"--------------------------------------------------------------------------------";
	}
}
s;


void adddatatonewfile()
{
 ofstream f("file.dat",ios::out|ios::binary);
 char ch;
 do
 {
  s.getdata();
  f.write((char*)&s,sizeof(s));
  cout<<"\n\nINFO ADDED ABOUT NEW GAME!!!";
  cout<<"\n\nDo you want to enter more?(Y/N):";
  cin>>ch;
 }
 while(ch=='y'||ch=='Y');
 f.close();
}


void adddatatoexistingfile()
{
 ofstream f("file.dat",ios::out|ios::binary|ios::app);
 char ch;
 do
 {
  s.getdata();
  f.write((char*)&s,sizeof(s));
  cout<<"\n\nINFO. ADDED ABOUT NEW GAME!!!!";
  cout<<"\n\nDo you want to enter more?(Y/N):";
  cin>>ch;
 }
 while(ch=='y'||ch=='Y');
 f.close();
}



void output()
{
 clrscr();
 cout<<"\n\n_____________________________________MENU_______________________________________";
 ifstream f("file.dat",ios::in|ios::binary);
 while( f.read((char*)&s,sizeof(s)))
 {
  s.putdata();
  cout<<endl;
  cout<<"--------------------------------------------------------------------------------";
 }
 f.close();
}


float buy()
{
 clrscr();
 cout<<"\n\n______________________________________MENU______________________________________";
 ifstream f("file.dat",ios::binary);
 float tprice=0;
 while(f.read((char*)&s,sizeof(s)))
 {
  s.putdata();
  cout<<endl;
  cout<<"------------------------------------------------------------------------------";
 }
 f.close();
 cout<<"\n\nEnter game serial no. you like to buy:";
 cin>>itno;
 ifstream f1("file.dat",ios::binary);
 while( f1.read((char*)&s,sizeof(s)))
 {
  if(s.getitem_no()==itno)
  {
   tprice=tprice+s.getprice();
  }
 }
 f1.close();
 return tprice;
}


void deletefile()
{
 ifstream f("file.dat",ios::in|ios::binary);
 ofstream f1("filenew.dat",ios::out|ios::binary);
 int ano;
 cout<<"\nEnter the game serial no. which you want to delete.:";
 cin>>ano;
 while(f.read((char*)&s,sizeof(s)))
 {
  if(s.getitem_no()!=ano)
  {
   f1.write((char*)&s,sizeof(s));
  }
 }
 f.close();
 f1.close();
 remove("file.dat");
 rename("filenew.dat","file.dat");
}


void passwordforadddatatoexistingfile()
{
 clrscr();
 char pass[4];
 cout<<"\n\nEnter the password:";
 for(int i=0;i<3;i++)
 {
  pass[i]=getch();
  cout<<"*";
 }
 pass[i]='\0';
 if(strcmp(pass,"pqr")==0)
 {
  cout<<"\n\nNOW YOU ARE ENTERING TO THE MASTERCODE ZONE!!!!"<<endl;
  adddatatoexistingfile();
 }
 else
 cout<<"\nACCESS DENIED!!!";
}


void passwordforadddatatonewfile()
{
 clrscr();
 char pass[4];
 cout<<"\n\nEnter the password:";
 for(int i=0;i<3;i++)
 {
  pass[i]=getch();
  cout<<"*";
 }
 pass[i]='\0';
 if(strcmp(pass,"abc")==0)
 {
  cout<<"\n\nNOW YOU ARE ENTERING TO THE MASTERCODE ZONE!!!!"<<endl;
  adddatatonewfile();
 }
 else
 cout<<"\nACCESS DENIED!!!";
}


void bill()
{
 ifstream f("file.dat",ios::in|ios::binary);
 float p=0;
 p=p+buy();
 clrscr();
 cout<<"\n\n______________________________________INVOICE___________________________________";
 cout<<"\nFor any quieries call on:9918707070.";
 cout<<"\nNo return or exchange of goods after their purchase.\n\n";
 while(f.read((char*)&s,sizeof(s)))
 {
  if(s.getitem_no()==itno)
  {
   s.putdata();
   cout<<"\n";
  }
 }
 cout<<"\nYour grand total is :"<<p;
 p=p+p*0.08;
 cout<<"\nYour grand total(Including GST) becomes:"<<p<<" Rupees";
}


void changeprice()
{
 clrscr();
 int sno;
 float p;
 cout<<"\nEnter the serial no. of that game whose price you want to change:";
 cin>>sno;
 fstream f("file.dat",ios::out|ios::in|ios::binary);
 while(f.read((char*)&s,sizeof(s)))
 {
  if(s.getitem_no()==sno)
  {
   cout<<"\nEnter the new price of the game:";
   cin>>p;
   s.modifyprice(p);
   f.seekp(-1*(int)sizeof(s),ios::cur);
   f.write((char*)&s,sizeof(s));
   cout<<"\n\nNew price updated!!!";
   break;
  }
 }
 f.close();
}


void changename()
{
 clrscr();
 char gname1[30],gname2[30];
 fstream f("file.dat",ios::out|ios::in|ios::binary);
 cout<<"\n\nEnter the name of game that you would like to change:";
 gets(gname1);
 while(f.read((char*)&s,sizeof(s)))
 {
  if(strcmpi(s.returnname(),gname1)==0)
  {
   cout<<"\n\nEnter the new game name:";
   gets(gname2);
   strcpy(s.returnname(),gname2);
   f.seekp(-1*(int)sizeof(s),ios::cur);
   f.write((char*)&s,sizeof(s));
   cout<<"\n\nName of game changed!!!";
   break;
  }
 }
 f.close();
}


void menu1()
{
 int choice;
 char ch;
 do
  {
    clrscr();
    cout<<"\n\n\n----------------------------------Game Store------------------------------------\n";
    cout<<"\n\t\tEnter your choice:";
    cout<<"\n\n1-Enter new data.";
    cout<<"\n\n2-Add to existing data.";
    cout<<"\n\n3-Display.";
    cout<<"\n\n4-Change price of any game.";
    cout<<"\n\n5-Change name of any game.";
    cout<<"\n\n6-Delete.";
    cout<<"\n\n7-Exit.";
    cout<<"\n\nYour choice:";
    cin>>choice;
    switch(choice)
		  {
		   case 1:
			    passwordforadddatatonewfile();
			    break;
		   case 2:
			    passwordforadddatatoexistingfile();
			    break;
		   case 3:
			    output();
			    break;
		   case 4:
			    changeprice();
			    break;
		   case 5:
			    changename();
			    break;
		   case 6:
			    deletefile();
			    break;
		   case 7:
			    return;
		   default:
			    cout<<"\n\nWRONG CHOICE!!!!!";
			    break;
		  }
  cout<<"\n\nDo you want to see menu 1 again?(Y/N):";
  cin>>ch;
  }
  while(ch=='y'||ch=='Y');
  return;
}


void passwordformenu1()
{
 clrscr();
 char pass[4];
 cout<<"\n\nEnter the password:";
 for(int i=0;i<3;i++)
 {
  pass[i]=getch();
  cout<<"*";
 }
 pass[i]='\0';
 if(strcmp(pass,"xyz")==0)
 {
  menu1();
 }
 else
 cout<<"\n\nACCESS DENIED!!!!";
}


void menu()
{
 int choice;
 char ch;
 do
 {
  clrscr();
  cout<<"\n\n------------------------------------GAME STORE----------------------------------";
  cout<<"\n\n\t\tEnter your choice:";
  cout<<"\n\n1-Buy a gaming console.";
  cout<<"\n\n2-Enter the staff data.";
  cout<<"\n\n3-Display.";
  cout<<"\n\n4-Exit.";
  cout<<"\n\nYour choice:";
  cin>>choice;
  switch(choice)
		{
		 case 1:
			  bill();
			  break;
		 case 2:
			  passwordformenu1();
			  break;
		 case 3:
			  output();
			  break;
		 case 4:
			  exit(0);
			  break;
		 default:
			  cout<<"\n\nWRONG CHOICE!!!!";
			  break;
		}
  cout<<"\n\nDo you want to see the menu again?(Y/N):";
  cin>>ch;
  }
  while(ch=='y'||ch=='Y');
}


void main()
{
 clrscr();
 menu();
 getch();
}
