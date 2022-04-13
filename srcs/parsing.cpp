#include "../includes/Node.hpp"
#include "../includes/utils.hpp"
#include "../includes/parsing.hpp"
#include "../includes/Errno.hpp"
#include <regex>
#include "../includes/NodeUtils.hpp" // remove at the end

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
		for (size_t j = 0; j < size; j++)
			mapCheck[map[i][j]] += 1;

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

	if (isNum == false)
		return Errno::setError(Errno::NP_LOGIC, "Parsing: not a digit");
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
	display_map_data(node->map); // Pour debug
	return true;
}

static bool parse_heuristic(const std::string &str, Node *const node) {
	const std::string heuristics[] = {
		HeuristicType::manhattan,
		HeuristicType::misplaced,
		HeuristicType::conflicts,
		HeuristicType::euclidian,
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

bool hasIncompatibleFlags(int flag) {
	if (isFlagSet(flag, ARG_PATH) && isFlagSet(flag, ARG_SIZE))
		return true;
	return false;
}

bool parse_args(int argc, char **argv, Node **node) {
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
				return Errno::setError(Errno::NP_DUPLICATE_ARG, "'" + it->start + "'");
			else {
				flag = setFlag(flag, it->type);
				if (hasIncompatibleFlags(flag))
					return Errno::setError(Errno::NP_INCOMPATIBLE_ARG, "", true);
				break ;
			}
		}
		if (it == ite)
			return Errno::setError(Errno::NP_UNKNOWN_ARG, "'" + str + "'");
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

	print_node_content(*node);
	return true;
}
