#include <string>
#include <vector>

/**
 * Reads a FASTA file.
 */
void fasta_read(const std::string& filename, std::vector<std::string>& heads, std::vector<std::string>& seqs);

/**
 * Writes a FASTA file.
 */
void fasta_write(const std::string& filename, const std::vector<std::string>& heads, const std::vector<std::string>& seqs);