// Clipboard.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

BOOL ClipboardGetText( LPTSTR lpszClipboardText, UINT uClipboardFormat = CF_TEXT );

DWORD ClipboardGetTextLength( UINT uClipboardFormat = CF_TEXT );
