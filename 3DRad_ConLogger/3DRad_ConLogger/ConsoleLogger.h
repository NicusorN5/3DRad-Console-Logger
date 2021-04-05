#pragma once
#include <windows.h>
#include <iostream>
#include <cstdint>
#include <fstream>

//
// ---------------------------------------------------------------------------------------------------------
//									MACRO DEFINITIONS
// ---------------------------------------------------------------------------------------------------------

#define DLL_EXPORT __declspec(dllexport)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

//
// ---------------------------------------------------------------------------------------------------------
//									REUSED FUNCTIONS
// ---------------------------------------------------------------------------------------------------------

/// <summary>
/// Reused from 3DRadExtender. 
/// </summary>
/// <param name="args">3DRad string argument</param>
/// <returns>The converted string</returns>
char* ParseStringFromFloatArray(float* args);

//
// ---------------------------------------------------------------------------------------------------------
//										DATA STRUCTURES AND ENUMS
// ---------------------------------------------------------------------------------------------------------

/// <summary>
/// Stores the settings of the logger.
/// </summary>
struct ConsoleLoggerSettings
{
	/// <summary>
	/// Checks it the logger will save into a file.
	/// </summary>
	bool WriteToFile;
	/// <summary>
	/// Sets the file where the log will be saved.
	/// </summary>
	char* FileName;
};
extern ConsoleLoggerSettings CSETTINGS;

//
// ---------------------------------------------------------------------------------------------------------
//										EXPOSED LIBRARY FUNCTIONS
// ---------------------------------------------------------------------------------------------------------

//SETTINGS FUNCTIONS

extern "C" {
	/// <summary>
	/// Sets the file logging feature.
	/// </summary>
	/// <param name="val">val[0] = bool</param>
	/// <returns></returns>
	void DLL_EXPORT ConsoleSetWriteToFile(float* val);

	/// <summary>
	/// Sets the log file name.
	/// </summary>
	/// <param name="val">File name</param>
	/// <returns></returns>
	void DLL_EXPORT ConsoleSetLogFile(float* val);
	//INITIALIZATION-UNLOAD FUNCTION

	/// <summary>
	/// Starts up the console with the specified settings.
	/// </summary>
	/// <param name="args"></param>
	void DLL_EXPORT InitializeConsole(float* args);

	/// <summary>
	/// Unloads needed memory.
	/// </summary>
	/// <param name="args">Not used</param>
	void DLL_EXPORT ConsoleUnload(float* args);

	/// WRITING FUNCTIONS AND COLOR FUNCTIONS


	/// <summary>
	/// Writes something into the console, and if the file writing is enabled, writes into the log file.
	/// </summary>
	/// <param name="val"></param>
	void DLL_EXPORT ConsoleWrite(float* val);

	/// <summary>
	/// Writes something into the console, and if the file writing is enabled, writes into the log file.
	/// </summary>
	/// <param name="val"></param>
	void DLL_EXPORT ConsoleWriteLine(float* val);

	/// <summary>
	/// Writes something into the console, and if the file writing is enabled, writes into the log file.
	/// </summary>
	/// <param name="val"></param>
	void DLL_EXPORT ConsoleNewLine(float* val);

	/// <summary>
	/// Prints coloured text to the console.
	/// WARNING: THE CAPACITY OF THE STRING IS REDUCED WITH 1 CHARACTER, THAT MEANING THE MAX STRING LENGTH IS 16382 NOT 16383 
	/// </summary>
	/// <param name="args">args[0] = color, the rest is a null-terminated string</param>
	/// <returns></returns>
	void DLL_EXPORT ConsolePrintColouredText(float* args);

	/// <summary>
	/// Sets the color of the next characters.
	/// </summary>
	/// <param name="args">args[0] = color</param>
	/// <returns></returns>
	void DLL_EXPORT ConsoleSetColor(float* args);

	/// <summary>
	/// Resets the Console color to the Windows default. ( 7 ) UNLESS A COLOR WAS SET IN REGEDIT
	/// </summary>
	/// <param name="args">Not used</param>
	/// <returns></returns>
	void DLL_EXPORT ConsoleResetColor(float* args);

}