#include "pch.h"
#include "VideoFileManager.h"
#include <algorithm>

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

void VideoFileManager::CountVideoFilesInDirectory(String^ directoryPath, int% VideoFilesCount, float% totalFilesSize, array<String^>^% allFilesFound) {
	if (!Directory::Exists(directoryPath)) {
		throw gcnew DirectoryNotFoundException("The specified directory does not exist: " + directoryPath);
	}
	array<String^>^ videoExtensions = { ".mp4", ".avi", ".mkv", ".mov", ".wmv", ".flv", ".mpeg", ".mpg" };
	array<String^>^ allFiles = Directory::GetFiles(directoryPath);
	int maxPossibleVideos = allFiles->Length;
	array<String^>^ videoFiles = gcnew array<String^>(maxPossibleVideos);

	int videoFileCount = 0;
	float totalFilesSizeMB = 0;

	for each (String ^ fileName in allFiles) { //checks if the file is a video file by comparing its extension to a list of known video file extensions
		for each (String^ extension in videoExtensions) {
			if (fileName->EndsWith(extension, StringComparison::OrdinalIgnoreCase)) {
				videoFiles[videoFileCount] = fileName;
				videoFileCount++;
				FileInfo^ fileInfo = gcnew FileInfo(fileName);
				if (fileInfo->Exists) {
					totalFilesSizeMB += static_cast<float>(fileInfo->Length / (1024.0f * 1024.0f)); // Convert bytes to MB
				}
				break;
			}
		}
	}

	Array::Resize(videoFiles, videoFileCount);

	allFilesFound = videoFiles;
	VideoFilesCount = videoFileCount;
	totalFilesSize = totalFilesSizeMB;
	
}