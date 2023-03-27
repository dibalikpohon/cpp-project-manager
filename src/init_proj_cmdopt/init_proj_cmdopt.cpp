#include "init_proj_cmdopt.hpp"
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <system_error>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

void InitProjCmdOptions::execute(const argumentum::ParseResult&) {
  //std::cout << "Hello, World!" << std::endl;

  if (this->is_c_project) {
    // TODO: check consistency between c projects or c++ projects
    //       and the standard version.
  }
  
  // Check if `cmake` exists
  std::clog << "Check if `cmake` exists in system...\n";
  if (system("which cmake > /dev/null 2>&1")) {
    // Command does not exist...
    std::cerr << "cmake does not exist in system. Exiting...";
    return; // I should've used exit(1) but it seems ugly here
            // I wonder if this library (argumentum) provides
            // features to fire errors from subcommand.
  }

  // Create a folder called <project_name>
  std::clog << "Creating folder " << this->project_name << "...\n";
  fs::path new_directory = fs::current_path();
  new_directory /= this->project_name;
  std::error_code ec;
  if (!fs::create_directory(new_directory, ec)) {
    std::cerr << "Fail to create directory: " << this->project_name << ".\n";
    std::cerr << "Reason: " << ec.message() << '\n' << std::endl;
    return;
  }

  std::clog << "Creating source, objects, and outputs directory...\n";
  // Create folder `src`, `obj`, `out` inside <project_name>.
  fs::path src_path = (new_directory / this->source_dir),
           obj_path = (new_directory / this->object_dir),
           out_path = (new_directory / this->output_dir);

  if (!fs::create_directory(src_path, ec)) {
    std::cerr << "Fail to create source directory: " << this->source_dir << ".\n"
              << "Reason: " << ec.message() << '\n' << std::endl;
    return;
  }

  if (!fs::create_directory(obj_path, ec)) {
    std::cerr << "Fail to create objects directory: " << this->object_dir << ".\n"
              << "Reason: " << ec.message() << '\n' << &std::endl;
    return;
  }

  if (!fs::create_directory(out_path, ec)) {
    std::cerr << "Fail to create output directory: " << this->output_dir << ".\n"
              << "Reason: " << ec.message() << '\n' << std::endl;
    return;
  }

  std::clog << "Writing project information...\n";
  // Write project.json file to project directory. 
  using namespace nlohmann;
  json json;
  json["project-name"] = this->project_name;
  json["language"] = this->is_c_project ? "c" : "c++";
  json["std"] = this->std_version;
  json["src-dir"] = fs::relative(src_path, new_directory);
  json["obj-dir"] = fs::relative(obj_path, new_directory);
  json["out-dir"] = fs::relative(out_path, new_directory);
  json["targets"] = json::array({
    json::object({
      {"name", this->project_name},
      {"type", "executable"},
      {"links", json::array()},
      {"include-dir", json::array()},
      {"sources", json::array({fs::relative(src_path/"main.cpp", new_directory)})}
    })
  });
  json["global-include-dir"] = nlohmann::json::array();

  std::ofstream project(new_directory/"project.json");
  project << std::setw(4) << json;
  project.close();

  std::ofstream main_file(src_path/"main.cpp");
  main_file << 
  "#include <iostream>\n\n"
  "int main(int argc, char *argv[])\n"
  "{\n"
  "\tstd::cout << \"Hello, world!\" << std::endl;\n"
  "}";

  // TODO: Generate CMakeLists.txt from `project.json` 


  std::cout << "All done! Your project is in " << new_directory << '\n';
}


void InitProjCmdOptions::add_arguments(argumentum::argument_parser &parser) {

  auto params = parser.params();
  params.add_parameter(project_name, "name")
    .nargs(1)
    .metavar("<Project Name>")
    .help("This project name")
    .required();

  params.add_parameter(is_c_project, "-c")
    .nargs(0)
    .help("This is a C project")
    .required(false)
    .default_value(false);

  params.add_parameter(std_version, "--std")
    .nargs(1)
    .metavar("<std>")
    .help("What C/C++ std version to use, defaults to c++17")
    .required(false)
    .default_value("c++17");

  params.add_parameter(source_dir, "--src-dir")
    .nargs(1)
    .metavar("<directory>")
    .help("Directory where all the source file lies, defaults to src")
    .required(false)
    .default_value("src");

  params.add_parameter(object_dir, "--obj-dir")
    .nargs(1)
    .metavar("<directory>")
    .help("Directory where all the transient(object files) lies, defaults to obj")
    .required(false)
    .default_value("obj");

  params.add_parameter(output_dir, "--out-dir")
    .nargs(1)
    .metavar("<directory>")
    .help("Directory where all the output(target) lies, defaults to out")
    .required(false)
    .default_value("out");

}
