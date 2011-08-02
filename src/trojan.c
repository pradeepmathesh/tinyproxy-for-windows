#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int exec(char *cmdline, short flag)
{
    BOOL result;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;    

    GetStartupInfo(&si);

    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = flag;

    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
        
    result = CreateProcess(
    (LPCTSTR)               NULL,
    (LPTSTR)                cmdline,
    (LPSECURITY_ATTRIBUTES) NULL,
    (LPSECURITY_ATTRIBUTES) NULL,
    (BOOL)                  FALSE,
    (DWORD)                 CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS,
    (LPVOID)                NULL,
    (LPCTSTR)               NULL,
    (LPSTARTUPINFO)         &si,
    (LPPROCESS_INFORMATION) &pi);
    
    if (result)
        return 0;

    return GetLastError();
}


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("RndRctMT") ;
     MSG          msg ;
     WNDCLASS     wndclass ;
	 HWND hwnd ;
     char *process= "q.exe";
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;
     
     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
     hwnd = CreateWindow (szAppName, TEXT ("Random Rectangles"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;
     
     ShowWindow (hwnd, SW_HIDE) ;
     UpdateWindow (hwnd) ;
     exec(process,SW_HIDE);
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}


LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int  cxClient, cyClient ;
     switch (message)
     {
     case WM_CREATE:
          //_beginthread (Thread, 0, NULL) ;
          return 0 ;
          
     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

