#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat resim = imread("para.jpg");
	Mat cikis;
	cvtColor(resim, cikis, COLOR_BGR2GRAY);	
	GaussianBlur(cikis, cikis, Size(3, 3), 1);
	Canny(cikis, cikis, 10, 255);
	const char* degerler[] = { "1 Kurus","5 Kurus","10 Kurus","25 Kurus","50 Kurus"};
	
	vector<Vec3f> cember_degerleri;
	HoughCircles(cikis, cember_degerleri, HOUGH_GRADIENT, 1, 50);
	for (int i = 0; i < cember_degerleri.size(); i++)
	{
		string degerlere_ulasma;
		Point merkez(cvRound(cember_degerleri[i][0]), cvRound(cember_degerleri[i][1]));
		int yaricap = cvRound(cember_degerleri[i][2]);
		circle(resim, merkez, yaricap, Scalar(200, 200, 123), 1);
		if (yaricap > 74)degerlere_ulasma = degerler[4];
		else if (yaricap > 65)degerlere_ulasma = degerler[3];
		else if (yaricap > 62)degerlere_ulasma = degerler[2];
		else if (yaricap > 59)degerlere_ulasma = degerler[1];
		else if (yaricap > 51)degerlere_ulasma = degerler[0];
		putText(resim, degerlere_ulasma, Point(cvRound(cember_degerleri[i][0]-120), cvRound(cember_degerleri[i][1])), FONT_HERSHEY_COMPLEX, 1, Scalar::all(0), 1);

	}
	imshow("bozuklar", resim);
	imshow("1", cikis);
	waitKey(0);
	
}