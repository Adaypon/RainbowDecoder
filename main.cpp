#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

const int numOfFiles = 12; // количество таблиц

int RainbowDecoder(const std::string& encryptedStr) {
	std::string line;
	std::ifstream fin;
	std::string fileName = "./Audero-MD5-Rainbow-Table/md5_rainbow_table_part_";
	//./Audero-MD5-Rainbow-Table/md5_rainbow_table_part_1.csv

	for (size_t i = 1; i <= numOfFiles; ++i) {
		int rows = 0;
		fin.open(fileName + std::to_string(i) + ".csv");
		if (fin.is_open()) {
			std::cout << "\tSearching in " << i << " table" << std::endl;
			/*
			
			// подсчитать количество строк
			while (getline(fin, line, '\n')) {
				++rows;
			}

			// вернуться назад в поток
			fin.clear();
			fin.seekg(0, std::ios_base::beg);

			// TODO бинарный поиск
			// ...

			*/
		
			// линейный поиск
			while (getline(fin, line, '\n')) {
				auto hash_start = line.find('"'); // ищем первую кавычку - начало хэша
				auto hash_end = line.find('"', hash_start + 1); // ищем вторую кавычку - конец хэша - отсчитвая с первой кавычки
				std::string hashStr = line.substr(hash_start + 1, hash_end - hash_start - 1);
				
				// то же самое
        		auto original_start = line.find('"', hash_end + 1);
        		auto original_end = line.find('"', original_start + 1);
        		std::string original = line.substr(original_start + 1, original_end - original_start - 1);

				if (encryptedStr == hashStr) {
					std::cout << "Found original" << original << std::endl;
					fin.close();
					return 0;
				}
			}
			// в этом файле не нашли, идем дальше
		}
		else {
			std::cerr << "Can't open file" << std::endl;
			return -1;
		}
		fin.close();
	}
	std::cout << "Original not found" << std::endl;
	return 1;
}


int main() {
	std::cout << "Please wait, since this may take a while..." << std::endl;
	RainbowDecoder("17189d9438d9749039c0de1045af1732");
	return 0;
}