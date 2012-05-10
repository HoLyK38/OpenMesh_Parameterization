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
IplImage *  Src_Img;
GLuint texture_id=0;
Tri_Mesh *mesh=NULL;
Tri_Mesh* newMesh=NULL;
bool isPoint = false;
bool isFace = false;
HWND m_hWnd;
HDC  m_hDC;
HGLRC m_hRC;
float m_rAngle=0;
std::vector<OMT::EHandle> edges;
//std::vector<OMT::VHandle> boundary_vh;
std::vector<OMT::VHandle> inside_vh;
//std::vector<OMT::Point> boundary_point2D;
std::map<int, OMT::Point> texturePos;
bool startDrawBound=false;
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

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button1;
	private: GLPanel::GLPanelControl^  glPanelControl1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::OpenFileDialog^  openImgFileDialog;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::Button^  button4;

	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;

	private: System::ComponentModel::IContainer^  components;








	protected: 
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
			GLPanel::HKCCameraProp^  hkcCameraProp1 = (gcnew GLPanel::HKCCameraProp());
			GLPanel::HKCDisplayProp^  hkcDisplayProp1 = (gcnew GLPanel::HKCDisplayProp());
			GLPanel::HKCPixelFormat^  hkcPixelFormat1 = (gcnew GLPanel::HKCPixelFormat());
			GLPanel::HKCTrackballProp^  hkcTrackballProp1 = (gcnew GLPanel::HKCTrackballProp());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig1 = (gcnew GLPanel::HKCTrackballTrig());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig2 = (gcnew GLPanel::HKCTrackballTrig());
			GLPanel::HKCTrackballTrig^  hkcTrackballTrig3 = (gcnew GLPanel::HKCTrackballTrig());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->glPanelControl1 = (gcnew GLPanel::GLPanelControl());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->openImgFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(547, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(103, 67);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// glPanelControl1
			// 
			hkcCameraProp1->Enabled = true;
			hkcCameraProp1->Far = 1000;
			hkcCameraProp1->Fov = 45;
			hkcCameraProp1->Near = 0.001;
			hkcCameraProp1->Type = GLPanel::HKCCameraProp::CAMERATYPE::PERSPECTIVE;
			hkcCameraProp1->Zoom = 5;
			this->glPanelControl1->Camera_Property = hkcCameraProp1;
			hkcDisplayProp1->Back_Color = System::Drawing::Color::White;
			hkcDisplayProp1->Grid_Axis = System::Drawing::Color::Black;
			hkcDisplayProp1->Grid_Draw = true;
			hkcDisplayProp1->Grid_Line = System::Drawing::Color::DimGray;
			this->glPanelControl1->Display_Property = hkcDisplayProp1;
			this->glPanelControl1->Empty_Panel = false;
			this->glPanelControl1->Location = System::Drawing::Point(26, 22);
			this->glPanelControl1->Name = L"glPanelControl1";
			hkcPixelFormat1->Accumu_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			hkcPixelFormat1->Alpha_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			hkcPixelFormat1->Stencil_Buffer_Bits = GLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			this->glPanelControl1->Pixel_Format = hkcPixelFormat1;
			this->glPanelControl1->Size = System::Drawing::Size(503, 292);
			this->glPanelControl1->TabIndex = 2;
			hkcTrackballProp1->Const_Res = false;
			hkcTrackballProp1->Delta_Res = 100;
			hkcTrackballProp1->Enabled = true;
			hkcTrackballProp1->Move_Res = 200;
			hkcTrackballTrig1->Key_Down = false;
			hkcTrackballTrig1->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig1->Mouse = System::Windows::Forms::MouseButtons::Right;
			hkcTrackballTrig1->Mouse_Down = false;
			hkcTrackballProp1->Move_Trigger = hkcTrackballTrig1;
			hkcTrackballTrig2->Key_Down = false;
			hkcTrackballTrig2->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig2->Mouse = System::Windows::Forms::MouseButtons::Left;
			hkcTrackballTrig2->Mouse_Down = false;
			hkcTrackballProp1->Rotate_Trigger = hkcTrackballTrig2;
			hkcTrackballProp1->Zoom_Res = 20;
			hkcTrackballTrig3->Key_Down = false;
			hkcTrackballTrig3->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig3->Mouse = System::Windows::Forms::MouseButtons::Middle;
			hkcTrackballTrig3->Mouse_Down = false;
			hkcTrackballProp1->Zoom_Trigger = hkcTrackballTrig3;
			this->glPanelControl1->Trackball_Property = hkcTrackballProp1;
			this->glPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::glPanelControl1_Paint);
			this->glPanelControl1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::glPanelControl1_KeyDown);
			this->glPanelControl1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::glPanelControl1_KeyUp);
			this->glPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::glPanelControl1_MouseDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(24, 448);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 12);
			this->label1->TabIndex = 3;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(238, 448);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 12);
			this->label2->TabIndex = 3;
			this->label2->Text = L"label2";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(547, 116);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(103, 64);
			this->button2->TabIndex = 4;
			this->button2->Text = L"mapto2D";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(547, 297);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(103, 67);
			this->button3->TabIndex = 6;
			this->button3->Text = L"OpenImg";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// openImgFileDialog
			// 
			this->openImgFileDialog->FileName = L"openImgFileDialog";
			this->openImgFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openImgFileDialog2_FileOk);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(452, 448);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(33, 12);
			this->label3->TabIndex = 7;
			this->label3->Text = L"label3";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(704, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(400, 400);
			this->pictureBox1->TabIndex = 8;
			this->pictureBox1->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(574, 213);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(47, 16);
			this->radioButton1->TabIndex = 9;
			this->radioButton1->Text = L"<<<<";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(574, 251);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(47, 16);
			this->radioButton2->TabIndex = 10;
			this->radioButton2->Text = L">>>>";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton2_CheckedChanged);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(649, 365);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(49, 30);
			this->button4->TabIndex = 11;
			this->button4->Text = L"button4";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(547, 365);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(49, 30);
			this->button5->TabIndex = 13;
			this->button5->Text = L"button5";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(682, 448);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(33, 12);
			this->label4->TabIndex = 14;
			this->label4->Text = L"label4";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(902, 448);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(33, 12);
			this->label5->TabIndex = 15;
			this->label5->Text = L"label5";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1183, 794);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->glPanelControl1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 timer1->Interval = 33;
				 timer1->Enabled = false;
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 openFileDialog1->ShowDialog();
			 }
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
				 std::string filename;
				 MarshalString( openFileDialog1->FileName, filename );

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

			 }

private: System::Void glPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 if ( mesh != NULL )
			 {
				 mesh->Render_SolidWireframe();

				 glEnable(GL_COLOR_MATERIAL);
				 glDisable(GL_LIGHTING);
				 glColor3f( 1.0, 0.0, 0.0 );
				 glBegin(GL_TRIANGLES);


				 if(isPoint)
				 {
					 for( OMT::VFIter vf_it = mesh->vf_iter(mesh->select_vh) ; vf_it ; ++vf_it )
					 {
						 for(OMT::FVIter fv_it= mesh->fv_iter(vf_it.handle()) ; fv_it ; ++fv_it){
							 glVertex3dv( mesh->point(fv_it).data() );
						 }
					 }
				 }
				 else if(isFace)
				 {
					 for(int i=0;i<mesh->select_mfh.size();i++)
					 {
						 for(OMT::FVIter fv_it= mesh->fv_iter(mesh->select_mfh[i]) ; fv_it ; ++fv_it){
							 glVertex3dv( mesh->point(fv_it).data() );
						 }
					 }
				 }
				 glEnd();
				 glEnable(GL_LIGHTING);
			 }
		 }

private: System::Void glPanelControl1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if ( e->KeyCode == System::Windows::Forms::Keys::ControlKey )
			 {
				 isPoint = true;
				 isFace = false;
				 glPanelControl1->Trackball_Property->Enabled = false ;
			 }
			 else if ( e->KeyCode == System::Windows::Forms::Keys::ShiftKey )
			 {
				 isFace = true;
				 isPoint = false;
				 glPanelControl1->Trackball_Property->Enabled = false ;
			 }
		 }
private: System::Void glPanelControl1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if ( e->KeyCode == System::Windows::Forms::Keys::ControlKey )
			 {
				 glPanelControl1->Trackball_Property->Enabled = true ;
			 }
			 else if ( e->KeyCode == System::Windows::Forms::Keys::ShiftKey )
			 {
				 glPanelControl1->Trackball_Property->Enabled = true ;
			 }
		 }
private: System::Void glPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 int Op_X,Op_Y;
			 Op_X = e->X ;
			 Op_Y = glPanelControl1->Height - e->Y ;
			 if ( e->Button == System::Windows::Forms::MouseButtons::Right )
			 {   
				 if( !glPanelControl1->Trackball_Property->Enabled)  
				 {
					 if(isPoint)
					 {
						 if(mesh!=NULL)mesh->Select_Point( Op_X, Op_Y );
					 }
					 else if(isFace)
					 {
						 if(mesh!=NULL)mesh->Select_MulFace( Op_X, Op_Y );
					 }
				 }
					
			 }
			 glPanelControl1->Invalidate();
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void openImgFileDialog2_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 std::string filename;
			 MarshalString( openImgFileDialog->FileName, filename );

			 if( Src_Img !=NULL )
				 delete Src_Img ;

			 
			 Src_Img = cvLoadImage(filename.c_str(),CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
			 int w, h;
			 w=Src_Img->width;
			 h=Src_Img->height;

			 glGenTextures( 1, &texture_id );
			 glBindTexture( GL_TEXTURE_2D, texture_id);
			 gluBuild2DMipmaps(GL_TEXTURE_2D,3,w,h,GL_BGR,GL_UNSIGNED_BYTE,Src_Img->imageData);
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			 glEnable(GL_TEXTURE_2D);
			 
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 openImgFileDialog->ShowDialog();
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 wglMakeCurrent( m_hDC, m_hRC );

			 glClearColor(1.0, 1.0, 1.0, 1.0);
			 glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
			 glMatrixMode(GL_PROJECTION);
			 glLoadIdentity();
			 glOrtho(-0.6,0.6,-0.6,0.6,-10,10);
			 glMatrixMode(GL_MODELVIEW); 
			 glLoadIdentity(); 
			 gluLookAt(0.5,0.5,1,0.5,0.5,0,0,1,0);   //視線的座標及方向

			 if(Src_Img!=NULL)
			 {
				 glBindTexture(GL_TEXTURE_2D,texture_id);//選擇你要用的材質
				 glColor3f(1,1,1);
				 glBegin(GL_QUADS);
				 glTexCoord2f(0,1);glVertex3f(0, 0, 0);
				 glTexCoord2f(1,1);glVertex3f(1, 0, 0);
				 glTexCoord2f(1,0);glVertex3f(1, 1, 0);
				 glTexCoord2f(0,0);glVertex3f(0, 1, 0);
				 glEnd();
			 }
			 
			 glBegin(GL_LINES);
			 glColor3f(0.0, 1.0, 0.0);
			 glVertex2f(0, 0);
			 glVertex2f(0, 1);
			 glVertex2f(0, 0);
			 glVertex2f(1, 0);
			 glEnd();

			 if(startDrawBound)
			 {
				 for(OMT::VIter v_it = newMesh->vertices_begin(); v_it != newMesh->vertices_end(); ++v_it)
				 {
					 OMT::Point currentV = texturePos[v_it.handle().idx()];
					 for(OMT::VVIter vv_it = newMesh->vv_iter(v_it.handle());vv_it;++vv_it)
					 {
						OMT::Point currentV2 = texturePos[vv_it.handle().idx()];
						glBegin(GL_LINES);
						glColor3f(0.0, 0.0, 0.0);
						glVertex3dv( currentV.data() );
						glVertex3dv( currentV2.data() );
						glEnd();
					 }
				 }
			 }
			 glFlush();
			 SwapBuffers( m_hDC );
		 }
private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Enabled = !radioButton1->Checked;
		 }
private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Enabled = radioButton2->Checked;
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 Tri_Mesh tempMesh;
			 std::vector<OMT::FHandle> toDelFh;
			 std::vector<OMT::FHandle> select_mfh;
			 tempMesh = *mesh;
			 select_mfh = mesh->select_mfh;
			 for(OMT::FIter f_it = tempMesh.faces_begin();f_it != tempMesh.faces_end();++f_it)
			 {
				 bool toDel = true;
				 for(int i=0;i<select_mfh.size();i++)
				 {
					 if(f_it.handle() == select_mfh[i])
					 {
						 toDel = false;
						 break;
					 }
				 }
				 if(toDel)
					 toDelFh.push_back(f_it.handle());
			 }
			 for(int i=0;i<toDelFh.size();i++)
			 {
				 tempMesh.delete_face(toDelFh[i]);
			 }
			 tempMesh.garbage_collection();
			 if(newMesh!=NULL)
				 delete newMesh;
			 newMesh = new Tri_Mesh;
			 newMesh->clear();
			 *newMesh = tempMesh;

			 Calculate_w();
			 
			 timer1->Enabled = true;
			 startDrawBound = true;
		 }
private: double GetTotalLength()
		 {
			 double sum=0;
			 OMT::HEHandle heh = newMesh->halfedge_handle(newMesh->vertices_begin().handle());
			 OMT::HEHandle heh_init = heh;
			 for(OMT::VIter v_it = newMesh->vertices_begin();v_it!=newMesh->vertices_end();++v_it)			//Find boundary
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
			 do
			 {
				 sum += ( newMesh->point(to_vh) - newMesh->point(current) ).length();
				 label5->Text += "\nid: " + to_vh.idx();
				 current = to_vh;
				 heh = newMesh->next_halfedge_handle(heh);
				 to_vh = newMesh->to_vertex_handle(heh);
			 }while(heh != heh_init);
			 return sum;
		 }
private: std::vector<OMT::VHandle> GetInsideVertices(Tri_Mesh* m)
		 {
			 std::vector<OMT::VHandle> i_vh;
			 for(OMT::VIter v_it = newMesh->vertices_begin();v_it!=newMesh->vertices_end();++v_it)
			 {
				 if(!newMesh->is_boundary(v_it.handle()))
					 i_vh.push_back(v_it.handle());
			 }
			 return i_vh;
		 }
private: void Calculate_w()
		 {
			 label1->Text = "label1";
			 label2->Text = "label2";
			 label3->Text = "label3";
			 label4->Text = "label4";
			 label5->Text = "label5";
			 //--GetInsideVertices
			 inside_vh = GetInsideVertices(newMesh);
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
			 double _x=0,_y=0;
			 double temp=0,temp_len=0;
			 double len = GetTotalLength();
			 do
			 {
				 if(newMesh->is_boundary(to_vh))
				 {

					 int idx = to_vh.idx();
					 temp_len = ( newMesh->point(to_vh)-newMesh->point(current) ).length();
					 temp += ( temp_len / len ) * 4;
					 if( temp<=1 )
					 {
						 _x = temp;
						 _y = 0.0;
					 }else if( temp<= 2 )
					 {
						 _x = 1.0;
						 _y = temp - 1.0;
					 }else if( temp<= 3 )
					 {
						 _x = 1.0 - (temp - 2.0);
						 _y = 1.0;
					 }else if( temp< 4 )
					 {
						 _x = 0.0;
						 _y = 1.0 - (temp - 3.0);
					 }else if ( temp>=4 )
					 {
						 _x = 0.0;
						 _y = 0.0;
					 }
					 p[idx] = OMT::Point(_x,_y,0);//對應的2D點
					 label2->Text += "\np[idx] 'idx = " + idx + " x: " + _x + " y: " + _y;
					 current = to_vh;
					 heh = newMesh->next_halfedge_handle(heh);
					 to_vh = newMesh->to_vertex_handle(heh);
				 }
			 }while(heh != heh_init);
			 //-------------------------------------------


			 //---calculate bigW BX BY smallw
			 for(int i=0;i<inside_vh.size();i++)
			 {
				 double sumW = 0.0;
				 double sumX = 0.0;//B
				 double sumY = 0.0;//B
				 OMT::Point pp = newMesh->point(inside_vh[i]);
				 std:;vector<double> tempw;
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
			 label3->Text += "\np s:" + p.size();
			 label3->Text += "\nbigW:" + bigW.size();
			 label3->Text += "\np smallw:" + smallw.size();
			 label3->Text += "\nBX s:" + BX.size();
			 label3->Text += "\nBY s:" + BY.size();
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
				 SparseLinearSystem sls2(new StableSparseMatrix(GA), B, 1);
				 try
				 {
					 if(n==1)
						bool result = GeneralSparseLSSolver::GetInstance()->Solve( &sls2, pY );
					 else
						bool result = LeastSquareSparseLSSolver::GetInstance()->Solve( &sls2, pY );
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
			//----------------------
			texturePos = p;
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Enabled = false;
		 }
};
}

