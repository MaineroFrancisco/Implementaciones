#include "auxiliares.h"

vector<Mat> cam1;
vector<Mat> cam2;

vector<Mat> pc1, pc2;

static int id = 0;
int save = 0;
Mat c1(4,4,CV_32FC1);
Mat c2(4,4,CV_32FC1);
int ind1=0, ind2=0;

void show_mat(Mat img, tipo t,  int cam)
{
	cv::Size s;
	switch(t)
	{
	case TEXTO:
		s = img.size();
		for(int i=0;i<s.height;i++) 
		{
			ostringstream os;
			for(int j=0;j<s.width;j++)
			{
				float im = img.at<float>(i,j);
				
				os << img.at<float>(i,j);
				os << ", ";
			}
			cout << os.str() <<endl;
			
			os.clear();
			os<<"";
		}
		break;
		
	case IMAGEN:
		
		ostringstream os;
		os<<cam;
		//			os<<id;
		//			id++;
		
		imshow("Imagen_"+os.str(), img);
		//			waitKey(0);
		break;
	}
}

/// CALLBACKS

///
//static int pct_id = 0;
void save_capture(Mat img,string path, int camera)
{
	ostringstream capture_id;
	capture_id << camera;

//	pct_id++;
	imwrite(path + "\\c"+ capture_id.str()+".png", img);
}

///
void callback_c1(int event, int x, int y, int flags, void* userdata)
{
	if(cam1.size() < 3)
	{
		if(ind1>=4)
		{
			cam1.push_back(c1.clone());
			c1 = Mat::zeros(4,4,CV_32FC1);
			ind1=0;
		}
		
		// p_reales = 0,0 | 0,1 | 1,0 | 1,1 
		if  ( event == EVENT_LBUTTONDOWN )
		{
			c1.at<float>(ind1, 0) = (float)x;
			c1.at<float>(ind1, 1) = (float)y;
			c1.at<float>(ind1, 2) = (ind1 & 2)/2;
			c1.at<float>(ind1, 3) = ind1 & 1;
			ind1++;
		}
	}
}

void callback_c2(int event, int x, int y, int flags, void* userdata)
{
	
	if(cam2.size() < 3)
	{
		if(ind2 >= 4)
		{
			cam2.push_back(c2.clone());
			c2 = Mat::zeros(4,4,CV_32FC1);
			ind2=0;
		}
		
		// p_reales = 0,0 | 0,1 | 1,0 | 1,1 
		if  ( event == EVENT_LBUTTONDOWN )
		{
			c2.at<float>(ind2, 0) = (float)x;
			c2.at<float>(ind2, 1) = (float)y;
			c2.at<float>(ind2, 2) = (ind2 & 2)/2;
			c2.at<float>(ind2, 3) = ind2 & 1;
			ind2++;
		}
	}
}

///
void draw_sys_coord(Mat M, viz::Viz3d windows)
{
	Mat Em = Mat::zeros(4,4,CV_32FC1);
	
	//	show_mat(M);
	
	M.row(0).copyTo(Em.row(0));
	M.row(1).copyTo(Em.row(1));
	M.row(2).copyTo(Em.row(2));
	
	Em.at<float>(3,3) = 1.0f;
	
	Mat dimtrim = (Mat_<float> (3,4) <<
				   1.0f,0.0f,0.0f,0.0f,
				   0.0f,1.0f,0.0f,0.0f,
				   0.0f,0.0f,1.0f,0.0f
				   );
	
	Mat invEm = dimtrim*Em.inv();
	
	Mat sc = (
			  Mat_<float>(4,3) <<
			  1.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f,
			  0.0f, 0.0f, 1.0f,
			  1.0f, 1.0f, 1.0f
			  );
	
	Mat orig = (
				Mat_<float>(4,1) <<
				0.0f, 0.0f, 0.0f, 1.0f
				);
	
	sc = invEm*sc;
	
	orig = invEm*orig;
	
	//	Affine3f cam(sc);
	
	ostringstream os;
	os << id;
	
	viz::WLine axisX(Point3f(orig), Point3f(sc.col(0)), Scalar(255,0,0));
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	windows.showWidget("X_"+os.str(), axisX);
	
	viz::WLine axisY(Point3f(orig), Point3f(sc.col(1)), Scalar(0,0,255));
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	windows.showWidget("Y_"+os.str(), axisY);
	
	viz::WLine axisZ(Point3f(orig), Point3f(sc.col(2)), Scalar(0,255,0));
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	windows.showWidget("Z_"+os.str(), axisZ);
	
	id++;
}

///
void callback_pc1(int event, int x, int y, int flags, void* userdata)
{
	Mat p(1,3,CV_32FC1);
	// p_reales = 0,0 | 0,1 | 1,0 | 1,1 
	if  ( event == EVENT_LBUTTONDOWN )
	{
		p.at<float>(0, 0) = (float)x;
		p.at<float>(0, 1) = (float)y;
		p.at<float>(0, 2) = 1.0f;
		
		pc1.push_back(p.clone());
	}
	
	
}

void callback_pc2(int event, int x, int y, int flags, void* userdata)
{
	Mat p(1,3,CV_32FC1);
	// p_reales = 0,0 | 0,1 | 1,0 | 1,1 
	if  ( event == EVENT_LBUTTONDOWN )
	{
		p.at<float>(0, 0) = (float)x;
		p.at<float>(0, 1) = (float)y;
		p.at<float>(0, 2) = 1.0f;
		
		pc2.push_back(p.clone());
	}
	
}




/// FUNCIONES
void save_images(string path, VideoCapture c1, int start)
{
	unsigned char pressed_key =0;
	int i = start;
	
	Mat f1;
	
	while(pressed_key != 27 )
	{
		c1>>f1;
		imshow("Camara 1", f1);
		
		if(pressed_key == 13) //Enter
		{
			save_capture(f1,path,i);
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
}

void histograma(Mat f_hist, int histSize)
{
	///Mostrar HISTOGRAMA / HOG
	
	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );
	
	Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0) );
	
	/// Normalize the result to [ 0, histImage.rows ]
	Mat result = f_hist.clone();
	normalize(result, result, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	
	/// Draw for each channel
	for( int l = 1; l < histSize; l++ )
	{
		line( histImage, Point( bin_w*(l-1), hist_h - cvRound(result.at<float>(l-1)) ) ,
			 Point( bin_w*(l), hist_h - cvRound(result.at<float>(l)) ),
			 Scalar(255), 2, 8, 0  );
	}
	show_mat(histImage,IMAGEN,0);
	
}

void show_hog(Mat gris, Point2f pos_feature, float orientation, Mat HOG)
	//void show_hog(Mat parche, Mat hist )
{	
	/// ESTA FUNCION RESIVE UN PARCHE DE LA IMAGEN SOBRE LA QUE SE VA A PLOTEAR, EL HISTOGRAMA DE ESE PARCHE (SUBPARCHE DE LA VNETANA GENERAL EN REALIDAD)
	/// Y CONSTRUYE LA SUBESTRUCTURA DE HOG PARA PLOTEAR, ESCALADA SEGUN EL HISTOGRAMA NORMALIZADO
	
	Mat copy_g = gris.clone();
	
	//	normalize(copy_g,copy_g,1,0,cv::NORM_MINMAX);
	
	// ORIENTAR LA IMAGEN SEGUN LA ORIENTACION GENERAL DE LA FEATURE, ASI OBTENER LA ROI CORRECTAMENTE
	Mat rot_g, m_rot;
	
	m_rot = getRotationMatrix2D(pos_feature, orientation, 1);
	
	warpAffine(copy_g, rot_g, m_rot,copy_g.size());
	
	// extraer parche de la feature
	Point2f pos = pos_feature;
	pos.x -=8;
	pos.y -=8;
	
	Mat roi_g = rot_g(Rect(pos.x,pos.y,16,16)).clone();
	Mat sub_roi, sub_hist;
	
	pyrUp( roi_g, roi_g, Size( roi_g.cols*2, roi_g.rows*2 ));
	pyrUp( roi_g, roi_g, Size( roi_g.cols*2, roi_g.rows*2 ));
	pyrUp( roi_g, roi_g, Size( roi_g.cols*2, roi_g.rows*2 ));
	
	Point2f center, pos_fin;
	float angle,x,y;
	
	for(int i=0;i<16;i++) 
	{
		
		sub_roi = roi_g(Rect(32*(i%4),32*(i/4),32,32));
		
		center = Point2f(16+(32*(i%4)),16+(32*(i/4)));
		
		sub_hist = HOG(Rect(0,i*8,1,8));
		
		for(int j=0;j<8;j++) 
		{
			angle = j*45;	// 45 = 360/n_bins
			//			x = 20*sub_hist.at<float>(j)*cos(angle*CV_PI/180);
			//			y = 20*sub_hist.at<float>(j)*sin(angle*CV_PI/180);
			x = 20*sub_hist.at<unsigned char>(j)*cos(angle*CV_PI/180);
			y = 20*sub_hist.at<unsigned char>(j)*sin(angle*CV_PI/180);
			
			pos_fin = center + Point2f(x,y);
			
			arrowedLine(roi_g,center, pos_fin, Scalar(125),1,8,0,0.1);
		}
	}
	
	show_mat(roi_g,IMAGEN,1);
}

Mat get_norm_matrix(Mat img)
{
	int N = img.size().height;
	
	float x_mean =0, y_mean=0, desv_x = 0, desv_y =0, scale_x, scale_y;
	
	for(int i=0;i<N;i++)
	{
		
		//		x_mean += img.at<float>(i,0);
		//		y_mean += img.at<float>(i,1);
		x_mean += img.at<float>(0,i);
		y_mean += img.at<float>(1,i);
		
	}
	
	x_mean = x_mean/N;
	y_mean = y_mean/N;
	
	for(int i=0;i<N;i++)
	{
		
		desv_x += (img.at<float>(i,0)-x_mean)*(img.at<float>(i,0)-x_mean);
		desv_y += (img.at<float>(i,1)-y_mean)*(img.at<float>(i,1)-y_mean);
		
	}
	
	desv_x = desv_x/N;
	desv_y = desv_y/N;
	
	scale_x = sqrt(2/desv_x);
	scale_y = sqrt(2/desv_y);
	
	Mat Na = ( Mat_<float>(3,3) <<
			  scale_x,		  0, -scale_x*x_mean,
			  0, 	scale_y, -scale_y*y_mean,
			  0, 		  0, 				1
			  );
	
	return Na;
}


Mat gauss_jordan(Mat input)
{
	Mat matriz = input.clone();		// para no alterar la matriz de entrada
	int m = matriz.size().width;
	//	int n = img.size().height;
	int n = m-1;
	
	float c;
	
	Mat d = Mat::zeros(1,m,CV_32FC1);
	
	//	show_mat(d);
	
	int i,j,k;
	for(i=0;i<n-1;i++)        // partial pivoting (trucho, no quiero 0 en la diagonal nomas)
	{
		if(matriz.at<float>(i,i) == 0){
			for(int k=i;k<n-1;k++)
			{
				
				if(matriz.at<float>(k,i) != 0)
				{
					for(j=0;j<m;j++)
					{
						c=matriz.at<float>(i,j);
						matriz.at<float>(i,j) = matriz.at<float>(k,j);
						matriz.at<float>(k,j) = c;
					}
					break;
				}
			}			
		}
	}
	
	//********* changing to upper triangular matrix*************//
	//********* Forward elimination process**************//
	for(k=0;k<n-1;k++)
	{
		for(i=k;i<n-1;i++)
		{
			
			c= (matriz.at<float>(i+1,k)/matriz.at<float>(k,k)) ;
			
			for(j=0;j<m;j++)
			{
				matriz.at<float>(i+1,j)-=c*matriz.at<float>(k,j);
			}
		}
	}
	
	//***************** Backward Substitution method****************//
	
	d.at<float>(0,m-1)=1;	//TRUCHO... para resolver sistema homogeneo, pone el ultimo (el parametro independiente) en 1 y substituye para arriba
	for(i=n-1;i>=0;i--)
	{
		c=0;
		for(j=i+1;j<m;j++){
			c=c+matriz.at<float>(i,j)*d.at<float>(0,j);
		}
		
		d.at<float>(0,i)= -c/matriz.at<float>(i,i);
	}
	
	return d;
}

// F = H*r;
Mat estimate_homography(vector<Point2f> f, vector<Point2f> r)
{
	//	int N = img.rows;
	int N = f.size();
	
	// Nx3 por la coordenada homogenea
	//	Mat p_real(N,3,CV_32FC1), foto(N,3,CV_32FC1);
	Mat p_real(3,N,CV_32FC1), foto(3,N,CV_32FC1);
	
	for(int i=0;i<N;i++) 
	{
		
		//		foto.at<float>(i,0) = f[i].x;
		//		foto.at<float>(i,1) = f[i].y;
		//		foto.at<float>(i,2) = 1.0f;
		foto.at<float>(0,i) = f[i].x;
		foto.at<float>(1,i) = f[i].y;
		foto.at<float>(2,i) = 1.0f;
		
		//		p_real.at<float>(i,0) = r[i].x;
		//		p_real.at<float>(i,1) = r[i].y;
		//		p_real.at<float>(i,2) = 1.0f;
		p_real.at<float>(0,i) = r[i].x;
		p_real.at<float>(1,i) = r[i].y;
		p_real.at<float>(2,i) = 1.0f;
	}
	
	Mat Na = get_norm_matrix(p_real);
	Mat Nb = get_norm_matrix(foto);	
	
	Mat M = Mat::zeros(2*N,9,CV_32FC1);
	Mat aux, aux2, a, b;
	
	float k;
	
	aux = Na*p_real;
	aux2 = Nb*foto;
	
	for(int i=0;i<N;i++) 
	{
		k = 2*i;
		
		//		transpose(p_real.row(i),aux);
		//		transpose(foto.row(i),aux2);
		//		
		//		a = Na * aux;
		//		b = Nb * aux2;
		a = aux.col(i);
		b = aux2.col(i);
		
		for(int j=0;j<3;j++) 
		{
			a.at<float>(j,0) = a.at<float>(j,0)/a.at<float>(2,0);
			
			b.at<float>(j,0) = b.at<float>(j,0)/b.at<float>(2,0);
			
		}
		
		Mat r1 = (Mat_<float>(1,9) <<		-a.at<float>(0,0), -a.at<float>(1,0), -1.0f, 
				  0.0f,0.0f,0.0f, 
				  a.at<float>(0,0)*b.at<float>(0,0), 	a.at<float>(1,0)*b.at<float>(0,0), b.at<float>(0,0) );
		Mat r2 = (Mat_<float>(1,9) <<		
				  0.0f,0.0f,0.0f, 
				  -a.at<float>(0,0), -a.at<float>(1,0), -1.0f, 
				  a.at<float>(0,0)*b.at<float>(1,0), 	a.at<float>(1,0)*b.at<float>(1,0), b.at<float>(1,0) );
		
		r1.copyTo(M.row(k));
		r2.copyTo(M.row(k+1));
	}
	
	
	Mat U,W,Vt;
//		Vt = gauss_jordan(M);
	SVD::compute(M,W,U,Vt, SVD::FULL_UV);
	
	int lst_row = Vt.size().height -1;
	
	Mat H = ( Mat_<float>(3,3) << 
			 Vt.at<float>(lst_row,0), Vt.at<float>(lst_row,1), Vt.at<float>(lst_row,2),
			 Vt.at<float>(lst_row,3), Vt.at<float>(lst_row,4), Vt.at<float>(lst_row,5),
			 Vt.at<float>(lst_row,6), Vt.at<float>(lst_row,7), Vt.at<float>(lst_row,8)	
			 );
	
////	Mat d = gauss_jordan(M);
////	int lst_row = 0;
////	Mat H = ( Mat_<float>(3,3) << 
////			 d.at<float>(lst_row,0), d.at<float>(lst_row,1), d.at<float>(lst_row,2),
////			 d.at<float>(lst_row,3), d.at<float>(lst_row,4), d.at<float>(lst_row,5),
////			 d.at<float>(lst_row,6), d.at<float>(lst_row,7), d.at<float>(lst_row,8)	
////			 );
	//	show_mat(H);
	//Invertir Normalizacion
	H = Nb.inv()*H*Na;
	
	H = H / H.at<float>(2,2);
	
	return H;
}


Mat fix_rectify(Mat img, Mat r)
//Mat fix_rectify(Mat img, Mat img2 Mat r1, Mat r2)
{
	Mat top_l= (Mat_<float>(3,1)<<
				0.0f,0.0f,1.0f
				);
	Mat top_r= (Mat_<float>(3,1)<<
				img.cols,0.0f,1.0f
				);
	Mat bot_l= (Mat_<float>(3,1)<<
				0.0f,img.rows,1.0f
				);
	Mat bot_r= (Mat_<float>(3,1)<<
				img.cols,img.rows,1.0f
				);
	
	Mat fix_topl = r*top_l;
	Mat fix_topr = r*top_r;
	Mat fix_botl = r*bot_l;
	Mat fix_botr = r*bot_r;
	
	fix_topl = fix_topl/fix_topl.at<float>(2);
	fix_topr = fix_topr/fix_topr.at<float>(2);
	fix_botl = fix_botl/fix_botl.at<float>(2);
	fix_botr = fix_botr/fix_botr.at<float>(2);
	
	float by, ty, bx, tx;
	ty = (fix_topl.at<float>(1)<fix_topr.at<float>(1))? fix_topl.at<float>(1) : fix_topr.at<float>(1);
	tx = (fix_topl.at<float>(0)<fix_topr.at<float>(0))? fix_topl.at<float>(0) : fix_topr.at<float>(0);
	
	by = (fix_botl.at<float>(1)>fix_botr.at<float>(1))? fix_botl.at<float>(1) : fix_botr.at<float>(1);
	bx = (fix_botl.at<float>(0)>fix_botr.at<float>(0))? fix_botl.at<float>(0) : fix_botr.at<float>(0);
	
	//	Mat fix_offset = Mat::zeros(3,3,CV_32F);
	Mat fix_offset = (Mat_<float>(3,3)<<
					  1.0f,0.0f,-tx,
					  0.0f,1.0f,-ty,
					  0.0f,0.0f,1.0f
					  );
	
	
	cout<<"tx: "<<tx<<"ty: "<<ty<<endl;
	cout<<"bx: "<<bx<<"by: "<<by<<endl;
	
	//	float asp_ratio = (by-ty)/(bx-tx);
	
	Size fix_s(bx-tx,by-ty);
	
	Mat img_rect;
	warpPerspective(img,img_rect,fix_offset*r,fix_s);
	
	return img_rect;
}



void draw_epiline(Mat img1, Mat I1, Mat E1, Mat img2, Mat I2, Mat E2, Point2f p)
{
	Mat temp_i1, temp_I1, temp_E1;
	Mat temp_i2, temp_I2, temp_E2;
	
	temp_i1 = img1.clone();
	temp_I1 = I1.clone();
	temp_E1 = E1.clone();
	
	temp_i2 = img2.clone();
	temp_I2 = I2.clone();
	temp_E2 = E2.clone();
	
	Mat epi1, epi2;
	
	Mat zero = (Mat_<float>(4,1) <<
				0.0f,
				0.0f,
				0.0f,
				1.0f				
				);
	
	Mat trim = (Mat_<float>(3,4) <<
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f
				);
	
	temp_E1.resize(4); temp_E2.resize(4);
	
	transpose(zero,temp_E1.row(3));
	transpose(zero,temp_E2.row(3));
	
	Mat IE1 = temp_E1.inv();
	Mat IE2 = temp_E2.inv();
	
	epi2 = temp_I2*trim*temp_E2*IE1*zero;	/// Epipolo en la imagen 2
	epi2 = epi2/epi2.at<float>(2);
	
	epi1 = temp_I1*trim*temp_E1*IE2*zero;	/// Epipolo en la imagen 1
	epi1 = epi1/epi1.at<float>(2);
	
	///-----------------------------------------------------------------------------
	/// EPIPOLAR LINES
	///-----------------------------------------------------------------------------
	
	Mat p1_epiline = (Mat_<float>(3,1)<<
					  p.x,
					  p.y,
					  1.0f
					  );
	
	//	cout<<"Antes epilinea"<<endl;
	Mat p1_epi_real = temp_I1.inv()*p1_epiline;
	//	p1_epi_real = p1_epi_real/p1_epi_real.at<float>(2);
	p1_epi_real = (Mat_<float>(4,1) <<
				   p1_epi_real.at<float>(0),
				   p1_epi_real.at<float>(1),
				   p1_epi_real.at<float>(2),
				   1.0f
				   );
	
	//	cout<<"Desp epilinea"<<endl;
	Mat img_p1er = IE1*p1_epi_real;
	img_p1er = img_p1er/img_p1er.at<float>(3);
	
	img_p1er = temp_I2*trim*temp_E2*img_p1er;
	img_p1er = img_p1er/img_p1er.at<float>(2);
	
	
	Mat epi_line_2 = img_p1er - epi2;
	//	epil2 = epil2/epil2.at<float>(2);
	
	Mat epi_line_1 = p1_epiline - epi1;
	//	epil1 = epil1/epil1.at<float>(2);
	
	Point2f EL11 = Point2f( 0, (epi_line_1.at<float>(1)/epi_line_1.at<float>(0))*(-epi1.at<float>(0)) + epi1.at<float>(1));
	Point2f EL12 = Point2f( img1.cols, (epi_line_1.at<float>(1)/epi_line_1.at<float>(0))*( img1.cols - epi1.at<float>(0)) + epi1.at<float>(1) );
	Point2f EL21 = Point2f( 0, (epi_line_2.at<float>(1)/epi_line_2.at<float>(0))*(-epi2.at<float>(0)) + epi2.at<float>(1));
	Point2f EL22 = Point2f( img2.cols, (epi_line_2.at<float>(1)/epi_line_2.at<float>(0))*( img2.cols - epi2.at<float>(0)) + epi2.at<float>(1) );
	
	///
	line(img1, 
		 EL11,
		 EL12,
		 Scalar(0,255,0),
		 2
		 );
	
	line(img2, 
		 EL21,
		 EL22,
		 Scalar(0,255,0),
		 2
		 );
	
	
	//	org_fix = fix_rectify(org, rect[0]);
	//	org2_fix = fix_rectify(org2, rect[1]);
	//	//	org_fix = fix_rectify(org, org2, rect[0], rect[1]);
	//	
	//	resize(org_fix,org_fix,Size(640,480));
	//	resize(org2_fix,org2_fix,Size(640,480));
	//	
	//	//	resize(org2_fix,org2_fix,org_fix.size());
	//	
	//	//	show_mat(org, IMAGEN,0);
	//	//	show_mat(org2, IMAGEN,2);
	//	
	//	show_mat(org_fix, IMAGEN, 0);
	//	show_mat(org2_fix, IMAGEN, 1);
	//	
	
//	show_mat(temp_i1, IMAGEN, 0);
//	show_mat(temp_i2, IMAGEN, 1);
//	
//	waitKey(0);	
}
