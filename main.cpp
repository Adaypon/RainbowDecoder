#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int numOfFiles = 12; // number of rainbow tables

int RainbowDecoder(const std::string& encryptedStr) {
	bool foundFlag = false;
	std::string line;
	std::ifstream fin;
	std::string fileName = "./Audero-MD5-Rainbow-Table/md5_rainbow_table_part_";
	//./Audero-MD5-Rainbow-Table/md5_rainbow_table_part_1.csv

	std::string firstHash;
	std::string lastHash;
	int firstFileNum = 1;
	int lastFileNum = numOfFiles;

	// checking that hash can be found in these files

	fin.open(fileName + std::to_string(firstFileNum) + ".csv");
	getline(fin, line);
	firstHash = line.substr(1, 32);
	fin.close();

	fin.open(fileName + std::to_string(lastFileNum) + ".csv");
	while (getline(fin, line, '\n')) {
		lastHash = line.substr(1, 32);
	}
	fin.close();

	if (encryptedStr >= firstHash && encryptedStr <= lastHash) {
		// continue search
		std::cout << "Searching..." << std::endl;
		
		int middFileNum;
		std::string middNextFirstHash; // first hash of next to midd file
		std::string middLastHash; // last hash of midd file
		while (firstFileNum < lastFileNum) {
			middFileNum = (firstFileNum + lastFileNum) / 2;

			fin.open(fileName + std::to_string(middFileNum) + ".csv");
			while (getline(fin, line, '\n')) {
				middLastHash = line.substr(1, 32);
			}
			fin.close();

			fin.open(fileName + std::to_string(middFileNum + 1) + ".csv");
			getline(fin, line);
			middNextFirstHash = line.substr(1, 32);
			fin.close();

			// 1st group (from firstFileNum to middFileNum)
			if (encryptedStr >= firstHash && encryptedStr <= middLastHash) {
				lastFileNum = middFileNum;
				lastHash = middLastHash;
			}
			// 2nd group (from middFileNum + 1 to lastFileNum)
			else {
				firstFileNum = middFileNum + 1;
				firstHash = middNextFirstHash;
			}
		}

		fin.open(fileName + std::to_string(lastFileNum) + ".csv");
		while (getline(fin, line, '\n')) {
			if (encryptedStr == line.substr(1, 32)) { // can't get bugs if you hardcode substring positions ( ͡° ͜ʖ ͡°)
				// 35 is the pos first " of original; the original itself starts at 36 pos
				size_t original_end = line.find('"', 36);
				std::string original = line.substr(36, original_end - 35 - 1);
				foundFlag = true;
				std::cout << "Found original: " << original << std::endl;
				break;
			}
		}
		fin.close();
		if (foundFlag) {
			return 0;
		}
		else {
			std::cout << "Original not found" << std::endl;
			return 1;
		}
	}
	else {
		std::cout << "Input hash does not belong to rainbow table scope" << std::endl;
		return 2;
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Invalid num of arguments" << std::endl;
		return -1;
	}
	return RainbowDecoder(argv[1]);
}