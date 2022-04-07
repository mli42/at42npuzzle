#include "../includes/main.hpp"
#include "../includes/Errno.hpp"

int main(int argc, char **argv) {
	PuzzleMap map;

	parsing(argc, argv, &map);

	if (Errno::hasErr())
		Errno::show();

	return Errno::hasErr();
}
