#include "cmakegen.hpp"
#include <fmt/core.h>
#include <fmt/format.h>
#include <stdexcept>
#include <string>

std::string cmakegen::cmake_minimum_required(const std::string &version) {
  
  return fmt::format("cmake_minimum_required(VERSION {})", version);
}

std::string cmakegen::project(const std::string &name, ProjectLanguage language) {

  using cmakegen::ProjectLanguage;

  switch (language) {
    case ProjectLanguage::C:
    return fmt::format("project({} {})", name, "C");
    case ProjectLanguage::CXX:
    return fmt::format("project({} {})", name, "CXX");
  }

  throw std::invalid_argument("Unsupported Language");
}

std::string cmakegen::set(cmakegen::CmakeVariables variable,
                          const std::string& value) {

  using cmakegen::CmakeVariables;

  switch(variable) {
    case CmakeVariables::CMAKE_C_STANDARD:
      return set("CMAKE_C_STANDARD", value);

    case CmakeVariables::CMAKE_CXX_STANDARD:
      return set("CMAKE_CXX_STANDARD", value);
    
    case CmakeVariables::CMAKE_BUILD_TYPE:
      return set("CMAKE_BUILD_TYPE", value);
  }

  throw std::invalid_argument("CMakeVariables does not exists or it has not yet implemented.");
}

std::string cmakegen::set(const std::string& variable,
                          const std::string& value) {

  return fmt::format("set({} {})", variable, value);
}

std::string cmakegen::add_executable(const std::string &target, std::initializer_list<std::string> sources) {

  return fmt::format("add_executable({} {})", target, fmt::join(sources, " "));  
}

std::string cmakegen::target_include_directories(const std::string &target, std::initializer_list<std::string> directories) {
  
  return fmt::format("target_include_directories({} {})", target, fmt::join(directories, " "));
}

std::string cmakegen::target_link_libraries(const std::string &target, std::initializer_list<std::string> libraries) {

  return fmt::format("target_link_libraries({} {})", target, fmt::join(libraries, " "));
} 
