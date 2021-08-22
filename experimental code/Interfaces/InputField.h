#ifndef MJCF_INPUTFIELD
#define MJCF_INPUTFIELD

class InputField
{
public:
	InputField();
	~InputField(){}

	void Setup(BAR region, COLOR c, char ch, DWORD flags);

	void Run();

private:
	BAR Region;
	COLOR TextColor;
	char BackgroundChar;
	DWORD InputFlags;
	UINT MaxLength;
	string MyText;
	BOOL InputRecived;
};

#endif