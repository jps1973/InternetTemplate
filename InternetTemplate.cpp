// InternetTemplate.cpp

#include "InternetTemplate.h"

BOOL ProcessTagFunction( LPTSTR lpszTag )
{
	BOOL bResult = FALSE;

	// Add tag to list box window
	if( ListBoxWindowAddString( lpszTag ) >= 0 )
	{
		// Successfully added tag to list box window

		// Update return value
		bResult = TRUE;

	} // End of successfully added tag to list box window

	return bResult;

} // End of function 

void EditWindowUpdateFunction( int nTextLength )
{
	// See if edit window contains text
	if( nTextLength > 0 )
	{
		// Edit window contains text

		// Enable button window
		ButtonWindowEnable( TRUE );

	} // End of edit window contains text
	else
	{
		// Edit window is empty

		// Disable button window
		ButtonWindowEnable( FALSE );

	} // End of edit window is empty

} // End of function EditWindowUpdateFunction

void ListBoxWindowDoubleClickFunction( LPCTSTR lpszItemText )
{
	// Display item text
	MessageBox( NULL, lpszItemText, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

} // End of function ListBoxWindowDoubleClickFunction

void ListBoxWindowSelectionChangedFunction( LPCTSTR lpszItemText )
{
	// Show item text on status bar window
	StatusBarWindowSetText( lpszItemText );

} // End of function ListBoxWindowSelectionChangedFunction

int ShowAboutMessage( HWND hWndParent )
{
	int nResult = 0;

	MSGBOXPARAMS mbp;

	// Clear message box parameter structure
	ZeroMemory( &mbp, sizeof( mbp ) );

	// Initialise message box parameter structure
	mbp.cbSize		= sizeof( MSGBOXPARAMS );
	mbp.hwndOwner	= hWndParent;
	mbp.hInstance	= NULL;
	mbp.lpszText	= ABOUT_MESSAGE_TEXT;
	mbp.lpszCaption	= ABOUT_MESSAGE_CAPTION;
	mbp.dwStyle		= ( MB_OK | MB_USERICON );
	mbp.lpszIcon	= MAIN_WINDOW_CLASS_ICON_NAME;

	// Show message box
	nResult = MessageBoxIndirect( &mbp );

	return nResult;

} // End of function ShowAboutMessage

LRESULT CALLBACK MainWndProc( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;
			HFONT hFont;

			// Get instance
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Get font
			hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

			// Create edit window
			if( EditWindowCreate( hWndMain, hInstance ) )
			{
				// Successfully created edit window

				// Set edit window font
				EditWindowSetFont( hFont );

				// Create button window
				if( ButtonWindowCreate( hWndMain, hInstance ) )
				{
					// Successfully created button window

					// Set button window font
					ButtonWindowSetFont( hFont );

					// Create list box window
					if( ListBoxWindowCreate( hWndMain, hInstance ) )
					{
						// Successfully created list box window

						// Set list box window font
						ListBoxWindowSetFont( hFont );

						// Create status bar window
						if( StatusBarWindowCreate( hWndMain, hInstance ) )
						{
							// Successfully created status bar window

							// Set status bar window font
							StatusBarWindowSetFont( hFont );

						} // End of successfully created status bar window

					} // End of successfully created list box window

				} // End of successfully created list box window

			} // End of successfully created edit window

			// Break out of switch
			break;

		} // End of a create message
		case WM_SIZE:
		{
			// A size message
			int nClientWidth;
			int nClientHeight;
			RECT rcStatus;
			int nStatusWindowHeight;
			int nListBoxWindowHeight;
			int nEditWindowWidth;
			int nButtonWindowLeft;
			int nListBoxWindowTop;

			// Store client width and height
			nClientWidth	= ( int )LOWORD( lParam );
			nClientHeight	= ( int )HIWORD( lParam );

			// Size status bar window
			StatusBarWindowSize();

			// Get status window size
			StatusBarWindowGetRect( &rcStatus );

			// Calculate window sizes
			nStatusWindowHeight		= ( rcStatus.bottom - rcStatus.top );
			nListBoxWindowHeight	= ( nClientHeight - ( BUTTON_WINDOW_HEIGHT + nStatusWindowHeight ) + WINDOW_BORDER_HEIGHT );
			nEditWindowWidth		= ( ( nClientWidth - BUTTON_WINDOW_WIDTH ) + WINDOW_BORDER_WIDTH );

			// Calculate window positions
			nButtonWindowLeft		= ( nEditWindowWidth - WINDOW_BORDER_WIDTH );
			nListBoxWindowTop		= ( BUTTON_WINDOW_HEIGHT - WINDOW_BORDER_HEIGHT );

			// Move control windoww
			EditWindowMove( 0, 0, nEditWindowWidth, BUTTON_WINDOW_HEIGHT );
			ButtonWindowMove( nButtonWindowLeft, 0, BUTTON_WINDOW_WIDTH, BUTTON_WINDOW_HEIGHT );
			ListBoxWindowMove( 0, nListBoxWindowTop, nClientWidth, nListBoxWindowHeight, TRUE );

			// Break out of switch
			break;

		} // End of a size message
		case WM_ACTIVATE:
		{
			// An activate message

			// Focus on edit window
			EditWindowSetFocus();

			// Break out of switch
			break;

		} // End of an activate message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_DROPFILES:
		{
			// A drop files message
			UINT uFileCount;
			HDROP hDrop;
			UINT uWhichFile;
			UINT uFileSize;

			// Allocate string memory
			LPTSTR lpszFilePath = new char[ STRING_LENGTH ];

			// Get drop handle
			hDrop = ( HDROP )wParam;

			// Count dropped files
			uFileCount = DragQueryFile( hDrop, ( UINT )-1, NULL, 0 );

			// Loop through dropped files
			for( uWhichFile = 0; uWhichFile < uFileCount; uWhichFile ++ )
			{
				// Get size of dropped file
				uFileSize = DragQueryFile( hDrop, uWhichFile, NULL, 0 );

				// Ensure that file size is valid
				if( uFileSize != 0 )
				{
					// File size is valid

					// Get file path
					if( DragQueryFile( hDrop, uWhichFile, lpszFilePath, ( uFileSize + sizeof( char ) ) ) )
					{
						// Successfully got file path

						// Add file path to list box window
						ListBoxWindowAddString( lpszFilePath );

					} // End of successfully got file path

				} // End of file size is valid

			}; // End of loop through dropped files

			// Free string memory
			delete [] lpszFilePath;

			// Break out of switch
			break;

		} // End of a drop files message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case BUTTON_WINDOW_ID:
				{
					// A button window command

					// Allocate string memory
					LPTSTR lpszUrl = new char[ STRING_LENGTH ];

					// Get url from edit window
					if( EditWindowGetText( lpszUrl ) )
					{
						// Successfully got url from edit window

						// Allocate strinf memory
						LPTSTR lpszLocalFilePath = new char[ STRING_LENGTH ];

						// Download file
						if( InternetDownloadFile( lpszUrl, lpszLocalFilePath ) )
						{
							// Successfully downloaded file

							// Read html file
							if( HtmlFileRead( lpszLocalFilePath ) )
							{
								// Successfully read html file

								// Process tags in html file
								HtmlFileProcessTags( &ProcessTagFunction );

								// Free memory associated with html file
								HtmlFileFreeMemory();

							} // End of successfully read html file

						} // End of successfully downloaded file
						else
						{
							// Unable to donload file

							// Allocate string memory
							LPTSTR lpszErrorMessage = new char[ STRING_LENGTH ];

							// Format error message
							wsprintf( lpszErrorMessage, INTERNET_UNABLE_TO_DOWNLOAD_FILE_ERROR_MESSAGE_FORMAT_STRING, lpszUrl );

							// Display error message
							MessageBox( NULL, lpszErrorMessage, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

							// Free string memory
							delete [] lpszErrorMessage;

						} // End of unable to connect to internet

					} // End of successfully got url from edit window

					// Free string memory
					delete [] lpszUrl;

					// Break out of switch
					break;

				} // End of a button window command
				case IDM_FILE_EXIT:
				{
					// A file exit command

					// Destroy window
					DestroyWindow( hWndMain );

					// Break out of switch
					break;

				} // End of a file exit command
				case IDM_HELP_ABOUT:
				{
					// A help about command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about command
				default:
				{
					// Default command

					// See if command message is from edit window
					if( IsEditWindow( ( HWND )lParam ) )
					{
						// Command message is from edit window

						// Handle command message from edit window
						if( !( EditWindowHandleCommandMessage( wParam, lParam, &EditWindowUpdateFunction ) ) )
						{
							// Command message was not handled from edit window

							// Call default procedure
							lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

						} // End of command message was not handled from edit window

					} // End of command message is from edit window
					else
					if( IsListBoxWindow( ( HWND )lParam ) )
					{
						// Command message is from list box window

						// Handle command message from list box window
						if( !( ListBoxWindowHandleCommandMessage( wParam, lParam, &ListBoxWindowDoubleClickFunction, &ListBoxWindowSelectionChangedFunction ) ) )
						{
							// Command message was not handled from list box window

							// Call default procedure
							lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

						} // End of command message was not handled from list box window

					} // End of command message is from list box window
					else
					{
						// Command message is not from list box window

						// Call default procedure
						lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					} // End of command message is not from list box window

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_SYSCOMMAND:
		{
			// A system command message

			// Select system command
			switch( LOWORD( wParam ) )
			{
				case IDM_HELP_ABOUT:
				{
					// A help about system command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about system command
				default:
				{
					// Default system command

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default system command

			}; // End of selection for system command

			// Break out of switch
			break;

		} // End of a system command message
		case WM_CONTEXTMENU:
		{
			// A context menu message
			HMENU hMenuContext;

			// Load context menu
			hMenuContext = LoadMenu( NULL, MAKEINTRESOURCE( IDR_CONTEXT_MENU ) );

			// Show context menu
			TrackPopupMenu( GetSubMenu( hMenuContext, 0 ), ( TPM_LEFTALIGN | TPM_LEFTBUTTON ), LOWORD( lParam ), HIWORD( lParam ), 0, hWndMain, NULL );

			// Break out of switch
			break;

		} // End of a context menu message
		case WM_CLOSE:
		{
			// A close message

			// Destroy main window
			DestroyWindow( hWndMain );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function MainWndProc

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow )
{
	MSG msg;

	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Connect to internet
	if( InternetConnect() )
	{
		// Successfully connected to internet
		WNDCLASSEX wcMain;

		// Clear window class structure
		ZeroMemory( &wcMain, sizeof( wcMain ) );

		// Initialise main window class structure
		wcMain.cbSize			= sizeof( WNDCLASSEX );
		wcMain.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
		wcMain.lpfnWndProc		= MainWndProc;
		wcMain.hInstance		= hInstance;
		wcMain.style			= MAIN_WINDOW_CLASS_STYLE;
		wcMain.hIcon			= MAIN_WINDOW_CLASS_ICON;
		wcMain.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
		wcMain.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
		wcMain.lpszMenuName		= MAIN_WINDOW_CLASS_MENU_NAME;
		wcMain.hIconSm			= MAIN_WINDOW_CLASS_ICON;

		// Register main window class
		if( RegisterClassEx( &wcMain ) )
		{
			// Successfully registered main window class
			HWND hWndMain;

			// Create main window
			hWndMain = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT, MAIN_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

			// Ensure that main window was created
			if( hWndMain )
			{
				// Successfully created main window
				HMENU hMenuSystem;
				LPWSTR *lpszArgumentList;
				int nArgumentCount;

				// Allocate string memory
				LPTSTR lpszInitialUrl = new char[ STRING_LENGTH + sizeof( char ) ];

				// Clear initial url
				lpszInitialUrl[ 0 ] = ( char )NULL;

				// Get system menu
				hMenuSystem = GetSystemMenu( hWndMain, FALSE );

				// Add separator to system menu
				InsertMenu( hMenuSystem, SYSTEM_MENU_SEPARATOR_ITEM_POSITION, ( MF_BYPOSITION | MF_SEPARATOR ), 0, NULL );

				// Add about item to system menu
				InsertMenu( hMenuSystem, SYSTEM_MENU_ABOUT_ITEM_POSITION, MF_BYPOSITION, IDM_HELP_ABOUT, SYSTEM_MENU_ABOUT_ITEM_TEXT );

				// Get argument list
				lpszArgumentList = CommandLineToArgvW( GetCommandLineW(), &nArgumentCount );

				// Ensure that argument list was got
				if( lpszArgumentList )
				{
					// Successfully got argument list

					// See if arguments were provided
					if( nArgumentCount > 1 )
					{
						// At least one argument was provided
						int nSizeNeeded;
						int nWideArgumentLength;

						// Get wide first argument length
						nWideArgumentLength = lstrlenW( lpszArgumentList[ 1 ] );

						// Get size required for first argument
						nSizeNeeded = WideCharToMultiByte( CP_UTF8, 0, lpszArgumentList[ 1 ], nWideArgumentLength, NULL, 0, NULL, NULL );

						// Convert first argument to ansi, and use as initial url
						WideCharToMultiByte( CP_UTF8, 0, lpszArgumentList[ 1 ], nWideArgumentLength, lpszInitialUrl, nSizeNeeded, NULL, NULL );

						// Terminate initial url
						lpszInitialUrl[ nSizeNeeded ] = ( char )NULL;

					}; // End of at least one argument was provided

				} // End of successfully got argument list

				// See if initial url is empty
				if( !( lpszInitialUrl[ 0 ] ) )
				{
					// Initial url is empty
					DWORD dwClipboardTextLength;

					// Get clipboard text length
					dwClipboardTextLength = ClipboardGetTextLength();

					// See if clipboard contains text
					if( dwClipboardTextLength > 0 )
					{
						// Clipboard contains text

						// Allocate string memory
						LPTSTR lpszClipboardText = new char[ dwClipboardTextLength + sizeof( char ) ];

						// Get clipboard text
						if( ClipboardGetText( lpszClipboardText ) )
						{
							// Successfully got clipboard text

							// Use clipboard text as initial url
							lstrcpyn( lpszInitialUrl, lpszClipboardText, STRING_LENGTH );

						} // End of successfully got clipboard text
						else
						{
							// Unable to get clipboard text

							// Use default initial url
							lstrcpy( lpszInitialUrl, DEFAULT_INITIAL_URL );

						} // End of unable to get clipboard text

					} // End of clipboard contains text
					else
					{
						// Clipboard is empty

						// Use default initial url
						lstrcpy( lpszInitialUrl, DEFAULT_INITIAL_URL );

					} // End of clipboard is empty

				} // End of initial url is empty

				// Show initial url on edit window
				EditWindowSetText( lpszInitialUrl );

				// Select edit window text
				EditWindowSelect();

				// Show main window
				ShowWindow( hWndMain, nCmdShow );

				// Update main window
				UpdateWindow( hWndMain );

				// Main message loop
				while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
				{
					// Translate message
					TranslateMessage( &msg );

					// Dispatch message
					DispatchMessage( &msg );

				}; // End of main message loop

				// Free string memory
				delete [] lpszInitialUrl;

			} // End of successfully created main window
			else
			{
				// Unable to create main window

				// Display error message
				MessageBox( NULL, UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

			} // End of unable to create main window

		} // End of successfully registered main window class
		else
		{
			// Unable to register main window class

			// Display error message
			MessageBox( NULL, UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to register main window class

		// Close internet
		InternetClose();

	} // End of successfully connected to internet
	else
	{
		// Unable to connect to internet

		// Display error message
		MessageBox( NULL, INTERNET_UNABLE_TO_CONNECT_INTERNET_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to connect to internet

	return msg.wParam;

} // End of function WinMain
