#include <list>
#include <string>

int
main(int argc, char * argv[])
{
	std::list<std::string> list;
	list.emplace_back("Hello world");
}