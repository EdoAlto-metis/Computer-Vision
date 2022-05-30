#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//FUNCTION SIGNATURE
void inputNumber(int *variable);
void showHistogram(vector<Mat>& hists, string plot_name);
void equalHist(Mat input_image);
void equalHist(Mat input_image);
void imageFiltering(Mat image, int filter_type);

// MAIN
int main() {
	while (true) {

		// user interface and task selection (1 for histogram equalization, 2 for image filtering, 3 for exit program)
		int task = 0;
		cout << "Chose task:\n";
		cout << "digit 1 for histogram equalization\n";
		cout << "digit 2 for image filtering\n";
		cout << "digit 3 to quit the program\n";
		inputNumber(&task);
		/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! INSERT HERE IMAGE DIRECTORY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
		string path = "C:/Users/Edoardo/Pictures/images/";	

		// task selection
		if (task == 1) {												// histogram equalization task

			// getting image in imput
			Mat input_image = imread(path + "overexposed.jpg");
			if (input_image.empty()) {
				printf("Error: Image not found");
				return EXIT_FAILURE;
			}
			// histogram equalization task
			equalHist(input_image);
			waitKey(0);
			destroyAllWindows();
		}

		if (task == 2) {												// filtering task

			// getting image in input
			Mat input_image = imread(path + "portello-noisy.png");
			if (input_image.empty()) {
				printf("Error: Image not found");
				return EXIT_FAILURE;
			}

			// chosing filter type for the imageFiltering function
			int filter_type = 0;
			cout << "Chose filter type for the second part:\n";
			cout << "digit 1 for Median\n";
			cout << "digit 2 for Gaussian\n";
			cout << "digit 3 for Bilateral\n";
			inputNumber(&filter_type);
			if (filter_type == 1 || filter_type == 2 || filter_type == 3) {
				// image filtering and printing
				imageFiltering(input_image, filter_type);
				waitKey(0);
				destroyAllWindows();
			}
			else{
				cout << "ERROR: select a proper filter"<<endl;
				cout << "turning back to main menu"<<endl;
			}
		}
		
		// exit from program
		if (task == 3) {
			cout << "Program quitted succesfully";
			return 0;
		}

		else {
			cout << "ERROR: select a proper task" << endl;
			cout << "turning back to main menu" << endl;
		}
	}
}


// FUNCTIONS
/**
	inputNumber function make sure that the cin input is an int
	input: pointer to the variable that the program has to take in input
*/
void inputNumber(int *variable) {
	while (1) {
		cin >> *variable;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input: integer number is required " << endl;
		}
		else
			break;
		cout << "Try again" << endl;
	}
}

/** 
	showInstogram function perform the plotting of the 3 colour channel instogram
	input: vector hists containing the 3 colour channel histograms; plot_name, name of the window where to plot the istograms 
*/
void showHistogram(vector<Mat>& hists, string plot_name) {

	// variuos parameters for the cv::line function
	const float width = 640;
	const float heigth = 480;
	const int hist_size = 255;
	const int hist_w = 512, hist_h = 400;
	const int bin_w = cvRound((double)hist_w / hist_size);
	const float bin_width = static_cast<float>(width) / static_cast<float>(hist_size);

	Mat hist_image(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));									// initialize histogram image
	Scalar colours[] =																			// colour channels initialization
	{
		{255, 0, 0},    // blue
		{0, 255, 0},    // green
		{0, 0, 255}     // red
	};
	for (int i = 0, end = hists.size(); i < end; i++)											// iterating over the instograms
	{
		Mat histogram = hists[i];																// current channel histogram
		Scalar color = colours[i];																// current color
		normalize(histogram, histogram, 0, hist_image.rows, cv::NORM_MINMAX);					// histogram normalization
		
	    // histogram image creation
		for (int i = 1; i < hist_size; i++)														
		{
			line(hist_image, Point(bin_w*(i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - cvRound(histogram.at<float>(i))),
				color, 2, 8, 0);
		}
	}
	// plot image
	imshow(plot_name, hist_image);
}

/**
	equalHist function perform the computation and equalization of the 3 channels instograms of a colour image
	input: Mat input_image containing the image to be equalized
*/
void equalHist(Mat input_image) {

	// divide the image in the 3 color channels
	vector<Mat> RGB_channels;
	split(input_image, RGB_channels);
	Mat R_channel = RGB_channels[0];
	Mat G_channel = RGB_channels[1];
	Mat B_channel = RGB_channels[2];

	// compute original channels histograms
	Mat Hist_R;
	Mat Hist_G;
	Mat Hist_B;

	int color_size = 255;
	float img_range[] = { 0, color_size };
	const float* Range = { img_range };

	calcHist(&R_channel, 1, 0, Mat(), Hist_R, 1, &color_size, &Range, true, false);							// red channel histogram
	calcHist(&G_channel, 1, 0, Mat(), Hist_G, 1, &color_size, &Range, true, false);							// green channel histogram
	calcHist(&B_channel, 1, 0, Mat(), Hist_B, 1, &color_size, &Range, true, false);							// blue channel histogram

	// equalizing channels

	Mat EQ_channel_R;																						// red
	Mat EQ_channel_G;																						// green
	Mat EQ_channel_B;																						// blue
	equalizeHist(R_channel, EQ_channel_R);
	equalizeHist(G_channel, EQ_channel_G);
	equalizeHist(B_channel, EQ_channel_B);

	// compute equalized histograms
	Mat EQ_hist_R;
	Mat EQ_hist_G;
	Mat EQ_hist_B;

	calcHist(&EQ_channel_R, 1, 0, Mat(), EQ_hist_R, 1, &color_size, &Range, true, false);					// red channel histogram
	calcHist(&EQ_channel_G, 1, 0, Mat(), EQ_hist_G, 1, &color_size, &Range, true, false);					// green channel histogram
	calcHist(&EQ_channel_B, 1, 0, Mat(), EQ_hist_B, 1, &color_size, &Range, true, false);					// blue channel histogram

	// combine channels and output for visualization
	vector<Mat> hists = { Hist_R, Hist_G, Hist_B };
	vector<Mat> equalized_hists = { EQ_hist_R, EQ_hist_G, EQ_hist_B };
	vector<Mat> equalized_channels = { EQ_channel_R, EQ_channel_G, EQ_channel_B };
	Mat EQ_image;
	merge(equalized_channels, EQ_image);


	// plotting histograms
	showHistogram(hists, "Originale Image Histogram");
	showHistogram(equalized_hists, "Equalized Image Histogram");


	// visualize the images
	cv::imshow("Origial Image", input_image);
	cv::imshow("Equalized Image", EQ_image);
}

/**
	imageFiltering function perform the filtering of an input image
	input: Mat image input image to be filtered; int filter_type, type of the filter to be applied (1 for Median, 2 for Gaussian, 3 for Bilateral)
*/
void imageFiltering(Mat image, int filter_type) {
	Mat filtered_image;
	int kernel_size = 0;																// filter window size
	int sigma_s = 0;																	// sigma s (for Gaussian and Bilateral filters)
	int sigma_r = 0;																	// sigma r (for Bilateral)

	// median filter
	if (filter_type == 1) {

		// create window for trackbars and output image
		namedWindow("Median Fiter (press q key to quit)", 1);
		createTrackbar("Window size", "Median Fiter (press q key to quit)", &kernel_size, 50);	// kernel size trackbar
		for (;;) {
			if (kernel_size % 2 == 0) { kernel_size += 1; }										// all the cv filtering methods works only with odd kernel size: if the input is pair one is added
			medianBlur(image, filtered_image, kernel_size);										// filtering
			
			// visualize the image
			imshow("Median Fiter (press q key to quit)", filtered_image);
			
			// exit routine
			char quit = (char)waitKey(30);
			if (quit == 'q' || quit == 'Q' || quit == 27) break;
		}
	}
	// gaussian filter
	else if (filter_type == 2) {

		// create window for trackbars and output image
		namedWindow("Gaussian Fiter (press q key to quit)", 1);
		createTrackbar("Window size", "Gaussian Fiter (press q key to quit)", &kernel_size, 50); // kernel size trackbar
		createTrackbar("Sigma S", "Gaussian Fiter (press q key to quit)", &sigma_s, 50);		 // sigma s trackbar
		for (;;) {
			if (kernel_size % 2 == 0) { kernel_size += 1; }										// all the cv filtering methods works only with odd kernel size: if the input is pair one is added
			GaussianBlur(image, filtered_image, Size(kernel_size, kernel_size), sigma_s);		// image filtering
			
			// visualize the image
			imshow("Gaussian Fiter (press q key to quit)", filtered_image);

			// exit routine
			char quit = (char)waitKey(30);
			if (quit == 'q' || quit == 'Q' || quit == 27) break;
		}

	}
	// bilateral filter
	else if (filter_type == 3) {

		// create window for trackbars and output image
		namedWindow("Bilateral Fiter (press q key to quit)", 1);
		createTrackbar("Window size", "Bilateral Fiter (press q key to quit)", &kernel_size, 50); // kernel size trackbar
		createTrackbar("Sigma R", "Bilateral Fiter (press q key to quit)", &sigma_r, 50);		  // sigma s trackbar
		createTrackbar("Sigma S", "Bilateral Fiter (press q key to quit)", &sigma_s, 50);		  // sigma r trackbar
		for (;;) {
			if (kernel_size % 2 == 0) { kernel_size += 1; }										  // all the cv filtering methods works only with odd kernel size: if the input is pair one is added
			bilateralFilter(image, filtered_image, kernel_size, sigma_r, sigma_s);

			// visualize the image
			imshow("Bilateral Fiter (press q key to quit)", filtered_image);

			// exit routine
			char quit = (char)waitKey(30);
			if (quit == 'q' || quit == 'Q' || quit == 27) break;
		}
	}
}
