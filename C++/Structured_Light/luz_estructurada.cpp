#include "luz_estructurada.hpp"

luz_estructurada::luz_estructurada() {
	
}

///--------------------------------------------------------------------------------------------------------
vector<Mat> luz_estructurada::generate_binary_code_patterns ( )
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
vector<Mat> luz_estructurada::generate_gray_code_patterns ( ) 
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

///

//Mat SL::decode_captured_patterns (Mat black, Mat white, vector<Mat> row_cap, vector<Mat> col_cap, Mat mask) {
Mat luz_estructurada::decode_captured_patterns (vector<Mat> captures, Mat mask) {
	
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
