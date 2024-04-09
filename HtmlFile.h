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

#define HTML_FILE_END_OF_TAG_NAME_CHARACTERS									" >"

#define HTML_FILE_ANCHOR_TAG_NAME												"a"
#define HTML_FILE_ANCHOR_TAG_HEADER												"Anchor"
#define HTML_FILE_ANCHOR_TAG_ATTRIBUTE_NAME										"href"

#define HTML_FILE_IMAGE_TAG_NAME												"img"
#define HTML_FILE_IMAGE_TAG_HEADER												"Image"
#define HTML_FILE_IMAGE_TAG_ATTRIBUTE_NAME										"src"

#define HTML_FILE_UNKNOWN_TAG_HEADER											"Unknown"

#define HTML_FILE_ABSOLUTE_IDENTIFIER											"://"


#define HTML_FILE_UNABLE_TO_READ_ERROR_MESSAGE_FORMAT_STRING					"Unable to read html file %s"

void HtmlFileFreeMemory();

BOOL HtmlFileGetAttributeValue( LPCTSTR lpszTag, LPCTSTR lpszParentUrl, LPCTSTR lpszAttributeName, LPTSTR lpszAttributeValue );

BOOL HtmlFileGetTagName( LPCTSTR lpszTag, LPTSTR lpszTagName );

int HtmlFileProcessTags( BOOL( lpTagFunction )( LPTSTR lpszTag ) );

BOOL HtmlFileRead( LPCTSTR lpszFilePath );
