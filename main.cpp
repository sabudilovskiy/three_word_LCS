#include <iostream>
#include <string>
#include <vector>
int count_max(const std::string& word1, const std::string& word2, const std::string& word3) {
    int*** A = new int** [word1.length() + 1];
    for (int i = 0;i < word1.length() + 1;i++)
    {
        A[i] = new int* [word2.length() + 1];
        for (int j = 0;j < word2.length() + 1;j++)
        {
            A[i][j] = new int[word3.length() + 1];
            for (int k = 0;k < word3.length() + 1;k++)
            {
                A[i][j][k] = 0;
            }
        }
    }
    int n = 'z' - 'a';
    int index = 0;

    std::vector<int> number_literals_word1;
    number_literals_word1.resize(n);
    for (int i = 1;i < word1.length() + 1;i++)
    {
        number_literals_word1[word1[i - 1] - 'a']++;
        std::vector<int> number_literals_word2;
        number_literals_word2.resize(n);
        for (int j = 1;j < word2.length() + 1;j++)
        {
            number_literals_word2[word2[j - 1] - 'a']++;
            std::vector<int> number_literals_word3;
            number_literals_word3.resize(n);
            for (int k = 1;k < word3.length() + 1;k++)
            {
                number_literals_word3[word3[k - 1] - 'a']++;
                index = word3[k - 1] - 'a';
                if (word1[i - 1] == word2[j - 1] && word2[j - 1] == word3[k - 1] && number_literals_word3[index] == number_literals_word1[index] && number_literals_word2[index] == number_literals_word1[index])
                {
                    int old_subs = A[i][j][k] = A[i - 1][j][k] + A[i][j - 1][k] + A[i][j][k - 1]
                                                - A[i - 1][j - 1][k] - A[i - 1][j][k - 1] - A[i][j - 1][k - 1]
                                                + A[i - 1][j - 1][k - 1];
                    int new_subs = old_subs * 2;
                    int index_found_i = word1.find(word1[i-1]);
                    bool found_i = index_found_i < i - 1;
                    int index_found_j = word2.find(word1[i-1]);
                    bool found_j = index_found_j < j - 1;
                    int index_found_k = word3.find(word1[i-1]);
                    bool found_k = index_found_k < k - 1;
                    if (!found_i || !found_j || !found_k) {
                        new_subs++;
                    }
                    A[i][j][k] = new_subs;
                }
                else
                {
                    A[i][j][k] = std::max(std::max(A[i][j][k - 1], A[i][j - 1][k]), A[i - 1][j][k]);
                }
            }
        }
        for (int j = 1; j < word2.length() + 1; j++) {
            for (int k = 1; k < word3.length() + 1; k++) std::cout << A[i][j][k] << " ";
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    return A[word1.length()][word2.length()][word3.length()];
}

int main()
{
    std::string word1;
    std::cin >> word1;
    std::string word2;
    std::cin >> word2;
    std::string word3;
    std::cin >> word3;
    int answer = count_max(word1, word2, word3);
    std::cout <<"Answer: " <<answer << '\n';
    std::cin.get();
    std::cin.get();
}