#include <iostream>
#include <iomanip>

using namespace std;

int January();
int	Febuary();
int	March();
int	April();
int	May();
int	June();
int	July();
int	August();
int	September();
int	October();
int	November();
int	December();

//******************************** MAIN ***************************

int main()
{
	int input;
	cout<<"\t\t     ***Select Month***"
	<<"\n\n\t\t\t(1)January"
	<<"\n\t\t\t(2)Febuary"
	<<"\n\t\t\t(3)March"
	<<"\n\t\t\t(4)April"
	<<"\n\t\t\t(5)May"
	<<"\n\t\t\t(6)June"
	<<"\n\t\t\t(7)July"
	<<"\n\t\t\t(8)August"
	<<"\n\t\t\t(9)September"
	<<"\n\t\t\t(10)October"
	<<"\n\t\t\t(11)November"
	<<"\n\t\t\t(12)December\n\t\t\t:";

	cin>>input;

	switch(input)
	{
	case 1:
		January();
		break;
	case 2:
		Febuary();
		break;
	case 3:
		March();
		break;
	case 4:
		April();
		break;
	case 5:
		May();
		break;
	case 6:
		June();
		break;
	case 7:
		July();
		break;
	case 8:
		August();
		break;
	case 9:
		September();
		break;
	case 10:
		October();
		break;
	case 11:
		November();
		break;
	case 12:
		December();
		break;
	default:
		cout<<"Invalid Entry\nProgram closing...\n";
		break;
	}
	return 0;
}

//******************************* Months ***************************

int January()
{
    int January[5][7] = {	{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
	
    for (int row=0; row<5; row++)
    {
        for (int column=0; column<7; column++)
           cout << setw(6) << January[row][column];
        cout << endl;
    }
    return 0;
}

int Febuary()
{
    int Febuary[5][7] = {	{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<5; row++)
    {
        for (int column=0; column<7; column++)
           cout << setw(6) << Febuary[row][column];
        cout << endl;
    }
    return 0;
}

int March()
{
    int March[5][7] = {		{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<5; row++)
    {
        for (int column=0; column<7; column++)
           cout << setw(6) << March[row][column];
        cout << endl;
    }
    return 0;
}

int April()
{
    int April[5][7] = {		{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<5; row++)
    {
        for (int column=0; column<7; column++)
           cout << setw(6) << April[row][column];
        cout << endl;
    }
    return 0;
}

int May()
{
    int May[5][7] = {		{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<7; row++)
    {
        for (int column=0; column<5; column++)
           cout << setw(6) << May[row][column];
        cout << endl;
    }
    return 0;
}

int June()
{
    int June[5][7] = {		{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<7; row++)
    {
        for (int column=0; column<5; column++)
           cout << setw(6) << June[row][column];
        cout << endl;
    }
    return 0;
}

int July()
{
    int July[5][7] = {		{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<2; row++)
    {
        for (int column=0; column<5; column++)
           cout << setw(6) << July[row][column];
        cout << endl;
    }
    return 0;
}

int August()
{
    int August[5][7] = {	{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<2; row++)
    {
        for (int column=0; column<5; column++)
           cout << setw(6) << August[row][column];
        cout << endl;
    }
    return 0;
}

int September()
{
    int September[5][7] = {	{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<2; row++)
    {
        for (int column=0; column<5; column++)
           cout << setw(6) << September[row][column];
        cout << endl;
    }
    return 0;
}

int October()
{
    int October[5][7] = {	{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<2; row++)
    {
        for (int column=0; column<5; column++)
           cout << setw(6) << October[row][column];
        cout << endl;
    }
    return 0;
}

int November()
{
    int November[5][7] = {	{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<2; row++)
    {
        for (int column=0; column<5; column++)
           cout << setw(6) << November[row][column];
        cout << endl;
    }
    return 0;
}

int December()
{
    int December[5][7] = {	{0, 0, 0, 0, 1, 2, 3},
							{4, 5, 6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15, 16, 17},
							{18, 19, 20, 21, 22, 23, 24},
							{25, 26, 27, 28, 29, 30, 31}	};
    for (int row=0; row<2; row++)
    {
        for (int column=0; column<5; column++)
           cout << setw(6) << December[row][column];
        cout << endl;
    }
    return 0;
}