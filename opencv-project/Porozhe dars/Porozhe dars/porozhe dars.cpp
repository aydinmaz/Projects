//porozhe khodam------------------------

#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

using namespace cv;
using namespace std;



int main()
{
	int s;
	Mat original;


	cout << " images with different light intensity (Task 1): \n 1 = TESI00 \n 2 = TESI01 \n 3 = TESI12 \n 4 = TESI21 \n 5 = TESI31 \n 6 = TESI33 \n\n images with another object(Task 2): \n 7 = TESI44\n 8 = TESI47\n 9 = TESI48\n 10 = TESI49\n\n images dirty with scattered iron powder (Task 2):\n 11 = TESI90\n 12 = TESI92 \n 13 = TESI98 " << endl;

	while (1)
	{
		cout << " \n\n Please select an image number 1 to 13 then press enter: " << endl;
		cin >> s;

		cout << "\n You have entered  " << s << endl;
		if (s > 13)
			cout << "The number that you have entered is not valid, please try again!\n";
		else

		{
			switch (s) {
			case 1:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI00.bmp", -1);
			break; }
			case 2:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI01.bmp", -1);
			break; }
			case 3:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI12.bmp", -1);
			break; }
			case 4:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI21.bmp", -1);

			break; }
			case 5:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI31.bmp", -1);
			break; }
			case 6:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI33.bmp", -1);
			break; }
			case 7:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI44.bmp", -1);
			break; }
			case 8:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI47.bmp", -1);
			break; }
			case 9:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI48.bmp", -1);
			break; }
			case 10:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI49.bmp", -1);
			break; }
			case 11:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI90.bmp", -1);
			break; }
			case 12:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI92.bmp", -1);
			break; }
			case 13:
			{ original = imread("C:/Users/majid/Desktop/c++/Opencv3.1/pictures/project/TESI98.bmp", -1);
			break; }
			}
			if (!original.data) { cout << "wrong address or name of image" << endl; system("pause"); return -1; }
			int w, h;
			w = original.cols;
			h = original.rows;
			printf("Image size: %d x %d\n", w, h);
			imshow("original image", original);

			Mat drawing = Mat::zeros(original.size(), CV_8UC3);
			Mat drawing2 = Mat::zeros(original.size(), CV_8UC3);
			Mat thresh;
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;



			// imshow("dilate",original);


			if (s>10) {			// if we had scattered powder
				for (int i = 1; i<6; i++)
					medianBlur(original, original, 3);
				imshow("Median filter", original);
			}
			GaussianBlur(original, original, Size(3, 3), 0, 0);
			imshow("Gaussian blur", original);


			threshold(original, thresh, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
			imshow("Threshed ", thresh);
			/// Find contours ---- this works on white objects------------ 
			findContours(thresh, contours, hierarchy, RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point(0, 0));
			imshow("contours", thresh);
			cout << "------------- Number of contours is : " << contours.size() << endl;
			/// Get the moments
			vector<Moments> mu(contours.size());
			vector<RotatedRect> minRect(contours.size());
			vector<Point2f>center(contours.size());
			vector<float>radius(contours.size());
			vector<Point2f> mc(contours.size());
			//----------------------------------
			for (int i = 0; i < contours.size(); i++)
			{
				mu[i] = moments(contours[i], false);
				mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
			}

			for (int i = 0; i < contours.size(); i++)
			{
				int a = contourArea(contours[i]);
				if (a>2000)      // if the area of contour is less than what we expected it is a redundant object out of process
				{
					if (hierarchy[i][3] == -1)
					{
						drawContours(drawing, contours, i, Scalar(0, 0, (i + 1) * 60), 2, 8, hierarchy, 0, Point());
						cout << "\n\n\n*********************************************************************" << endl;
						//cout<<"*********************************************************************"<<endl;
						printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
						int A = 0;
						// for( int z = 0; z< contours.size(); z++ )			 
						//{


						//--finding and drawing minrect and orientation------------------------------
						minRect[i] = minAreaRect(Mat(contours[i]));//acquire minrect
						Point2f rect_points[4];
						minRect[i].points(rect_points);
						for (int j = 0; j < 4; j++)//draw minrect
							line(drawing, rect_points[j], rect_points[(j + 1) % 4], Scalar((i + 1) * 70, 50, 50), 1, 8);
						//double angle =(- minRect[i].angle);
						// cout<<"angle of contour = "<<angle<<endl;
						cout << "                          center of mass = " << mc[i] << endl;
						//--- 
						if (minRect[i].size.width < minRect[i].size.height) {
							printf("Angle along longer side respect to X axe =%7.2f\n", -minRect[i].angle - 90);
							//printf("Angle along longer side: %7.2f\n", minRect[i].angle+180); 
						}
						else {
							printf("Angle along longer side respect to X axe =%7.2f\n", -minRect[i].angle);
							//printf("Angle along longer side: %7.2f\n", minRect[i].angle+90); 
						}
						cout << "                                  Width = " << minRect[i].size.width << endl;
						cout << "                                  height = " << minRect[i].size.height << endl;
						circle(drawing, mc[i], 4, (50, 150, 100), -1, 8, 0);

						//-----------finding width in Barycentre------------------------------------
						float a_min = 300.00;//I define this a great number to be greater than any possible value of "a"
						for (int i = 0; i < contours.size(); i++)//contours.size means number of counters 
						{   //cout<<contours[i].size()<<endl;//conturs[i].size number of countours
							for (int j = 0; j < contours[i].size(); j++)//find barycentre by checking every point of each contour 
							{

								double b = pow((contours[i][j].x - mc[i].x), 2) + pow((contours[i][j].y - mc[i].y), 2);
								double a = sqrt(b);
								if (a < a_min)
									a_min = a;
							}
						}
						cout << "                     Width at Barycentre = " << a_min * 2 << endl;
						//----find it is type A or B------------------------------			  
						for (int z = 0; z < contours.size(); z++)
						{
							if (hierarchy[z][3] == i)// find who his father is i
								A = A++;
						}
						if (A == 1)// if there is one nested contour in i
						{
							cout << "\n                     ***   contour " << i << "  has 1 hole   ***" << endl;
							putText(drawing, "A", mc[i], FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 2);
						}
						else  //(if A==2)//else there is two nested contour in i
						{
							cout << "\n                    ***   contour " << i << "  has 2 holes   ***" << endl;
							putText(drawing, "B", mc[i], FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 2);
						}
					}
					//---Print the characteristics of the moments----------------------------------    


					//----Find center and radius of the holes	  
					int B = 0;
					for (int z = 0; z< contours.size(); z++)
					{
						//------Find holes-----------------------
						if (hierarchy[z][3] == i)//   if the father of nested contour is i
						{
							B++;
							drawContours(drawing, contours, z, Scalar(0, (z + 1) * 50, 0), 2, 8, hierarchy, 0, Point());
							minEnclosingCircle(contours[z], center[z], radius[z]);
							circle(drawing2, center[z], radius[z], Scalar(0, 0, 255), 2, 8, 0);
							cout << "------------------------------------" << endl;
							cout << "         ****  details of hole number " << B << "  ****" << endl;
							cout << "            radious = " << radius[z] << endl;
							cout << "            diameter = " << 2 * radius[z] << endl;
							cout << "center by mincircle = " << center[z] << endl;
							cout << "   center by moment = " << mc[z] << endl;

						}
					}

				}
			} //}
			imshow("Type A or B", drawing);
			imshow("Holes ", drawing2);

			waitKey();

			// destroyAllWindows();
		}

	}


}