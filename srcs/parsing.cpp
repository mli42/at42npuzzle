#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"
#include "../includes/parsing.hpp"

std::vector<int> parse_line(char *line) {
	std::vector<int> split_line;
	char *token_token;

	token_token = strtok(line, " ");
	split_line.push_back(atoi(token_token));
	while ((token_token = strtok(NULL, " ")))
		split_line.push_back(atoi(token_token));
	return split_line;
}

static bool parse_file(const std::string &filename, PuzzleMap * const map) {
	std::ifstream f;
	std::string line;
	std::vector<int> tmp;
	char *token_line;
	char *token_token;
	int type = ARG_NONE;

	f.open(filename);
	if (!f.is_open())
		ft_exit("Cannot read file " + filename);
	while (std::getline(f, line))
	{
		if (line[0] != '#')
		{
			token_line = strtok(&line[0], "#");
			if (!isFlagSet(type, ARG_SIZE))
			{
				token_token = strtok(token_line, " ");
				type = setFlag(type, ARG_SIZE);
			}
			else
				tmp = parse_line(token_line);
			(*map).map.push_back(tmp);
			tmp.clear();
		}
	}
	display_map_data((*map).map); // Pour debug
	f.close();
	return true;
}

bool parse_size(const std::string &str, PuzzleMap *const map) {
	(void)str; (void)map;
	std::cout << "Call size with " << str << std::endl;
	return true;
}

bool parse_heuristic(const std::string &str, PuzzleMap *const map) {
	(void)str; (void)map;
	std::cout << "Call heuristic with " << str << std::endl;
	return true;
}

bool hasIncompatibleFlags(int flag) {
	if (isFlagSet(flag, ARG_PATH) && isFlagSet(flag, ARG_SIZE))
		return true;
	return false;
}

bool parse_args(int argc, char **argv, PuzzleMap *const map) {
	std::vector<FlagExec> exec = std::vector<FlagExec>();
	std::vector<FlagExec>::iterator it, ite;
	int flag = 0;

	exec.push_back({ ARG_PATH, "--file=", parse_file });
	exec.push_back({ ARG_SIZE, "--size=", parse_size });
	exec.push_back({ ARG_H, "--heuristic=", parse_heuristic });
	ite = exec.end();

	// Check flags validity
	for (int i = 1; i < argc; i++) {
		const std::string str = argv[i];

		for (it = exec.begin(); it != ite; it++) {
			if (!starts_with(str, it->start))
				continue;
			else if (isFlagSet(flag, it->type))
				ft_exit(std::string("Duplicate flag ") + it->start);
			else {
				flag = setFlag(flag, it->type);
				if (hasIncompatibleFlags(flag))
					ft_exit("Incompatible flags", true);
				break ;
			}
		}
		if (it == ite)
			ft_exit("Unknown flag", true);
	}

	// Execute flags functions
	for (int i = 1; i < argc; i++) {
		const std::string str = argv[i];

		for (it = exec.begin(); it != ite; it++)
			if (starts_with(str, it->start))
				it->fct(str.substr(it->start.length()), map);
	}
	return true;
}

bool parsing(int argc, char **argv, PuzzleMap *const map) {
	if (!parse_args(argc, argv, map))
		return false;
	return true;
}
