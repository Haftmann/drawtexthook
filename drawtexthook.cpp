// MSVC6 without standard library, even no MSVCRT.DLL

#include <windows.h>
#include <algorithm>	// std::swap()
#include <shlwapi.h>
#include <stdlib.h>	// countof()

#pragma comment(linker,"/NOD /RELEASE /SUBSYSTEM:WINDOWS,4.00 /OPT:NOWIN98 /LARGEADDRESSAWARE")
#pragma intrinsic(memcpy)
#define elemof(x) (sizeof(x)/sizeof(*(x)))

#pragma pack(push,1)
struct JumpInstr{
  typedef BYTE buf_t[5];	// byte buffer for saving and restoring
  BYTE opcode;			// 0xE9: same for x86 and x64
  LONG distance;		// distance between target and end-of-opcode, same for x86 and x64
  const void*end() const {return this+1;}	// end-of-opcode
  void save(buf_t buf) const {memcpy(buf,this,5);}
  void restore(const buf_t buf) {memcpy(this,buf,5);}
  void swap(buf_t buf) {std::swap(*this,*(JumpInstr*)buf);}
  void setjmp(const void*target) {opcode=0xE9; distance=LONG((BYTE*)target-(BYTE*)end());}
};
#pragma pack(pop)

static JumpInstr*dt;		// USER32.DLL::DrawTextW
static JumpInstr::buf_t dt_buf;

static JumpInstr*dtex;		// same for DrawTextExW
static JumpInstr::buf_t dtex_buf;

void _cdecl debug(const TCHAR*t,...) {
 va_list va;
 va_start(va,t);
 TCHAR s[256];
 wvnsprintf(s,elemof(s),t,va);
 va_end(va);
 OutputDebugString(s);
}

int WINAPI DrawTextX(HDC dc,const TCHAR*s,int slen,RECT*rc,UINT uFormat) {
  debug(TEXT("DrawText(%X,\"%s\",%d,{%d,%d,%d,%d},%X)\n"),dc,s,slen,rc?rc->left:0,rc?rc->top:0,rc?rc->right:0,rc?rc->bottom:0,uFormat);
  dt->swap(dt_buf);	// of-course, needs single-threading
  int i=DrawText(dc,const_cast<TCHAR*>(s),slen,rc,uFormat);
  dt->swap(dt_buf);
  return i;
}

int WINAPI DrawTextExX(HDC dc,const TCHAR*s,int slen,RECT*rc,UINT uFormat,DRAWTEXTPARAMS*dtp) {
  debug(TEXT("DrawTextEx(%X,\"%s\",%d,{%d,%d,%d,%d},%X,%X)\n"),dc,s,slen,rc?rc->left:0,rc?rc->top:0,rc?rc->right:0,rc?rc->bottom:0,uFormat,dtp);
  dtex->swap(dtex_buf);	// of-course, needs single-threading
  int i=DrawTextEx(dc,const_cast<TCHAR*>(s),slen,rc,uFormat,dtp);
  dtex->swap(dtex_buf);
  return i;
}

void WinMainCRTStartup() {
  dt=(JumpInstr*)DrawText;	// USER32.DLL::DrawTextW
  dtex=(JumpInstr*)DrawTextEx;	// same for DrawTextExW
  DWORD oldprot[2];
  VirtualProtect(dt,sizeof*dt,PAGE_EXECUTE_WRITECOPY,oldprot);
  dt->save(dt_buf);
  dt->setjmp(DrawTextX);

  VirtualProtect(dtex,sizeof*dtex,PAGE_EXECUTE_WRITECOPY,oldprot+1);
  dtex->save(dtex_buf);
  dtex->setjmp(DrawTextExX);

  HWND w=CreateWindowEx(0,TEXT("Static"),TEXT("Test&123"),WS_OVERLAPPEDWINDOW|WS_VISIBLE,
  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
  0,0,0,0);
  ShowWindow(w,SW_SHOWDEFAULT);
  UpdateWindow(w);
  MessageBox(0,TEXT("Hier ist\n&mehrzeiliger Text"),0,MB_OK|MB_ICONEXCLAMATION);
  dtex->restore(dtex_buf);
  VirtualProtect(dtex,sizeof*dtex,oldprot[1],oldprot+1);
  dt->restore(dt_buf);
  VirtualProtect(dt,sizeof*dt,oldprot[0],oldprot);
  ExitProcess(0);
}

/*
Ergebnis: Die Funktion DrawText (Static) oder DrawTextEx (MessageBox) wird nur bei wirksamem Manifest aufgerufen!
Für den Allgemeinfall nützt das also nichts,
man muss die Fensterklassen "Static" und "Button" bei Bedarf sub- oder superklassifizieren.
Offenbar ruft die User-Implementierung (der Fensterklassen Static und DialogBox) irgendetwas internes auf.
*/
