#include "../includes/Errno.hpp"

Errno::nperrno Errno::err = Errno::NP_NO_ERR;
std::string Errno::detail = "";

const Errno::meaning_map Errno::meaning = {
	{Errno::NP_NO_ERR, "No error"},
	{Errno::NP_DUPLICATE_ARG, "Parsing: Duplicate flag"},
};
