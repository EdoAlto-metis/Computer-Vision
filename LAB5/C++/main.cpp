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
        sub_images.push_back(sub_image);
    }
    imshow("sub_image", sub_images[0]);
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
    for(int i=1;i<content.size();i++){
        slot_id_coll.push_back(content[i][0]);
        int x = stoi(content[i][1]);
        int y = stoi(content[i][2]);
        int width = stoi(content[i][3]);
        int high = stoi(content[i][4]);
        Rect park_slot = Rect(x, y, width, high);
        park_slot_coll.push_back(park_slot);        
    }
    camera -> slot_id_coll;
    camera -> park_slot_coll;
}