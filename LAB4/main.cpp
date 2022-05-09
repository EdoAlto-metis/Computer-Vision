#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int, char**) {
    std::cout << "Hello, world!\n";
}
string path = "/Desktop/Computer-Vision/img/LAB4/LNSRT1";										// insert here images directory
Mat input_image = cv::imread(path + "padova.jpg");

cv::imshow("input image", input_image);
waitKey(0);
