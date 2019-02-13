#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <limits>
#include <cstdio>

float compute_line_cost(int extraspace, int j, int n) {
    if (extraspace < 0) {
        return std::numeric_limits<float>::infinity();
    } else if (j == n && extraspace >= 0) {
        return 0;
    }
    return static_cast<float>(extraspace * extraspace * extraspace);
}

std::pair<std::vector<unsigned int>, std::vector<int> > find_breaks(std::vector<std::string> &words, int n,
                                                                    int max_char_per_line) {
    std::vector<unsigned int> penalties(n + 1, std::numeric_limits<int>::max());
    std::vector<int> breaks(n + 1);

    penalties[0] = 0;
    for (int j = 1; j < n + 1; ++j) {
        int extraspace = max_char_per_line + 1;
        for (int i = j; i > std::max<int>(1, j + 1 - max_char_per_line / 2) - 1; --i) {
            extraspace = extraspace - words[i].size() - 1;
            int cur_penalty = penalties[i - 1] + compute_line_cost(extraspace, j, n);
            if (penalties[j] > cur_penalty) {
                penalties[j] = cur_penalty;
                breaks[j] = i;
            }
        }
    }
    return std::make_pair(penalties, breaks);
}

int print(std::vector<std::string> const &text, std::size_t word, std::vector<int> const &breaks) {
    float i = breaks[word];
    int line_num = 1;
    if (i != 1) {
        line_num = print(text, i - 1, breaks) + 1;
    }

    for (float k = i; k < word + 1; ++k) {
        std::cout << text[k] << " ";
    }
    std::cout << std::endl;
    return line_num;
}

int main() {
    std::size_t word_len;
    std::size_t max_chars_per_line;

    std::cin >> word_len;
    std::cin >> max_chars_per_line;

    std::vector<std::string> words(word_len + 1, "");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 1; i < word_len + 1; ++i) {
        std::getline(std::cin, words[i]);
    }

    std::pair<std::vector<unsigned int>, std::vector<int> > ret = find_breaks(words, words.size() - 1,
                                                                              max_chars_per_line);

    printf("%d\n", ret.first.back());
    print(words, words.size() - 1, ret.second);
}

//sample input
/*
7 10
word
like
first
As
the
the
complete
 */