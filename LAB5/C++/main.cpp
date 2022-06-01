#include <iostream>
#include <opencv2/opencv.hpp>


#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;
using namespace cv;

struct CameraInfo{
    vector<string> slot_id_coll;
    vector<Rect> park_slot_coll;
};

void readCameraInfoCSV(CameraInfo *camera, string file_name);
Mat equalHist(Mat input_image);
 
int main(int, char**) {
    std::cout << "Hello, world!\n";
    string image_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/unpacked_images/";										// insert here images directory
    Mat input_image = cv::imread(image_path + "2015-11-12_0709.jpg");
    imshow("Input Image", input_image);
    waitKey(0);
    CameraInfo cam_1;
    string filename_cam_1 = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/camera1.csv";
    readCameraInfoCSV(&cam_1, filename_cam_1);
    vector<Mat> sub_images;
    for (int i = 0; i < cam_1.park_slot_coll.size(); i++)
    {
        Rect park_slot = cam_1.park_slot_coll[i];
        Mat sub_image = input_image(park_slot);
		Mat resized_sub_image;
		resize(sub_image, resized_sub_image, Size(250, 250), INTER_LINEAR);
		Mat EQ_sub_image = equalHist(resized_sub_image);
        sub_images.push_back(EQ_sub_image);
    }
	for (int img_index = 0; img_index<sub_images.size(); img_index++){
		Mat image = sub_images[img_index];
		imshow("substracted image", image);
		waitKey(0);
	}
	destroyAllWindows();

    //equalHist();
	//waitKey(0);
}

void readCameraInfoCSV(CameraInfo *camera, string file_name){
    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    fstream file (file_name, ios::in);
    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
    cout<<"Could not open the file\n";
    
    vector<string> slot_id_coll;
    vector<Rect> park_slot_coll; 
	float conv_factor = 0.385;
    for(int i=1;i<content.size();i++){
        slot_id_coll.push_back(content[i][0]);
        int x = int(stoi(content[i][1])*conv_factor);
        int y = int(stoi(content[i][2])*conv_factor);
        int width = int(stoi(content[i][3])*conv_factor);
        int high = int(stoi(content[i][4])*conv_factor);
        Rect park_slot = Rect(x, y, width, high);
        park_slot_coll.push_back(park_slot);        
    }
    camera -> slot_id_coll = slot_id_coll;
    camera -> park_slot_coll = park_slot_coll;
}

/**
	equalHist function perform the computation and equalization of the 3 channels instograms of a colour image
	input: Mat input_image containing the image to be equalized
*/
Mat equalHist(Mat input_image) {

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
	return EQ_image;
}