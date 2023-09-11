#include <iostream>
#include "MyFramework.h"
#include <vector>
#include <sstream>


void tokenize(std::vector<std::string>& tokens, std::string& command, char separator)
{
	std::stringstream ss(command);
	std::string token;
	while (std::getline(ss, token, separator))
	{
		tokens.push_back(token);
	}
}

void setResolution(std::string& command, int& width, int& height)
{
	std::vector<std::string> tokens;
	tokenize(tokens, command, ' ');
	// "game -window 800x600"

	std::cout << tokens.size() << std::endl;
	std::cout << tokens[0] << std::endl;

	if (tokens.size() == 3 && tokens[0] == "game" && tokens[1] == "-window")
	{
		std::vector<std::string> resolution;
		tokenize(resolution, tokens[2], 'x');


		if (resolution.size() != 2)
		{
			std::cout << "Invalid command!" << std::endl;
			std::cout << "To change the resolution you should use this: game -window [number]x[number]" << std::endl;
			return;
		}
		width = std::stoi(resolution[0]);
		height = std::stoi(resolution[1]);

	}
	else
	{
		std::cout << "Invalid command!" << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::cout << "you can set screen resolution by using this command: game -window [width]x[height]" << std::endl;
	int screenWidth = 320, screenHeight = 512;

	std::string input;
	std::getline(std::cin, input);

	if(!input.empty())
		setResolution(input, screenWidth, screenHeight);
	

    MyFramework framework(screenWidth, screenHeight);
    run(&framework);
}