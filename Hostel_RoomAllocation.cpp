#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
#include<algorithm>   //for sorting
#include<sstream>     //string to int
using namespace std;
int counter=0;
struct student
{
	string name;
	string rno;//reg no
	int roomno=-1;// room no
	int marks;
}s[10];
bool acompare(student lhs,student rhs) { return lhs.marks > rhs.marks; }
void showallremaining(int i)// displays the unallocated students
{
    for(;i<counter;i++)
    {
    	if(s[i].roomno==-1)
    	{
    		cout<<s[i].name<<"\t";
    		cout<<s[i].rno<<"\n";
		}
	}
}
void getfiledetails()
 {
 	ifstream file("details.txt");
 	string Name;
 	getline(file,Name);
   while(getline(file,Name))
    {
	  int i=0;string temp;string name;// here name is different than Name
      while(isalpha(Name[i])||isdigit(Name[i]))
      {
      	temp.push_back(Name[i]);
      	i++;
	  }
	  s[counter].name=temp;
	  temp.clear();
	  while(!(isalpha(Name[i])||isdigit(Name[i])))
	  {
	  	i++;
	  }
	  while(isalpha(Name[i])||isdigit(Name[i]))
      {
      	temp.push_back(Name[i]);
      	i++;
	  }
	  s[counter].rno=temp;
      while(!(isalpha(Name[i])||isdigit(Name[i])))
	  {
	  	i++;
	  }
	  temp.clear();
	  while(isalpha(Name[i])||isdigit(Name[i]))
      {
      	temp.push_back(Name[i]);
      	i++;
	  }
	   stringstream obj(temp);
	   int x=0;
	   obj>>x;
      s[counter].marks=x;
      counter++;
    }
    file.close();
}
void display()
{
    cout<<"Name"<<"   "<<"Reg no"<<"  "<<"Marks"<<endl;
	for(int i=0;i<counter;i++)
	{
		cout<<s[i].name<<"\t";
		cout<<s[i].rno<<"\t";
		cout<<s[i].marks<<"\n";
	}
}
void roomallotment()
{
	int roomtype,rno=1;
	int nosl=counter;// no of student left in room allocation
	cout<<nosl<<"is nosl";
	for(int i=0;i<counter;i++)
	{
		if(s[i].roomno==-1)
		{
			s[i].roomno=rno;
			cout<<"\n\nWelcome "<<s[i].name<<" to the room allotment program\n";
			here:
			cout<<"You have 4 options to choose between rooms\n1BED\n2BED\n3BED\n4BED\n";
			cin>>roomtype;
			if(roomtype>nosl)
			{
				cout<<"\Failed\nyou can choose maximum "<<nosl<<" as your roommate\n";
				goto here;
			}
			for(int j=0;j<roomtype-1;j++)   //j<roomtype-1 ...how many times loop will run based on choice of roomtype
			{
				cout<<"\nyou have following may-be-future roommates left\n";
				showallremaining(i);
				cout<<"\nenter your friend's registeration number:";
				string frreg;
				cin>>frreg;
				int flag=0;
				for(int k=i+1;k<10;k++)  //k=i+1 ...to compare the reg no of roommates except for the one whose counselling is on
				{
					if(s[k].roomno==-1)
					{
						if(frreg.compare(s[k].rno)==0)
						{
							s[k].roomno=rno;
							cout<<"\nsuccessfully found your roommate and allocated room with you";
							flag=1;
							break;
						}
					}
				}
				if(flag==0)
				{
					cout<<"entered regno doesn't exist or is not available";
					j--;
				}
			}
			cout<<"\n"<<s[i].name<<" your allotment is successful\n"<<"you got roomno: "<<rno<<"\nThank you :)\n";
			rno++;
			nosl=nosl-roomtype;
		}// IF ENDS
	} //FOR ENDS


}

void makeroomalotmentfile()
{
	fstream file("rooms.txt");
 	file<<"Name\tRegNo\troomNo\n\n";
	cout<<"\nName\tRegNo\troomNo\n\n";
	for(int i=0;i<counter;i++)
	{
		if(s[i].roomno>0)
		file<<s[i].name<<"\t";
		cout<<s[i].name<<"\t";
		file<<s[i].rno<<"\t";
		cout<<s[i].rno<<"\t";
		file<<s[i].roomno<<"\n";
		cout<<s[i].roomno<<"\n";
	}
	file.close();
}


int main()
{
      system("color 0B ") ;
      getfiledetails();
      sort(s,s+10,acompare);
      display();
      roomallotment();
      makeroomalotmentfile();

}//MAIN ENDS






