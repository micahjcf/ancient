//Advanced Kitty
//by Micah Fullerton
//started on 1/27/04
//finished on 1/27/04

#include<iostream.h>

void CostomizeAnimal();

//******************************** classes ******************************

class Animal
{
public:
	Animal(int, int, int, int, float);
	~Animal();
	int getAge() const {return age;}
	int getDay() const {return dateDay;}
	int getMonth() const {return dateMonth;}
	int getYear() const {return dateYear;}
	float getWeight() const {return weight;}
private:
	int age;
	int dateDay;
	int dateMonth;
	int dateYear;
	float weight;
};

//******************* constructors ***** deconstructors*****************

Animal::Animal(int inAge, int inDateYear, int inDateMonth, int inDateDay, float inWeight)
{
	age=inAge;
	dateDay=inDateDay;
	dateMonth=inDateMonth;
	dateYear=inDateYear;
	weight=inWeight;
}

Animal::~Animal()
{
}

//***************************** CostomizeCat() ***************************

void CostomizeAnimal(unsigned int choise)
{
	int inAge, inDateYear, inDateMonth, inDateDay;
	float inWeight;

	if(choise==1)
		cout<<"\n\nTime to costomize your kitty...";
	else
		cout<<"\n\nTime to costomize your puppy...";

	cout<<"\n\tEnter its age: ";
	cin>>inAge;

	cout<<"\n\tEnter the year it was born in: ";
	cin>>inDateYear;

	cout<<"\n\tEnter the month it was born in: ";
	cin>>inDateMonth;

	cout<<"\n\tEnter the day it was born on: ";
	cin>>inDateDay;

	cout<<"\n\tEnter its weight in pounds: ";
	cin>>inWeight;

	if(choise==1)
	{
	Animal Kitty(inAge, inDateYear, inDateMonth, inDateDay, inWeight);

	cout<<"\nYour kitten is " <<Kitty.getAge() <<" years old.";
	cout<<"\nIt was born on "<<Kitty.getDay() <<"/" <<Kitty.getMonth() <<"/";
			cout<<Kitty.getYear();
	cout<<"\nIt is also " <<Kitty.getWeight() <<" pounds.\n\n";
	}
	else
	{
	Animal Doggy(inAge, inDateYear, inDateMonth, inDateDay, inWeight);

	cout<<"\nYour puppy is " <<Doggy.getAge() <<" years old.";
	cout<<"\nIt was born on "<<Doggy.getDay() <<"/" <<Doggy.getMonth() <<"/";
			cout<<Doggy.getYear();
	cout<<"\nIt is also " <<Doggy.getWeight() <<" pounds.\n\n";
	}
}

//***************************** MAIN ***********************************

int main()
{
	unsigned int input;
	cout<<"Advanced Kitty\nBy Micah Fullerton\n\n";
	cout<<"(0)Quit   (1)Make a Kitty   (2)Make a Puppy :";
	cin>>input;

	switch(input)
	{
	case 0:
		return 0;
		break;
	case 1:
		CostomizeAnimal(input);
		break;
	case 2:
		CostomizeAnimal(input);
		break;
	default:
		cout<<"Invalid entery\n\n";
		break;
	}
	return 0;
}
