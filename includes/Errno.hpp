#ifndef ERRNO_HPP
# define ERRNO_HPP

# include <iostream>
# include <map>

class Errno {
	public:
	enum nperrno {
		NP_NO_ERR = 0,
		NP_DUPLICATE_ARG,
		NP_UNKNOWN_ARG,
	};

	typedef std::map<Errno::nperrno, std::string> meaning_map;

	const static meaning_map meaning;

	static nperrno err;
	static std::string detail;

	// Returns true if there is no error
	static bool setError(Errno::nperrno error = Errno::NP_NO_ERR, std::string detail = "") {
		Errno::err = error;
		Errno::detail = detail;
		return error == Errno::NP_NO_ERR;
	};

	static void show() {
		std::cerr << Errno::meaning.at(Errno::err);
		if (!Errno::detail.empty())
			std::cerr << ": " << Errno::detail;
		std::cerr << std::endl;
	};

	static bool hasErr() {
		return Errno::err != Errno::NP_NO_ERR;
	};
};

#endif // ERRNO_HPP
