#include <iostream>
#include <opencv2/opencv.hpp>


#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
 
using namespace std;
using namespace cv;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

struct CameraInfo{
    vector<string> slot_id_coll;
    vector<Rect> park_slot_coll;
};

void readCameraInfoCSV(CameraInfo *camera, string file_name);
void write_csv(std::string filename, vector<pair<string, vector<string>>> dataset);
 
int main(int, char**) {
    string work_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/test/camera1/";		// insert here images directory
	string image_collect_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/splitted/";
	int image_counter = 1;
	vector<string> original_path_coll;
	vector<string> splitted_path_coll;
    // Iterating over the file in the work path folder
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
		// Iterating over park slot
        for (int i = 0; i < cam_1.park_slot_coll.size(); i++)
		{	
			Rect park_slot = cam_1.park_slot_coll[i];
			park_slot_x_coll.push_back(to_string(park_slot.x));
			park_slot_y_coll.push_back(to_string(park_slot.y));
			park_slot_width_coll.push_back(to_string(park_slot.width));
			park_slot_height_coll.push_back(to_string(park_slot.height));
			// Extracting the park slot image
            Mat sub_image = input_image(park_slot);
			Mat resized_sub_image;
			// Resizing in 250x250
            resize(sub_image, resized_sub_image, Size(250, 250), INTER_CUBIC);
			String split_filename = save_slot_order_path+"_slot_"+to_string(i+1)+".jpg";
			park_slot_path_coll.push_back(split_filename);
			imwrite(split_filename, resized_sub_image);
		}
        // Writing CSV
		vector<pair<string, vector<string>>> park_slot_info = {{"Park Slot Image", park_slot_path_coll},
															   {"Park Slot X", park_slot_x_coll},
															   {"Park Slot Y", park_slot_y_coll},
															   {"Park Slot Width", park_slot_width_coll},
															   {"Park Slot Height", park_slot_height_coll}};
		write_csv(image_collect_path+"image_"+to_string(image_counter)+"_park_slot_info.csv", park_slot_info);
		image_counter++;
	}
    // Writing image linker csv
	vector<pair<string, vector<string>>> path_link = {{"Original Path", original_path_coll}, {"Splitted Image Path", splitted_path_coll}};
	write_csv(image_collect_path+"image_linker.csv", path_link);

	std::cout << "Image splitting task completed" << endl;
}

/*
    readCameraInfoCSV returns inside a ParkInfo structure the information about the park slot:
    position in x,y and are, width and high
*/

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
    float conv_factor = 0.385;                                                      // From original resolution to 1000x750 pixel image
	float size_increment = 1.2;														// Adding 20% window size
    for(int i=1;i<content.size();i++){
        slot_id_coll.push_back(content[i][0]);
        int x = int(stoi(content[i][1])*conv_factor);
        int y = int(stoi(content[i][2])*conv_factor);
        int width = int(stoi(content[i][3])*conv_factor);
		int high = int(stoi(content[i][4])*conv_factor);
        // Incrementing park slot size when possible
		if (x+width*size_increment<1000)
		{
			width = int(width*size_increment);
		}
		if (y+high*size_increment<750)
		{
			high = int(high*size_increment);
		}
        Rect park_slot = Rect(x, y, width, high);
        park_slot_coll.push_back(park_slot);        
    }
    camera -> slot_id_coll = slot_id_coll;
    camera -> park_slot_coll = park_slot_coll;
}

/*
    write csv method, taken from internet
*/
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