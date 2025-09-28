#pragma once
#include "MonitorHelper.h"
#include "VideoFileManager.h"
#include "PresetMenu.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;
	using namespace System::IO;
	using namespace System::Text::RegularExpressions;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_Closing);

		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ CLILocation;
	protected:


	private: System::Windows::Forms::TextBox^ CLI_LocationTextBox;
	private: System::Windows::Forms::Button^ FolderInput;


	private: System::Windows::Forms::TextBox^ FolderInputTextBox;

	private: FolderBrowserDialog^ folderDlg = gcnew FolderBrowserDialog;
	private:OpenFileDialog^ fileDlg = gcnew OpenFileDialog;

	private: System::Windows::Forms::TextBox^ PresetLocationTextBox;
	private: System::Windows::Forms::Button^ PresetLocation;

	private: System::Windows::Forms::TextBox^ MainOutput;
	private: System::Windows::Forms::Button^ CompressionStart;
	private: System::Windows::Forms::Button^ CompressionTest;
	private: System::Windows::Forms::ProgressBar^ CompressionProgress;
	private: System::Windows::Forms::TextBox^ FileNum;

	private: System::Diagnostics::Process^ currentProcess;  // Tracks the running HandBrakeCLI process
	private: bool cancelRequested = false;                 // Tracks if the user requested cancellation

	private: bool isTestRunFlag; // Tracks if this is a test run (no actual compression)
	private: System::Windows::Forms::CheckBox^ BatchMode; // Checkbox for batch mode

	private: bool isBatchMode = false; // Tracks if batch mode is enabled
	private: bool checkAllLayers = false; // Tracks current recursion depth setting

	private: bool deleteOriginals = false; // Tracks if original files should be deleted after compression

	private: System::Windows::Forms::TextBox^ RecursionDepth;
	private: System::Windows::Forms::RadioButton^ Depth1;
	private: System::Windows::Forms::RadioButton^ Depth2;
	private: System::Windows::Forms::CheckBox^ DeleteOriginals;



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->CLILocation = (gcnew System::Windows::Forms::Button());
			this->CLI_LocationTextBox = (gcnew System::Windows::Forms::TextBox());
			this->FolderInput = (gcnew System::Windows::Forms::Button());
			this->FolderInputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PresetLocationTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PresetLocation = (gcnew System::Windows::Forms::Button());
			this->MainOutput = (gcnew System::Windows::Forms::TextBox());
			this->CompressionStart = (gcnew System::Windows::Forms::Button());
			this->CompressionTest = (gcnew System::Windows::Forms::Button());
			this->CompressionProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->FileNum = (gcnew System::Windows::Forms::TextBox());
			this->BatchMode = (gcnew System::Windows::Forms::CheckBox());
			this->RecursionDepth = (gcnew System::Windows::Forms::TextBox());
			this->Depth1 = (gcnew System::Windows::Forms::RadioButton());
			this->Depth2 = (gcnew System::Windows::Forms::RadioButton());
			this->DeleteOriginals = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// CLILocation
			// 
			this->CLILocation->Location = System::Drawing::Point(12, 12);
			this->CLILocation->Name = L"CLILocation";
			this->CLILocation->Size = System::Drawing::Size(83, 23);
			this->CLILocation->TabIndex = 0;
			this->CLILocation->Text = L"CLI Location:";
			this->CLILocation->UseVisualStyleBackColor = true;
			this->CLILocation->Click += gcnew System::EventHandler(this, &Form1::CLI_LocationButton);
			// 
			// CLI_LocationTextBox
			// 
			this->CLI_LocationTextBox->Location = System::Drawing::Point(101, 14);
			this->CLI_LocationTextBox->Name = L"CLI_LocationTextBox";
			this->CLI_LocationTextBox->ReadOnly = true;
			this->CLI_LocationTextBox->Size = System::Drawing::Size(816, 20);
			this->CLI_LocationTextBox->TabIndex = 1;
			this->CLI_LocationTextBox->Text = L"C:\\Program Files\\HandBrake";
			// 
			// FolderInput
			// 
			this->FolderInput->Location = System::Drawing::Point(12, 42);
			this->FolderInput->Name = L"FolderInput";
			this->FolderInput->Size = System::Drawing::Size(83, 23);
			this->FolderInput->TabIndex = 2;
			this->FolderInput->Text = L"Folder Input:";
			this->FolderInput->UseVisualStyleBackColor = true;
			this->FolderInput->Click += gcnew System::EventHandler(this, &Form1::FolderInputButton);
			// 
			// FolderInputTextBox
			// 
			this->FolderInputTextBox->Location = System::Drawing::Point(101, 44);
			this->FolderInputTextBox->Name = L"FolderInputTextBox";
			this->FolderInputTextBox->ReadOnly = true;
			this->FolderInputTextBox->Size = System::Drawing::Size(816, 20);
			this->FolderInputTextBox->TabIndex = 3;
			this->FolderInputTextBox->Text = L"Please select the folder containing the files to be compressed";
			// 
			// PresetLocationTextBox
			// 
			this->PresetLocationTextBox->Location = System::Drawing::Point(101, 74);
			this->PresetLocationTextBox->Name = L"PresetLocationTextBox";
			this->PresetLocationTextBox->ReadOnly = true;
			this->PresetLocationTextBox->Size = System::Drawing::Size(816, 20);
			this->PresetLocationTextBox->TabIndex = 5;
			this->PresetLocationTextBox->Text = L"Please select the folder containing the preset you wish to be used";
			this->PresetLocationTextBox->Visible = false;
			// 
			// PresetLocation
			// 
			this->PresetLocation->Location = System::Drawing::Point(12, 72);
			this->PresetLocation->Name = L"PresetLocation";
			this->PresetLocation->Size = System::Drawing::Size(83, 23);
			this->PresetLocation->TabIndex = 4;
			this->PresetLocation->Text = L"Preset Input:";
			this->PresetLocation->UseVisualStyleBackColor = true;
			this->PresetLocation->Visible = false;
			this->PresetLocation->Click += gcnew System::EventHandler(this, &Form1::PresetLocationButton);
			// 
			// MainOutput
			// 
			this->MainOutput->Location = System::Drawing::Point(12, 113);
			this->MainOutput->Multiline = true;
			this->MainOutput->Name = L"MainOutput";
			this->MainOutput->ReadOnly = true;
			this->MainOutput->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->MainOutput->Size = System::Drawing::Size(905, 318);
			this->MainOutput->TabIndex = 6;
			// 
			// CompressionStart
			// 
			this->CompressionStart->Location = System::Drawing::Point(811, 467);
			this->CompressionStart->Name = L"CompressionStart";
			this->CompressionStart->Size = System::Drawing::Size(106, 23);
			this->CompressionStart->TabIndex = 7;
			this->CompressionStart->Text = L"Start Compression";
			this->CompressionStart->UseVisualStyleBackColor = true;
			this->CompressionStart->Click += gcnew System::EventHandler(this, &Form1::StartCompression_Click);
			// 
			// CompressionTest
			// 
			this->CompressionTest->Location = System::Drawing::Point(12, 467);
			this->CompressionTest->Name = L"CompressionTest";
			this->CompressionTest->Size = System::Drawing::Size(106, 23);
			this->CompressionTest->TabIndex = 8;
			this->CompressionTest->Text = L"Test Start";
			this->CompressionTest->UseVisualStyleBackColor = true;
			this->CompressionTest->Click += gcnew System::EventHandler(this, &Form1::TestCompression_Click);
			// 
			// CompressionProgress
			// 
			this->CompressionProgress->Location = System::Drawing::Point(13, 438);
			this->CompressionProgress->Name = L"CompressionProgress";
			this->CompressionProgress->Size = System::Drawing::Size(801, 23);
			this->CompressionProgress->TabIndex = 9;
			// 
			// FileNum
			// 
			this->FileNum->Location = System::Drawing::Point(821, 440);
			this->FileNum->Name = L"FileNum";
			this->FileNum->ReadOnly = true;
			this->FileNum->Size = System::Drawing::Size(96, 20);
			this->FileNum->TabIndex = 10;
			// 
			// BatchMode
			// 
			this->BatchMode->AutoSize = true;
			this->BatchMode->Location = System::Drawing::Point(445, 473);
			this->BatchMode->Name = L"BatchMode";
			this->BatchMode->Size = System::Drawing::Size(96, 17);
			this->BatchMode->TabIndex = 11;
			this->BatchMode->Text = L"Recurse Mode";
			this->BatchMode->UseVisualStyleBackColor = true;
			this->BatchMode->Click += gcnew System::EventHandler(this, &Form1::BatchMode_Click);
			// 
			// RecursionDepth
			// 
			this->RecursionDepth->Location = System::Drawing::Point(558, 469);
			this->RecursionDepth->Name = L"RecursionDepth";
			this->RecursionDepth->Size = System::Drawing::Size(92, 20);
			this->RecursionDepth->TabIndex = 12;
			this->RecursionDepth->Text = L"Recursion Depth:";
			this->RecursionDepth->Visible = false;
			// 
			// Depth1
			// 
			this->Depth1->AutoSize = true;
			this->Depth1->Checked = true;
			this->Depth1->Location = System::Drawing::Point(667, 462);
			this->Depth1->Name = L"Depth1";
			this->Depth1->Size = System::Drawing::Size(60, 17);
			this->Depth1->TabIndex = 13;
			this->Depth1->TabStop = true;
			this->Depth1->Text = L"1 Layer";
			this->Depth1->UseVisualStyleBackColor = true;
			this->Depth1->Visible = false;
			// 
			// Depth2
			// 
			this->Depth2->AutoSize = true;
			this->Depth2->Location = System::Drawing::Point(667, 480);
			this->Depth2->Name = L"Depth2";
			this->Depth2->Size = System::Drawing::Size(70, 17);
			this->Depth2->TabIndex = 14;
			this->Depth2->TabStop = true;
			this->Depth2->Text = L"All Layers";
			this->Depth2->UseVisualStyleBackColor = true;
			this->Depth2->Visible = false;
			this->Depth2->CheckedChanged += gcnew System::EventHandler(this, &Form1::Depth2_CheckedChanged);
			// 
			// DeleteOriginals
			// 
			this->DeleteOriginals->AutoSize = true;
			this->DeleteOriginals->Location = System::Drawing::Point(134, 471);
			this->DeleteOriginals->Name = L"DeleteOriginals";
			this->DeleteOriginals->Size = System::Drawing::Size(114, 17);
			this->DeleteOriginals->TabIndex = 15;
			this->DeleteOriginals->Text = L"Delete original files";
			this->DeleteOriginals->UseVisualStyleBackColor = true;
			this->DeleteOriginals->Click += gcnew System::EventHandler(this, &Form1::DeleteOriginals_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(944, 501);
			this->Controls->Add(this->DeleteOriginals);
			this->Controls->Add(this->Depth2);
			this->Controls->Add(this->Depth1);
			this->Controls->Add(this->RecursionDepth);
			this->Controls->Add(this->BatchMode);
			this->Controls->Add(this->FileNum);
			this->Controls->Add(this->CompressionProgress);
			this->Controls->Add(this->CompressionTest);
			this->Controls->Add(this->CompressionStart);
			this->Controls->Add(this->MainOutput);
			this->Controls->Add(this->PresetLocationTextBox);
			this->Controls->Add(this->PresetLocation);
			this->Controls->Add(this->FolderInputTextBox);
			this->Controls->Add(this->FolderInput);
			this->Controls->Add(this->CLI_LocationTextBox);
			this->Controls->Add(this->CLILocation);
			this->Name = L"Form1";
			this->Text = L"Compressinator";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void CLI_LocationButton(System::Object^ sender, System::EventArgs^ e) {

		if (folderDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			CLI_LocationTextBox->Text = folderDlg->SelectedPath;
		}

	}

	private: System::Void FolderInputButton(System::Object^ sender, System::EventArgs^ e) {

		if (folderDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) { // Opens folder browser dialog if button is clicked
			FolderInputTextBox->Text = folderDlg->SelectedPath;
		}

		String^ inputFolder = FolderInputTextBox->Text;
		checkInputFolder(inputFolder); // Check for video files in the selected folder

		PresetLocation->Visible = true;
		PresetLocationTextBox->Visible = true;
	}

	private: array<String^>^ checkInputFolder(String^ inputFolder) { // Checks the input folder for video files and returns an array of file paths
		array<String^>^ allFiles;
		array<String^>^ allSubFiles;
		AppendOutput("Scanning folder for video files: " + inputFolder);
		int videoCount;
		float totalSize;
		VideoFileManager::CountVideoFilesInDirectory(FolderInputTextBox->Text, videoCount, totalSize, allFiles);
		AppendOutput("Folder scan complete.");

		if (isBatchMode) { // If batch mode is enabled, check subdirectories for video files, keeping track of total video count and size
			array<String^>^ subFolders;
			AppendOutput("Batch Mode Enabled: Searching subdirectories for video files.");
			if (checkAllLayers) { // Check recursion depth setting
				AppendOutput("Recursion Depth: All Layers");
				subFolders = System::IO::Directory::GetDirectories(FolderInputTextBox->Text, "*", System::IO::SearchOption::AllDirectories);
			}
			else {
				AppendOutput("Recursion Depth: 1 Layer");
				subFolders = System::IO::Directory::GetDirectories(FolderInputTextBox->Text, "*", System::IO::SearchOption::TopDirectoryOnly);
			}

			AppendOutput("Found " + subFolders->Length + " subdirectories.");
			int subFolderCount = 1;

			for each(String ^ folder in subFolders) {
				AppendOutput("Scanning subdirectory " + subFolderCount + " of " + subFolders->Length + ": " + folder);
				AppendOutput("Subdirectory " + subFolderCount + " path: " + FolderInputTextBox->Text + folder);

				int subVideoCount;
				float subTotalSize;
				VideoFileManager::CountVideoFilesInDirectory(folder, subVideoCount, subTotalSize, allSubFiles);
				videoCount += subVideoCount;
				totalSize += subTotalSize;
				subFolderCount++;

				int subFolderSize = allSubFiles->Length;
				int allFilesSize = allFiles->Length;
				Array::Resize(allFiles, subFolderSize + allFilesSize);
				Array::Copy(allSubFiles, 0, allFiles, allFilesSize, subFolderSize);
				videoCount += subFolderSize;
			}
		}

		AppendOutput("Number of video files found: " + videoCount);

		if (totalSize > 1024) { // Display total size in GiB if over 1024 MiB
			totalSize = totalSize / 1024;
			AppendOutput("Total size of video files: " + static_cast<float>(Math::Round(totalSize, 2)) + " GB");
		}

		else { // Otherwise display total size in MiB
			totalSize = static_cast<float>(Math::Round(totalSize, 2));
			AppendOutput("Total size of video files: " + totalSize + " MB");
		}
		return allFiles;
	}


	private: System::Void PresetLocationButton(System::Object^ sender, System::EventArgs^ e) {
		if (fileDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			PresetLocationTextBox->Text = fileDlg->FileName;
		}
	}

	private: System::Void TestCompression_Click(System::Object^ sender, System::EventArgs^ e) {
		AppendOutput("\r\n\nTest Run Initiated");
		compressFiles(true);

	}
	private: System::Void StartCompression_Click(System::Object^ sender, System::EventArgs^ e) {
		AppendOutput("\r\n\nCompression Started");
		compressFiles(false);
	}

	private: System::Void compressFiles(bool isTestRun) { // Starts compression in a background Task to keep UI responsive
		isTestRunFlag = isTestRun;
		Task::Run(gcnew Action(this, &Form1::RunCompressionWrapper));
	}

	private: void RunCompressionWrapper() { // Wrapper to call RunCompression and handle exceptions
		try {
			RunCompression(isTestRunFlag);
		}
		catch (Exception^ ex) {
			AppendOutput("An error occurred: " + ex->Message);
		}
	}

	private: void RunCompression(bool isTestRun) { // Main compression logic
		cancelRequested = false;
		MainOutput->Invoke(gcnew Action(this, &Form1::ClearMainOutput)); // Clear output box at start

		this->Invoke(gcnew Action<bool>(this, &Form1::SetControlsEnabled), false); // Disable buttons during compression

		String^ handbrakeCLIPath = System::IO::Path::Combine(CLI_LocationTextBox->Text, "HandBrakeCLI.exe");
		
		String^ presetFile = PresetLocationTextBox->Text;

		String^ inputFolder = FolderInputTextBox->Text;

		if (!System::IO::File::Exists(handbrakeCLIPath)) { // Validate HandBrakeCLI path
			AppendOutput("HandBrakeCLI not found at: " + handbrakeCLIPath);
			this->Invoke(gcnew Action<bool>(this, &Form1::SetControlsEnabled), true);
			return;
		}

		if (!System::IO::Directory::Exists(inputFolder)) { // Validate input folder
			AppendOutput("Input folder does not exist: " + inputFolder);
			this->Invoke(gcnew Action<bool>(this, &Form1::SetControlsEnabled), true);
			return;
		}

		if (!System::IO::File::Exists(presetFile)) { // Validate preset file
			AppendOutput("Preset file not found: " + presetFile);
			this->Invoke(gcnew Action<bool>(this, &Form1::SetControlsEnabled), true);
			return;
		}


		array<String^>^ videoFiles; 
		videoFiles = checkInputFolder(inputFolder);
		FileNum->Invoke(gcnew Action<String^>(this, &Form1::UpdateFileNum), "0 / " + videoFiles->Length.ToString()); // Initialize file counter display

		int currentFileIndex = 1;
		for each(String ^ inputFile in videoFiles) { // Loop through each video file and compress
			if (cancelRequested) {
				break;
			}
			CompressionProgress->Invoke(gcnew Action(this, &Form1::ResetProgress)); // Reset progress bar for each file
			FileNum->Invoke(gcnew Action<String^>(this, &Form1::UpdateFileNum), 
				(currentFileIndex.ToString() + " / " + videoFiles->Length.ToString())); // Update file counter display

			String^ inputFolder = System::IO::Path::GetDirectoryName(inputFile);
			String^ outputFolder = System::IO::Path::Combine(inputFolder, "Compressed");

			if (!System::IO::Directory::Exists(outputFolder)) { // Create output folder if it doesn't exist
				System::IO::Directory::CreateDirectory(outputFolder);
			}

			String^ fileName = System::IO::Path::GetFileName(inputFile);
			String^ outputFile = System::IO::Path::Combine(outputFolder, fileName);

			String^ args;
			String^ presetName = GetPresetNameFromJson(presetFile); // Extract preset name from JSON file
			if (!String::IsNullOrEmpty(presetName)) { 
				AppendOutput("Applying preset: " + presetName); 
				args = String::Format("-i \"{0}\" -o \"{1}\" --preset-import-file \"{2}\" -Z \"{3}\"", 
					inputFile, outputFile, presetFile, presetName);
			}
			else { // Fallback if no preset name found
				AppendOutput("No preset name found in JSON; only importing the file.");
				args = String::Format("-i \"{0}\" -o \"{1}\" --preset-import-file \"{2}\"",
					inputFile, outputFile, presetFile);
			}


			if (isTestRun) { // In test mode, just log what would be done
				AppendOutput("Would compress " + fileName + " to " + outputFile);
				if (deleteOriginals) { AppendOutput("Would delete " + fileName + " after compression"); }
				continue;
			}

			System::Diagnostics::ProcessStartInfo^ psi = gcnew System::Diagnostics::ProcessStartInfo();
			psi->FileName = handbrakeCLIPath;
			psi->Arguments = args;
			psi->UseShellExecute = false;
			psi->RedirectStandardOutput = true;
			psi->RedirectStandardError = true;
			psi->CreateNoWindow = true;

			System::Diagnostics::Process^ process = gcnew System::Diagnostics::Process();
			process->StartInfo = psi;
			process->EnableRaisingEvents = true;

			// attach handlers BEFORE Start
			process->OutputDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &Form1::Process_OutputDataReceived); 
			process->ErrorDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &Form1::Process_ErrorDataReceived);

			AppendOutput("Running: " + handbrakeCLIPath + " " + args);

			// track it so FormClosing / Cancel can kill it
			currentProcess = process;

			process->Start();
			process->BeginOutputReadLine();
			process->BeginErrorReadLine();

			// Wait for it to complete 
			process->WaitForExit();

			// clear tracker
			try {
				process->Close();
			}
			catch (Exception^) { /* ignore */ }
			currentProcess = nullptr;

			if (!isTestRun && deleteOriginals) {
				try {
					System::IO::File::Delete(inputFile);
					AppendOutput("Deleted original file: " + inputFile);
				}
				catch (Exception^ ex) {
					AppendOutput("\r\nError deleting file: " + inputFile + " Erorr: " + ex->Message);
				}
			}

			currentFileIndex++;
		}
		this->Invoke(gcnew Action<bool>(this, &Form1::SetControlsEnabled), true);
	}

	private: void Process_OutputDataReceived(Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e) { // Handle standard output from HandBrakeCLI
		if (!String::IsNullOrEmpty(e->Data)) { 
			MainOutput->Invoke(gcnew Action<String^>(this, &Form1::AppendOutput), e->Data); 
			// Look for HandBrake progress percentage
			System::Text::RegularExpressions::Match^ match = System::Text::RegularExpressions::Regex::Match(e->Data, "(\\d{1,3}\\.\\d{1,2}) %");
			if (match->Success) {
				int percent = safe_cast<int>(Convert::ToDouble(match->Groups[1]->Value));

				CompressionProgress->Invoke(gcnew Action<int>(this, &Form1::UpdateProgressBar), percent);
			}
		}
	}

	private: void UpdateProgressBar(int val) {
		CompressionProgress->Value = val;
	}

	private: void UpdateFileNum(String^ text) {
		FileNum->Text = text;
	}

	private: void ResetProgress() {
		CompressionProgress->Value = 0;
	}

	private: void Process_ErrorDataReceived(Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e) {
		if (!String::IsNullOrEmpty(e->Data)) {
			MainOutput->Invoke(gcnew Action<String^>(this, &Form1::AppendOutput), "HandbrakeCLI: " + e->Data);
		}
	}

	private: void AppendOutput(String^ text) {
		// Ensure we are on the UI thread
		if (MainOutput->InvokeRequired) {
			MainOutput->Invoke(gcnew Action<String^>(this, &Form1::AppendOutput), text);
			return;
		}

		MainOutput->AppendText(text + "\r\n");
	}

	private: void ClearMainOutput() {
		MainOutput->Clear();
	}

	private: void SetControlsEnabled(bool enabled) {
		CompressionStart->Enabled = enabled;
		CompressionTest->Enabled = enabled;
	}


	private: System::Void Form1_Closing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		cancelRequested = true; // signal the loop to stop

		if (currentProcess != nullptr && !currentProcess->HasExited) {
			try {
				currentProcess->Kill(); // force-stop HandBrakeCLI
				currentProcess->WaitForExit();
			}
			catch (Exception^) {
				// ignore errors if process already exited
			}
		}
	}

	private: String^ GetPresetNameFromJson(String^ presetFilePath) {
		if (String::IsNullOrEmpty(presetFilePath) || !File::Exists(presetFilePath)) return nullptr;

		try {
			String^ json = File::ReadAllText(presetFilePath);
			// Find first occurrence of "PresetName": "Some Preset Name"
			// This is simple and works for typical exported HandBrake preset json files.
			Match^ m = Regex::Match(json, "\"PresetName\"\\s*:\\s*\"([^\"]+)\"", RegexOptions::IgnoreCase);
			if (m->Success) return m->Groups[1]->Value;
		}
		catch (Exception^) {
			// ignore or log error
		}
		return nullptr;
	}

	private: System::Void BatchMode_Click(System::Object^ sender, System::EventArgs^ e) {
		
		if (BatchMode->Checked) {
			isBatchMode = true;
			AppendOutput("Recurse Mode Enabled - Will check input folder for more folders");
		}
		else {
			isBatchMode = false;
			AppendOutput("Recurse Mode Disabled - Will only check input folder");
		}

		RecursionDepth->Visible = isBatchMode;
		Depth1->Visible = isBatchMode;
		Depth2->Visible = isBatchMode;

		if (FolderInputTextBox->Text != "Please select the folder containing the files to be compressed") {
			String^ inputFolder = FolderInputTextBox->Text;
			checkInputFolder(inputFolder);
		}

	}
private: System::Void Depth2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (Depth2->Checked) {
		checkAllLayers = true;
	}
	else {
		checkAllLayers = false;
	}
	if (FolderInputTextBox->Text != "Please select the folder containing the files to be compressed") {
		String^ inputFolder = FolderInputTextBox->Text;
		checkInputFolder(inputFolder);
	}
}
private: System::Void DeleteOriginals_Click(System::Object^ sender, System::EventArgs^ e) {
	if (DeleteOriginals->Checked) {
		AppendOutput("Original files will be deleted after compression.");
		deleteOriginals = true;
	}
	else {
		AppendOutput("Original files will be kept after compression.");
		deleteOriginals = false;
	}
}
};
}
