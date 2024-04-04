// HtmlFile.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define HTML_FILE_START_OF_TAG_CHARACTER										ASCII_LESS_THAN_CHARACTER
#define HTML_FILE_END_OF_TAG_CHARACTER											ASCII_GREATER_THAN_CHARACTER

#define HTML_FILE_COMMENT_PREFIX												"<!--"
#define HTML_FILE_COMMENT_SUFFIX												"-->"

#define HTML_FILE_UNABLE_TO_READ_ERROR_MESSAGE_FORMAT_STRING					"Unable to read html file %s"

void HtmlFileFreeMemory();

int HtmlFileProcessTags( BOOL( lpTagFunction )( LPTSTR lpszTag ) );

BOOL HtmlFileRead( LPCTSTR lpszFilePath );
