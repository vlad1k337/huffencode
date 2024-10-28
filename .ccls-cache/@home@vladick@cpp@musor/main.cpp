#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>

#include "files.h"
#include "huffman.h"

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		const std::string path(argv[1]);

		if(argv[2] != nullptr && std::strcmp(argv[2], "--show-code") == 0)
		{
			generateCode(path);
			printCode();
		}

		encode(path);


	} else {
		std::cout << "blyoo ukaji file dolbaeb\n";
	};
	return 0;
}
