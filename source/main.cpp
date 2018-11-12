#include "Core.h"

int main(int argc, char **argv)
{
	Core::Initialise(argc, argv);

	Core::run();

	return 0;
}