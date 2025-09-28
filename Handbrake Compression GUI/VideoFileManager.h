#pragma once
using namespace System;

ref class VideoFileManager
{
public:
	static void CountVideoFilesInDirectory(String^ directoryPath, int% videoFilesCount,	float% totalFilesSize, array<String^>^% allFilesFound);
};