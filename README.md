# drawtexthook
Enhance Win32 Static, Button, MessageBox with RichText: bold, italic, subscript, superscript, color etc.

**Intended audience:** Win32 C++ programmers

For scientific applications, users often need indices = subscrips for static text (describing edit boxes), checkboxes, MessageBox etc. One solution would be API hooking of DrawText() which is generally used inside for such dialogs or dialog elements. As such, there would be no need to subclassify or superclassify the Button, Static, and DialogBox class, extra functionality would come for free. (In-Process hooking is desired, not hooking other processes for now.)
My idea for adding extra functionality is space-preserving by using unused control codes between 0x01 and 0x1F. No RTF, it's harder to parse and string-space wasting. No HTML for the same reason. But that are implementation details.
So I wrote this small test program (drawtexthook.cpp) to check whether hooking would work at all.

**Procedure:** When reaching the dummy `DrawText()` and `DrawTextEx()` calls, `OutputDebugString()` shows the parameters, so one can see in the output window whether the functions get called. On my Windows 10, `DrawText()` is called for `UpdateWindow()` (which inside invokes WM_PAINT for the Static text) and for the `MessageBox()` multi-line text, whereas `DrawTextEx()` is called for the OK button.

**Result:** When a manifest resource using COMCTL32.DLL for subclassified controls, the `DrawText()` and `DrawTextEx()` functions will be invoked. But when calls are made using USER32.DLL (in case of no manifest), NO hook is called!
Therefore, hooking `DrawText()` is not universal. Sorry.
