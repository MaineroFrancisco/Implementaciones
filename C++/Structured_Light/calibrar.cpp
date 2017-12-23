#include "calibrar.h"

calibrar::calibrar() {
	
}


Mat calibrar::gauss_jordan(Mat img)
{
	int m = img.size().width;
	int n = m-1;
	
	float c;
	
	Mat d = Mat::zeros(1,m,CV_32FC1);
	d.at<float>(0,m-1)=1;
	
	int i,j,k;
	for(i=0;i<n-1;i++)        // partial pivoting (trucho, no quiero 0 en la diagonal nomas)
	{
		if(img.at<float>(i,i) == 0){
			for(int k=i;k<n-1;k++)
			{
				
				if(img.at<float>(k,i) != 0)
				{
					for(j=0;j<m;j++)
					{
						c=img.at<float>(i,j);
						img.at<float>(i,j)=img.at<float>(k,j);
						img.at<float>(k,j)=c;
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
			
			c= (img.at<float>(i+1,k)/img.at<float>(k,k)) ;
			
			for(j=0;j<m;j++)
			{
				img.at<float>(i+1,j)-=c*img.at<float>(k,j);
			}
		}
	}

	//***************** Backward Substitution method****************//
	
	for(i=n-1;i>=0;i--)
	{
		c=0;
		for(j=i+1;j<m;j++){
			c=c+img.at<float>(i,j)*d.at<float>(0,j);
		}
		
		d.at<float>(0,i)= -c/img.at<float>(i,i);
	}
	
	return d;
}

Mat calibrar::get_norm_matrix(Mat img)
{
	int N = img.size().height;
	
	float x_mean =0, y_mean=0, desv_x = 0, desv_y =0, scale_x, scale_y;
	
	for(int i=0;i<N;i++)
	{
		
		x_mean += img.at<float>(i,0);
		y_mean += img.at<float>(i,1);
		
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


Mat calibrar::estimate_homography(Mat img)
{
	int N = img.size().height;
	
	// Nx3 por la coordenada homogenea
	Mat p_real(N,3,CV_32FC1), pict(N,3,CV_32FC1);
	
	for(int i=0;i<N;i++) 
	{
		pict.at<float>(i,0) = img.at<float>(i,0);
		pict.at<float>(i,1) = img.at<float>(i,1);
		pict.at<float>(i,2) = 1.0f;
		
		p_real.at<float>(i,0) = img.at<float>(i,2);
		p_real.at<float>(i,1) = img.at<float>(i,3);
		p_real.at<float>(i,2) = 1.0f;
	}
	
	Mat Na = get_norm_matrix(p_real);
	Mat Nb = get_norm_matrix(pict);	
	
	Mat M = Mat::zeros(2*N,9,CV_32FC1);
	Mat aux, aux2, a, b;
	
	float k;
	
	for(int i=0;i<N;i++) 
	{
		k = 2*i;
		
		transpose(p_real.row(i),aux);
		transpose(pict.row(i),aux2);
		
		a = Na * aux;
		b = Nb * aux2;
		
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
	
	//	gauss_jordan(M);
	
	Mat U,W,Vt;
	Vt = gauss_jordan(M);
	//	SVD::compute(M,W,U,Vt, SVD::FULL_UV);
	//
	int lst_row = Vt.size().height -1;
	
	Mat H = ( Mat_<float>(3,3) << 
			 Vt.at<float>(lst_row,0), Vt.at<float>(lst_row,1), Vt.at<float>(lst_row,2),
			 Vt.at<float>(lst_row,3), Vt.at<float>(lst_row,4), Vt.at<float>(lst_row,5),
			 Vt.at<float>(lst_row,6), Vt.at<float>(lst_row,7), Vt.at<float>(lst_row,8)	
			 );
	
	//	show_mat(H);
	//Invertir Normalizacion
	H = Nb.inv()*H*Na;
	
	H = H / H.at<float>(2,2);
	
	return H;
}

Mat calibrar::vij(Mat H, int i , int j)
{
	Mat v =( Mat_<float>(1,6) <<  
			H.at<float>(0,i)*H.at<float>(0,j),
			H.at<float>(0,i)*H.at<float>(1,j) + H.at<float>(1,i)*H.at<float>(0,j),
			H.at<float>(1,i)*H.at<float>(1,j),
			H.at<float>(2,i)*H.at<float>(0,j) + H.at<float>(0,i)*H.at<float>(2,j),
			H.at<float>(2,i)*H.at<float>(1,j) + H.at<float>(1,i)*H.at<float>(2,j),
			H.at<float>(2,i)*H.at<float>(2,j)
			);
	
	return v;
}

vector<Mat> calibrar::plane_base_calibration (vector<Mat> p_corrs) {
	// p_corrs : Vector con multiples fotos (mas de 2) de la planilla para calibrar para UNA SOLA CAMARA
	/*	Formato:
	Cada elemento del vector corresponde con una fotografia distinta (es decir, de otro angulo).
	Estos elementos consisten en un Mat que guarda para cada posicion de la resolucion del proyector,
	con que punto de la imagen se correponde (o promedio de puntos en caso de haber mas de
	una coincidencia) .
	
	*/
	
	/// Cosas a usar:
	int n = p_corrs.size(); //Cantidad de fotografias
	
	// Matrices y Vectores
	Mat H[n];									// Matriz de la Homografia.
	Mat h1, h2, h3;
	
	Mat A = Mat::zeros(8,9, CV_32FC1);		// Matriz de la camara (calibracion intrinseca).  8 x 9, uso SVD para obtener la homografia, requiero 4 puntos (de 1 foto),
											//		si uso mas estoy sobredeterminando.
	Mat U,W,Vt;								// Descomposicion SVD de A, U eigenvectores izquierda, W eigenvalores, Vt eigenvectores derecha (transpuestos)
	Mat U1,W1,V1t;
	
	Mat r1, r2, r3, t;						// Vectores de Rotacion  (r1, r2 y r3 ; X, Y y Z respectivamente) y Traslacion t
	Mat B, b;								// B = A^-t * A^-1		-> 		b = [B11, B12, B22, B13, B23, B33 ]^t
	Mat v01, v00, v11;									// v(i,j) = [hi1*hj1, hi1*hj2 + hi2*hj2, hi2*hj2, hi3*hj1 + hi1*hj3, hi3*hj2 + hi2*hj3, hi3*hj3]^t
	Mat V; 									// V = [ v12^t ; (v11 - v22)^t]
	
	Mat I,E;								// Matriz para los parametros Extrinsicos
	
	//Constantes
	float w, d;
	float lambda;							// Factor de escala para la solucion
	float u0,v0;							// Translacion dentro del sistema de coordenadas de la camara.
	float alpha, beta; 						// Factores de escala para el eje X e Y respectivamente (dependiente de la distancia focal 
											// 		y la discretizacion en pixeles de los puntos del espacio real)
	float gamma; 							// Factor de Skewness(torsion, oblicuidad) de los ejes del sistema de coordenadas de la fotografia.
	
	/// Extraer la homografia.
	// Resolver un Sistema Lineal Homogeneo de ecuaciones para la deduccion de la Homografia entre pares de imagenes
	// 4 puntos de 1 imagen para parametros Extrinsicos, 6 puntos de al menos 2 imagenes para parametros Intrinsicos
	/*
	
	Homografia: 
	Cambio importante:
	Z = 0 para toda la imagen.
	Se computa la homografia entre la imagen y el MODELO... osea las
	coordenadas en el mundo real.
	
	Q = A*[r1 r2 t] -> r3 = 0
	
	*/
	
	if (n==2)
	{
		V = Mat::zeros((2*n+1), 6,CV_32FC1);
		
		V.at<float>(4,0) = 0.0f;
		V.at<float>(4,1) = 1.0f;
		V.at<float>(4,2) = 0.0f;
		V.at<float>(4,3) = 0.0f;
		V.at<float>(4,4) = 0.0f;
		V.at<float>(4,5) = 0.0f;
	}
	else{
		V = Mat(2*n, 6,CV_32FC1);
	}
	
	/// Construyo Matriz para resolver la Homografia, Correspondencias con el plano fotografiado
	///		
	Mat act;
	cv::Size s_act;
	
	float c_x,c_y,pl_x,pl_y;
	for(int foto = 0; foto < n; foto++)	// Columna
	{
		int k = 0;
		
		act = p_corrs[foto];
		
		H[foto] = estimate_homography(act);
		
		/// COMPUTE INTRINSIC Parameters
		//Columnas: h1 y h2 para una misma H
		
		v01 = vij(H[foto],0,1);
		
		v00 = vij(H[foto],0,0);
		v11 = vij(H[foto],1,1);
		
		V.row(2*foto) = v01;
		v01.copyTo(V.row(2*foto));
		Mat auxv = v00 - v11;
		auxv.copyTo(V.row(2*foto+1));
	}
	
	//	SVD::compute(V,W1,U1,V1t, SVD::FULL_UV);
	//
	//	// computar B
	//	cv::Size s_v1t = V1t.size();
	
	b = gauss_jordan(V);
	transpose(b,b);
	
	//	show_mat(V1t); cout<<endl;
	//	
	//	int lst_row_1 = V1t.size().height-1;
	//
	//	b = 
	//	(
	//		Mat_<float>(6,1) <<
	//		V1t.at<float>(lst_row_1,0),
	//		V1t.at<float>(lst_row_1,1),
	//		V1t.at<float>(lst_row_1,2),
	//		V1t.at<float>(lst_row_1,3), 
	//		V1t.at<float>(lst_row_1,4), 
	//		V1t.at<float>(lst_row_1,5)	
	//	);
	//	
	if (b.at<float>(0,0) < 0 || b.at<float>(2,0) < 0 || b.at<float>(5,0) < 0 )
	{
		b = -1*b;
	}
	
	//--------------------------------------------------------------------------
	// Burger Paper - Zhang Algorithm
	w =   b.at<float>(0,0)*b.at<float>(2,0)*b.at<float>(5,0) 
		- b.at<float>(1,0)*b.at<float>(1,0)*b.at<float>(5,0)
		- b.at<float>(0,0)*b.at<float>(4,0)*b.at<float>(4,0) 
		+ 2*b.at<float>(1,0)*b.at<float>(3,0)*b.at<float>(4,0)
		- b.at<float>(2,0)*b.at<float>(3,0)*b.at<float>(3,0);
	
	d =   b.at<float>(0,0)*b.at<float>(2,0) - b.at<float>(1,0)*b.at<float>(1,0);
	
	alpha 	=	sqrt(abs(w/(d*b.at<float>(0,0))));
	beta	=	sqrt(abs((w/(d*d))*b.at<float>(0,0)));
	gamma	=	sqrt(abs(w/(d*d*b.at<float>(0,0))))*b.at<float>(1,0);
	u0		=	(b.at<float>(1,0)*b.at<float>(4,0) - b.at<float>(2,0)*b.at<float>(3,0))/d;
	v0		=	(b.at<float>(1,0)*b.at<float>(3,0) - b.at<float>(0,0)*b.at<float>(4,0))/d;
	
	//--------------------------------------------------------------------------
	// Construir matriz A
	
	I = 
		(
		 Mat_<float>(3,3) << 
		 alpha, gamma, u0,
		 0,  beta, v0,
		 0, 	   0,  1
		 );
	
	//	cout<<"Im: "; show_mat(I);  cout<<endl;
	
	Mat Iinv = I.inv();
	
	/// Calcular Parametros Extrinsicos. x camara
	
	vector<Mat> P;
	P.push_back(I);
	
	shared_ptr<Mat> temp_img;
	
	for(int foto =0; foto<n; foto++)
	{
		
		h1 = H[foto].col(0);
		h2 = H[foto].col(1);
		h3 = H[foto].col(2);
		
		float scale = 1 / norm(Iinv * h1);
		
		r1 = scale * Iinv * h1;
		r2 = scale * Iinv * h2;
		r3 = r1.cross(r2);
		t = scale * Iinv * h3;
		
		temp_img = make_shared<Mat>(Mat(3, 4, CV_32FC1));
		//		E = Mat::zeros(3,4, CV_32FC1);
		
		r1.copyTo(temp_img->col(0));
		r2.copyTo(temp_img->col(1));
		r3.copyTo(temp_img->col(2));
		t.copyTo(temp_img->col(3));
		
		//		Mat p = I*E;
		
		//		cout<<"E: "<<endl; show_mat(*temp_img);  cout<<endl;
		
		P.push_back(*temp_img);
	}
	
	return P;
}

