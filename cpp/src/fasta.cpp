#include "fasta.hpp"

#include <fstream>
#include <iostream>

using namespace std;

void fasta_read(const string& filename, vector<string>& heads, vector<string>& seqs) {
    ifstream file;
    string line;

    file.open(filename);

    if (!file.is_open()) {
        cerr << "error: " + filename + ": Cannot read such file" << endl;
        exit(1);
    }

    while (getline(file, line))
        if (line.empty())
            continue;
        else if (line[0] == '>') {
            size_t i = 0;
            while (line[++i] == ' ');
            heads.push_back(line.substr(i));
            seqs.push_back("");
        } else
            seqs.back().append(line);

    file.close();
}

void fasta_write(const string& filename, const vector<string>& heads, const vector<string>& seqs) {
    ofstream file;

    file.open(filename);

    if (!file.is_open()) {
        cerr << "error: " + filename + ": Cannot write such file" << endl;
        exit(1);
    }

    auto ith = heads.begin(), its = seqs.begin();

    while (ith != heads.end() and its != seqs.end())
        file << "> " << *(ith++) << '\n' << *(its++) << endl;

    file.close();
}