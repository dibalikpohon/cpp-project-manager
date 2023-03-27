#include <argumentum/argparse.h>
#include <string_view>


class InitProjCmdOptions: public argumentum::CommandOptions 
{
  public:
    std::string project_name;
    bool is_c_project;
    std::string std_version;
    std::string source_dir;
    std::string object_dir;
    std::string output_dir;

    void execute(const argumentum::ParseResult& res) override; 

    InitProjCmdOptions(std::string_view name): argumentum::CommandOptions(name) { }

  protected:
    void add_arguments(argumentum::argument_parser& parser) override;

};
