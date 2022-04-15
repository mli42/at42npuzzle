#include "../includes/Node.hpp"
#include "../includes/utils.hpp"
#include "../includes/parsing.hpp"
#include "../includes/Errno.hpp"
#include <regex>

static const std::map<std::string, bool> bools = {
	{"true", true},
	{"false", false},
	{"1", true},
	{"0", false},
};

bool parse_map(Node *node)
{
	const size_t &size = Node::size;
	const MapData map = node->map;
	std::map<int, int> mapCheck;
	auto ite = mapCheck.end();

	if (node->map.empty())
		return true;
	for (size_t i = 0; i < Node::double_size; i++)
		mapCheck.insert({i, 0});

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++) {
			if (map[i][j] == 0)
				node->empty_tile = Coord(i, j);
			mapCheck[map[i][j]] += 1;
		}

	for (auto it = mapCheck.begin(); it != ite; ++it)
		if (it->second != 1)
			return Errno::setError(Errno::NP_LOGIC, "File: wrong tile");

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

static bool parse_size(const std::string &str, Node *const node) {
	const int isNum = std::regex_match(str, std::regex("\\d+"));

	if (isNum == false || str.size() >= 10)
		return Errno::setError(Errno::NP_LOGIC, "Parsing: not an integer");
	const int size = atoi(str.c_str());
	if (isMapRightSize(size) == false)
		return Errno::setError(Errno::NP_LOGIC, "Parsing size: wrong value");

	node->size = size;
	node->double_size = size * size;
	return true;
}

static bool parse_file(const std::string &filename, Node *const node) {
	std::ifstream f;
	std::string line;
	std::vector<int> tmp;
	char *token_line;
	char *token_token;
	int type = ARG_NONE;

	f.open(filename);
	if (!f.is_open())
		return Errno::setError(Errno::NP_CANT_OPEN, "'" + filename + "'");
	while (std::getline(f, line))
	{
		if (line[0] == '#')
			continue ;
		token_line = strtok(&line[0], "#");
		if (!isFlagSet(type, ARG_SIZE))
		{
			token_token = strtok(token_line, " ");
			if (parse_size(token_token, node) == false)
			{
				f.close();
				return Errno::setError(Errno::NP_LOGIC, "File corrupted (size)");
			}
			type = setFlag(type, ARG_SIZE);
		}
		else
		{
			tmp = parse_line(token_line);
			if (tmp.size() != Node::size)
			{
				f.close();
				return Errno::setError(Errno::NP_LOGIC, "File corrupted (row length not identical)");
			}
			node->map.push_back(tmp);
			tmp.clear();
		}
	}
	f.close();
	if (node->map.size() != Node::size)
		return Errno::setError(Errno::NP_LOGIC, "File corrupted (col length not identical)");
	return true;
}

static bool parse_heuristic(const std::string &str, Node *const node) {
	const std::string heuristics[] = {
		HeuristicType::manhattan,
		HeuristicType::misplaced,
		HeuristicType::conflicts,
		HeuristicType::euclidian,
		HeuristicType::custom,
	};
	const size_t size = sizeof(heuristics) / sizeof(*heuristics);

	for (unsigned short int i = 0; i < size; ++i) {
		if (heuristics[i] == str) {
			node->heuristic_type = str;
			return true;
		}
	}
	return Errno::setError(Errno::NP_UNKNOWN_ARG, "'" + str + "'" + " is an unknown heuristic");
}

static bool parse_unsolvable(const std::string &str, Node *const node) {
	std::map<std::string, bool>::const_iterator it = bools.begin(), ite = bools.end();

	for (; it != ite; ++it) {
		if (it->first == str) {
			node->unsolvable = it->second;
			return true;
		}
	}
	return Errno::setError(Errno::NP_UNKNOWN_ARG, "wrong boolean value: '" + str + "'");
}

static bool parse_visualizer(const std::string &str, Node *const node) {
	std::map<std::string, bool>::const_iterator it = bools.begin(), ite = bools.end();

	for (; it != ite; ++it) {
		if (it->first == str) {
			node->visualizer = it->second;
			return true;
		}
	}
	return Errno::setError(Errno::NP_UNKNOWN_ARG, "wrong boolean value: '" + str + "'");
}

static bool parse_greedy(const std::string &str, Node *const node) {
	std::map<std::string, bool>::const_iterator it = bools.begin(), ite = bools.end();

	for (; it != ite; ++it) {
		if (it->first == str) {
			node->greedy = it->second;
			return true;
		}
	}
	return Errno::setError(Errno::NP_UNKNOWN_ARG, "wrong boolean value: '" + str + "'");
}

static bool parse_cost(const std::string &str, Node *const node) {
	std::map<std::string, bool>::const_iterator it = bools.begin(), ite = bools.end();

	for (; it != ite; ++it) {
		if (it->first == str) {
			node->cost = it->second;
			return true;
		}
	}
	return Errno::setError(Errno::NP_UNKNOWN_ARG, "wrong boolean value: '" + str + "'");
}

static bool parse_iteration(const std::string &str, Node *const node) {
	const int isNum = std::regex_match(str, std::regex("\\d+"));

	if (isNum == false || str.size() >= 10)
		return Errno::setError(Errno::NP_LOGIC, "Parsing: not an integer");
	const int iter = atoi(str.c_str());
	if (iter <= 0 || iter >= 100000)
		return Errno::setError(Errno::NP_LOGIC, "Parsing iter: wrong value");

	node->iteration = iter;
	return true;
}

static bool parse_help(const std::string &str, Node *const node) {
	(void)str; (void)node;
	return Errno::setError(Errno::NP_HELP, "", true);
}

bool hasIncompatibleFlags(int flag) {
	if (isFlagSet(flag, ARG_PATH) && isFlagSet(flag, ARG_SIZE))
		return true;
	else if (isFlagSet(flag, ARG_PATH) && isFlagSet(flag, ARG_UNSOLVABLE))
		return true;
	else if (isFlagSet(flag, ARG_PATH) && isFlagSet(flag, ARG_ITERATION))
		return true;
	else if (isFlagSet(flag, ARG_GREEDY) && isFlagSet(flag, ARG_COST))
		return true;
	return false;
}

bool parse_args(int argc, char **argv, Node **node) {
	std::vector<FlagExec> exec = std::vector<FlagExec>();
	std::vector<FlagExec>::iterator it, ite;
	int flag = 0;
	exec.push_back({ ARG_HELP, "--help", parse_help });

	exec.push_back({ ARG_PATH, "--file=", parse_file });
	exec.push_back({ ARG_SIZE, "--size=", parse_size });
	exec.push_back({ ARG_H, "--heuristic=", parse_heuristic });
	exec.push_back({ ARG_UNSOLVABLE, "--unsolvable=", parse_unsolvable });
	exec.push_back({ ARG_VISUALIZER, "--visualizer=", parse_visualizer });
	exec.push_back({ ARG_GREEDY, "--greedy=", parse_greedy });
	exec.push_back({ ARG_COST, "--cost=", parse_cost });
	exec.push_back({ ARG_ITERATION, "--iteration=", parse_iteration });

	exec.push_back({ ARG_PATH, "-f=", parse_file });
	exec.push_back({ ARG_SIZE, "-s=", parse_size });
	exec.push_back({ ARG_H, "-h=", parse_heuristic });
	exec.push_back({ ARG_UNSOLVABLE, "-u=", parse_unsolvable });
	exec.push_back({ ARG_VISUALIZER, "-v=", parse_visualizer });
	exec.push_back({ ARG_GREEDY, "-g=", parse_greedy });
	exec.push_back({ ARG_COST, "-c=", parse_cost });
	exec.push_back({ ARG_ITERATION, "-i=", parse_iteration });

	ite = exec.end();

	// Check flags validity
	for (int i = 1; i < argc; i++) {
		const std::string str = argv[i];

		for (it = exec.begin(); it != ite; it++) {
			if (!starts_with(str, it->start))
				continue;
			else if (isFlagSet(flag, it->type))
				return Errno::setError(Errno::NP_DUPLICATE_ARG, "'" + it->start + "'");
			else {
				flag = setFlag(flag, it->type);
				if (hasIncompatibleFlags(flag))
					return Errno::setError(Errno::NP_INCOMPATIBLE_ARG, "", true);
				break ;
			}
		}
		if (it == ite)
			return Errno::setError(Errno::NP_UNKNOWN_ARG, "'" + str + "'", true);
	}

	// Execute flags functions
	for (int i = 1; i < argc; i++) {
		const std::string str = argv[i];

		for (it = exec.begin(); it != ite; it++)
			if (starts_with(str, it->start))
				if (!it->fct(str.substr(it->start.length()), *node))
					return false;
	}
	return true;
}

bool	parsing(int argc, char **argv, Node **node) {
	*node = new Node(MapData(), Coord(), NULL);

	if (!parse_args(argc, argv, node) || !parse_map(*node)) {
		delete *node;
		*node = NULL;
		return false;
	}
	if ((*node)->map.empty() == true) {
		delete *node;
		*node = NULL;
	}
	return true;
}
