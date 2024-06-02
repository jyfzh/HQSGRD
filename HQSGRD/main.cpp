#include <sys/io.h>

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

void getAllFiles(std::string path, std::vector<fs::path>& files) {
  for (const auto& entry : fs::directory_iterator(path)) {
    if (entry.is_regular_file()) {
      files.push_back(entry.path().filename());
    }
  }
}

int main() {
  vector<fs::path> files;
  vector<double> run_time;

  fs::path Basic_folder = "/home/jyf/source/uavid/";
  fs::path Input_folder =  Basic_folder / "raw/";
  fs::path RCF_folder =  Basic_folder / "rcf/";
  fs::path Output_folder = Basic_folder / "hqs/";

  getAllFiles(Input_folder, files);

  for (int Superpixel_Num = 100; Superpixel_Num <= 1000;
      Superpixel_Num += 100) {
    for (auto file : files) {
      cout << "file / Superpixel Number: " << file << " / ";
      const auto input_file = Input_folder / file;
      const auto RCF_file = RCF_folder / file;
      const auto output_file = Output_folder / file;

      HQSGTRD sp;
      sp.Superpixel_Segmentation(input_file, RCF_file, Superpixel_Num,
          file, run_time, iteration_num,
          Save_Image, Save_Label_file);
    }
  }
  return 0;
}
