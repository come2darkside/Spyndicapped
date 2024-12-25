#include "Main.h"
#include "Args.h"
#include "Find.h"
#include "MyAutomationEventHandler.h"
#include "Errors.h"


void ShowAwesomeBanner() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x0C);
	std::wcout << R"(              
              ._
                |
                |
                |L___,
              .' '.  T        
             :  *  :_|
              '._.'   L		

[Spyndicapped]
CICADA8 Research Team
Christmas present from MzHmO
)" << std::endl;

	SetConsoleTextAttribute(hConsole, 0x07);
}

void ShowHelp()
{
	std::wcout << L"There are different work modes:" << std::endl;
	
	std::wcout << L"[FIND mode]" << std::endl;
	std::wcout << L"\t Displays the windows available for spying with --window or --pid" << std::endl;
	std::wcout << L"\t Ex: Spyndicapped.exe find" << std::endl;
	
	std::wcout << L"[SPY mode]" << std::endl;
	std::wcout << L"\t Window(s) spying mode" << std::endl;
	std::wcout << L"\t --window <name> <- grabs information from that window" << std::endl;
	std::wcout << L"\t --pid <pid> <- grabs information from that process (GUI Required)" << std::endl;
	std::wcout << L"\t Ex: Spyndicapped.exe spy" << std::endl;
	std::wcout << L"\t Ex: Spyndicapped.exe spy --window \"Program Manager\" " << std::endl;
	std::wcout << L"\t Ex: Spyndicapped.exe spy --pid 123" << std::endl;

	std::wcout << L"[Other]" << std::endl;
	std::wcout << L"\t --debug <- displays more information" << std::endl;
}


int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "");

	ShowAwesomeBanner();

	if (argc == 1)
	{
		ShowHelp();
		return 0;
	}

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (cmdOptionExists(argv, argv + argc, L"--debug"))
	{
		g_DebugModeEnable = true;
	}

	if (cmdOptionExists(argv, argv + argc, L"find"))
	{
		if (Finder::DisplayActiveWindows() != 0)
		{
			Log(L"Failed to find windows!", WARNING);
			return -1;
		}
		Log(L"FindWindows() success", DBG);
	} 
	else if (cmdOptionExists(argv, argv + argc, L"spy"))
	{
		wchar_t* windowName = NULL;
		DWORD pid = 0;
		if (cmdOptionExists(argv, argv + argc, L"--window"))
		{
			windowName = getCmdOption(argv, argv + argc, L"--window");
		}

		if (cmdOptionExists(argv, argv + argc, L"--pid"))
		{
			std::wstring pidStr = getCmdOption(argv, argv + argc, L"--pid");
			pid = static_cast<DWORD>(std::wcstoul(pidStr.c_str(), nullptr, 10));
		}

		MyAutomationEventHandler::Deploy(windowName, pid);
	}
	else if ( cmdOptionExists(argv, argv + argc, L"-h") || (cmdOptionExists(argv, argv + argc, L"--help")) )
	{
		ShowHelp();
	}

	CoUninitialize();

	return 0;
}