#include<windows.h>
#include<cstdlib>
#include<commctrl.h>
#include<string>

class UIObject {
	private:
		HWND parent;
};

class UIButton : private UIObject {
	public:
		UIButton(HWND parent, HINSTANCE instance, int x, int y, int width, int height, bool isDefault, std::string text);
		
		~UIButton();
		
		HWND GetButton();
		int GetId();
	private:
		HWND buttonObj;
		int buttonId;
};



class UITextBox : private UIObject {
	public:
		UITextBox(HWND parent, HINSTANCE instance, int x, int y, int width, int height);
		
		~UITextBox();
		
		HWND GetTextBox();
		int GetId();
		std::string GetText();
	private:
		HWND textBoxObj;
		int textBoxId;
};

class UIText {
	public:
		UIText(HWND parent, HINSTANCE instance, int x, int y, int width, int height, std::string text);
		
		~UIText();
		
		HWND GetTextObj();
		int GetId();
		std::string GetText();
	private:
		HWND textObj;
		int textId;
};




