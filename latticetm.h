#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class LatticeTM {

private:

	vector< string > inputFiles_; // the files to be used as input

public:

	LatticeTM() {}

	void test() {
		cout << "test function.\n";
		string defaultInputFileList = "file-list.txt";
		loadCorpus(defaultInputFileList);
	}

	void loadCorpus(string inputFileList) {
		ifstream files(inputFileList);
		if (!files) {
			cerr << "Couldn't find the file list: " << inputFileList << endl;
			exit(1);
		}
		string buff;
		while (getline(files,buff)) {
			inputFiles_.push_back(buff);
			ifstream checkFile(buff.c_str());
			if (!checkFile) {
				cerr << "Couldn't find input file: " << buff << endl;
				exit(1);
			}
			checkFile.close();
		}

		files.close();
	}
};
