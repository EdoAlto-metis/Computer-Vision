#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int, char**) {
    std::cout << "Hello, world!\n";
    string path = "/home/edoardo/Pictures/Computer-Vision/LAB4/LNSRT1/";										// insert here images directory
    Mat input_image = cv::imread(path + "padova.jpg");
    imshow("Greta mi fa respirare", input_image);
    waitKey(0);
}