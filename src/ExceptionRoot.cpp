#include "ExceptionRoot.h"

ExceptionRoot::ExceptionRoot(std::string file, int line) noexcept
	:File(file), Line(line)
{
}

const char* ExceptionRoot::what() const
{
	return "\n something\n";
}
