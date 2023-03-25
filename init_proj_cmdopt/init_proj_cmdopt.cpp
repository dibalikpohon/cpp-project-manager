#include "init_proj_cmdopt.hpp"
#include <argumentum/inc/argparser.h>


void InitProjCmdOptions::execute(const argumentum::ParseResult &res) {
  std::cout << "Hello, World!" << std::endl;
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
