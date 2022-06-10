#include <iostream>
#include <opencv2/opencv.hpp>


#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;
using namespace cv;

struct ParkInfo{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    bool isOccupied = false;
};

vector<vector<string>> readCSV(string file_name);
vector<vector<string>> readImageInfoCSV(string file_name);
vector<ParkInfo> readParkInfoCSV(string file_name);

Mat equalHist(Mat input_image);
 
int main(int, char**) {
	string work_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/splitted/";
    string save_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/program_output/";
    string csv_filename = work_path+"image_linker.csv";
    vector<string> original_image_filenames;
    vector<string> splitted_partial_paths;
    vector<vector<string>> string_collection;
    string_collection = readImageInfoCSV(csv_filename);
    original_image_filenames = string_collection[0];
    splitted_partial_paths = string_collection[1];
    for (int image_i=0; image_i<original_image_filenames.size(); image_i++){
        Mat original_image = imread(original_image_filenames[image_i]);
        string park_info_csv_file_path = splitted_partial_paths[image_i]+"_park_slot_info.csv";
        vector<ParkInfo> park_info_coll = readParkInfoCSV(park_info_csv_file_path);
        for (int park_i = 0; park_i<park_info_coll.size(); park_i++)
        {
            ParkInfo park = park_info_coll[park_i];
            if(!park.isOccupied)
            {
                Rect reagion = Rect(park.x, 
                                    park.y,
                                    park.width, 
                                    park.height);
                rectangle(original_image, reagion, Scalar(0, 255, 0));
            }
            else
            {
                Rect reagion = Rect(park.x, 
                                    park.y,
                                    park.width, 
                                    park.height);
                rectangle(original_image, reagion, Scalar(0, 0, 255));
            }
        }
        string final_image_filename = save_path+"classification"+to_string(image_i+1)+".jpg";
        imwrite(final_image_filename, original_image);
    }
    cout << "Image merging completed" << endl;
}

vector<vector<string>> readImageInfoCSV(string file_name){
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
    vector<string> original_paths;
    vector<string> splitted_partial_paths;
    vector<vector<string>> output;

    for(int i=1;i<content.size();i++){
        original_paths.push_back(content[i][0]);
        splitted_partial_paths.push_back(content[i][1]);       
    }
    output.push_back(original_paths);
    output.push_back(splitted_partial_paths);
    return output;
}


vector<ParkInfo> readParkInfoCSV(string file_name){
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

    ParkInfo park_slot;
    vector<ParkInfo> park_slot_info_collection;
    int classification;
    for(int i=1;i<content.size();i++)
    {
        park_slot.x = stoi(content[i][2]);
        park_slot.y = stoi(content[i][3]);
        park_slot.width = stoi(content[i][4]);
        park_slot.height = stoi(content[i][5]);

        classification = stoi(content[i][6])==1;
        if (classification==1) park_slot.isOccupied = true;    
        park_slot_info_collection.push_back(park_slot);  
    }
    return park_slot_info_collection;
}