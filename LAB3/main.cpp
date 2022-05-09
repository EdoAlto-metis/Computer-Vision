#include <stdio.h>
#include <opencv2/opencv.hpp>

void imageShow(cv::Mat input_image);
cv::Mat cannyEdgeDetector(cv::Mat input_image);
cv::Mat hugesTransform(cv::Mat canny_edges);

int main() {

	std::string path = "/home/edoardo/Pictures/Computer-Vision/LAB3/";										// insert here images directory

	cv::Mat input_image = cv::imread(path + "road2.png");
	if (input_image.empty()) {
		std::printf("Error: Image not found");
		return EXIT_FAILURE;
	}
	imageShow(input_image);
	// Canny Edge Finder
	cv::Mat canny_output;
	canny_output = cannyEdgeDetector(input_image);
}

void imageShow(cv::Mat input_image) {
	cv::imshow("Input image", input_image);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

cv::Mat cannyEdgeDetector(cv::Mat input_image) {

	cv::Mat edges;
	double Th = 600;
	double Tl = 200;
	int aperture_size = 3;
	bool L2_gradient = true;
	cv::Canny(input_image, edges, Tl, Th, aperture_size, L2_gradient);
	cv::imshow("Canny algorithm output image", edges);
	cv::waitKey(0);
	cv::destroyAllWindows();
	return edges;
}


cv::Mat hugesTransform(cv::Mat canny_edges) {
	cv::Mat huges_lines_param;
	return huges_lines_param;
}