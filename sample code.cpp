#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;

using namespace std;


Mat rotate(Mat src, double angle) {
	Mat dst;
	Point2f pt(src.cols / 2., src.rows / 2.);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, Size(src.cols, src.rows));
	return dst;
}

Mat genSinogram(Mat oriImg) {
	Mat rotatedImg;
	Mat colAddImg(180, oriImg.cols, CV_32FC1); //0~179度

	for (int angle = 0; angle < 180; angle++) {
		//旋轉圖片(0 ~ 179度)
		rotatedImg = rotate(oriImg, angle);

		float originalColSum;
		//遍歷每個col
		for (int col = 0; col < rotatedImg.cols; col++) {
			//計算每個colSum
			originalColSum = 0;
			for (int row = 0; row < rotatedImg.rows; row++) {
				originalColSum += rotatedImg.at<uchar>(row, col);
			}
			//算完後要與row平均(防止溢位)
			colAddImg.at<float>(angle, col) = originalColSum / oriImg.rows;
		}
	}

	return colAddImg;
}

void saveImg(Mat results, char filename[], int iter) {
	cv::normalize(results, results, 0, 255, NORM_MINMAX, CV_8UC1);
	char iterNum[30];
	sprintf_s(iterNum, "%d", iter+1);
	//draw text
	cv::putText(results, //target image
		iterNum, //text
		cv::Point(10, results.rows - 20), //top-left position
		cv::FONT_HERSHEY_DUPLEX,
		1.0,
		CV_RGB(255, 255, 255), //font color
		2);
	imwrite(filename, results);
}

int main() {
	string image_path = samples::findFile("image2.png");
	Mat oriImg = imread(image_path, IMREAD_GRAYSCALE);
	
	if (oriImg.empty()) {
		cout << "Could not read the image: " << image_path << endl;
		return 1;
	}

	int oriRows = oriImg.rows;
	Mat colAddImg = genSinogram(oriImg);
	
	cv::normalize(colAddImg, colAddImg, 0, 255, NORM_MINMAX, CV_8UC1);
	namedWindow("colAddImg", WINDOW_AUTOSIZE);
	imshow("colAddImg", colAddImg);
	imwrite("colAddImg.png", colAddImg);
	//waitKey(0);
	//注意這裡要使用CV_32FC1才能用at<float>
	cv::normalize(colAddImg, colAddImg, 0, 1, NORM_MINMAX, CV_32FC1);
	

	Mat results(oriRows, colAddImg.cols, CV_32FC1, Scalar(1));

	double anglePerPhoto = 180.0/16;
	int totIter = 8;

	for (int iter = 0; iter < totIter; iter++) {
		for (double angle = 0; angle < 180; angle += anglePerPhoto) {
			for (int col = 0; col < results.cols; col++) {
				float colSum = colAddImg.at<float>(angle, col);
				float newColSum = 0;
				for (int row = 0; row < results.rows; row++) {
					newColSum += results.at<float>(row, col);
				}
				for (int row = 0; row < results.rows; row++) {
					if (iter < 8) {
						//AART
						results.at<float>(row, col) += ((colSum - newColSum) / results.rows);
						//if (results.at<float>(row, col) < 0) results.at<float>(row, col) = 0;
					}
					else {
						//MART
						if (newColSum == 0) newColSum = 1; //防止除以0
						results.at<float>(row, col) *= (colSum / newColSum);
					}
				}
			}
			results = rotate(results, anglePerPhoto);
		}
		results = rotate(results, 180);

		//save image 需要先自己建立MART資料夾
		char fileName[30];
		sprintf_s(fileName, "MART/MART_%d_%d.png", (int)(180 / anglePerPhoto), iter);
		saveImg(results, fileName, iter);
	}

	cv::normalize(results, results, 0, 255, NORM_MINMAX, CV_8UC1);

	//OUTPUT RESULT HERE
	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", results);
	imwrite("result.png", results);
	waitKey(0);

	return 0;
}
