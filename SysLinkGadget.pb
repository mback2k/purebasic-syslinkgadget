Define EventID
Define LinkHTML$="<a href=" + Chr(34) + "http://www.purebasic.fr/german/index.php" + Chr(34) + ">PureBoard</a>, Hello World"

If OpenWindow(0, 0, 0, 500, 400, "Window", #PB_Window_SystemMenu | #PB_Window_ScreenCentered)
  TextGadget(0, 0, 0, 500, 400, "PureBoard, Hello World")
  SysLinkGadget(1, 0, 12, 500, 400, "PureBoard, Hello World")
  Debug GetGadgetText(1)
  SetGadgetText(1, LinkHTML$)
  Debug GetGadgetText(1)
  Debug GetGadgetFont(0)
  Debug GetGadgetFont(1)
  SetGadgetColor(1, #PB_Gadget_BackColor, RGB(0, 0, 0))

  Repeat
    EventID = WaitWindowEvent()
    If EventID = #PB_Event_CloseWindow
      End
    EndIf
  ForEver
EndIf
; IDE Options = PureBasic 5.00 Beta 3 (Windows - x86)
; CursorPosition = 5
; EnableThread
; EnableXP
; CPU = 1
; EnableBuildCount = 0