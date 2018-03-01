#ifndef SL_H
#define SL_H

#include <vector>
//#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;


enum cod_mode{BINARY, GRAY};

class SL 
{
private:
	
	/// Atributos Necesarios
	
	unsigned int proj_w;		// | Resolucion del projector,
	unsigned int proj_h;		// | hasta que punto contrastan la resolucion de las imagenes capturadas contra la del projector?

	unsigned int row_lvl;		// | Necesarios? Ahorra recalcular para generar los patrones, en caso de patron custom debe definirse. Necesaria la resoluion? (decodificacion?)
	unsigned int col_lvl;		// |
	
	
	Mat background_mask;		// | No considero que haga falta 2 mascacras separadas, reveer para corregir.
	Mat shadow_mask;			// |
	
	vector<Mat> code_patterns;	// Necesario?
	Mat disparity_map;
	Mat point_cloud;
	
	
	/// Atributos Opcionales (osea, wut?)
	
	/// Funciones planteadas como privadas (revisar la disposicion posterior en la clase).
	
	Mat capture(VideoCapture cap, bool show = false);		//Funcion para capturar generica.
//	void error(unsigned int type);		//Funcion para display de error generico. || Usar nomenclatura para clarificar, typedef, enum....
	
public:
	
	SL(const unsigned int p_w, const unsigned int p_h);
	
	/// Funciones Necesarias
	Mat background_substraction(Mat after_placement, Mat before_placement, unsigned char thresh); // Quizas necesite capturas adicionales para este paso (REVISAR!)
	Mat background_substraction(VideoCapture cap, unsigned char thresh); // 
	
//	vector<Mat> generate_binary_code_patterns();
//	vector<Mat> generate_gray_code_patterns();
	vector<Mat> generate_code_patterns(cod_mode c = BINARY);
	
	Mat shadow_mask_filtering(Mat light, Mat dark, unsigned char thresh); // Necesita 2 patterns mas, uno full blanco y otro full negro... 
	Mat shadow_mask_filtering(VideoCapture cap, unsigned char thresh); // Necesita 2 patterns mas, uno full blanco y otro full negro... 
							 // estimo que puede deducirse de los demas patterns de captura, al computar tambien el inverso para 
							 // definir niveles de iluminacion.
	
	// Funcion de decodificacion de los patrones de luz fotografiados.
	// Por ahora solo esta implementado para codificacion Binaria
	// Para transformar a GRAY, usar XOR. HACER!!
	Mat decode_captured_patterns(vector<Mat> captures, Mat mask);		// | Hasta que punto estas 2 partes corresponden estar separadas,
///	Mat decode_captured_patterns(Mat black, Mat white, vector<Mat> row_cap, vector<Mat> col_cap, Mat mask);

	// Funcion para la calibracion de las Camaras. Todas las correspondencias entre captuas y proyectos
	//	se pasan dentro de un vector de Mat.
	///	Sigue el enfoque de Zhang para Closed-Form Solution
//	vector<Mat> plane_base_calibration(vector<Mat> p_corrs);
	vector<Mat> plane_base_calibration (vector<vector<Point2f>> p_foto, vector<Point2f> p_planilla);

	//	get_disparity_map();			// mierda inutil o cosa importante?

	// DEVUELVE LA FORMULA DE LA LINEA QUE VA DEESDE EL ORIGEN DE LA CAMARA HASATA EL PUNTO DE LA FOTOGRAFIA
	Mat get_line(Mat Im, Mat Em, Mat cam_p);
	// OBTIENE LA INTERSECCION DE 
	Point3f calc_intersection(Mat line_1, Mat line_2);

//	reconstruct_point_cloud();		// | existe alternativas a una nube de puntos? hasta que punto es redituable?
//	
//	visualize_reconstructed_mesh(); // Revisar opencv Viz, o desligarme de la visualizacion. 
//	
	/// Deberia involucrar la reconstruccion de la malla?? Deberia plantearlo como algo opcional??
	/// Hasta donde sobre este topico puedo involucrar a OpenCV ?? Requerire el uso de algo externo (OpenGL)??

	/// Funciones Opcionales
//	use_custom_patterns();
//	generate_default_calibration_patterns();

//	
	Mat get_fundamental_matrix(vector<Point2f> c1, vector<Point2f> c2 );
	vector<Mat> rectification(vector<Mat> cam1, vector<Mat> cam2);
	~SL();
};

#endif
