#include "reconstruccion.h"

reconstruccion::reconstruccion() {
	
}


Mat reconstruccion::get_line(Mat Im, Mat Em, Mat cam_p)
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

Point3f reconstruccion::calc_intersection(Mat line_1, Mat line_2)
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
