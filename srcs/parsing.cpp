#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"
#include "../includes/parsing.hpp"
#include <regex>

bool parse_map(MapData map)
{
	int size = 4; // a enlever quand on aura une variable globale
	std::map<int, int> mapCheck;
	auto ite = mapCheck.end();

	for (int i = 0; i < size * size; i++)
		mapCheck.insert({i, 0});

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mapCheck[map[i][j]] += 1;

	for (auto it = mapCheck.begin(); it != ite; ++it)
		if (it->second != 1)
			return false;

	return true;
}

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
				if (parse_size(token_token, map) == false)
				{
					f.close();
					return false;
				}
				type = setFlag(type, ARG_SIZE);
			}
			else
			{
				tmp = parse_line(token_line);
				if (tmp.size() != map->size)
				{
					f.close();
					return false;
				}
				map->map.push_back(tmp);
				tmp.clear();
			}
		}
	}
	f.close();
	if (map->map.size() != map->size)
		return false;
	display_map_data(map->map); // Pour debug
	return true;
}

static bool parse_size(const std::string &str, PuzzleMap *const map) {
	const int isNum = std::regex_match(str, std::regex("\\d+"));

	if (isNum == false) return false;
	const int size = atoi(str.c_str());
	if (isMapRightSize(size) == false) return false;

	map->size = size;
	return true;
}

static bool parse_heuristic(const std::string &str, PuzzleMap *const map) {
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
				if (!it->fct(str.substr(it->start.length()), map))
					return false;
	}
	return true;
}

bool parsing(int argc, char **argv, PuzzleMap *const map) {
	if (!parse_args(argc, argv, map))
		return false;
	map_data_generation(); // test
	std::cout << parse_map(map->map) << std::endl;
	return true;
}
