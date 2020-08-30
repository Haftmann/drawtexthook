# drawtexthook
Enhance Win32 Static, Button, MessageBox with RichText: bold, italic, subscript, superscript, color etc.

For scientific applications, users often need indices = subscrips for static text (describing edit boxes), checkboxes, MessageBox etc. One solution would be API hooking of DrawText() which is generally used inside for such dialogs or dialog elements. As such, there would be no need to subclassify or superclassify the Button, Static, and DialogBox class, extra functionality would come for free. (In-Process hooking is desired, not hooking other processes for now.)
My idea for adding extra functionality is space-preserving by using unused control codes between 0x01 and 0x1F. No RTF, it's harder to parse and string-space wasting. No HTML for the same reason. But that are implementation details.
So I wrote this small test program (drawtexthook.cpp) to check whether hooking would work at all.

**Procedure:** When reaching the dummy `DrawText()` and `DrawTextEx()` calls, I switched to disassembly window and traced to the first instruction inside USER32.DLL and set a breakpoint. Then I checked whether the breakpoints are hit on `UpdateWindow()` (which inside invokes WM_PAINT for the Static text) and `MessageBox()`, where `DrawText()` is used or multiline text formatting.

**Result:** When a manifest resource using COMCTL32.DLL for subclassified controls, the `DrawText()` and `DrawTextEx()` functions will be invoked, and the breakpoints are hit. But when calls are made using USER32.DLL (in case of no manifest), NO breakpoint was hit!
Therefore, hooking `DrawText()` is not universal. Sorry. Project died.
