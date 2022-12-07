#include "ui.h"
#include <sstream>

// UIButton

UIButton::UIButton(HWND parent, HINSTANCE instance, int x, int y, int width, int height, bool isDefault, std::string text) {
	buttonId = rand();
	
	buttonObj = CreateWindowEx(
	WS_EX_LEFT | WS_EX_LTRREADING, // Set window's extended style
	"BUTTON", // Window class of the object - in this case: Button - which has been registered
	reinterpret_cast <char*> ((char*) text.c_str()), // Window name - in this case the caption of the button
	(isDefault ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON) | BS_TEXT | WS_VISIBLE | WS_CHILD, // Set window style,
	x, y, width, height, // x, y, width, height,
	parent, // Parent for the button to assign to
	(HMENU) buttonId, // hMenu will be button?
	instance,
	NULL
	);
	
	HFONT hFont=CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,"Segoe UI");
	SendMessage(buttonObj, WM_SETFONT, (WPARAM) hFont , true);
	//SendMessage(buttonObj, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
}

UIButton::~UIButton() {
	DestroyWindow(buttonObj);
}

HWND UIButton::GetButton() {
	return buttonObj;
}

int UIButton::GetId() {
	return buttonId;
}

// UITextBox

UITextBox::UITextBox(HWND parent, HINSTANCE instance, int x, int y, int width, int height) {
	textBoxId = rand();
	
	textBoxObj = CreateWindowEx(
	WS_EX_LEFT, // Set window's extended style
	"EDIT", // Window class of the object - in this case: Button - which has been registered
	"", // Window name - in this case the value of the text box
	ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER, // Set window style,
	x, y, width, height, // x, y, width, height,
	parent, // Parent for the button to assign to
	(HMENU) textBoxId, // hMenu will be button?
	instance,
	NULL
	);
	
	
	HFONT hFont=CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,"Segoe UI");
	SendMessage(textBoxObj, WM_SETFONT, (WPARAM) hFont , true);
	// Let textbox use default system font
	//SendMessage(textBoxObj, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
}

UITextBox::~UITextBox() {
	DestroyWindow(textBoxObj);
}

HWND UITextBox::GetTextBox() {
	return textBoxObj;
}

int UITextBox::GetId() {
	return textBoxId;
}

std::string UITextBox::GetText() {
	std::string text;
	std::stringstream stream;
	int len = GetWindowText(GetTextBox(), reinterpret_cast <char*> ((char*) text.c_str()),512);
	stream << "Char length: " << len;
	//MessageBox(GetTextBox(), reinterpret_cast <char*> ((char*) stream.str().c_str()), "Hey...", MB_ICONINFORMATION);
	return text;
}

// UIText
UIText::UIText(HWND parent, HINSTANCE instance, int x, int y, int width, int height, std::string text) {
	textId = rand();
	
	textObj = CreateWindowEx(
	WS_EX_TRANSPARENT, // Set window's extended style
	"STATIC", // Window class of the object - in this case: Button - which has been registered
	reinterpret_cast <char*> ((char*) text.c_str()), // Window name - in this case the value of the text box
	ES_CENTER | WS_CHILD | WS_VISIBLE, // Set window style,
	x, y, width, height, // x, y, width, height,
	parent, // Parent for the button to assign to
	(HMENU) textId, // hMenu will be button?
	instance,
	NULL
	);
	
	
	HFONT hFont=CreateFont (40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,"Segoe UI");
	SendMessage(textObj, WM_SETFONT, (WPARAM) hFont , true);
	// Let textbox use default system font
	//SendMessage(textBoxObj, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
}

UIText::~UIText() {
	DestroyWindow(textObj);
}

HWND UIText::GetTextObj() {
	return textObj;
}

int UIText::GetId() {
	return textId;
}

std::string UIText::GetText() {
	std::string text;
	std::stringstream stream;
	int len = GetWindowText(GetTextObj(), reinterpret_cast <char*> ((char*) text.c_str()),512);
	stream << "Char length: " << len;
	//MessageBox(GetTextBox(), reinterpret_cast <char*> ((char*) stream.str().c_str()), "Hey...", MB_ICONINFORMATION);
	return text;
}

