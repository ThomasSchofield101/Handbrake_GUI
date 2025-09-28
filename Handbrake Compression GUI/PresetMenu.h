#pragma once

namespace MyApp {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class PresetMenu : public Form
    {
    public:
        PresetMenu(void)
        {
            InitializeComponent();
        }

    protected:
        ~PresetMenu()
        {
            if (components)
                delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->SuspendLayout();
            // 
            // PresetMenu
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(284, 261);
            this->Name = L"PresetMenu";
            this->Text = L"PresetMenu";
            this->ResumeLayout(false);
        }
    };
}
