#include "../includes/Errno.hpp"

Errno::nperrno Errno::err = Errno::NP_NO_ERR;
std::string Errno::detail = "";
bool Errno::print_usage = false;

const Errno::meaning_map Errno::meaning = {
	{Errno::NP_NO_ERR, "No error"},
	{Errno::NP_HELP, "Help triggered"},
	{Errno::NP_LOGIC, "Logic error"},
	{Errno::NP_CANT_OPEN, "Parsing: Cannot read file"},
	{Errno::NP_DUPLICATE_ARG, "Parsing: Duplicate flag"},
	{Errno::NP_UNKNOWN_ARG, "Parsing: Flag unknown"},
	{Errno::NP_INCOMPATIBLE_ARG, "Parsing: Flags are incompatibles"},
};
