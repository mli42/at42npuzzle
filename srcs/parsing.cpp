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
      if (!(type & ARG_SIZE))
			{
        token_token = strtok(token_line, " ");
        type |= ARG_SIZE;
      }
      else
				tmp = parse_line(token_line);
      (*map).map.push_back(tmp);
      tmp.clear();
    }
	}
	display_map(map);
  f.close();
	return true;
}

static bool parse_args(int argc, char **argv, PuzzleMap *const map) {
	(void)argc; (void)argv; (void)map;
	return true;
}

bool parsing(int argc, char **argv, PuzzleMap *const map) {
	parse_args(argc, argv, map);

	parse_file("map/comment.txt", map);

	return true;
}
