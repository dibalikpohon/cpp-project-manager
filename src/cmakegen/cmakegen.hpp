#include <string>
#include <initializer_list>

namespace cmakegen {
enum class ProjectLanguage {
  C, CXX
};

enum class CmakeVariables {
  CMAKE_CXX_STANDARD,
  CMAKE_C_STANDARD,
  CMAKE_BUILD_TYPE,
};

std::string 
  cmake_minimum_required(const std::string& version);

std::string
  project(const std::string& name,
          ProjectLanguage language);

std::string
  set(CmakeVariables variable, 
      const std::string& value);

std::string
  set(const std::string& variable, 
      const std::string& value);

std::string 
  add_executable(const std::string& target,
                 std::initializer_list<std::string> sources);

std::string
  target_include_directories(const std::string& target,
                             std::initializer_list<std::string> directories);

std::string
  target_link_libraries(const std::string& target,
                        std::initializer_list<std::string> libraries);
}
