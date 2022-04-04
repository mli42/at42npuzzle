#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"
#include "../includes/parsing.hpp"

static bool parse_file(const std::string &filename) {
  std::ifstream f;
  std::string line;
  char *token_line;
  char *token_token;
  PuzzleMap map;
  int type = ARG_NONE;
  int i = 0;
  std::vector<int> tmp;

  f.open(filename);
  if (!f.is_open())
    ft_exit("Cannot read file " + filename);
  while (std::getline(f, line)) {
    // std::cout << line << std::endl;
    if (line[0] != '#') {
      token_line = strtok(&line[0], "#");
      if (!(type & ARG_SIZE)) {
        token_token = strtok(token_line, " ");
        type |= ARG_SIZE;
      }
      else {
        token_token = strtok(token_line, " ");
        tmp.push_back(atoi(token_token));
        while (token_token) {
          token_token = strtok(NULL, " ");
          tmp.push_back(atoi(token_token));
        }
      }
      map.map.push_back(tmp);
      tmp.clear();
      i++;
    }
  }
  for (unsigned long i = 0; i < map.map.size(); i++) {
    for (unsigned long j = 0; j < map.map[i].size(); j++) {
      std::cout << map.map[i][j] << std::endl;
    }
  }

  f.close();
	return true;
}

/*
	--file=path
	--size=N
	--h={,,}

	-> redirige vers les fonctions associees ?
*/
static bool parse_args(int argc, char **argv, PuzzleMap *const map) {
	(void)argc; (void)argv; (void)map;
	return true;
}

bool parsing(int argc, char **argv, PuzzleMap *const map) {
	parse_args(argc, argv, map);

	parse_file("map/basic.txt");

	return true;
}
