#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

string int_to_string(int i){
	ostringstream ss;
	ss << i;
	return ss.str();
}

void save_to_ppm(unsigned char* img_data, unsigned int width, unsigned int heigth ){
	string header = "P6	256 256	255"
}

unsigned char* generate_data_pattern(int shift, unsigned int mask){
	unsigned char* image_data;
	
	return image_data;
}

void create_pattern(unsigned int width, unsigned int heigth ){
	unsigned int n_row = log10(heigth)/log10(2);
	unsigned int n_col = log10(heigth)/log10(2);
	unsigned int mask = 1,leftover;
	
	string filename_pattern;
	string filename_extension = ".ppm";
	
	unsigned char white = 255, black = 0;
	
	for(int i=0; i<n_row; i++){
		ofstream file;
		
		filename_pattern = "pattern_";
		
		filename_pattern.append(int_to_string(i));
		filename_pattern.append(filename_extension);
		
		file.open(filename_pattern.c_str(), ios::binary);
		
		for(int j=0; j<heigth; j++){
			for(int k=0; k<width; k++){
				
				if( (j >> i) & mask){
					file << white;
					file << white;
					file << white;
				}
				else{
					file << black;
					file << black;
					file << black;
				}
			}
		}
		
		file.close();
		
	}
	
	for(int i=0; i<n_row; i++){
		
	}
}


int main (int argc, char *argv[]) {
	
	create_pattern(1024, 768);
	
	return 0;
}

