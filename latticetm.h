#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <fst/fstlib.h>

#include "singlesample.h"

using namespace std;
using namespace fst;

namespace latticelm {

class LatticeTM {

private:

	vector<string> inputFiles_; // the files to be used as input
	vector< pair<StdVectorFst,vector<string>> > corpus_; // the FSTs, if cached

public:

	LatticeTM() {}

	void test() {
		cout << "test function.\n";
		string defaultInputFileList = "file-list.txt";
		string defaultSymbolFile = "symbols.txt";
		loadFileList(defaultInputFileList);
		loadCorpus();
		for(int i = 0; i < inputFiles_.size(); i++){
			corpus_[i].first.Write("test" + to_string(i+1) + ".fst");
			cout << corpus_[i].second[0] << " " << corpus_[i].second[1] << endl;
		}
	}

	void loadFileList(string inputFileList) {
		ifstream files(inputFileList);
		if (!files) {
			cerr << "Couldn't find the file list: " << inputFileList << endl;
			exit(1);
		}
		string prefix;
		string fn;
		while (getline(files,prefix)) {
			inputFiles_.push_back(prefix);
			// Checking for the FST file.
			fn = prefix + ".fst";
			ifstream * checkFile;
			checkFile = new ifstream(fn.c_str());
			if (!checkFile) {
				cerr << "Couldn't find input file: " << fn << endl;
				exit(1);
			}
			checkFile->close();
			delete checkFile;
			// Checking the English translations.
			fn = prefix + ".en";
			checkFile = new ifstream(fn.c_str());
			if (!checkFile) {
				cerr << "Couldn't find input file: " << fn << endl;
				exit(1);
			}
			checkFile->close();
		}
		files.close();
	}

	void loadCorpus() {
		StdVectorFst * fst;
		string line;
		ifstream *enFile;
		istringstream *buf;
		vector<string> * en;

		for (int i = 0; i < inputFiles_.size(); i++) {

			fst = StdVectorFst::Read(inputFiles_[i] + ".fst");
			fst->SetFinal(2, 1.0);
			fst->Write("blah.fst");

			enFile = new ifstream(inputFiles_[i] + ".en");
			getline(*enFile,line);
			buf = new istringstream(line);
			en = new vector<string>;
			copy(istream_iterator<string>(*buf),
					istream_iterator<string>(),
					back_inserter(*en));

			pair<StdVectorFst,vector<string>> *corpusPair;
			corpusPair = new pair<StdVectorFst,vector<string>>(*fst, *en);
			corpus_.push_back(*corpusPair);
		}
	}

	/** Seems to either return the value corresponding to the input key, if
	 * it's in the map; otherwise it adds the key to the map with some new id
	 * number */
	/*
    CharId findId(const string & str, std::unordered_map<string,CharId> & idHash, vector<string> & idList) {
        std::unordered_map<string,CharId>::iterator it = idHash.find(str);
        if(it == idHash.end()) {
            idHash.insert(pair<string,CharId>(str,idHash.size()));
            idList.push_back("x"+str);
            return idHash.size()-1;
        }
        return it->second;
    }
	*/

};

}
