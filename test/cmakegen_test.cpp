#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "../src/cmake_gen/cmake_gen.hpp"


using namespace cmakegen;

TEST(cmakegen, CMakeMinimumRequired) {
  
  std::string minimum_required = cmake_minimum_required("3.10");
  EXPECT_STRCASEEQ("cmake_minimum_required(VERSION 3.10)", minimum_required.c_str());
}

TEST(cmakegen, ProjectC) {
  
  std::string str = project("Testing", ProjectLanguage::C);
  EXPECT_STRCASEEQ("project(Testing C)", str.c_str());
}

TEST(cmakegen, ProjectCXX) {

  std::string str = project("Testing", ProjectLanguage::CXX);
  EXPECT_STRCASEEQ("project(Testing CXX)", str.c_str());
}

TEST(cmakegen, SetCMakeVariables) {

  std::string str = set(CmakeVariables::CMAKE_BUILD_TYPE, "Release");
  EXPECT_STRCASEEQ("set(CMAKE_BUILD_TYPE Release)", str.c_str());

  str = set(CmakeVariables::CMAKE_C_STANDARD, "17");
  EXPECT_STRCASEEQ("set(CMAKE_C_STANDARD 17)", str.c_str());

  str = set(CmakeVariables::CMAKE_CXX_STANDARD, "20");
  EXPECT_STRCASEEQ("set(CMAKE_CXX_STANDARD 20)", str.c_str());
}

TEST(cmakegen, AddExecutable) {

  std::string p1("src/main.cpp"), p2("src/hello.cc");
  std::string str1 = add_executable("Target", { p1 });
  EXPECT_STRCASEEQ("add_executable(Target src/main.cpp)", str1.c_str());

  // I don't really understand why I can't do this:
  // std::string str2 = add_executable("Target", p1, p2)
  // I was thinking that `add_executable` function in cmakegen namespace 
  // accepts variadic function with type std::string& but I can't pass
  // both p1 and p2. It shows an error saying that they can't pass
  // non-trivial objects on variadic function. So I did this below
  // and it worked, but ugly...
  std::string str2 = add_executable("Target", { p1, p2 });
  EXPECT_STRCASEEQ("add_executable(Target src/main.cpp src/hello.cc)", str2.c_str());
}

TEST(cmakegen, TargetIncludeDirectories) {

  std::string p1("include/imgui"), p2("include/c++11");
  std::string str1 = target_include_directories("Target", { p1 });
  EXPECT_STRCASEEQ("target_include_directories(Target include/imgui)", str1.c_str());

  std::string str2 = target_include_directories("Target", { p1, p2 });
  EXPECT_STRCASEEQ("target_include_directories(Target include/imgui include/c++11)", str2.c_str());
}

TEST(cmakegen, TargetLinkLibraries) {

  std::string p1("fmt"), p2("armadillo");
  std::string str1 = target_link_libraries("Target", { p1 });
  EXPECT_STRCASEEQ("target_link_libraries(Target fmt)", str1.c_str());

  std::string str2 = target_link_libraries("Target", { p1, p2 });
  EXPECT_STRCASEEQ("target_link_libraries(Target fmt armadillo)", str2.c_str());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
