#include <sys/io.h>
#include <time.h>

#include <filesystem>
#include <iostream>
#include <vector>

#include "Superpixel_Generation.h"

using namespace std;
namespace fs = std::filesystem;

const int iteration_num = 4;
const int Superpixel_Num = 300;
const int Save_Image = 1;
const int Save_Label_file = 0;

void getAllFiles(std::string path, std::vector<fs::path>& files,
                 std::string filetype) {
  for (const auto& entry : fs::directory_iterator(path)) {
    if (entry.is_regular_file() && entry.path().extension() == filetype) {
      files.push_back(entry.path());
    }
  }
}

int main() {
  vector<fs::path> input_files;
  vector<double> run_time;

  fs::path Input_folder = "/home/jyf/Downloads/dataset/BSD/";
  fs::path Output_folder = "/home/jyf/Downloads/result/";

  getAllFiles(Input_folder, input_files, ".jpg");

  for (int Superpixel_Num = 100; Superpixel_Num <= 1000;
       Superpixel_Num += 100) {
    for (auto input_file : input_files) {
      cout << "input_file: " << input_file << " ";
      const auto RCF_file = input_file.replace_extension("png");
      const auto temp_name = input_file.filename();
      const auto output_file = Output_folder.string() + temp_name.string();
      cout << "output_file: " << output_file << " ";

      HQSGTRD sp;
      sp.Superpixel_Segmentation(input_file, RCF_file, Superpixel_Num,
                                 output_file, run_time, iteration_num,
                                 Save_Image, Save_Label_file);
    }
    double time = 0;
    for (int i = 0; i < run_time.size(); i++) {
      time += run_time[i];
    }
    time = time / run_time.size();
    cout << "The running time of the algorithm is:  " << time << "\n";
  }
  return 0;
}
