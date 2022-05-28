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
    vector<int> x_coll;
    vector<int> y_coll;
    vector<int> width_coll;
    vector<int> hight_coll;
};

void readCameraInfoCSV(CameraInfo *camera, string file_name);

 
int main(int, char**) {
    std::cout << "Hello, world!\n";
    string path = "/home/edoardo/Pictures/Computer-Vision/LAB4/LNSRT1/";										// insert here images directory
    Mat input_image = cv::imread(path + "padova.jpg");
    imshow("Greta mi fa respirare", input_image);
    waitKey(0);
    CameraInfo cam_1;
    string filename_cam_1 = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/camera1.csv";
    readCameraInfoCSV(&cam_1, filename_cam_1);
    for (int element = 0; element<=cam_1.slot_id_coll.size();element++)
        std::cout << cam_1.slot_id_coll[element];
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
    vector<int> x_coll;
    vector<int> y_coll;
    vector<int> width_coll;
    vector<int> hight_coll;    
    for(int i=0;i<content.size();i++){
        slot_id_coll.push_back(content[i][0]);
        x_coll.push_back(stoi(content[i][1]));
        y_coll.push_back(stoi(content[i][2]));
        width_coll.push_back(stoi(content[i][3]));
        hight_coll.push_back(stoi(content[i][4]));
    }
    camera -> slot_id_coll;
    camera -> x_coll;
    camera -> y_coll;
    camera -> width_coll;
    camera -> hight_coll;
}