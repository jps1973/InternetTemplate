cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra InternetTemplate.cpp ButtonWindow.cpp EditWindow.cpp HtmlFile.cpp Internet.cpp ListBoxWindow.cpp StatusBarWindow.cpp Resource.o -o InternetTemplate.exe -lwininet
