#pragma once
#using <System.Drawing.dll>

inline System::Drawing::Size GetHalfMonitorSize() {
    System::Drawing::Size fullSize = System::Windows::Forms::Screen::PrimaryScreen->Bounds.Size;
    return System::Drawing::Size(fullSize.Width / 2, fullSize.Height / 2);
}


