#include "SL.hpp"

///
//#include "auxiliares.h"
///
SL::SL (const unsigned int p_w, const unsigned int p_h)
{
	proj_h = p_h;
	proj_w = p_w;
	
	row_lvl = ceil(log(p_h)/CV_LOG2);
	col_lvl = ceil(log(p_w)/CV_LOG2);
}


SL::~SL()
{
	
}

///--------------------------------------------------------------------------------------------------------
/// EMPEZAR A COMENTAR WACHO!
///--------------------------------------------------------------------------------------------------------


///--------------------------------------------------------------------------------------------------------
/// generate_binary_code_patterns: Genera los patrones a ser projectados siguiendo la codificacion binaria
/*
Ejemplo: resolucion del projector 1024*768

	nro_columnas_total = log2(1024) = 10			| -> entonces tendre 10 patrones para representar 
	nro_filas_total = log2(768) = ceil(9.58) = 10	| 		la codificacion de las filas, y 10 para las columnas

	nro_columna (243) = 0011110011 -> entonces, para cada uno de los patrones, 
									donde la columna corresponda al valor 243, el valor en el mismo va
									a ser 1 o 0 dependiendo la posicion del binario que represente


	8 x 8: Codifico las columnas (8 -> log2(8)=3)
		
		0 0 0 0 1 1 1 1		0 0 1 1 0 0 1 1		0 1 0 1 0 1 0 1 	| ->	0 1 2 3 4 5 6 7
        0 0 0 0 1 1 1 1 	0 0 1 1 0 0 1 1 	0 1 0 1 0 1 0 1 	| ->	0 1 2 3 4 5 6 7
		0 0 0 0 1 1 1 1 	0 0 1 1 0 0 1 1 	0 1 0 1 0 1 0 1 	| ->	0 1 2 3 4 5 6 7
		0 0 0 0 1 1 1 1 	0 0 1 1 0 0 1 1 	0 1 0 1 0 1 0 1 	| ->	0 1 2 3 4 5 6 7
	
*/
///--------------------------------------------------------------------------------------------------------
vector<Mat> SL::generate_binary_code_patterns ( )
{
	
	code_patterns.clear();
	shared_ptr<Mat> temp_img, temp_inv;
	unsigned char white = 255, black = 0;
	
	int bit, mask = 1;

	///--------------------------------------------------------------------------------------------------------
	for(int i=0; i<row_lvl; i++)
	{
		
		temp_img = make_shared<Mat>(Mat(proj_h, proj_w, CV_8UC1));
		temp_inv = make_shared<Mat>(Mat(proj_h, proj_w, CV_8UC1));
		
		for(unsigned int j=0; j<proj_h; j++)
		{
			
			bit = (j >> ((row_lvl-1)-i));
			
			for(unsigned int k=0; k<proj_w; k++)
			{
				temp_img->at<unsigned char>(j,k) = (bit & mask)? white : black; 
				temp_inv->at<unsigned char>(j,k) = (bit & mask)? black : white; 
			}
			
		}
		
		code_patterns.push_back(*temp_img);
		code_patterns.push_back(*temp_inv);
	}
	
	for(int i=0; i<col_lvl; i++)
	{
		
		temp_img = make_shared<Mat>(Mat(proj_h, proj_w, CV_8UC1));
		temp_inv = make_shared<Mat>(Mat(proj_h, proj_w, CV_8UC1));
		
		for(int k=0; k<proj_w; k++)
		{	
			bit = (k >> ((col_lvl-1)-i));
			
			for(int j=0; j<proj_h; j++)
			{
				temp_img->at<unsigned char>(j,k) = (bit & mask)? white : black; 
				temp_inv->at<unsigned char>(j,k) = (bit & mask)? black : white; 
			}
		}
		
		code_patterns.push_back(*temp_img);
		code_patterns.push_back(*temp_inv);
	}
	
	return code_patterns;
}

///--------------------------------------------------------------------------------------------------------
/// generate_gray_code_patterns: Genera los patrones a ser projectados siguiendo la codificacion GRAY (cambia de a 1 bit a la vez)
/*
Ejemplo: resolucion del projector 1024*768

nro_columnas_total = log2(1024) = 10			| -> entonces tendre 10 patrones para representar 
nro_filas_total = log2(768) = ceil(9.58) = 10	| 		la codificacion de las filas, y 10 para las columnas

nro_columna (243) = 0010001010	-> entonces, para cada uno de los patrones, 
									donde la columna corresponda al valor 243, el valor en el mismo va
									a ser 1 o 0 dependiendo la posicion del binario que represente


8 x 8: Codifico las columnas (8 -> log2(8)=3)

0 0 0 0 1 1 1 1		0 0 1 1 1 1 0 0		0 1 1 0 1 1 0 1 	| ->	0 1 2 3 4 5 6 7
0 0 0 0 1 1 1 1		0 0 1 1 1 1 0 0		0 1 1 0 1 1 0 1 	| ->	0 1 2 3 4 5 6 7
0 0 0 0 1 1 1 1		0 0 1 1 1 1 0 0		0 1 1 0 1 1 0 1 	| ->	0 1 2 3 4 5 6 7
0 0 0 0 1 1 1 1		0 0 1 1 1 1 0 0		0 1 1 0 1 1 0 1 	| ->	0 1 2 3 4 5 6 7

*/
///--------------------------------------------------------------------------------------------------------
vector<Mat> SL::generate_gray_code_patterns ( ) 
{
	
	code_patterns.clear();
	shared_ptr<Mat> temp_img, temp_inv;
	unsigned char white = 255, black = 0;	//black = 0
	
	int bit, mask = 1;
	
	///--------------------------------------------------------------------------------------------------------
	for(int i=0; i<row_lvl; i++)
	{
		
		temp_img = make_shared<Mat>(Mat(proj_h, proj_w, CV_8UC1));
		temp_inv = make_shared<Mat>(Mat(proj_h, proj_w, CV_8UC1));
		
		for(unsigned int j=0; j<proj_h; j++)
		{
			bit = (j xor (j>>1))>>((row_lvl-1)-i);
			
			for(unsigned int k=0; k<proj_w; k++)
			{
				temp_img->at<unsigned char>(j,k) = (bit & mask)? white : black; 				
				temp_inv->at<unsigned char>(j,k) = (bit & mask)? black : white; 
			}
		}
		
		code_patterns.push_back(*temp_img);
		code_patterns.push_back(*temp_inv);
	}
	
	for(int i=0; i<col_lvl; i++) 
	{
		
		temp_img = make_shared<Mat>(Mat(proj_h, proj_w, CV_8UC1));
		temp_inv = make_shared<Mat>(Mat(proj_h, proj_w, CV_8UC1));
	
		for(int k=0; k<proj_w; k++)
		{	
			bit = (k xor (k>>1))>>((col_lvl-1)-i);
			
			for(int j=0; j<proj_h; j++)
			{

				temp_img->at<unsigned char>(j,k) = (bit & mask)? white : black; 
				temp_inv->at<unsigned char>(j,k) = (bit & mask)? black : white; 
			}
		}
		
		code_patterns.push_back(*temp_img);
		code_patterns.push_back(*temp_inv);
	}
	
	return code_patterns;
}

///--------------------------------------------------------------------------------------------------------
/*
Compute the shadow mask for the object to be captured.
	It requires to do (or have already) 2 captures 
*/
///--------------------------------------------------------------------------------------------------------

//Mat SL::decode_captured_patterns (Mat black, Mat white, vector<Mat> row_cap, vector<Mat> col_cap, Mat mask) {
Mat SL::decode_captured_patterns (vector<Mat> captures, Mat mask) {
	
	// Orden para las capturas:
	//		Captura Filas (real | invert)
	//	
	//		Captura Columnas (real | invert)
	//
	
	// Extraer las capturas correspondiete a OSCURIDAD e ILUMINACION
	//										(todo negro, todo blanco)

	// Variable para almacenar el tamanio.
	Size size = captures[0].size();
	
	
	// Matriz para todos los pixeles de la foto matcheados con los del projector,
	// en caso de haber problema con los tamanios, reescalar las cosas a un tamanio base.
	// 2 columnas: fila, col (en la imagen), cant_pixels_per_point,
	//  			fila_deco, col_deco (en el patron projectado)
	
	// Ordenado por columnas, luego filas... 1024x768 ... 
	// 1024 valores en el array repreesntan una fila, al siguiente cambia la fila.
	Mat proj = Mat::zeros(proj_h*proj_w, 3, CV_32SC1);
	
	//Mat proj = Mat::ones(size,CV_32SC1)*-1;
	
	//Separo la parte de las filas y de las columnas. Ordenadas desde menos
	//		significativas a mas significativas.
	vector<Mat> row_cap, col_cap;
	
	//Filas
	row_cap.assign(captures.begin(),captures.begin()+row_lvl*2);
	
	//Columnas
	col_cap.assign(captures.begin()+row_lvl*2,captures.end());
	
	// Variables Auxiliares para almacenar el valor actual de un patron
	//	y construir las salidas decodificadas.
	int row_pixel_accum, col_pixel_accum, k, c, pos;
	int row_pixel_value, row_pixel_inv, col_pixel_value, col_pixel_inv, thresh;
	
	// Variables auxiliares para Shift del binario de patrones.
	Mat cap, inv;
	k = 0;
	
	for(int i=0;i<size.height;i++)
	{
		for(int j=0;j<size.width;j++)
		{
			
			if(mask.at<unsigned char>(i,j))
			{
				col_pixel_accum = 0;
				for(int k=0;k<col_cap.size();k++)
				{
					Mat c = col_cap[k];
					Mat c2 = col_cap[++k];
					
					col_pixel_value = c.at<unsigned char>(i,j);
					col_pixel_inv = c2.at<unsigned char>(i,j);
					
					if(abs(col_pixel_value - col_pixel_inv)<10)
					{
						col_pixel_accum = -1;
						break;
					}
					
					if(col_pixel_value>col_pixel_inv)
					{
						// Poner el bit en 1
						col_pixel_accum = (col_pixel_accum<<1) | 1;	
					}
					else
					{
						// Poner el bit en 0
						col_pixel_accum = (col_pixel_accum<<1) & (~1);	
					}	
						
				}
				
				row_pixel_accum = 0;
				for(int k=0;k<row_cap.size();k++)
				{
					Mat c = row_cap[k];
					Mat c2 = row_cap[++k];
					
					row_pixel_value = c.at<unsigned char>(i,j);
					row_pixel_inv = c2.at<unsigned char>(i,j);
					
					if(abs(row_pixel_value - row_pixel_inv)<10)
					{
						row_pixel_accum = -1;
						break;
					}
					
					if(row_pixel_value>row_pixel_inv)
					{
						// Poner el bit en 1
						row_pixel_accum = (row_pixel_accum<<1) | 1;	
					}
					else
					{
						// Poner el bit en 0
						row_pixel_accum = (row_pixel_accum<<1) & (~1);	
					}	
					
				}
				
				if(col_pixel_accum == -1 || row_pixel_accum == -1)
					continue;
				
				if(col_pixel_accum<proj_w && row_pixel_accum<proj_h)
				{
					proj.at<int>(row_pixel_accum*proj_w + col_pixel_accum,0) += i;
					proj.at<int>(row_pixel_accum*proj_w + col_pixel_accum,1) += j;
					proj.at<int>(row_pixel_accum*proj_w + col_pixel_accum,2) += 1;
				}
			}
		}
	}

	// Devuelvo 
	return proj;
	
}

///--------------------------------------------------------------------------------------------------------
/// Camera Calibration
/*
	Consideraciones:
		Se supone una camara ideal. Imagen centrada en el sistema de coordenadas de la camara y sin distorsion o desenfoque.
			Con lo cual se ignoran las coordenadas Intrinsecas de la camara ( = Identidad )
		
		Revisar si es necesaria una Normalizacion de la distribucion
		
		Por ahora pensado para pares de camara (Stereo Vision)
		
		La presente funcion sigue el enfoque de Zhang para la calibracion de la camara, se considera
			al objeto fotografia como una superficie plana.
*/

///--------------------------------------------------------------------------------------------------------
///	Zhang:
/// Funcion para Calibracion de "1 SOLA CAMARA" a partir de varias fotos
///		Entrada: Lista de fotos de una sola camara
///--------------------------------------------------------------------------------------------------------

Mat gauss_jordan(Mat input)
{
	Mat matriz = input.clone();		// para no alterar la matriz de entrada
	int m = matriz.size().width;
//	int n = img.size().height;
	int n = m-1;
	
	float c;
	
	Mat d = Mat::zeros(1,m,CV_32FC1);
	d.at<float>(0,m-1)=1;
	
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

Mat get_norm_matrix(Mat img)
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


Mat estimate_homography(Mat img)
{
	int N = img.size().height;

	// Nx3 por la coordenada homogenea
	Mat p_real(N,3,CV_32FC1), foto(N,3,CV_32FC1);
	
	for(int i=0;i<N;i++) 
	{
		foto.at<float>(i,0) = img.at<float>(i,0);
		foto.at<float>(i,1) = img.at<float>(i,1);
		foto.at<float>(i,2) = 1.0f;
		
		p_real.at<float>(i,0) = img.at<float>(i,2);
		p_real.at<float>(i,1) = img.at<float>(i,3);
		p_real.at<float>(i,2) = 1.0f;
	}
	
	Mat Na = get_norm_matrix(p_real);
	Mat Nb = get_norm_matrix(foto);	
	
	Mat M = Mat::zeros(2*N,9,CV_32FC1);
	Mat aux, aux2, a, b;
	
	float k;
	
	for(int i=0;i<N;i++) 
	{
		k = 2*i;
		
		transpose(p_real.row(i),aux);
		transpose(foto.row(i),aux2);
		
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

Mat vij(Mat H, int i , int j)	/// matriz qu enac de la ortogonalidad de la matriz de rotacion, me permite descomponer el producto de la Homografia y la Inversa de los param_intrinsecos(incognitas) para elaborar un sistema de ecuaciones
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


vector<Mat> SL::plane_base_calibration (vector<Mat> p_corrs) {
	// p_corrs : Vector con multiples fotos (mas de 2) de la planilla para calibrar para UNA SOLA CAMARA
	/*	Formato:
			Cada elemento del vector corresponde con una fotografia distinta (es decir, de otro angulo).
			Estos elementos consisten en un Mat que guarda para cada posicion de la resolucion del proyector,
				con que punto de la imagen se correponde (o promedio de puntos en caso de haber mas de
				una coincidencia) .
	
	*/
	
	/// FALTA NORMALIZAR... DIVIDIR ESTA MIERDA... SEPARAR ESTILO MATLAB...
	
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
	
	Mat I,E;									// Matriz para los parametros Extrinsicos
	
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
	
//	show_mat(V); cout<<endl;
	
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
	
//	show_mat(b); cout<<endl;
	//--------------------------------------------------------------------------
	// Burger Paper - Zhang Algorithm
	w =   b.at<float>(0,0)*b.at<float>(2,0)*b.at<float>(5,0) 
		- b.at<float>(1,0)*b.at<float>(1,0)*b.at<float>(5,0)
		- b.at<float>(0,0)*b.at<float>(4,0)*b.at<float>(4,0) 
		+ 2*b.at<float>(1,0)*b.at<float>(3,0)*b.at<float>(4,0)
		- b.at<float>(2,0)*b.at<float>(3,0)*b.at<float>(3,0);
	
	d =   b.at<float>(0,0)*b.at<float>(2,0) - b.at<float>(1,0)*b.at<float>(1,0);
	
	// 
//	float step1 = d*b.at<float>(0,0);
	
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
	
	for(int foto =0; foto<n; foto++){
	
//		cout<<"H: "; show_mat(H[foto]);  cout<<endl;
		
		h1 = H[foto].col(0);
		h2 = H[foto].col(1);
		h3 = H[foto].col(2);

//		cout<<"h1: "; show_mat(h1);  cout<<endl;
//		cout<<"h2: "; show_mat(h2);  cout<<endl;
//		cout<<"h3: "; show_mat(h3);  cout<<endl;
		
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


///
/// Triangulacion
///

Mat SL::get_line(Mat Im, Mat Em, Mat cam_p)
{
	
	Mat line_ec(2,3,CV_32FC1);
	
	Mat org = (Mat_<float>(1,4) << 
		0.0f,0.0f,0.0f,1.0f
	);
	
	//
	Em.resize(4);
	org.copyTo(Em.row(3));
	
	transpose(org,org);
	Mat invEm = Em.inv();
	
	//
	Mat offset = invEm*org;
	
	//
	transpose(cam_p,cam_p);

	cam_p = Im.inv()*cam_p;
	Mat cp = (Mat_<float>(4,1)<<
			  
			  cam_p.at<float>(0,0),
			  cam_p.at<float>(1,0),
			  cam_p.at<float>(2,0),
			  1.0f
			  );
	
	cp = invEm*cp;
	
	//
	
	Mat r1 = (Mat_<float>(1,3) << 
		offset.at<float>(0,0),
		offset.at<float>(1,0),
		offset.at<float>(2,0)
	);
		
	r1.copyTo(line_ec.row(0));
	
	Mat r2 = (Mat_<float>(1,3) << 
		cp.at<float>(0,0),
		cp.at<float>(1,0),
		cp.at<float>(2,0)
	);
	
//	r2 = r2-r1;
	
	r2.copyTo(line_ec.row(1));

	return line_ec;
}

Point3f SL::calc_intersection(Mat line_1, Mat line_2)
{
	
//	show_mat(line_1);
//	show_mat(line_2);
	
	Mat r1_0,r1_1, r2_0, r2_1;
	Mat inters, b;
	float n2, dist,alpha,beta;
	
	line_1.row(0).copyTo(r1_0);
	line_1.row(1).copyTo(r1_1);
//	r1_1 = line_1.row(0)+line_1.row(1);
	
	line_2.row(0).copyTo(r2_0);
	line_2.row(1).copyTo(r2_1);
//	r2_1 = line_2.row(0)+line_2.row(1);
	
//	show_mat(r1_1);
//	show_mat(r2_1);
	
	Mat d1 = r1_1 - r1_0;
	Mat d2 = r2_1 - r2_0;

	Mat df = r2_0 - r1_0;
	
	Mat n =  d1.cross(d2);
	
	n2 = n.dot(n);
	
	if (n2!=0)
	{
		dist = df.dot(n/norm(n));
		
		if (abs(dist)<0.001)
		{
			b = n.cross(df);
			alpha = b.dot(d2);
			beta = b.dot(d1);
			
			inters = r1_0 + (alpha/n2)*d1;
			
		}
		else
		{
			n = n/norm(n);
			
			r1_0 = r1_0 + ((dist/2)*n);
			r1_1 = r1_1 + ((dist/2)*n);
			r2_0 = r2_0 - ((dist/2)*n);
			r2_1 = r2_1 - ((dist/2)*n);
			
			d1 = r1_1 - r1_0;
			d2 = r2_1 - r2_0;
			
			df = r2_0 - r1_0;
			
			n = d1.cross(d2);
			n2 = n.dot(n);
			
			b = n.cross(df);
			alpha = b.dot(d2);
			beta = b.dot(d1);
			
		    inters = r1_0 + (alpha/n2)*d1;
			
		}
		
	}
	else
	{
		cout<<"Error Interseccion: LINEAS PARALELAS"<<endl;
	}
	
	Point3f p;
	
	p.x = inters.at<float>(0,0);
	p.y = inters.at<float>(0,1);
	p.z = inters.at<float>(0,2);
	
	return p;
	
}


