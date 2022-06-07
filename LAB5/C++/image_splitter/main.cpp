#include <iostream>
#include <opencv2/opencv.hpp>


#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <utility> // std::pair
 
using namespace std;
using namespace cv;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

struct CameraInfo{
    vector<string> slot_id_coll;
    vector<Rect> park_slot_coll;
};

void readCameraInfoCSV(CameraInfo *camera, string file_name);
void write_csv(std::string filename, vector<pair<string, vector<string>>> dataset);
Mat equalHist(Mat input_image);
 
int main(int, char**) {
	bool hist_equalize = false;
    string work_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/test/camera1/";		// insert here images directory
	string image_collect_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/splitted/";
	int image_counter = 1;
	vector<string> original_path_coll;
	vector<string> splitted_path_coll;
	for(auto& path_obj: recursive_directory_iterator(work_path))
	{	
		string save_slot_order_path = image_collect_path+"image_"+to_string(image_counter);
		original_path_coll.push_back(path_obj.path());
		splitted_path_coll.push_back(save_slot_order_path);
		Mat input_image = cv::imread(path_obj.path());
		CameraInfo cam_1;
		string filename_cam_1 = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/test/camera1.csv";
		readCameraInfoCSV(&cam_1, filename_cam_1);
		vector<string> park_slot_path_coll;
		vector<string> park_slot_x_coll;
		vector<string> park_slot_y_coll;
		vector<string> park_slot_width_coll;
		vector<string> park_slot_height_coll; 
		for (int i = 0; i < cam_1.park_slot_coll.size(); i++)
		{	
			Rect park_slot = cam_1.park_slot_coll[i];
			park_slot_x_coll.push_back(to_string(park_slot.x));
			park_slot_y_coll.push_back(to_string(park_slot.y));
			park_slot_width_coll.push_back(to_string(park_slot.width));
			park_slot_height_coll.push_back(to_string(park_slot.height));
			Mat sub_image = input_image(park_slot);
			Mat resized_sub_image;
			resize(sub_image, resized_sub_image, Size(150, 150), INTER_LINEAR);
			if (hist_equalize)
			{
				resized_sub_image = equalHist(resized_sub_image);
			}
			String split_filename = save_slot_order_path+"_slot_"+to_string(i+1)+".jpg";
			park_slot_path_coll.push_back(split_filename);
			imwrite(split_filename, resized_sub_image);
		}
		vector<pair<string, vector<string>>> park_slot_info = {{"Park Slot Image", park_slot_path_coll},
															   {"Park Slot X", park_slot_x_coll},
															   {"Park Slot Y", park_slot_y_coll},
															   {"Park Slot Width", park_slot_width_coll},
															   {"Park Slot Height", park_slot_height_coll}};
		write_csv(image_collect_path+"park_"+to_string(image_counter)+"_park_slot_info.csv", park_slot_info);
		image_counter++;
	}
	vector<pair<string, vector<string>>> path_link = {{"Original Path", original_path_coll}, {"Splitted Image Path", splitted_path_coll}};
	write_csv(image_collect_path+"image_linker.csv", path_link);

	std::cout << "Image splitting task completed" << endl;
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
	float size_increment = 1.2;														// Adding 20% window size
    for(int i=1;i<content.size();i++){
        slot_id_coll.push_back(content[i][0]);
        int x = int(stoi(content[i][1])*conv_factor);
        int y = int(stoi(content[i][2])*conv_factor);
        int width = int(stoi(content[i][3])*conv_factor);
		width = int(width*size_increment);
        int high = int(stoi(content[i][4])*conv_factor);
		high = int(high*size_increment);
        Rect park_slot = Rect(x, y, width, high);
        park_slot_coll.push_back(park_slot);        
    }
    camera -> slot_id_coll = slot_id_coll;
    camera -> park_slot_coll = park_slot_coll;
}


void write_csv(std::string filename, vector<pair<string, vector<string>>> dataset){
    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    // as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size
    
    // Create an output filestream object
    std::ofstream myFile(filename);
    
    // Send column names to the stream
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";
    
    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }
    
    // Close the file
    myFile.close();
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