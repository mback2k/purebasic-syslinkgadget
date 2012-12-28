/*
 *  SysLinkGadget() command for PureBasic
 */

#include "SysLinkGadget.h"
#include "RegisterCommonControls.h"

static PB_GadgetVT SysLinkVT;
static int         Initialized;
static int         Registered;

// -----------------------------------------------------------------------------------------

static M_GADGETVIRTUAL(integer) SysLink_Callback(PB_Gadget *Gadget, HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
  integer Result = PB_EventNotProcessed;

  if (Message == WM_NOTIFY) // Handle any message here
  {
    Result = 0; // set Result to 0, if you don't want the event to be populated to next handlers
  }

  return Result;
}

// ---------------------------------------------------------------------------------------

static M_GADGETVIRTUAL(void) SysLink_SetGadgetText(PB_Gadget *Gadget, const TCHAR *Text)
{
  if (Text) {
    SendMessage(Gadget->Gadget, WM_SETTEXT, 0, (LPARAM)Text);
  }
}

// ---------------------------------------------------------------------------------------

static M_GADGETVIRTUAL(void) SysLink_GetGadgetText(PB_Gadget *Gadget, int PreviousStringPosition)
{
  LRESULT Length = SendMessage(Gadget->Gadget, WM_GETTEXTLENGTH, 0, 0) + sizeof(TCHAR);
  TCHAR *Result = SYS_GetOutputBuffer(Length, PreviousStringPosition);

  if (Result) {
    SendMessage(Gadget->Gadget, WM_GETTEXT, Length, (LPARAM)Result);
  }
}

// ---------------------------------------------------------------------------------------

static M_GADGETVIRTUAL(void) SysLink_SetGadgetFont(PB_Gadget *Gadget, HFONT Font)
{
  if (Font) {
    SendMessage(Gadget->Gadget, WM_SETFONT, (WPARAM)Font, (LPARAM)TRUE);
  }
}

// ---------------------------------------------------------------------------------------

static M_GADGETVIRTUAL(HFONT) SysLink_GetGadgetFont(PB_Gadget *Gadget)
{
  return (HFONT)SendMessage(Gadget->Gadget, WM_GETFONT, 0, 0);
}

// ---------------------------------------------------------------------------------------

static M_GADGETVIRTUAL(void) SysLink_SetGadgetColor(PB_Gadget *Gadget, int ColorType, int Color)
{
}

// ---------------------------------------------------------------------------------------

static M_GADGETVIRTUAL(integer) SysLink_GetGadgetColor(PB_Gadget *Gadget, int ColorType)
{
  return 0;
}

// -----------------------------------------------------------------------------

M_PBFUNCTION(HWND) PB_SysLinkGadget2(integer GadgetID, int x, int y, int Width, int Height, const TCHAR *Title, int Flags)
{
  PB_GadgetGlobals *Globals = PB_Object_GetThreadMemory(PB_Gadget_Globals);
  PB_Gadget *Gadget;
  HWND Result;

  int Mask = WS_TABSTOP | WS_CHILD | WS_VISIBLE | Flags;

  if (!Registered)
  {
    if (RegisterCommonControls())
    {
      Registered = 1;
    }
  }

  if (Result = CreateWindowExW(0, WC_LINK, NULL, Mask, x, y, Width, Height, Globals->CurrentWindow, (HMENU)0, PB_Instance, 0))
  {
    SendMessage(Result, WM_SETTEXT, 0, (LPARAM)Title);

    if (!Initialized)
    {
      PB_Gadget_GetCommonControlsVersion();
          
      ZeroMemory(&SysLinkVT, sizeof(PB_GadgetVT));

      SysLinkVT.GadgetType = PB_GadgetType_Unknown;
      SysLinkVT.SizeOf     = sizeof(PB_GadgetVT);

      SysLinkVT.GadgetCallback      = SysLink_Callback;
      SysLinkVT.FreeGadget          = PB_Gadget_SharedFreeGadget;
      SysLinkVT.SetGadgetText       = SysLink_SetGadgetText;
      SysLinkVT.GetGadgetText       = SysLink_GetGadgetText;
      SysLinkVT.SetGadgetFont       = SysLink_SetGadgetFont;
      SysLinkVT.GetGadgetFont       = SysLink_GetGadgetFont;
      SysLinkVT.SetGadgetColor      = SysLink_SetGadgetColor;
      SysLinkVT.GetGadgetColor      = SysLink_GetGadgetColor;

      Initialized = 1;
    }

    Gadget = PB_Gadget_GetOrAllocateID(GadgetID);

    Result = PB_Gadget_RegisterGadget(GadgetID, Gadget, Result, &SysLinkVT);
  }

  return Result;
}

// -----------------------------------------------------------------------------

M_PBFUNCTION(HWND) PB_SysLinkGadget(integer GadgetID, int x, int y, int Width, int Height, const TCHAR *Title)
{
  return PB_SysLinkGadget2(GadgetID, x, y, Width, Height, Title, 0);
}
