#include <string>
#include <fstream>

class Logger 
{
public:
    static void info(const std::string &message);
    static void error(const std::string &message);

private:
    static std::ofstream out_;
};