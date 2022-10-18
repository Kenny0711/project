#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
//#include "opencv2/imgproc.hpp"
//#include "opencv2/calib3d.hpp"
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
using namespace cv;
int main(int argc, char* argv[]) {
    ifstream fin1;
    fin1.open(argv[1]);
    while (!fin1.eof() ) {
        string s;
        getline(fin1, s);
        if (s == "" || s == "\n")break;
        Mat picture = imread(s);//input圖片
        vector<Point2f> angle_point;//特徵角點
        bool found = findChessboardCorners(picture, Size(9, 6), angle_point);//找出特徵角點
       // drawChessboardCorners(image_in, Size(9, 6), corners, found);
      //  imshow("test", image_in);
      //  waitKey(0);
        vector<Point3f> point_3D;//三維點
        for (int j = 0; j < 6; j++) {//二維點丟到三維
            for (int k = 0; k < 9; k++) {
                point_3D.push_back(Point3f(j * 1.0, k * 1.0, 0));
            }
        }
        vector<vector<Point2f> > angle_point_set;
        vector<vector<Point3f> > point_3D_set;
        vector<Mat> Rotation_matrix, Displacement_matrix;//旋轉矩陣跟位移矩陣
        Mat camera;//相機矩陣
        Mat distCoeffs;//畸變矩陣
        int flags = 0;
        if (found) {//如果有特徵角點的話
            angle_point_set.push_back(angle_point);
            point_3D_set.push_back(point_3D);
            calibrateCamera(point_3D_set, angle_point_set, picture.size(), camera, distCoeffs, Rotation_matrix, Displacement_matrix, flags);
        }
        Mat input = imread(argv[2]);
        Mat output;
        undistort(input, output, camera, distCoeffs);//矯正
        imshow("result", output);//輸出
       // waitKey(0);
        string a = "C:\\Users\\kenny\\OneDrive\\桌面\\筆記\\線代\\hw3\\hw2-1\\hw2-1\\result\\abc";
        a = a + s;
        imwrite(argv[3], output);//儲存
    }
}