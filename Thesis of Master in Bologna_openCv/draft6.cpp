#include <iostream>
#include <string>
#include <fstream>
#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
using namespace std;
using namespace cv;

//header functions***************
void fill__r_angle_masscenter(Mat& coordinates, Mat& angle, Mat& r, Mat& mid_x, Mat& mid_y, Point2i& masscenter);
void show_arrows_Samplelimage(Mat& image, Mat& mid_x, Mat& mid_y, Point2i& masscenter);
//takes sample object image and gives back Mat Data

Mat Create_Table(Mat& angle2, Mat& r2, int teta);
//takes adress of Mat Data and teta and gives back Mat table
Mat Create_Table2(Mat& angle_r, int teta);
void make_bin(Mat& image, Mat& coordinates, Mat& Table, Mat1i& bin, int teta);
void rotation(int teta_rotate, Mat& r, Mat& angle, Mat& r2, Mat& angle2);
//takes orignal image and adres of Mat Table and teta and gives back Mat bin
void draw_arrows_of_origImage(Mat& coordinates, Mat& drawnlines_orignal, Mat& Table, int& teta, int& teta_rotate);

void drawFoundObject(Mat& img, Point maxLoc, Mat& r2);
//takes adres of Mat image,Point maxoc of bin ,and adres of Mat r and shows found image
void supress_smallLines(Mat& coordinates, int& line_length);
Mat lsd(Mat& image, Mat& coordinates);
void boxFilterbin(Mat1i& bin, int& kernel_size);//function baray inke dar Mat bin,majmu khaneh hay atraf bin(i,j) 
				//ro be shoa r jam kone va tu bin(i,j) begzare/misheh hazfesh kard va moshkeli pish nemiyad

int main()
{
	double start = double(getTickCount());//baray andaze giri zaman
	//chizi ke yad gereftam,bar aks gofte ha tu stackoverflow ,vaghti argument MAT migzari,header ro kopi nemikone
	//balke ye kopi az mat mide be function.hala rah hal gozashtan & hast ke ham baaes sarfejui dar ram mishe
	//va ham mituni dakhel fanction value in argument ro taghir bedi ,yani tu main ham taghir mikone on mat argument


	//Mat Sampleobject_image = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/test/model06.jpg", 0);
	//Mat original_image = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/test/test009.jpg", 0);
	//Mat img_showfoundObject = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/test/test009.jpg", 1);

	Mat Sampleobject_image = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/projectsamples/sample7.jpg", 0);
	Mat original_image = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/projectsamples/org26.jpg", 0);
	Mat img_showfoundObject = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/projectsamples/org26.jpg", 1);

	/*Mat Sampleobject_image = imread("C:/Users/aydin/Desktop/c++/pictures/test3/model_02.jpg", 0);
	Mat original_image      = imread("C:/Users/aydin/Desktop/c++/pictures/test3/test_01.jpg", 0);
	Mat img_showfoundObject = imread("C:/Users/aydin/Desktop/c++/pictures/test3/test_01.jpg", 1);*/



	//Mat Sampleobject_image = imread("C:/Users/aydin/Desktop/c++/pictures/projectsamples/sample1.jpg", 0);
	//Mat original_image = imread("C:/Users/aydin/Desktop/c++/pictures/projectsamples/org2.jpg", 0);
	//Mat img_showfoundObject = imread("C:/Users/aydin/Desktop/c++/pictures/projectsamples/org2.jpg", 1);

	if (!Sampleobject_image.data) { cout << "wrong address or name of sampleobjectimage" << endl; system("pause"); return -1; }
	if (!original_image.data) { cout << "wrong address or name of original_image" << endl; system("pause"); return -1; }
	if (!img_showfoundObject.data) { cout << "wrong address or name of img_showfoundObject" << endl; system("pause"); return -1; }


	//ba treshhold kar kharab misheh,hatta bedun rotation ro ham peyda nemikone ,shayad be dalil inke dar dakhel
	//treshhold ,labe ha ro taghir mideh ba bluring ya har chi
	//threshold(Sampleobject_image2, Sampleobject_image, 0, 255, CV_THRESH_OTSU);




	int table_step = 3; 
	int Rotation_step = 3;
	int good_enough_max_bin = 20;
	int kernel_size = 21;
	string supress_line_check = "no";
	int line_supress_length = 50;

	int RotationInterval_start = -179; 
	int RotationInterval_end = 180;
	if (RotationInterval_start >180 || RotationInterval_start <-180 || RotationInterval_end >180 
		|| RotationInterval_end <-180 || RotationInterval_start > RotationInterval_end)
	{
		cout << "please enter your rotation intervals between -180 ,180 \n also Rotationinterval_start < Rotationinterval_End" << 
			endl; system("pause"); return -1;
	}
	string Rotation = "yes";//no or yes
	if (Rotation == "no") { RotationInterval_start = 0, RotationInterval_end = 0; }//injuri dige rotation hzf mishe

	Mat coordinates;
	Mat drawnLines = lsd(Sampleobject_image, coordinates);//Mat coordinates ro por mikone va tasvir khotut ro barmigardune
	if (supress_line_check == "yes") { supress_smallLines(coordinates, line_supress_length); }
	//function for supressing small lines;it takes Mat coordinate
	// and gives back Mat coordinate with new size you can comment out it 
	imshow("sample picture", drawnLines);
	imwrite("C:/Users/majid/Desktop/images/drawnLines.jpg", drawnLines);
	cout << "number of lines of object is : " << coordinates.rows << endl;
	Point2i masscenter;
	Mat angle, r;
	Mat1f mid_x, mid_y;
	//mid_x ,y ro birun func. dorost kardam chon 2 ta func. azash estefade mikonan.
	fill__r_angle_masscenter(coordinates, angle, r, mid_x, mid_y, masscenter);
	show_arrows_Samplelimage(drawnLines, mid_x, mid_y, masscenter);
	//cout << "\n angle dast nakhorde \n" << angle << endl;
	angle = 360 - angle;
						

	Mat coord_main_image;
	Mat drawnlines_orignal = lsd(original_image, coord_main_image);
	imshow("main picture", drawnlines_orignal);
	cout << "number of lines of main picture is : " << coord_main_image.rows << endl;
	imwrite("C:/Users/majid/Desktop/images/main.jpeg", drawnlines_orignal);
	if (supress_line_check == "yes") { supress_smallLines(coord_main_image, line_supress_length); }
	int All_possible_objects_rowNumbr = ((RotationInterval_end - RotationInterval_start) / Rotation_step) + 1;

	Mat1i All_possible_objects(All_possible_objects_rowNumbr,4,0);
	
	int s = 0;
	Mat angle2, r2;

	for (int i = RotationInterval_start; i < RotationInterval_end + 1; i = i + Rotation_step)
		//agar nemikhay rotation ro emal koni.in upper limit ro ham sefr begzar ke halghe khonsa she
	{
		
		rotation(i, r, angle, r2, angle2);
		
		Mat Table = Create_Table(angle2, r2, table_step);//Data ro mideh va Table ro pas migire
			 //Mat Table = Create_Table2(angle_r, teta);//Data ro mideh va Table ro pas migire

		Mat1i bin(original_image.size() * 2, 0);//ijad yek bin khali ba abaad image asli	
		Mat1f mid_x2, mid_y2;
		make_bin(original_image, coord_main_image, Table, bin, table_step);// function original image returns bin mat
		boxFilterbin(bin, kernel_size);				//cout << "\n originalimagedata \n" << originalimagedata << endl;


		
		double maxVal;
		Point maxLoc;
		minMaxLoc(bin, 0, &maxVal, 0, &maxLoc);
	
		All_possible_objects(s, 0) = i;
		All_possible_objects(s, 1) = maxLoc.x;
		All_possible_objects(s, 2) = maxLoc.y;
		All_possible_objects(s, 3) =int( maxVal);
		s = s + 1;
		}
	
	//in 2 ta vase bargardoondan mokhtasat maxval az bin be image hast
	int length = original_image.rows;
	int width = original_image.cols;
	
	//cout << bin_last << endl;
	int s2 = good_enough_max_bin;
	int s3 = 0;//vase inke radif un maximum maxval peyda shode ro bedoonim
	int s4=0;//yek shomarande sade
	for (int i = 0; i < All_possible_objects_rowNumbr; i++)//yaftan bishtarin maxval az bin_last
	{
		if (All_possible_objects(i, 3) > s2)
		{
			s4++;//shomarande vase inke bege are ye moredi peyda shod
			s2 = All_possible_objects(i, 3); s3 = i;
		}
		if (All_possible_objects(i,3) > good_enough_max_bin)//in ro vase ehtiyat gozashtam ke neshoon bede kojaha object ehtemali hast
		{
			cout << "\n this is bigger than good_enough: angle=" << All_possible_objects(i, 0) << "  x,y="
				<< All_possible_objects(i, 1) - width / 2 << "," << All_possible_objects(i, 2) - length / 2
				<< "   val=" << All_possible_objects(i, 3);
		}
	}
		//int maxVal = bin_last(s, 3);
	if (s4!=0)//yani agar maxvali vujud dare
	{
		// draw_arrows_of_origImage(coordinates32, drawnlines_orignal, Table, table_step, i);
		cout << "\n\n found object: angle=" << All_possible_objects(s3,0) <<"   x,y="<< All_possible_objects(s3, 1) - width / 2 << ","
			<< All_possible_objects(s3, 2) - length / 2<<"   maxval=" << All_possible_objects(s3, 3) << endl;
		
		//baray transfer maxloc az mokhtasat bin be mokhtasat img be khater ekhtelaf size bin va img
		Point maxLoc = Point(All_possible_objects(s3,1) - width / 2, All_possible_objects(s3,2) - length / 2);
		//Mat1f r2 = angle_r(Range::all(), Range(1, 3));//extract r from Mat angle_r
		rotation(All_possible_objects(s3,0), r, angle, r2, angle2);
		drawFoundObject(img_showfoundObject, maxLoc, r2);
	}
	
	imshow("foundObject", img_showfoundObject);
	imwrite("C:/Users/majid/Desktop/images/found.jpeg", img_showfoundObject);
	
	
	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();
	std::cout << "It took " << duration_ms << " ms." << std::endl;
	waitKey(0);
	return 0;
}








void fill__r_angle_masscenter(Mat& coordinates, Mat& angle, Mat& r, Mat& mid_x, Mat& mid_y, Point2i& masscenter)
{
	Mat1f diff_x = coordinates.col(2) - coordinates.col(0);
	Mat1f diff_y = coordinates.col(3) - coordinates.col(1);
	//cout << coordinates.col(0) << endl;
	//cout << diff_x << endl;
	////finding angles of ines
	Mat1f magnitude;
	cartToPolar(diff_x, diff_y, magnitude, angle, true);
	
	//finding midpoints 
	mid_x = coordinates.col(0) + diff_x / 2;
	mid_y = coordinates.col(1) + diff_y / 2;
	//finding bary ceter(mass center)
	
	//cout << coordinates << "\n\n" << mid_x << "\n\n" << mid_y << endl;

	float sum_x = 0, sum_y = 0;
	for (size_t i = 0; i < coordinates.rows; i++)
	{
		sum_x = sum_x + mid_x.at<float>(i);
		sum_y = sum_y + mid_y.at<float>(i);
	}
	masscenter = Point2i(sum_x / (coordinates.rows), sum_y / (coordinates.rows));//Point2i because pixes should be int.

	 //finding r . r hamoon vector vasel vasat khutut ba masscenter hast
	Mat r_x, r_y;
	subtract(mid_x, masscenter.x, r_x);
	subtract(mid_y, masscenter.y, r_y);
	hconcat(r_x, r_y, r);
}





void show_arrows_Samplelimage(Mat& drawnLines, Mat& mid_x, Mat& mid_y, Point2i& masscenter)
{
	int a = masscenter.x;
	int b = masscenter.y;

	
	for (size_t i = 0; i < mid_x.rows; i++)
	{
		arrowedLine(drawnLines, Point(mid_x.at<float>(i),
			mid_y.at<float>(i)), masscenter, Scalar(0, 200, 0), 1, 8, 0, 0.1);
	}
	imshow("sample image with arrows of r", drawnLines);
	imwrite("C:/Users/majid/Desktop/images/arrow.jpg", drawnLines);
	//// avval return coordinates; minveshtam kar nemikard ta inke baad az 2 saat az link paain yad gereftam ke clone() begzaram.
	////http://stackoverflow.com/questions/18680709/opencv-c-returning-a-mat-then-saving-it-to-file	
}







void rotation(int teta_rotate, Mat& r, Mat& angle, Mat& r2, Mat& angle2)
{
	float teta_rad = teta_rotate*3.14 / 180;//convert from degrees to rad.
	Mat1f A = (Mat1f(2, 2) << cos(teta_rad), -sin(teta_rad), sin(teta_rad), cos(teta_rad));//matrix rotation
	r2 = r*A;
	angle2 = 0;
	//cout << "\n angle2 sefre shode \n" << angle2;
	angle2 = angle + teta_rotate;//agar teta manfi bashe ke -teta mishe mosbat,agar ham teta mosbat bashe ke

	for (size_t i = 0; i < angle2.rows; i++)
	{
		float h = 0;
		h = angle2.at<float>(i);
		//cout <<"h avval  " <<h << endl;
		//in 2 satr vase ine ke masalan angle 350 hast va teta rotate 20 ke mishe 370,va mire birron 360
		//ya angle 5 hast teta rotate -20 ke mishe -15 ke baz mire biroon 360 
		if (h < 0.0) { angle2.at<float>(i) = 360.0 + h; }
		if (h >= 360.0) { angle2.at<float>(i) = h - 360.0; }
	
		h = angle2.at<float>(i);//in bayad basheh chon alan dige angle2 avaz shodeh baad az if hay bala
								//if (h == 360.0) { angle2.at<float>(i) = 0.0; }//be jay in,hamoon bala ye = ezafe kardm
		if (h >= 180.0) { angle2.at<float>(i) = h - 180.0; }
		//cout << "h baad az 180  "<< angle2.at<float>(i) << endl;
	}

}






//function baray ijaad table
//Mat data ro az function Sampleimage va teta ro az main migire va Table ro tahvil mideh
Mat Create_Table(Mat& angle2, Mat& r2, int teta)
{
	////finding dimension for creating R-table---------------------------------------------------------
	Mat1i Table_bin(180 / teta, 1, 0);
	//ijad yek mat 1 sotuni va row=row number of Mat angle_r baray yaftan max col table
	int max_bin = 0;
	int s = angle2.rows;
	//cout << angle2 << endl;
	for (size_t j = 0; j < s; j++)
	{
		//float *m = &(angle_r.at<float>(j, 0));
		/*	if (angle2.at<float>(j) > 359)
		{
		angle2.at<float>(j) = angle2.at<float>(j) - 360;
		}*/
		//cout << "h = " << angle2.at<float>(j) << int(angle2.at<float>(j)) << endl;

		int h = int(angle2.at<float>(j)) / teta;//in int ke gozashtam baes mishe a'shar hazf beshe
		Table_bin(h)++;//inja lazem nist az at. estefade beshe chon Mat1i hast
		if (Table_bin(h) > max_bin) { max_bin = Table_bin(h); }
	}


	int Table_colnumber = 2 * max_bin;//chon har r 2 ta moallefe dare
	 //cout << "\n Table_rownumber = " << 180 / teta << "   Table_colnumber = " << Table_colnumber << endl;


	 ////Creating R-Table**************************************************************************************
	Mat Table(180 / teta, Table_colnumber, DataType<float>::type, 0.0);
	//0.0 akhar vase ine ke matrix ro ba sefr (double) por kone

	for (size_t i = 0; i <s; i++)
	{
		int d = int(angle2.at<float>(i)) / teta;
		//meghdar zaviye ro cast mikonam be int ta kar taghsim rahat tar beshe

		int f = 0;
		while (Table.at<float>(d, f) != 0) { f = f + 2; }
		// agar !=0 yani inke ghablan por shode on khune
		//setting elements in Table
		Table.at<float>(d, f) = r2.at<float>(i, 0);
		Table.at<float>(d, f + 1) = r2.at<float>(i, 1);
	}

	return Table.clone();
}






//function baray ijaad table

Mat Create_Table2(Mat& angle_r, int teta)
{
	int row_num = 16;//in adad bayad zoj bashe
	int s = angle_r.rows;
	////Creating R-Table**************************************************************************************
	Mat Table(row_num, 360 / teta, DataType<float>::type, 0.0);
	//0.0 akhar vase ine ke matrix ro ba sefr (double) por kone

	for (size_t i = 0; i <s; i++)
	{
		int d = int(angle_r.at<float>(i, 0)) / teta;
		//meghdar zaviye ro cast mikonam be int ta kar taghsim rahat tar beshe
		int f = 0;
		while (Table.at<float>(f, d) != 0)
		{
			f = f + 2;
			if (f>row_num - 1)
			{
				Mat new_row(1, 360 / teta, DataType<float>::type, 0.0);;
				Table.push_back(new_row);
				Table.push_back(new_row);
				row_num = row_num + 2;
			}
		}
		// agar !=0 yani inke ghablan por shode on khune
		//setting elements in Table

		Table.at<float>(f, d) = angle_r.at<float>(i, 1);
		Table.at<float>(f + 1, d) = angle_r.at<float>(i, 2);
	}
	cout << "table size " << row_num << "  " << 360 / teta << endl;
	return Table.clone();
}







void make_bin(Mat& image, Mat& coordinates, Mat& Table, Mat1i& bin, int teta)
{
	Mat1f diff_x = coordinates.col(2) - coordinates.col(0);
	Mat1f diff_y = coordinates.col(3) - coordinates.col(1);

	////finding angles of ines
	Mat1f magnitude, angle;
	cartToPolar(diff_x, diff_y, magnitude, angle, true);
	angle = 360 - angle;// in angle main image has ba un yeki fargh dare
	//cout << "\n angle cor32 \n" << angle << endl;
	for (size_t i = 0; i < angle.rows; i++)
	{// teta  >= 180 ro be baze 0 ta 180 miyaram
		float h = 0.0;
		h = angle.at<float>(i);
		if (h == 360.0) { angle.at<float>(i) = 0.0; }
		else if (h >= 180.0) { angle.at<float>(i) = h - 180.0; }
	}

	Mat1f mid_x = coordinates.col(0) + diff_x / 2;
	Mat1f mid_y = coordinates.col(1) + diff_y / 2;
	//cout << "image size " << image.cols << "  " << image.rows << "\n bin size " << bin.cols << "  " << bin.rows << endl;
	// 2 vase inke felesh ha ba'zan birun mirand						   
	int length = image.rows, width = image.cols;
	//keshidan felesh ha ruy tasvir asli
	for (size_t i = 0; i < coordinates.rows; i++)
	{
		int h = int(angle.at<float>(i)) / teta;
		int f = int(magnitude.at<float>(i));
		int m = 0, x = 0, y = 0;
		while ((Table.at<float>(h, m) != 0) && (m < Table.cols - 2))
			//koli moatal shodam ta fahmidam agar in 2 ro dar akhar nagzaram m bishtar az sutun hay matrix mishe va error mideh
		{
			x = mid_x.at<float>(i) - Table.at<float>(h, m);
			y = mid_y.at<float>(i) - Table.at<float>(h, m + 1);
			m = m + 2;

			x = x + width / 2; y = y + length / 2;//transfer noghat peyda shode,be bin
			if ((x < bin.cols) && (y < bin.rows) && x > 0 && y > 0)//maybe center of line plus r goes out of bin
				
			{
				bin(y, x)++;
				//bin(y, x)=bin(y, x)+f;
			}
			//cout << "bin(x,y) = " << bin(y,x) << endl;//ye ruz moatal shodam ta fahmidam in int ro bayad bezaram
		}
	}

}













void draw_arrows_of_origImage(Mat& coordinates, Mat& drawnlines_orignal, Mat& Table, int& teta, int& teta_rotate)
{
	Mat1f diff_x = coordinates.col(2) - coordinates.col(0);
	Mat1f diff_y = coordinates.col(3) - coordinates.col(1);
	//finding midpoints 
	Mat1f mid_x = coordinates.col(0) + diff_x / 2;
	Mat1f mid_y = coordinates.col(1) + diff_y / 2;
	////finding angles of ines
	Mat1f magnitude, angle;
	cartToPolar(diff_x, diff_y, magnitude, angle, true);
	for (size_t i = 0; i < angle.rows; i++)
	{// teta  >= 180 ro be baze 0 ta 180 miyaram
		float h = 0.0;
		h = angle.at<float>(i);
		if (h == 360.0) { angle.at<float>(i) = 0.0; }
		if (h >= 180.0) { angle.at<float>(i) = h - 180.0; }
	}
	for (size_t i = 0; i < coordinates.rows; i++)
	{
		int h = int(angle.at<float>(i, 0)) / teta;
		int m = 0, x = 0, y = 0;
		while ((Table.at<float>(h, m) != 0) && (m < Table.cols - 2))
			//koli moatal shodam ta fahmidam agar in 2 ro dar akhar nagzaram m bishtar az sutun hay matrix mishe va error mideh
		{
			x = mid_x.at<float>(i) - Table.at<float>(h, m);
			y = mid_y.at<float>(i) - Table.at<float>(h, m + 1);
			m = m + 2;
			//if ((x < drawnLines.rows) && (y < drawnLines.cols) && x > 0 && y > 0)
			//{
			arrowedLine(drawnlines_orignal, Point(mid_x.at<float>(i), mid_y.at<float>(i)),
				Point(x, y), Scalar(0, 200, 0), 1, 8, 0, 0.1);
			//}

		}
		/*	if (i == 20)
		{
		imshow("ORIGINAL picture with arrows", drawnlines_orignal);
		}*/
	}
}






//show found object in image **************
// location maxpoint dar Bin  be ezafe Mat r ro migire , va object peyda shode ro neshun mideh
void drawFoundObject(Mat& img, Point maxLoc, Mat& r2)
{


	//maxLoc = Point(300, -1);
	Mat1i point_x_img = maxLoc.x + r2.col(0);
	Mat1i point_y_img = maxLoc.y + r2.col(1);

	Mat1i r22;//noghat dor object ke mikhaym rang konim 
	hconcat(point_x_img, point_y_img, r22);

	for (size_t i = 0; i < r22.rows; i++)
	{
		if ((r22(i, 0) < img.cols) && (r22(i, 1) < img.rows))
		{
			/*img.at<Vec3b>(Point2i(r2(i, 0), r2(i, 1)))[0] = 0;
			img.at<Vec3b>(Point2i(r2(i, 0), r2(i, 1)))[1] = 0;
			img.at<Vec3b>(Point2i(r2(i, 0), r2(i, 1)))[2] = 200;*/
			circle(img, Point2i(r22(i, 0), r22(i, 1)), 2, Scalar(0, 0, 255), FILLED, LINE_AA);
		}
	}

	//change Mat to vector point baray convex hull
	std::vector<Point> points;
	//http://stackoverflow.com/questions/31944013/how-to-convert-mat-image-to-vectorpoint
	for (size_t i = 0; i < r22.rows; i++)
	{
		points.push_back(Point(r22(i, 0), r22(i, 1)));
		//cout<<points[i]<<endl;	
	}
	//Print out results
	//for (Point p : points)
	//std::cout << p << "\n";

	vector<int> hull;
	convexHull(Mat(points), hull, true);
	int hullcount = (int)hull.size();
	Point pt0 = points[hull[hullcount - 1]];
	for (int i = 0; i < hullcount; i++)
	{
		Point pt = points[hull[i]];
		line(img, pt0, pt, Scalar(0, 255, 0), 1, LINE_AA);
		pt0 = pt;
	}
	if (maxLoc.x <img.rows && maxLoc.y >img.cols && maxLoc.x > 0 && maxLoc.y > 0)
	{
		circle(img, Point(maxLoc), 7, Scalar(0, 255, 0), -1, 8);
	}//keshidan dayre bar ruy ref point peyda shode}



}







Mat lsd(Mat& image, Mat& coordinates)
{
#if 0
	Canny(image, image, 50, 200, 3); // Apply canny edge
#endif

									 // Create and LSD detector with standard or no refinement.
#if 1
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
#else
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_NONE);
#endif

	/*double start = double(getTickCount());*/
	vector<Vec4f> lines_std;
	ls->detect(image, lines_std);
	/*double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();
	std::cout << "It took " << duration_ms << " ms." << std::endl;*/

	coordinates = (Mat4f(lines_std).reshape(1)).clone();

	// Show found lines-------------
	Mat drawnLines(image);
	ls->drawSegments(drawnLines, lines_std);

	return drawnLines.clone();


}








void supress_smallLines(Mat& coordinates, int& line_length)
{

	Mat coordinates_new;
	Mat1f diff_x = coordinates.col(2) - coordinates.col(0);
	Mat1f diff_y = coordinates.col(3) - coordinates.col(1);
	Mat1f Length;
	magnitude(diff_x, diff_y, Length);//zaman ha ro andaze gereftam va didam magnitude saritar az nam nama distance hast

	for (size_t i = 0; i < Length.rows; i++)
	{
		if (Length.at<float>(i) >= line_length)
		{
			//cout << euclidean_distance.at<float>(i) << "\n";
			coordinates_new.push_back(coordinates.row(i));
		}
	}
	coordinates = coordinates_new;
	//return coordinates_new.clone();
}








void boxFilterbin(Mat1i& bin, int& kernel_size)
{
	Mat1i bin_temp(bin.size(), 0);

	//3 saat zahmat keshidam halghe for gozashtam akhar sar didam be rahati ba boxfilter mishe hamoon kar ro kard

	//http://docs.opencv.org/3.0-beta/modules/imgproc/doc/filtering.html
	//http://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/filter_2d/filter_2d.html
	boxFilter(bin, bin_temp, -1, Size(kernel_size, kernel_size), Point(-1, -1), false, BORDER_DEFAULT);
	//filter2D(bin, bin2, 0, kernel, Point(-1,-1), 0, BORDER_DEFAULT);

	bin = bin_temp;
}












