#ifndef ERRNO_HPP
# define ERRNO_HPP

# include <iostream>
# include <map>

class Errno {
	public:
	enum nperrno {
		NP_NO_ERR = 0,
		NP_DUPLICATE_ARG,
	};

	typedef std::map<Errno::nperrno, std::string> meaning_map;

	const static meaning_map meaning;

	static nperrno err;
	static std::string detail;

	static void setError(Errno::nperrno error, std::string detail = "") {
		Errno::err = error;
		Errno::detail = detail;
	};

	static void show() {
		std::cerr << Errno::meaning.at(Errno::err);
		if (!Errno::detail.empty())
			std::cerr << ": " << Errno::detail;
		std::cerr << std::endl;
	};
};

#endif // ERRNO_HPP
