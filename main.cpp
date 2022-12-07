#include "ui.h"
#include <windows.h>
#include <sstream>
#include <string>


#define IDC_TEXTBOX 1000
#define IDC_BUTTON 1001
#define IDC_STATIC 1002

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


// NOTE: EVERYTHING IS A WINDOW: BUTTONS, TEXTBOXES, TOOLBARS, WINDOW INSIDE WINDOWS
// EVERYTHING!!!!


HWND hMainWindow; /* A 'HANDLE', hence the H, or a pointer to our window */
HINSTANCE hMainInstance; // Main instance of the window
UIButton* button;
UITextBox* textbox;
UIText* text;

/*
RECT screen;
GetWindowRect((HWND)GetDesktopWindow(),&screen);
*/
int wWidth = 300;
int wHeight = 200;



/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: { // UPON WINDOW CREATION
			hMainWindow = hwnd;
			button = new UIButton(hwnd, hMainInstance, 20, 120, wWidth - 50, 30, false, "Greet!");
			textbox = new UITextBox(hwnd, hMainInstance, 20, 80, wWidth - 50, 30);
			text = new UIText(hwnd, hMainInstance, 20,20,wWidth - 50,50,"Greeting Machine");
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			delete button;
			delete textbox;
			PostQuitMessage(0);
			break;
		}
		
		case WM_LBUTTONUP: { // HANDLING LEFT MOUSE UP
			MessageBox(hwnd,"You released the LMB!","LMOUSE released!", MB_OK);
			break;
		}
		
		case WM_KEYDOWN: // HANDLING KEYPRESS CHANGES
			MessageBox(hwnd,"You pressed a key!","Key press detected", MB_OK);
			break;
		
		case WM_COMMAND: { // HANDLING WINDOW COMMANDS - aka interacive events
			if (LOWORD(wParam) == button->GetId()) {
				std::stringstream stream;
				std::string text = textbox->GetText();
				stream << "Hello, " << text.c_str() << "!";
				// Spaghetti way to check an empty string
				// Checks whether the character dereferenced at address of the char array is not null
				if (*text.c_str() != '\0') { 
					MessageBox(hwnd, reinterpret_cast <char*> ((char*) stream.str().c_str()), "Hey...", MB_ICONINFORMATION);
				} else { // Else, print the below message
					MessageBox(hwnd, "Uhm...hello Mr. No Name?", "Bruh", MB_ICONINFORMATION);
				}
				
				//MessageBox(hwnd, "Hello cac ban!", "Xin chao!", MB_ICONINFORMATION);
				break;
			}
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) { // Registering new class for such window component
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hMainWindow = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Greeting Machine",WS_VISIBLE| WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN) - wWidth) / 2.0, /* x */
		(GetSystemMetrics(SM_CYSCREEN) - wHeight) / 2.0, /* y */
		wWidth, /* width */
		wHeight, /* height */
		NULL,NULL,hInstance,NULL);

	if(hMainWindow == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	hMainInstance = hInstance;

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
