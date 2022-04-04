#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"
#include "../includes/parsing.hpp"

bool parse_path(const std::string &str) {
	return false;
}

static bool parse_args(int argc, char **argv, PuzzleMap *const map) {
	std::vector<parsing_flag_exec> exec = std::vector<parsing_flag_exec>(3);
	std::vector<parsing_flag_exec>::iterator it, ite;

	exec.push_back({ ARG_PATH, "--file=", parse_path });
	exec.push_back({ ARG_SIZE, "--size=", parse_path });
	exec.push_back({ ARG_H, "--heuristic=", parse_path });
	ite = exec.end();

	for (int i = 0; i < argc; i++) {
		const std::string str = argv[i];

		// for (it = exec.begin())

		if (starts_with(str, "--file=")) {
		}
		else if (starts_with(str, "--size=")) {
		}
		else if (starts_with(str, "--heuristic=")) {
		}
		else {
			ft_exit("Unknown flag");
		}

	}
	return true;
}
