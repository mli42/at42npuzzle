#ifndef ERRNO_HPP
# define ERRNO_HPP

# include <iostream>
# include <map>

static void printUsage(void) {
	std::cerr << "Usage n-puzzle:" << std::endl << \
		"\t[--help]" << std::endl << \
		"\t[--file/-f=] (incompatible with -s/-u/-i)" << std::endl << \
		"\t[--size/-s=] (3 < x < 9) (incompatible with -f)" << std::endl << \
		"\t[--heuristic/-h=] {manhattan, misplaced, conflicts, euclidian, custom}" << std::endl << \
		"\t[--unsolvable/-u=] (bool) (incompatible with -f)" << std::endl << \
		"\t[--visualizer/-v=] (bool)" << std::endl << \
		"\t[--greedy/-g=] (bool) (incompatible with -c)" << std::endl << \
		"\t[--cost/-c=] (bool) (incompatible with -g)" << std::endl << \
		"\t[--iteration/-i=] (0 < x < 100000) (incompatible with -f)" << std::endl;
}

class Errno {
	public:
	enum nperrno {
		NP_NO_ERR = 0,
		NP_HELP,
		NP_LOGIC,
		NP_CANT_OPEN,
		NP_DUPLICATE_ARG,
		NP_UNKNOWN_ARG,
		NP_INCOMPATIBLE_ARG,
	};

	typedef std::map<Errno::nperrno, std::string> meaning_map;

	const static meaning_map meaning;

	static nperrno err;
	static std::string detail;
	static bool print_usage;

	// Returns true if there is no error
	static bool setError(Errno::nperrno error = Errno::NP_NO_ERR, std::string detail = "", bool print_usage = false) {
		Errno::err = error;
		Errno::detail = detail;
		Errno::print_usage = print_usage;
		return error == Errno::NP_NO_ERR;
	};

	static void show() {
		if (Errno::hasErr())
			std::cerr << Errno::meaning.at(Errno::err);
		if (!Errno::detail.empty()) {
			if (Errno::hasErr())
				std::cerr << ": ";
			std::cerr << Errno::detail;
		}
		std::cerr << std::endl;
		if (Errno::print_usage) printUsage();
	};

	static bool hasErr() {
		return Errno::err != Errno::NP_NO_ERR;
	};
};

#endif // ERRNO_HPP
