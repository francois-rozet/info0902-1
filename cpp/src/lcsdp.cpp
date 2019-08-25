#include "fasta.hpp"
#include "dynamic.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    }

    auto start = chrono::steady_clock::now();

    triple t = dynamic_search<char>(G[0], G[1]);

    auto end = chrono::steady_clock::now();
    auto time = chrono::duration <double, milli> (end - start).count();

    string head = "L: " + to_string(get<0>(t));
    head += " G1: " + to_string(get<1>(t) + 1);
    head += " G2: " + to_string(get<2>(t) + 1);
    head += " N: " + to_string(n);
    head += " T: " + to_string(time);

    string subseq = string(G[0].begin() + get<1>(t), G[0].begin() + get<1>(t) + get<0>(t));

    fasta_write("subseqdp.fa", {head}, {subseq});
}