#include "RegisterCommonControls.h"

// -----------------------------------------------------------------------------------------
// The following code is taken from:
//  http://blog.speedproject.de/2008/04/18/syslink-control-unter-windows-2000/
// Thank you very much!

BOOL RegisterCommonControls()
{
    // Deklarationen
    INITCOMMONCONTROLSEX initCCex;
    WNDCLASSW wndLinkClass;
    HINSTANCE hModShell32;
    BOOL fSuccess;

    // Common Controls initialisieren
    initCCex.dwSize = sizeof(initCCex);
    initCCex.dwICC = ICC_WIN95_CLASSES | ICC_LINK_CLASS;

    // Common Controls initialisieren
    InitCommonControlsEx(&initCCex);

    // Erfolg?
    fSuccess = FALSE;

    // Fensterklasse abrufen
    if (!GetClassInfoW(NULL, L"SysLink", &wndLinkClass))
    {
        // Registrierungsfunktion
        typedef BOOL (WINAPI* pfnLinkWindowRegisterProc)();

        // Shell32-Dll laden
        hModShell32 = LoadLibraryW(L"shell32.dll");
        if (NULL != hModShell32)
        {
            // Funkion importieren
            pfnLinkWindowRegisterProc pfnLinkWindowRegister = (pfnLinkWindowRegisterProc) GetProcAddress(hModShell32, MAKEINTRESOURCEA(258));
            if (NULL != pfnLinkWindowRegister)
            {
                fSuccess = pfnLinkWindowRegister();
            }

            // Dll freigeben
            FreeLibrary(hModShell32);
        }

        // Fensterklasse fuer "Link Window" registriert
        if (fSuccess)
        {
            // Fensterklasse abrufen
            if (GetClassInfoW(NULL, L"Link Window", &wndLinkClass))
            {
                // Fensterklasse auf SysLink setzen
                wndLinkClass.lpszClassName = L"SysLink";

                // Fensterklasse registrieren
                if (!RegisterClassW(&wndLinkClass))
                {
                    fSuccess = FALSE;
                }
            }

            // Fehler beim Abruf der Fensterklasse
            else
            {
                fSuccess = FALSE;
            }
        }
    }

    // Fensterklasse existiert bereits
    else
    {
        fSuccess = TRUE;
    }

    // Erfolg
    return fSuccess;
}
