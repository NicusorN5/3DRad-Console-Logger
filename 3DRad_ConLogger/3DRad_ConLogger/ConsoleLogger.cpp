#pragma once
#include "ConsoleLogger.h"

ConsoleLoggerSettings CSETTINGS;

FILE* a,*b,*c;

char* ParseStringFromFloatArray(float* args)
{
	char* str = new char[16383]; //Oh yes, that's how many arguments the args[] can have, as documented in 3D Rad's documentation.
	int s;
	for (int i = 0; ; i++)
	{
		str[i] = (uint8_t)args[i];
		if (args[i] == 0)
		{
			s = i;
			break;
		}
	}
	char* ret = new char[s + 1];
	for (int i = 0; i <= s; i++)
	{
		ret[i] = str[i];
	}
	delete[] str;
	return ret; //This is prone to memory leaks if not used correctly.
	//Store the result in a separate string and then delete it.
}


void DLL_EXPORT ConsoleSetWriteToFile(float* val)
{
	CSETTINGS.WriteToFile = (bool)val[0];
}

void DLL_EXPORT ConsoleSetLogFile(float* val)
{
	CSETTINGS.FileName = ParseStringFromFloatArray(val); //won't be freed until release.
}

void DLL_EXPORT InitializeConsole(float* args)
{
	char* def = new char[23];
	memcpy_s(def, 23, "3DRadConsoleLogger.log", 23);

	if (CSETTINGS.FileName == nullptr) CSETTINGS.FileName = def;
	else delete[] def;

	AllocConsole();
	//taken without shame from StackOverflow lel
	a = freopen("conin$", "r", stdin);
	b = freopen("conout$", "w", stdout);
	c = freopen("conout$", "w", stderr);
}

void DLL_EXPORT ConsoleUnload(float* args)
{
	delete[] CSETTINGS.FileName;
	fclose(a);
	fclose(b);
	fclose(c);
	FreeConsole();
}

void DLL_EXPORT ConsoleWriteLine(float* val)
{
	//this is a null-terminated C string
	char* str = ParseStringFromFloatArray(val);
	printf(str);
	printf("\r\n");

	if (CSETTINGS.WriteToFile)
	{
		std::ofstream fw(CSETTINGS.FileName);
		fw << str << std::endl;
		fw.close();
	}

	delete[] str;
}
void DLL_EXPORT ConsoleNewLine(float* val)
{
	printf("\r\n");
}
void DLL_EXPORT ConsoleWrite(float* val)
{
	//this is a null-terminated C string
	char* str = ParseStringFromFloatArray(val);
	printf(str);

	if (CSETTINGS.WriteToFile)
	{
		std::ofstream fw(CSETTINGS.FileName);
		fw << str;
		fw.close();
	}

	delete[] str;
}

void DLL_EXPORT ConsolePrintColouredText(float* args)
{
	ConsoleSetColor(args);
	ConsoleWrite(args + 1);
	ConsoleResetColor(nullptr);
}

void DLL_EXPORT ConsoleSetColor(float* args)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)args[0]);
}

void DLL_EXPORT ConsoleResetColor(float* args)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7); // 7 = default color
}