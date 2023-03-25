#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <argumentum/argparse.h>
#include "init_proj_cmdopt/init_proj_cmdopt.hpp"

int main(int argc, char* argv[]) {

  using argumentum::argument_parser;

  auto parser = argument_parser{};
  parser.config().program("pprojman").description("A Project manager for C and C++");

  auto params = parser.params();
  params.add_command<InitProjCmdOptions>("init").help("Initialize C or C++ project");

  auto res = parser.parse_args(argc, argv, 1);
  if (!res) return 1;

  if (res.commands.empty()) return 1;

  auto pcmd = res.commands.front();
  if (!pcmd) return 1;

  pcmd->execute(res);

  return 0;
}
