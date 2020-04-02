#include <windows.h>
#include <stdio.h>

#define plus_op 1
#define minus_op 2
#define multiply_op 3
#define divide_op 4

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void addControls(HWND);
void My_op(HWND,HWND,HWND,int);
HWND input1,input2;
char data1[10],data2[10];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

        case WM_COMMAND: {
            switch (wParam) {
                case plus_op:{
                    My_op(hwnd,input1,input2,1);
                    break;
                }
                case minus_op:{
                    My_op(hwnd,input1,input2,2);
                    break;
                }
                case multiply_op:{
                    My_op(hwnd,input1,input2,3);
                    break;
                }
                case divide_op:{
                    My_op(hwnd,input1,input2,4);
                    break;
                }

            }
        }
            break;

        case WM_CREATE: {
            addControls(hwnd);
            break;
        }
            break;


		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
            break;
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hbrBackground = CreateSolidBrush(RGB(153, 255, 51));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

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

void addControls(HWND hwnd){
    CreateWindow("static","Please input two numbers",WS_VISIBLE|WS_CHILD,
                    20,20,200,20,
                    hwnd,NULL,NULL,NULL);
    input1 = CreateWindow("edit","",WS_VISIBLE|WS_CHILD,
                           45,50,150,20,
                           hwnd,NULL,NULL,NULL);
    input2 = CreateWindow("edit","",WS_VISIBLE|WS_CHILD,
                           45,80,150,20,
                           hwnd,NULL,NULL,NULL);
    CreateWindow("button","+",WS_VISIBLE|WS_CHILD,
                  55,110,25,25,
                  hwnd, (HMENU) plus_op,NULL,NULL);
    CreateWindow("button","-",WS_VISIBLE|WS_CHILD,
                 90,110,25,25,
                 hwnd, (HMENU) minus_op,NULL,NULL);
    CreateWindow("button","*",WS_VISIBLE|WS_CHILD,
                 125,110,25,25,
                 hwnd, (HMENU) multiply_op,NULL,NULL);
    CreateWindow("button","/",WS_VISIBLE|WS_CHILD,
                 160,110,25,25,
                 hwnd, (HMENU) divide_op,NULL,NULL);
}

void My_op(HWND hwnd,HWND input1,HWND input2,int op){
    double rsl;
    char conv[10];
    GetWindowText(input1, &data1[0], 10);
    GetWindowText(input2, &data2[0], 10);
    switch (op){
        case 1: rsl=atof(data1)+atof(data2);
                break;
        case 2: rsl=atof(data1)-atof(data2);
            break;
        case 3: rsl=atof(data1)*atof(data2);
            break;
        case 4: rsl=atof(data1)/atof(data2);
            break;
    }

    sprintf(conv,"%f",rsl);
    MessageBox(hwnd,conv,"Result",MB_OK);
}