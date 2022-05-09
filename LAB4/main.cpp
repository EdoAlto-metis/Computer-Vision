#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int, char**) {
    std::cout << "Hello, world!\n";
}
std::string path = "C:/Users/Edoardo/Gith/Computer-Vision/LAB3/imgs";										// insert here images directory
cv::Mat input_image = cv::imread(path + "road1.png");
