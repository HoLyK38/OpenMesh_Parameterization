Tri_Mesh *mesh=NULL;//main mesh
//std::map<int, OMT::Point> texture2DPos;
bool isFace = false;
bool isDelFace = false;
bool draw2DPos = false;
bool isPrintResult = false;
bool a=false;
//GLuint texture_id;
std::vector<OMT::FHandle> toDelFh;
std::string n_filename = "NULL";
HWND m_hWnd;
HDC  m_hDC;
HGLRC m_hRC;


class NewInfo
{
public:
	Tri_Mesh *newMesh;
	std::vector<OMT::VHandle> inside_vh;
	std::map<int, OMT::Point> texturePos;
	std::map<int, OMT::Point> ReTexturePos;
	std::vector<OMT::FHandle> select_mfh;
	std::string fileName;
	GLuint texture_id;
	IplImage *Src_Img;
	bool draw2DPos;
	bool isLoadImg;
	bool pIsLoadImg;
	GLuint pTexture_id;
	double scale;
	double angle;

	NewInfo(){
		newMesh = NULL;
		texture_id = 0;
		pTexture_id = 0;
		scale = 1.0;
		angle = 0.0;
		fileName = "NULL";
		draw2DPos = false;
		isLoadImg = false;
		pIsLoadImg = false;
		Src_Img = new IplImage();
	}
	void Scalar(double s)
	{
		scale=s;

		for(int i=0;i<this->texturePos.size();i++)
		{
			double x = this->texturePos[i][0];
			double y = this->texturePos[i][1];
			x = (x-0.5)*this->scale + 0.5;
			y = (y-0.5)*this->scale + 0.5;
			OMT::Point p = OMT::Point( x , y );
			this->texturePos[i] = p ;
		}
	}
	void Restore()
	{
		for(int i=0;i<this->texturePos.size();i++)
		{
			double x = this->texturePos[i][0];
			double y = this->texturePos[i][1];
			x = ( (x-0.5) / this->scale ) + 0.5;
			y = ( (y-0.5) / this->scale ) + 0.5;
			OMT::Point p = OMT::Point( x , y );
			this->texturePos[i] = p ;
		}
	}
	bool LoadImg()
	{
		if(fileName=="NULL")
			return false;
		Src_Img = cvLoadImage(fileName.c_str(),CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

		int w, h;
		w=Src_Img->width;
		h=Src_Img->height;

		glGenTextures( 1, &texture_id );
		glBindTexture( GL_TEXTURE_2D, texture_id);
		gluBuild2DMipmaps(GL_TEXTURE_2D,3,w,h,GL_BGR,GL_UNSIGNED_BYTE,Src_Img->imageData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		isLoadImg = true;
		return true;
	}
	bool PLoadImg()
	{
		if(fileName=="NULL")
			return false;
		Src_Img = cvLoadImage(fileName.c_str(),CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

		int w, h;
		w=Src_Img->width;
		h=Src_Img->height;

		glGenTextures( 1, &pTexture_id );
		glBindTexture( GL_TEXTURE_2D, pTexture_id);
		gluBuild2DMipmaps(GL_TEXTURE_2D,3,w,h,GL_BGR,GL_UNSIGNED_BYTE,Src_Img->imageData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		pIsLoadImg = true;
		return true;
	}
	bool SaveInfo(std::string path,Tri_Mesh *mesh)
	{
		ofstream out( path+".txt" );
		out<<fileName<<endl;
		out<<scale<<endl;
		out<<angle<<endl;
		for(std::map<int, OMT::Point>::iterator i=ReTexturePos.begin(); i!=ReTexturePos.end(); i++)
		{
			int index = (*i).first;
			out<<index<<endl;
			OMT::Point p = ReTexturePos[index];
			out<<p[0]<<endl<<p[1]<<endl;
		}
		out<<888888<<endl;
		for(std::map<int, OMT::Point>::iterator i=texturePos.begin(); i!=texturePos.end(); i++)
		{
			int index = (*i).first;
			out<<index<<endl;
			OMT::Point p = texturePos[index];
			out<<p[0]<<endl<<p[1]<<endl;
		}
		out<<999999<<endl;
		
		for(int j=0;j<select_mfh.size();j++)
		{
			out<<select_mfh[j].idx()<<endl;
		}
		out.close();
		return SaveFile(path+".obj",this->newMesh);
	}
	bool LoadInfo(std::string path,Tri_Mesh *mesh)
	{
		ifstream _in( path );
		_in>>fileName;
		_in>>scale;
		_in>>angle;
		int i;
		double x,y,z;
		while(_in>>i)
		{
			if(i==888888)
				break;
			else
			{
				_in>>x>>y;
				ReTexturePos[i] = OMT::Point(x,y,0);
			}

		}
		while(_in>>i)
		{
			if(i==999999)
				break;
			else
			{
				_in>>x>>y;
				texturePos[i] = OMT::Point(x,y,0);
			}
			
		}
		int l = path.length();
		path[l-3] = 'o';
		path[l-2] = 'b';
		path[l-1] = 'j';
		this->draw2DPos = true;
		this->isLoadImg = false;
		if( this->newMesh != NULL )
			delete this->newMesh ;
		this->newMesh = new Tri_Mesh;
		bool result = ReadFile(path,this->newMesh);

		int n;
		select_mfh.clear();
		if(result==true)
		{
			while(_in>>n)
			{
				for(OMT::FIter f_it = mesh->faces_begin() ; f_it!=mesh->faces_end();++f_it)
				{
					if(f_it.handle().idx() == n)
						this->select_mfh.push_back(f_it.handle());
				}
			}
		}

		this->texturePos = this->ReTexturePos;
		this->Scalar(scale);
		this->RotateAngle(angle);

		_in.close();
		return result;
	}
	void copyMesh(Tri_Mesh *mesh)//將已選好的面變成新MESH
	{
		std::vector<OMT::FHandle> toDelFh;
		Tri_Mesh tempMesh;
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
		if(this->newMesh!=NULL)
			delete this->newMesh;
		this->newMesh = new Tri_Mesh;
		this->newMesh->clear();
		*(this->newMesh) = tempMesh;
	}
	bool SaveFile(std::string _fileName,Tri_Mesh *_mesh)
	{
		bool isSave = false;
		OpenMesh::IO::Options opt;
		if ( OpenMesh::IO::write_mesh(*_mesh, _fileName, opt) )
		{
			isSave = true;
		}
		return isSave;
	}
	bool ReadFile(std::string _fileName,Tri_Mesh *_mesh)
	{
		bool isRead = false;
		OpenMesh::IO::Options opt;
		if ( OpenMesh::IO::read_mesh(*_mesh, _fileName, opt) )
		{
			//read mesh from filename OK!
			isRead = true;
		}
		if(isRead)
		{
			// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them
			if (!opt.check( OpenMesh::IO::Options::VertexNormal ) && _mesh->has_vertex_normals())
			{
				_mesh->update_normals();
			}
		}
		return isRead;
	}
	void Rotate(int n)
	{
		for(std::map<int, OMT::Point>::iterator i=texturePos.begin(); i!=texturePos.end(); i++)
		{
			int index = (*i).first;
			OMT::Point p = texturePos[index];
			p[n] = 1-p[n];
			texturePos[index] = p;
		}
	}
	void RotateAngle(double an)
	{
		angle = an;
		for(int i=0;i<this->texturePos.size();i++)
		{
			double x = this->texturePos[i][0]-0.5;
			double y = this->texturePos[i][1]-0.5;
			double nx,ny;
			nx = cos(an) * x - sin(an)*y;
			ny = sin(an) * x + cos(an)*y;
			OMT::Point p = OMT::Point( nx+0.5 , ny+0.5 );
			this->texturePos[i] = p ;
		}

	}
};

bool isFhEqual(OMT::FHandle fh1,OMT::FHandle fh2)
{
	OMT::Point P1,P2;
	OMT::FVIter fv_it1 = mesh->fv_iter(fh1);
	OMT::FVIter fv_it2 = mesh->fv_iter(fh2);
	int i;
	for(i=0;i<3;i++)
	{
		P1 = mesh->point(fv_it1.handle());
		P2 = mesh->point(fv_it2.handle());
		if(P1 != P2)
		{
			return false;
			break;
		}
		++fv_it1;++fv_it2;
	}
	if(i==3)
		return true;
	else
		return false;

}