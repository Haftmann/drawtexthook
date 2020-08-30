#include <windows.h>

void WinMainCRTStartup() {
  DrawText(0,0,0,0,0);		// zum Setzen eines Breakpoints
  DrawTextEx(0,0,0,0,0,0);	// zum Setzen eines Breakpoints
  HWND w=CreateWindowEx(0,TEXT("Static"),TEXT("Test123"),WS_OVERLAPPEDWINDOW|WS_VISIBLE,
  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
  0,0,0,0);
  ShowWindow(w,SW_SHOWDEFAULT);
  UpdateWindow(w);
  ExitProcess(MessageBox(0,TEXT("Hier ist\nmehrzeiliger Text"),0,MB_OK|MB_ICONEXCLAMATION));
}

/*
Ergebnis: Die Funktion DrawText (Static) oder DrawTextEx (MessageBox) wird nur bei wirksamem Manifest aufgerufen!
Für den Allgemeinfall nützt das also nichts,
man muss die Fensterklassen "Static" und "Button" bei Bedarf sub- oder superklassifizieren.
Offenbar ruft die User-Implementierung (der Fensterklassen Static und DialogBox) irgendetwas internes auf.
*/
