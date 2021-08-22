#ifndef _SYSTEM_
#define _SYSTEM_

void DrawScrn(DWORD color)
{
	for(int y=0; y<50; y++)
	{
		Text(0, y, "*", color);
		Text(79, y, "*", color);
	}
	for(int x=1; x<79; x++)
	{
		Text(x, 0, "*", color);
		Text(x, 49, "*", color);
	}
	Text(0,0,"");
}

void WelcomeScrn()
{
	cout<<"Maximize this DOS console by pushing Alt-Enter\n\n";
	cout<<"Then press the space bar to continue.";

	KB_WAIT(VK_SPACE);

	ConsoleSetUp();
	ClrScrn();

	Text(32, 4, "Snakerz", Green_I);
	Text(30, 6, "Version:", Blue_I);
	Text(39, 6, "1", Yellow_I);
	Text(28, 8, "Programmed by:");

	for(int i=0; i<4; i++)
	{
		Text(28, 10, "Micah Fullerton", Red);
		cout<<endl;
		Sleep(250);
		Text(28, 10, "Micah Fullerton", Red_I);
		//Text(28, 10, "Micah Fullerton", B_Red | Red_I);
		cout<<endl;
		Sleep(250);
	}
	Text(30, 20, "Press Space");
	KB_WAIT(VK_SPACE);

	ClrScrn();
}

void MainMenu(bool &done)
{
	while(!done)
	{
		DrawScrn(Blue_I);

		Text(3, 3, "[ ] New Game", Teal_I);
		Text(3, 4, "[ ] Options", Teal_I);
		Text(3, 5, "[ ] Exit", Teal_I);
		Text(4, 3, "*", Green_I);

		int Y = 3;

		do{
			GetKeyboardInput();

			switch(kb.dwKeyPressed)
			{
			case VK_RETURN:
				break;
			case VK_UP:
				if(Y != 3)
				{
					Text(4, Y, " ");
					Text(4, --Y, "*", Green_I);
				}
				break;
			case VK_DOWN:
				if(Y != 5)
				{
					Text(4, Y, " ");
					Text(4, ++Y, "*", Green_I);
				}
				break;
			default:
				break;
			}
		}while(kb.dwKeyPressed != VK_RETURN);

		switch(Y)
		{
		case 3:
			SetUp();
			Engine();
			break;
		case 4:
			//Options();
			break;
		case 5:
			done = true;
			break;
		default:	// impossible event
			break;
		}
	}
}

#endif