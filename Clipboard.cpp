// Clipboard.cpp

#include "Clipboard.h"

BOOL ClipboardGetText( LPTSTR lpszClipboardText, UINT uClipboardFormat )
{
	BOOL bResult = FALSE;

	// Open clipboard
	if( ::OpenClipboard( NULL ) )
	{
		// Successfully opened clipboard
		HANDLE hClipboardData;

		// Get clipboard data
		hClipboardData = ::GetClipboardData( uClipboardFormat );

		// Ensure that clipboard data was got
		if( hClipboardData )
		{
			// Successfully got clipboard data

			// Get clipboard data as string
			LPTSTR lpszClipboardData = static_cast<LPTSTR>( GlobalLock( hClipboardData ) );

			// Ensure that clipboard data was got as string
			if( lpszClipboardData )
			{
				// Successfully got clipboard data as string

				// Update clipboard text
				lstrcpy( lpszClipboardText, lpszClipboardData );

				// Update return value
				bResult = TRUE;

			} // End of successfully got clipboard data as string

			// Unlock clipboard data
			GlobalUnlock( hClipboardData );

		} // End of successfully got clipboard data

		// Close clipboard
		::CloseClipboard();

	} // End of successfully opened clipboard

	return bResult;

} // End of function ClipboardGetText

DWORD ClipboardGetTextLength( UINT uClipboardFormat )
{
	DWORD dwResult = 0;

	// Open clipboard
	if( ::OpenClipboard( NULL ) )
	{
		// Successfully opened clipboard
		HANDLE hClipboardData;

		// Get clipboard data
		hClipboardData = ::GetClipboardData( uClipboardFormat );

		// Ensure that clipboard data was got
		if( hClipboardData )
		{
			// Successfully got clipboard data

			// Get clipboard data as string
			LPTSTR lpszClipboardData = static_cast<LPTSTR>( GlobalLock( hClipboardData ) );

			// Ensure that clipboard data was got as string
			if( lpszClipboardData )
			{
				// Successfully got clipboard data as string

				// Get clipboard text length
				dwResult = lstrlen( lpszClipboardData );

			} // End of successfully got clipboard data as string

			// Unlock clipboard data
			GlobalUnlock( hClipboardData );

		} // End of successfully got clipboard data

		// Close clipboard
		::CloseClipboard();

	} // End of successfully opened clipboard

	return dwResult;

} // End of function ClipboardGetTextLength