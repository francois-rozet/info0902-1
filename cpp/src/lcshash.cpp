#include "fasta.hpp"
#include "hash-table.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

char nucleotide2int(char c) {
    if (c == 'A')
        return 0;
    else if (c == 'C')
        return 1;
    else if (c == 'G')
        return 2;
    else if (c == 'T')
        return 3;

    return 42;
}

char int2nucleotide(char c) {
    if (c == 0)
        return 'A';
    else if (c == 1)
        return 'C';
    else if (c == 2)
        return 'G';
    else if (c == 3)
        return 'T';

    return ' ';
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "fatal-error: missing argument(s)" << endl;
        exit(1);
    }

    size_t n = atoi(argv[3]);

    vector<string> heads, seqs;
    vector<vector<char>> G;

    for (size_t i = 0; i < 2; i++) {
        fasta_read(argv[i + 1], heads, seqs);
        n = n < seqs.back().size() ? n : seqs.back().size();
        G.push_back(vector<char>(seqs.back().begin(), seqs.back().begin() + n));
        transform(G[i].begin(), G[i].end(), G[i].begin(), &nucleotide2int);
    }

    auto start = chrono::steady_clock::now();

    triple t = hash_table_search<char>(G[0], G[1], 4);

    auto end = chrono::steady_clock::now();
    auto time = chrono::duration <double, milli> (end - start).count();

    string head = "L: " + to_string(get<0>(t));
    head += " G1: " + to_string(get<1>(t) + 1);
    head += " G2: " + to_string(get<2>(t) + 1);
    head += " N: " + to_string(n);
    head += " T: " + to_string(time);

    transform(G[0].begin(), G[0].end(), G[0].begin(), &int2nucleotide);
    string subseq = string(G[0].begin() + get<1>(t), G[0].begin() + get<1>(t) + get<0>(t));

    fasta_write("subseqhash.fa", {head}, {subseq});
}