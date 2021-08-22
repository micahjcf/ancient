#include<iostream.h>

class cat
{
public:
	cat(int temp);
	~cat();
	void showAge();
	void setAge();
private:
	int age;
};

cat::cat(int temp)
{
	age=temp;
}

cat::~cat()
{
}

void cat::showAge()
{
	cout<<"\nFluffy the cat is " <<age <<" years old";
}

void cat::setAge()
{
	int newAge;
	cout<<"\nEnter the new age for Fluffy :";
	cin>>newAge;
	age=newAge;
	cout<<"\nFluffy the cat is now " <<age <<" years old.";
}

int main()
{
	int input;
	cat fluffy(2);
	cout<<"class tester\nby Micah Fullerton";

	while(input!=0)
	{
	cout<<"\n\n\n(0)Quit   (1)show cats age   (2)change cats age    :";
	cin>>input;

		switch(input)
	{
case 0:
	cout<<"\n\nCloseing...\n\n";
	return 0;
	break;
case 1:
	fluffy.showAge();
	break;
case 2:
	fluffy.setAge();
	break;
default:
	cout<<"\n\nInvalid entry\nProgram now closing...\n\n";
	return 0;
	break;
	}
	}

	return 0;
}

