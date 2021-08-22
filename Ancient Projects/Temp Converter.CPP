//Temperature converter
//by Micah Fullerton
//started on 1/2/04
//completed on 1/4/04

#include<iostream.h>
#include<cstdlib>				//for system("PAUSE")

float Convert(float TempFer);
float ReConverter(float TempCel);

main()
{
	int choise;
	float TempCel, TempFer;
	cout<<"Temperature converter\nby Micah Fullerton\n\n";

	while(choise!=0)
	{
	cout<<"(0)Quit   (1)Convert into Celcuis   (2)Convert into Ferenheit    :";
	cin>>choise;

	switch(choise)
	{
	case 0:
		cout<<'\n';
		return 0;
		break;
	case 1:
		cout<<"\nEnter a Ferenheit temperature to convert: ";
		cin>>TempFer;
		cout<<'\n';
		TempCel=Convert(TempFer);
		cout<<"That is ";
		cout<<TempCel;
		cout<<" in celcius\n\n";
		break;
	case 2:
		cout<<"\nEnter a celcuis temperature to convert: ";
		cin>>TempCel;
		cout<<'\n';
		TempFer=ReConverter(TempCel);
		cout<<"That is ";
		cout<<TempFer;
		cout<<" in ferenheit\n\n";
		break;
	default:
		cout<<"\nInvalid Entry...\n";
		cout<<"Program breaking execution\n\n";
		break;
	}
	}
	system("PAUSE");
	return 0;
}

float Convert(float TempFer)
{
	float TempCel;
	TempCel=((TempFer-32)*5)/9;
	return TempCel;
}

float ReConverter(float TempCel)
{
	float TempFer;
	TempFer=((TempCel*9)/5)+32;
	return TempFer;
}