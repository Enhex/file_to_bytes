#include <fstream>
#include <iterator>
#include <fmt/format.h>

int main(int argc, char* argv[])
{
	if (argc != 2) {
		fmt::print("usage: f2b <file>\n");
		return EXIT_FAILURE;
	}

	fmt::print("{}\n", argv[1]);
	std::ifstream file(argv[1], std::ios::binary);

	std::string output =
		"#pragma once\n"
		"unsigned char const file_bytes[] = {";
	auto iter = std::istreambuf_iterator<char>(file);
	auto const end = std::istreambuf_iterator<char>();
	if(iter != end)  {
		output += fmt::format("0x{:x}", (unsigned char)*iter);
		++iter;
	}
	for(; iter != end; ++iter) {
		output += fmt::format(",0x{:x}", (unsigned char)*iter);
	}
	output += "};";

	fmt::print("{}\n", output);

	auto const ofile_name = std::string(argv[1]) + ".h";
	std::ofstream ofile(ofile_name, std::ios::binary);
	ofile << output;
}
