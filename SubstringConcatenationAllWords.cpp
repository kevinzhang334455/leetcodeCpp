#include "PrintUtil.hpp"
#include <vector>
#include<string>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

// Find a substring for s where s contains all the strings specified in 'words'.
class Solution
{
public:
     vector<int>findSubstring(string s, vector<string> words)
     {
         vector<int> result;
         if (s.empty() || words.empty())
         {
             return result;
         }

         int wordLen = words[0].size();
         int numWords = words.size();

         unordered_map<string, int> wordDict;
         for (auto word : words)
         {
             if (wordDict.find(word) == wordDict.end())
             {
                 wordDict.emplace(word, 0);
             }

             wordDict[word]++;
         }

        // Optimization: Avoid uncessary loops
         for (int i = 0; i < s.size() - wordLen * numWords + 1; i++)
         {
             // Dict copy is very slow. Compare the seen number instead.
             // auto currDict = wordDict;

             unordered_map<string, int> currDict;

             for (int j = 0; j < numWords; j++)
             {
                int wordStart = i + wordLen * j;
                //  int wordEnd  = wordStart + wordLen - 1;
                //  if (wordEnd >= s.size())
                //  {
                //      break;
                //  }
                 auto substr = s.substr(wordStart, wordLen);
                 if (wordDict.find(substr) == wordDict.end())
                 {
                     break;
                 }

                 if (currDict.find(substr) == currDict.end())
                 {
                     currDict.emplace(substr, 0);
                 }

                 if (1 + currDict[substr] > wordDict[substr])
                 {
                     break;
                 }

                 currDict[substr]++;

                 if (j == numWords - 1)
                 {
                     result.push_back(i);
                 }
             }
         }

         return result;
     }
};

int main ()
{
    Solution solution;
    PrintUtil printUtil;

    // Test 1
    vector<string> words1 = {"foo", "bar"};
    string s1 = "foobarfooobarfoo";
    printUtil.printVectorOf<int>(solution.findSubstring(s1, words1));

    // Test 2
    vector<string> words2 = { "foo", "bar" };
    string s2 = "barfoothefoobarman";
    printUtil.printVectorOf<int>(solution.findSubstring(s2, words2));

    // Test 3
    vector<string> words3 = { "word", "good", "best", "word" };
    string s3 = "wordgoodgoodgoodbestword";
    printUtil.printVectorOf<int>(solution.findSubstring(s3, words3)); 
}