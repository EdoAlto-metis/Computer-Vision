#include <iostream>
#include <opencv2/opencv.hpp>


#include <fstream>
#include <filesystem>
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
	bool hist_equalize = false;
	string work_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/splitted/";		// insert here images directory
    Mat input_image = cv::imread(work_path + "2016-01-12_0746.jpg");
    imshow("Input Image", input_image);
    waitKey(0);
    CameraInfo cam_1;
    string filename_cam_1 = work_path + "camera1.csv";
    readCameraInfoCSV(&cam_1, filename_cam_1);
    vector<Mat> sub_images;
    for (int i = 0; i < cam_1.park_slot_coll.size(); i++)
    {
        Rect park_slot = cam_1.park_slot_coll[i];
        Mat sub_image = input_image(park_slot);
		Mat resized_sub_image;
		resize(sub_image, resized_sub_image, Size(250, 250), INTER_LINEAR);
		if (hist_equalize)
		{
			resized_sub_image = equalHist(resized_sub_image);
		}
        sub_images.push_back(resized_sub_image);
    }
	String image_collect_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/splitted/";
	for (int i = 0; i < sub_images.size(); i++)
	{
		String filename = image_collect_path+"image_"+to_string(i+1)+".jpg";
		imwrite(filename, sub_images[i]);
	}
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