#pragma once
#include "DotNetUtilities.h"
#include "GUA_OM.h"
#include <LinearSystemLib.h>
#include "glext.h"
#include <cmath>
#include <map>
#include <windows.h>
#include <gl/glut.h>
#include <cv.h>
#include <highgui.h> 
#include <cxcore.h>
#include "Data.h"

std::vector<NewInfo*> n_info;
int info_idx=0;
OMT::Point p[4];
bool md=false;
bool rd=false;//旋轉
int px,py,sx,sy;
double tx=0,ty=0;
OMT::Point rp[4];
bool solidwire=true;
using namespace LinearSystemLib;
namespace OpenMesh_Parameterization {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			// ------------------------------------------------------------------
			p[0] = OMT::Point(0,1);
			p[1] = OMT::Point(1,1);
			p[2] = OMT::Point(1,0);
			p[3] = OMT::Point(0,0);
			// OpenGL Initiation

			// Get Handle
			m_hWnd = (HWND)this->pictureBox1->Handle.ToInt32();
			m_hDC = GetDC( m_hWnd );

			// Set pixel format
			PIXELFORMATDESCRIPTOR pfd;
			ZeroMemory( &pfd, sizeof( pfd ) );
			pfd.nSize = sizeof( pfd );
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
				PFD_SUPPORT_OPENGL | 
				PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 32;
			pfd.iLayerType = PFD_MAIN_PLANE;
			int nFormat = ChoosePixelFormat( m_hDC, &pfd );
			SetPixelFormat( m_hDC, nFormat, &pfd );

			// Create OpenGL Rendering Context
			m_hRC = wglCreateContext( m_hDC );
			// Assign OpenGL Rendering Context
			if (wglMakeCurrent( m_hDC, m_hRC ) == false) 
				MessageBox::Show("wglMakeCurrent Error", "Error");
			// ------------------------------------------------------------------

			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  modelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  imageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  scriptToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  scriptToolStripMenuItem1;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog1;
	private: GLPanel::GLPanelControl^  glPanelControl1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;
	private: GLPanel::GLPanelControl^  glPanelControl2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::OpenFileDialog^  openImageDialog1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::RadioButton^  AddRadioButton;
	private: System::Windows::Forms::RadioButton^  EditRadioButton;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

	private: System::Windows::Forms::OpenFileDialog^  openScriptDialog1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::RadioButton^  DeleteRadioButton;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::ToolStripMenuItem^  viewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  solidWireToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  solidToolStripMenuItem;


	private: System::ComponentModel::IContainer^  components;




	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			GLPanel::HKCCameraProp^  hkcCameraProp3 = (gcnew GLPanel::HKCCameraProp());
			GLPanel::HKCDisplayProp^  hkcDisplayProp3 = (gcnew GLPanel::HKCDisplayProp());
			GLPanel::HKCPixelFormat^  hkcPixelFormat3 = (gcnew GLPanel::HKCPixelFormat());
			GLPanel::HKCTrackballProp^  hkcTrackballProp3 = (gcnew GLPanel::HKCTrackballProp());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig7 = (gcnew GLPanel::HKCTrackballTrig());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig8 = (gcnew GLPanel::HKCTrackballTrig());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig9 = (gcnew GLPanel::HKCTrackballTrig());
			GLPanel::HKCCameraProp^  hkcCameraProp4 = (gcnew GLPanel::HKCCameraProp());
			GLPanel::HKCDisplayProp^  hkcDisplayProp4 = (gcnew GLPanel::HKCDisplayProp());
			GLPanel::HKCPixelFormat^  hkcPixelFormat4 = (gcnew GLPanel::HKCPixelFormat());
			GLPanel::HKCTrackballProp^  hkcTrackballProp4 = (gcnew GLPanel::HKCTrackballProp());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig10 = (gcnew GLPanel::HKCTrackballTrig());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig11 = (gcnew GLPanel::HKCTrackballTrig());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig12 = (gcnew GLPanel::HKCTrackballTrig());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->modelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->imageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->scriptToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->scriptToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->glPanelControl1 = (gcnew GLPanel::GLPanelControl());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->glPanelControl2 = (gcnew GLPanel::GLPanelControl());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->openImageDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->AddRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->EditRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openScriptDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->DeleteRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->solidWireToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->solidToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->loadToolStripMenuItem, 
				this->saceToolStripMenuItem, this->viewToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1251, 32);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->modelToolStripMenuItem, 
				this->imageToolStripMenuItem, this->scriptToolStripMenuItem});
			this->loadToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14));
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(66, 28);
			this->loadToolStripMenuItem->Text = L"Load";
			// 
			// modelToolStripMenuItem
			// 
			this->modelToolStripMenuItem->Name = L"modelToolStripMenuItem";
			this->modelToolStripMenuItem->Size = System::Drawing::Size(138, 28);
			this->modelToolStripMenuItem->Text = L"Model";
			this->modelToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::modelToolStripMenuItem_Click);
			// 
			// imageToolStripMenuItem
			// 
			this->imageToolStripMenuItem->Name = L"imageToolStripMenuItem";
			this->imageToolStripMenuItem->Size = System::Drawing::Size(138, 28);
			this->imageToolStripMenuItem->Text = L"Image";
			this->imageToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::imageToolStripMenuItem_Click);
			// 
			// scriptToolStripMenuItem
			// 
			this->scriptToolStripMenuItem->Name = L"scriptToolStripMenuItem";
			this->scriptToolStripMenuItem->Size = System::Drawing::Size(138, 28);
			this->scriptToolStripMenuItem->Text = L"Script";
			this->scriptToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::scriptToolStripMenuItem_Click);
			// 
			// saceToolStripMenuItem
			// 
			this->saceToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->scriptToolStripMenuItem1});
			this->saceToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14));
			this->saceToolStripMenuItem->Name = L"saceToolStripMenuItem";
			this->saceToolStripMenuItem->Size = System::Drawing::Size(64, 28);
			this->saceToolStripMenuItem->Text = L"Save";
			// 
			// scriptToolStripMenuItem1
			// 
			this->scriptToolStripMenuItem1->Name = L"scriptToolStripMenuItem1";
			this->scriptToolStripMenuItem1->Size = System::Drawing::Size(131, 28);
			this->scriptToolStripMenuItem1->Text = L"Script";
			this->scriptToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::scriptToolStripMenuItem1_Click);
			// 
			// openModelDialog1
			// 
			this->openModelDialog1->FileName = L"openModelDialog1";
			this->openModelDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openModelDialog1_FileOk);
			// 
			// glPanelControl1
			// 
			hkcCameraProp3->Enabled = true;
			hkcCameraProp3->Far = 1000;
			hkcCameraProp3->Fov = 45;
			hkcCameraProp3->Near = 0.001;
			hkcCameraProp3->Type = GLPanel::HKCCameraProp::CAMERATYPE::PERSPECTIVE;
			hkcCameraProp3->Zoom = 3;
			this->glPanelControl1->Camera_Property = hkcCameraProp3;
			hkcDisplayProp3->Back_Color = System::Drawing::Color::White;
			hkcDisplayProp3->Grid_Axis = System::Drawing::Color::Black;
			hkcDisplayProp3->Grid_Draw = true;
			hkcDisplayProp3->Grid_Line = System::Drawing::Color::DimGray;
			this->glPanelControl1->Display_Property = hkcDisplayProp3;
			this->glPanelControl1->Empty_Panel = false;
			this->glPanelControl1->Location = System::Drawing::Point(0, 70);
			this->glPanelControl1->Name = L"glPanelControl1";
			hkcPixelFormat3->Accumu_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			hkcPixelFormat3->Alpha_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			hkcPixelFormat3->Stencil_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			this->glPanelControl1->Pixel_Format = hkcPixelFormat3;
			this->glPanelControl1->Size = System::Drawing::Size(400, 400);
			this->glPanelControl1->TabIndex = 1;
			hkcTrackballProp3->Const_Res = false;
			hkcTrackballProp3->Delta_Res = 166.66666666666666;
			hkcTrackballProp3->Enabled = true;
			hkcTrackballProp3->Move_Res = 333.33333333333331;
			hkcTrackballTrig7->Key_Down = false;
			hkcTrackballTrig7->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig7->Mouse = System::Windows::Forms::MouseButtons::Right;
			hkcTrackballTrig7->Mouse_Down = false;
			hkcTrackballProp3->Move_Trigger = hkcTrackballTrig7;
			hkcTrackballTrig8->Key_Down = false;
			hkcTrackballTrig8->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig8->Mouse = System::Windows::Forms::MouseButtons::Left;
			hkcTrackballTrig8->Mouse_Down = false;
			hkcTrackballProp3->Rotate_Trigger = hkcTrackballTrig8;
			hkcTrackballProp3->Zoom_Res = 33.333333333333336;
			hkcTrackballTrig9->Key_Down = false;
			hkcTrackballTrig9->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig9->Mouse = System::Windows::Forms::MouseButtons::Middle;
			hkcTrackballTrig9->Mouse_Down = false;
			hkcTrackballProp3->Zoom_Trigger = hkcTrackballTrig9;
			this->glPanelControl1->Trackball_Property = hkcTrackballProp3;
			this->glPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::glPanelControl1_Paint);
			this->glPanelControl1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::glPanelControl1_KeyDown);
			this->glPanelControl1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::glPanelControl1_KeyUp);
			this->glPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::glPanelControl1_MouseDown);
			this->glPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::glPanelControl1_MouseMove);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(839, 70);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(400, 400);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseUp);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(779, 515);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(93, 41);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// glPanelControl2
			// 
			hkcCameraProp4->Enabled = true;
			hkcCameraProp4->Far = 1000;
			hkcCameraProp4->Fov = 45;
			hkcCameraProp4->Near = 0.001;
			hkcCameraProp4->Type = GLPanel::HKCCameraProp::CAMERATYPE::PERSPECTIVE;
			hkcCameraProp4->Zoom = 3;
			this->glPanelControl2->Camera_Property = hkcCameraProp4;
			hkcDisplayProp4->Back_Color = System::Drawing::Color::White;
			hkcDisplayProp4->Grid_Axis = System::Drawing::Color::Black;
			hkcDisplayProp4->Grid_Draw = true;
			hkcDisplayProp4->Grid_Line = System::Drawing::Color::DimGray;
			this->glPanelControl2->Display_Property = hkcDisplayProp4;
			this->glPanelControl2->Empty_Panel = false;
			this->glPanelControl2->Location = System::Drawing::Point(421, 70);
			this->glPanelControl2->Name = L"glPanelControl2";
			hkcPixelFormat4->Accumu_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			hkcPixelFormat4->Alpha_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			hkcPixelFormat4->Stencil_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			this->glPanelControl2->Pixel_Format = hkcPixelFormat4;
			this->glPanelControl2->Size = System::Drawing::Size(400, 400);
			this->glPanelControl2->TabIndex = 4;
			hkcTrackballProp4->Const_Res = false;
			hkcTrackballProp4->Delta_Res = 166.66666666666666;
			hkcTrackballProp4->Enabled = true;
			hkcTrackballProp4->Move_Res = 333.33333333333331;
			hkcTrackballTrig10->Key_Down = false;
			hkcTrackballTrig10->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig10->Mouse = System::Windows::Forms::MouseButtons::Right;
			hkcTrackballTrig10->Mouse_Down = false;
			hkcTrackballProp4->Move_Trigger = hkcTrackballTrig10;
			hkcTrackballTrig11->Key_Down = false;
			hkcTrackballTrig11->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig11->Mouse = System::Windows::Forms::MouseButtons::Left;
			hkcTrackballTrig11->Mouse_Down = false;
			hkcTrackballProp4->Rotate_Trigger = hkcTrackballTrig11;
			hkcTrackballProp4->Zoom_Res = 33.333333333333336;
			hkcTrackballTrig12->Key_Down = false;
			hkcTrackballTrig12->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig12->Mouse = System::Windows::Forms::MouseButtons::Middle;
			hkcTrackballTrig12->Mouse_Down = false;
			hkcTrackballProp4->Zoom_Trigger = hkcTrackballTrig12;
			this->glPanelControl2->Trackball_Property = hkcTrackballProp4;
			this->glPanelControl2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::glPanelControl2_Paint);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(137, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(125, 31);
			this->label1->TabIndex = 5;
			this->label1->Text = L"3D Model";
			// 
			// openImageDialog1
			// 
			this->openImageDialog1->FileName = L"openImageDialog1";
			this->openImageDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openImageDialog1_FileOk);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(578, 36);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 31);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Result";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(939, 36);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(138, 31);
			this->label3->TabIndex = 7;
			this->label3->Text = L"2D Texture";
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Location = System::Drawing::Point(12, 478);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(300, 160);
			this->listBox1->TabIndex = 8;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox1_SelectedIndexChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(518, 515);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(93, 41);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Clear Select Fh";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// AddRadioButton
			// 
			this->AddRadioButton->AutoSize = true;
			this->AddRadioButton->Checked = true;
			this->AddRadioButton->Location = System::Drawing::Point(367, 515);
			this->AddRadioButton->Name = L"AddRadioButton";
			this->AddRadioButton->Size = System::Drawing::Size(106, 16);
			this->AddRadioButton->TabIndex = 11;
			this->AddRadioButton->TabStop = true;
			this->AddRadioButton->Text = L"Add New Texture";
			this->AddRadioButton->UseVisualStyleBackColor = true;
			// 
			// EditRadioButton
			// 
			this->EditRadioButton->AutoSize = true;
			this->EditRadioButton->Location = System::Drawing::Point(367, 555);
			this->EditRadioButton->Name = L"EditRadioButton";
			this->EditRadioButton->Size = System::Drawing::Size(81, 16);
			this->EditRadioButton->TabIndex = 12;
			this->EditRadioButton->Text = L"Edit Texture";
			this->EditRadioButton->UseVisualStyleBackColor = true;
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::saveFileDialog1_FileOk);
			// 
			// openScriptDialog1
			// 
			this->openScriptDialog1->FileName = L"openScriptDialog1";
			this->openScriptDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openScriptDialog1_FileOk);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(647, 515);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(93, 41);
			this->button3->TabIndex = 13;
			this->button3->Text = L"上下翻轉";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(647, 574);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(93, 41);
			this->button4->TabIndex = 14;
			this->button4->Text = L"左右翻轉";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// DeleteRadioButton
			// 
			this->DeleteRadioButton->AutoSize = true;
			this->DeleteRadioButton->Location = System::Drawing::Point(367, 599);
			this->DeleteRadioButton->Name = L"DeleteRadioButton";
			this->DeleteRadioButton->Size = System::Drawing::Size(91, 16);
			this->DeleteRadioButton->TabIndex = 15;
			this->DeleteRadioButton->Text = L"Delete Texture";
			this->DeleteRadioButton->UseVisualStyleBackColor = true;
			// 
			// timer1
			// 
			this->timer1->Interval = 16;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(922, 582);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(93, 41);
			this->button5->TabIndex = 16;
			this->button5->Text = L"Scale";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(779, 593);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 17;
			this->textBox1->Text = L"1";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(518, 574);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(93, 41);
			this->button6->TabIndex = 18;
			this->button6->Text = L"復原貼圖座標";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// viewToolStripMenuItem
			// 
			this->viewToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->solidWireToolStripMenuItem, 
				this->solidToolStripMenuItem});
			this->viewToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14));
			this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
			this->viewToolStripMenuItem->Size = System::Drawing::Size(66, 28);
			this->viewToolStripMenuItem->Text = L"View";
			// 
			// solidWireToolStripMenuItem
			// 
			this->solidWireToolStripMenuItem->Name = L"solidWireToolStripMenuItem";
			this->solidWireToolStripMenuItem->Size = System::Drawing::Size(167, 28);
			this->solidWireToolStripMenuItem->Text = L"SolidWire";
			this->solidWireToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::solidWireToolStripMenuItem_Click);
			// 
			// solidToolStripMenuItem
			// 
			this->solidToolStripMenuItem->Name = L"solidToolStripMenuItem";
			this->solidToolStripMenuItem->Size = System::Drawing::Size(167, 28);
			this->solidToolStripMenuItem->Text = L"Solid";
			this->solidToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::solidToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1251, 650);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->DeleteRadioButton);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->EditRadioButton);
			this->Controls->Add(this->AddRadioButton);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->glPanelControl2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->glPanelControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
//private: Image^ emptyImg;
private: System::Void modelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 openModelDialog1->ShowDialog();
			 }
private: System::Void openModelDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 std::string filename;
			 MarshalString( openModelDialog1->FileName, filename );
			 
			 if( mesh != NULL )
				 delete mesh ;

			 mesh = new Tri_Mesh;


			 if(ReadFile(  filename, mesh  ) )
			 {
				 std::cout<<filename<<std::endl;
				 mesh->select_fh = mesh->face_handle(0) ;
				 mesh->select_vh = mesh->vertex_handle(0);
			 }
			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
			 
		 }
private: System::Void openImageDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 std::string filename;
			 MarshalString( openImageDialog1->FileName, filename );
			 
			 int n=filename.length();
			 if( filename[n-3]=='b' && filename[n-2]=='m' && filename[n-1]=='p' )
			 {
				 n_filename = filename;
				 MessageBox::Show("Load Img Success!!");
				 //pictureBox1->Image = Image::FromFile(openImageDialog1->FileName);
			 }
			 else
			 {
				 MessageBox::Show("Load Img Fail!!");
				 n_filename = "NULL";
			 }
		     
			 
			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
		 }
private: System::Void openScriptDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 std::string filename;
			 MarshalString( openScriptDialog1->FileName, filename );

			 int n=filename.length();
			 if( filename[n-3]=='t' && filename[n-2]=='x' && filename[n-1]=='t' )
			 {
				 NewInfo *tInfo = new NewInfo();
				 tInfo->LoadInfo(filename,mesh);
				 tInfo->draw2DPos = true;
				 tInfo->isLoadImg = false;
				 n_info.push_back(tInfo);
				 listBox1->Items->Add("Texture : " + (n_info.size()-1));
			 }
			 else
			 {
				 MessageBox::Show("Load Script Fail!!");
			 }
			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
		 }
private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 std::string filename;
			 MarshalString( saveFileDialog1->FileName, filename );
			 n_info[info_idx]->SaveInfo(filename,mesh);
		 }
private: System::Void imageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 openImageDialog1->ShowDialog();
		 }
private: System::Void scriptToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 openScriptDialog1->ShowDialog();
		 }
private: System::Void scriptToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveFileDialog1->ShowDialog();
		 }
private: System::Void pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
// 			 if(pictureBox1->Image)
// 			 {
// 				 float fx = pictureBox1->Width / pictureBox1->Image->Width;
// 				 float fy = pictureBox1->Height / pictureBox1->Image->Height;
// 				 e->Graphics->ScaleTransform(fx,fy);
// 			 }
// 			 System::Drawing::Pen^ myPen;
// 			 myPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
// 			 myPen->Width = 3;
// 			 if(n_info.size()!=0)
// 			 {
// 
// 				 if(n_info[info_idx]->draw2DPos)
// 				 {
// 					 Tri_Mesh *newMesh = n_info[info_idx]->newMesh;
// 					 for(OMT::VIter v_it = newMesh->vertices_begin(); v_it != newMesh->vertices_end(); ++v_it)
// 					 {
// 						 OMT::Point currentV = n_info[info_idx]->texturePos[v_it.handle().idx()];
// 						 for(OMT::VVIter vv_it = newMesh->vv_iter(v_it.handle());vv_it;++vv_it)
// 						 {
// 							 OMT::Point currentV2 = n_info[info_idx]->texturePos[vv_it.handle().idx()];
// 							 int x1,x2,y1,y2;
// 							 x1 = (int)(currentV[0] * pictureBox1->Width);
// 							 y1 = (int)((1.0 - currentV[1]) * pictureBox1->Height);
// 							 x2 = (int)(currentV2[0] * pictureBox1->Width);
// 							 y2 =(int)((1.0 - currentV2[1]) * pictureBox1->Height);
// 							 e->Graphics->DrawLine(myPen,x1,y1,x2,y2);
// 						 }
// 					 }
// 				 }
// 			 }
		 }
private: System::Void glPanelControl1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if ( e->KeyCode == System::Windows::Forms::Keys::ControlKey )
			 {
				 isDelFace = true;
				 isFace = false;
				 glPanelControl1->Trackball_Property->Enabled = false ;
			 }
			 else if ( e->KeyCode == System::Windows::Forms::Keys::ShiftKey )
			 {
				 isDelFace = false;
				 isFace = true;
				 glPanelControl1->Trackball_Property->Enabled = false ;
			 }
			 

			 if( e->KeyCode == System::Windows::Forms::Keys::A )
			 {
				 std::vector<OMT::FHandle>	mfh;
				 for(int i=0;i<mesh->select_mfh.size();i++)
				 {
					 mfh.push_back(mesh->select_mfh[i]);
					 for(OMT::FFIter ff_it = mesh->ff_iter(mesh->select_mfh[i]);ff_it;++ff_it)
					 {
						 mfh.push_back(ff_it.handle());
					 }
				 }
				 for(int i=0;i<mfh.size()-1;i++)
				 {
					 for(int j=i+1;j<mfh.size();j++)
					 {
						 if( mfh[i]==mfh[j] )
						 {
							 mfh.erase(mfh.begin()+j);
							 j--;
						 }
					 }
				 }
				 mesh->select_mfh = mfh;
			 }
			 glPanelControl1->Invalidate();
		 }
private: System::Void glPanelControl1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if ( e->KeyCode == System::Windows::Forms::Keys::ControlKey )
			 {
				 glPanelControl1->Trackball_Property->Enabled = true ;
				 isDelFace = false;
				 isFace = false;
			 }
			 else if ( e->KeyCode == System::Windows::Forms::Keys::ShiftKey )
			 {
				 glPanelControl1->Trackball_Property->Enabled = true ;
				 isDelFace = false;
				 isFace = false;
			 }
			 glPanelControl1->Invalidate();
		 }
private: System::Void glPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 }
private: System::Void glPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 int Op_X,Op_Y;
			 Op_X = e->X ;
			 Op_Y = glPanelControl1->Height - e->Y ;
			 if ( e->Button == System::Windows::Forms::MouseButtons::Right )
			 {   
				 if( !glPanelControl1->Trackball_Property->Enabled)  
				 {
					 if(isFace){
						 if(mesh!=NULL)mesh->Select_MulFace( Op_X, Op_Y );
					 }
					 else if(isDelFace){
						 if(mesh!=NULL)mesh->Delete_MulFace( Op_X, Op_Y );
					 }
				 }
			 }
			 glPanelControl1->Invalidate();
		 }
private: std::vector<OMT::VHandle> GetInsideVertices(Tri_Mesh* m)
		{
			std::vector<OMT::VHandle> i_vh;
			for(OMT::VIter v_it = m->vertices_begin();v_it!=m->vertices_end();++v_it)
			{
				if(!m->is_boundary(v_it.handle()))
					i_vh.push_back(v_it.handle());
			}
			return i_vh;
		}
private: double GetTotalLength(Tri_Mesh* m)
		{
			double sum=0;
			OMT::HEHandle heh = m->halfedge_handle(m->vertices_begin().handle());
			OMT::HEHandle heh_init = heh;
			for(OMT::VIter v_it = m->vertices_begin();v_it!=m->vertices_end();++v_it)			//Find boundary
			{
				if(m->is_boundary(v_it.handle()))
				{
					heh = heh_init = m->halfedge_handle(v_it.handle());

					if(!(m->is_boundary(heh_init)))
					{
						heh_init = m->opposite_halfedge_handle(heh_init);
						heh = heh_init;
					}

					break;
				}
			}
			OMT::VHandle current = m->from_vertex_handle(heh);
			OMT::VHandle to_vh = m->to_vertex_handle(heh);
			do
			{
				sum += ( m->point(to_vh) - m->point(current) ).length();
				current = to_vh;
				heh = m->next_halfedge_handle(heh);
				to_vh = m->to_vertex_handle(heh);
			}while(heh != heh_init);
			return sum;
		}
private: void Calculate_w(NewInfo *info)
		{
			std::map<int, OMT::Point> texturePos;
			Tri_Mesh *newMesh = info->newMesh;
			//--GetInsideVertices
			info->inside_vh = GetInsideVertices(info->newMesh);
			std::vector<OMT::VHandle> inside_vh = info->inside_vh;
			//--
			std::map<int, std::map<int, double>> smallw;
			std::vector<double> bigW;
			std::vector<double> BX;
			std::vector<double> BY;
			std::map<int , OMT::Point> p;
			//--Get2DboundaryPoint
			OMT::HEHandle heh = newMesh->halfedge_handle(newMesh->vertices_begin().handle());
			OMT::HEHandle heh_init = heh;
			for(OMT::VIter v_it = newMesh->vertices_begin();v_it!=newMesh->vertices_end();++v_it)
			{
				if(newMesh->is_boundary(v_it.handle()))
				{
					heh = heh_init = newMesh->halfedge_handle(v_it.handle());

					if(!(newMesh->is_boundary(heh_init)))
					{
						heh_init = newMesh->opposite_halfedge_handle(heh_init);
						heh = heh_init;
					}

					break;
				}
			}
			OMT::VHandle current = newMesh->from_vertex_handle(heh);
			OMT::VHandle to_vh = newMesh->to_vertex_handle(heh);
			double _x=0.0,_y=0.0;
			double temp=0.0,temp_len=0.0;
			double len = GetTotalLength(newMesh);
			do
			{
				if(newMesh->is_boundary(to_vh))
				{
					int idx = to_vh.idx();
					temp_len = ( newMesh->point(to_vh)-newMesh->point(current) ).length();
					temp += ( temp_len / len ) * 4;
						 
					if( temp<=1 )
					{
						_x = 0.0;
						_y = temp;
					}else if( temp<= 2 )
					{
						_x = temp - 1.0;
						_y = 1.0;
					}else if( temp<= 3 )
					{
						_x = 1.0;
						_y = 1.0 - (temp - 2.0);
					}else if( temp< 4 )
					{
						_x = 1.0 - (temp - 3.0);
						_y = 0.0;
					}else if ( temp>=4 )
					{
						_x = 0.0;
						_y = 0.0;
					}
					p[idx] = OMT::Point(_x,_y,0);//對應的2D點
					current = to_vh;
					heh = newMesh->next_halfedge_handle(heh);
					to_vh = newMesh->to_vertex_handle(heh);
				}
			}while(heh != heh_init);
			//---calculate bigW BX BY smallw
			for(int i=0;i<inside_vh.size();i++)
			{
				double sumW = 0.0;
				double sumX = 0.0;//B
				double sumY = 0.0;//B
				OMT::Point pp = newMesh->point(inside_vh[i]);
				std::vector<double> tempw;
				for(OMT::VVIter vv_it = newMesh->vv_iter(inside_vh[i]) ; vv_it ; ++vv_it)
				{
					OMT::HEHandle he = newMesh->find_halfedge(inside_vh[i], vv_it.handle());
					OMT::Point to = newMesh->point(vv_it.handle());
					OMT::Point p1 = newMesh->point(newMesh->to_vertex_handle(newMesh->next_halfedge_handle(he)));
					OMT::Point p2 = newMesh->point(newMesh->to_vertex_handle(newMesh->next_halfedge_handle(newMesh->opposite_halfedge_handle(he))));
					OMT::Vec2d v(pp[0] - to[0], pp[1] - to[1]);
					OMT::Vec2d v1(pp[0] - p1[0], pp[1] - p1[1]);
					OMT::Vec2d v2(pp[0] - p2[0], pp[1] - p2[1]);
					double dota = v | v1;
					double dotb = v | v2;
					double len = sqrt(v[0]*v[0] + v[1]*v[1]);
					double a = sqrt(v1[0]*v1[0] + v1[1]*v1[1]);
					double b = sqrt(v2[0]*v2[0] + v2[1]*v2[1]);
					double angleA = std::acos(dota / (len*a));
					double angleB = std::acos(dotb / (len*b));
					double result = (std::tan(angleA/2) + std::tan(angleB / 2)) / len;//wi
					if(newMesh->is_boundary(vv_it.handle()))
					{
						int idx = vv_it.handle().idx();
						sumX += result * p[idx][0];
						sumY += result * p[idx][1];
					}
					(smallw[inside_vh[i].idx()])[vv_it.handle().idx()] = result;
					sumW += result;
				}
				bigW.push_back(sumW);
				BX.push_back(sumX);
				BY.push_back(sumY);
			}
			//-------------------------------------------
			//---解線性系統
			int n = inside_vh.size();//要解的點數量
			
			if(n>0)
			{
				GeneralSparseMatrix GA;
				GA.Create(n, n);
				for(int i=0;i<n;i++)
				{
					for(int j=0,temp=0;j<n;j++)
					{
						if(i!=j){
							GA.SetElement(i, j, (smallw[inside_vh[i].idx()])[inside_vh[j].idx()] * -1.0);
							temp++;
						}
						else
							GA.SetElement(i, j, bigW[i]);
					}
				}
				double** B = new double*[1];
				double** pX = 0;//X point
				double** pY = 0;//Y point
				B[0] = new double[BX.size()];
				for(int i=0;i<BX.size();i++)
					B[0][i] = BX[i];
				SparseLinearSystem sls(new StableSparseMatrix(GA), B, 1);
				try
				{
					if(n==1)
						bool result = GeneralSparseLSSolver::GetInstance()->Solve( &sls, pX );
					else
						bool result = LeastSquareSparseLSSolver::GetInstance()->Solve( &sls, pX );
				} 
				catch( exception e )
				{
					cerr << e.what() << endl;
				}
				for(int i=0;i<BY.size();i++)
					B[0][i] = BY[i];
				try
				{
					if(n==1)
						bool result = GeneralSparseLSSolver::GetInstance()->Solve( &sls, pY );
					else
						bool result = LeastSquareSparseLSSolver::GetInstance()->Solve( &sls, pY );
				} 
				catch( exception e )
				{
					cerr << e.what() << endl;
				}
				for(int i=0;i<n;i++)
				{
					OMT::Point temp(pX[0][i], pY[0][i],0);
					int idx = inside_vh[i].idx();
					p[idx] = temp;
				}
			}
			info->texturePos = p;
		}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 if(AddRadioButton->Checked == true)
			 {

				 NewInfo *tInfo = new NewInfo();
				 tInfo->copyMesh(mesh);
				 Calculate_w(tInfo);
				 tInfo->select_mfh = mesh->select_mfh;
				 tInfo->draw2DPos = true;
				 tInfo->isLoadImg = false;
				 tInfo->ReTexturePos = tInfo->texturePos;
				 tInfo->fileName = n_filename;
				 n_info.push_back(tInfo);

				 listBox1->Items->Add("Texture : " + (n_info.size()-1));
				 timer1->Enabled = true;
			 }else if(EditRadioButton->Checked==true)
			 {
				 NewInfo *tInfo = new NewInfo();
				 tInfo->copyMesh(mesh);
				 Calculate_w(tInfo);
				 tInfo->select_mfh = mesh->select_mfh;
				 tInfo->draw2DPos = true;
				 tInfo->isLoadImg = false;
				 tInfo->fileName = n_filename;
				 tInfo->ReTexturePos = tInfo->texturePos;
				 n_info[info_idx] = tInfo;
				 timer1->Enabled = true;
			 }else if(DeleteRadioButton->Checked == true)
			 {
				 n_info.erase(n_info.begin()+info_idx);
				 listBox1->Items->Clear();
				 for(int i=0;i<n_info.size();i++)
				 {
					 listBox1->Items->Add("Texture : " + i);
				 }
				 timer1->Enabled = false;
			 }
			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
			 
		 }
private: System::Void glPanelControl2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 if(n_info.size()>0){
				 glEnable(GL_COLOR_MATERIAL);
				 mesh->Render_Solid();
			 }
			 for(int i=0;i<n_info.size();i++)
			 {

				 if(n_info[i]->isLoadImg==false)
				 {
					 n_info[i]->LoadImg();
				 }
				 
				 glEnable(GL_TEXTURE_2D);
				 glDisable(GL_LIGHTING);
				 glColor3f(1.0f,1.0f,1.0f);
				 glBindTexture(GL_TEXTURE_2D,n_info[i]->texture_id);//選擇你要用的材質
				 glBegin(GL_TRIANGLES);
				 for (OMT::FIter f_it = n_info[i]->newMesh->faces_begin(); f_it != n_info[i]->newMesh->faces_end(); ++f_it) 
				 {
					 for (OMT::FVIter fv_it = n_info[i]->newMesh->fv_iter( f_it ); fv_it; ++fv_it)
					 {
						 int idx = fv_it.handle().idx();
						 glTexCoord2f(n_info[i]->texturePos[idx][0],1-n_info[i]->texturePos[idx][1]);
						 glVertex3dv(&n_info[i]->newMesh->point(fv_it.handle())[0]);
					 }
				 }
				 glEnd();
				 glDisable(GL_TEXTURE_2D);
			 }
		 }
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 info_idx = listBox1->SelectedIndex;
			 mesh->select_mfh = n_info[info_idx]->select_mfh;

			 if(n_info.size()>0)
			 {
				 timer1->Enabled = true;
			 }else
				 timer1->Enabled = false;

			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 mesh->select_mfh.clear();
			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
		 }
private: System::Void glPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 if ( mesh != NULL )
			 {
				 if(solidwire)
					mesh->Render_SolidWireframe();
				 else
					mesh->Render_Solid();

				 
				 glEnable(GL_COLOR_MATERIAL);
				 glDisable(GL_LIGHTING);
				 glColor3f( 1.0, 0.0, 0.0 );
				 glBegin(GL_TRIANGLES);
				 for(int i=0;i<mesh->select_mfh.size();i++)
				 {
					 for(OMT::FVIter fv_it= mesh->fv_iter(mesh->select_mfh[i]) ; fv_it ; ++fv_it){
						 glVertex3dv( mesh->point(fv_it).data() );
					 }
				 }

				 glEnd();

				 
			 }
			 
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 n_info[info_idx]->Rotate(1);//1:上下
			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 n_info[info_idx]->Rotate(0);//0:左右
			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 wglMakeCurrent( m_hDC, m_hRC );
				 
				 glClearColor(1.0, 1.0, 1.0, 1.0);
				 glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
				 glMatrixMode(GL_PROJECTION);
				 glLoadIdentity();
				 glOrtho(-0.5,0.5,-0.5,0.5,-10,10);
				 glMatrixMode(GL_MODELVIEW); 
				 glLoadIdentity(); 
				 gluLookAt(0.5,0.5,1,0.5,0.5,0,0,1,0);   //視線的座標及方向
				 
				 if(n_info[info_idx]->fileName!="NULL")
				 {
					 if(n_info[info_idx]->pIsLoadImg==false)
					 {
						 n_info[info_idx]->PLoadImg();
					 }
					 glEnable(GL_TEXTURE_2D);
					 glBindTexture(GL_TEXTURE_2D,n_info[info_idx]->pTexture_id);//選擇你要用的材質
					 glColor3f(1,1,1);

					 glBegin(GL_QUADS);
					 glTexCoord2f((0-0.5)*n_info[info_idx]->scale + 0.5,(1-0.5)*n_info[info_idx]->scale + 0.5);glVertex3f(0, 0, 0);
					 glTexCoord2f((1-0.5)*n_info[info_idx]->scale + 0.5,(1-0.5)*n_info[info_idx]->scale + 0.5);glVertex3f(1, 0, 0);
					 glTexCoord2f((1-0.5)*n_info[info_idx]->scale + 0.5,(0-0.5)*n_info[info_idx]->scale + 0.5);glVertex3f(1, 1, 0);
					 glTexCoord2f((0-0.5)*n_info[info_idx]->scale + 0.5,(0-0.5)*n_info[info_idx]->scale + 0.5);glVertex3f(0, 1, 0);

					 glEnd();
					 glDisable(GL_TEXTURE_2D);
				 }


				 for(OMT::VIter v_it = n_info[info_idx]->newMesh->vertices_begin(); v_it != n_info[info_idx]->newMesh->vertices_end(); ++v_it)
				 {
					 OMT::Point currentV = n_info[info_idx]->texturePos[v_it.handle().idx()];
					 
					 for(OMT::VVIter vv_it = n_info[info_idx]->newMesh->vv_iter(v_it.handle());vv_it;++vv_it)
					 {
						 OMT::Point currentV2 = n_info[info_idx]->texturePos[vv_it.handle().idx()];
						 glBegin(GL_LINES);
						 glColor3f(0.0, 0.0, 0.0);
						 double x,y;
						 x = currentV[0];
						 y = currentV[1];
						 x = ( (x-0.5) / n_info[info_idx]->scale ) + 0.5;
						 y = ( (y-0.5) / n_info[info_idx]->scale ) + 0.5;
						 OMT::Point V = OMT::Point(x , y , 0);
						 x = currentV2[0];
						 y = currentV2[1];
						 x = ( (x-0.5) / n_info[info_idx]->scale ) + 0.5;
						 y = ( (y-0.5) / n_info[info_idx]->scale ) + 0.5;
						 OMT::Point V2 = OMT::Point(x ,y , 0);
						 glVertex3dv( V.data() );
						 glVertex3dv( V2.data() );
						 glEnd();
					 }
					 glPointSize(10.0f);
					 glBegin(GL_POINTS);
					 glColor4f(0.0, 1.0, 0.0,0.5);
					 glVertex3dv( currentV.data() );
					 glEnd();
				 }
				 SwapBuffers( m_hDC );
		 }
private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(e->Button == System::Windows::Forms::MouseButtons::Left)
			 {
				 md = true;
				 rd = false;
				 sx = e->X;
				 sy = e->Y;
				 rp[0] = p[0];
				 rp[1] = p[1];
				 rp[2] = p[2];
				 rp[3] = p[3];
			 }else if(e->Button == System::Windows::Forms::MouseButtons::Right)
			 {
				 md = false;
				 rd = true;
				 sx = 200;
				 sy = e->Y;
				 tx = 0;
				 ty = 0;
			 }
			 else
			 {
				 md = false;
				 tx = 0;
				 ty = 0;
			 }
		 }
private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(e->Button == System::Windows::Forms::MouseButtons::Left)
			 {
				 md = false;
				 rd = false;
				 tx = 0;
				 ty = 0;
			 }else if(e->Button == System::Windows::Forms::MouseButtons::Right)
			 {
				 md = false;
				 rd = false;
				 tx = 0;
				 ty = 0;
			 }
		 }
private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(!md)
			 {

			 }
			 else
			 {
				 int tempx,tempy;
				 tempx = e->X - sx;
				 tx = double(tempx) / double(pictureBox1->Width);
				 tempy = (e->Y - sy) * -1;
				 ty = double(tempy) / double(pictureBox1->Height);
				 for(int i=0;i<n_info[info_idx]->texturePos.size();i++)
				 {
					 double x = n_info[info_idx]->texturePos[i][0]+tx;
					 double y = n_info[info_idx]->texturePos[i][1]+ty;
					 OMT::Point p = OMT::Point( x , y );
					 n_info[info_idx]->texturePos[i] = p ;
				 }
				 sx = e->X;
				 sy = e->Y;

				 glPanelControl1->Invalidate();
				 glPanelControl2->Invalidate();

			 }

			 if(rd)
			 {
				 int tempx,tempy;
				 tempx = e->X;
				 tempy = e->Y;
				 double x,y;
				 x = (tempx - sx)/10;
				 y = (tempy - sy)/10;
				 double ang = atan(y/x)*-1;
				 n_info[info_idx]->RotateAngle(ang);

				 glPanelControl1->Invalidate();
				 glPanelControl2->Invalidate();
			 }

		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 double s = System::Double::Parse(textBox1->Text);
			 n_info[info_idx]->Restore();
			 n_info[info_idx]->Scalar(s);
			//n_info[info_idx]->RotateAngle(s);
			 glPanelControl1->Invalidate();
			 glPanelControl2->Invalidate();
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 n_info[info_idx]->texturePos = n_info[info_idx]->ReTexturePos;
			 n_info[info_idx]->scale = 1.0;
			 n_info[info_idx]->angle = 0.0;
			 timer1->Enabled=true;
			 
		 }
private: System::Void solidWireToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 solidwire = true;
		 }
private: System::Void solidToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 solidwire = false;
		 }
};
}

