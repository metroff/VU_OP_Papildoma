#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>

class WordData {
    public:
        int count;
        std::vector<int> containingLines;

    WordData(int lineNum) : count{1}, containingLines{lineNum} {}
};

const std::regex word_expression("[.%,?!/;:\"'()\\]\\[*0-9]");
const std::regex url_expression("(((https?)://)?www\\.)?[a-zA-Z0-9@:%._\\-+~#?&/=]{2,256}\\.[a-z]{2,6}\\b([a-zA-Z0-9@:%._\\-+~#?&/=]*)");

std::string cleanWord(std::string word) {
    return std::regex_replace(word, word_expression, "");
}

bool isURL(std::string word) {
    return std::regex_match(word, url_expression);
}

// Funkcija taip/ne klausimui
bool yesNoQuestion(std::string question) {
    std::string answer;
    while (answer != "y" && answer != "n") {
        std::cout << question << " (y/n): ";
        std::cin >> answer;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return answer == "y";
}

void insertWord(std::string word, std::map<std::string, WordData> &words, int lineNum) {
    if (!word.empty() && word != "-" && word != "–") {
        auto searchResult = words.find(word);

        if (searchResult == words.end()) {
            words.insert(make_pair(word, WordData(lineNum)));
        } else {
            if (lineNum != searchResult->second.containingLines.back()) {
                searchResult->second.containingLines.push_back(lineNum);
            }
            searchResult->second.count+=1;
        }
    }
}

void printWordTable(std::map<std::string, WordData> &words) {
    std::stringstream buffer;

    buffer << std::setw(22) << std::left << "Word" << "Count\n";
    buffer << "--------------------------------\n";
    for (auto word : words) {
        if (word.second.count > 1) {
            buffer << std::setw(22) << std::left << word.first << "\t";
            buffer << word.second.count << "\n";
        }
    }

    std::ofstream table("word_table.txt");
    table << buffer.rdbuf();
    table.close();
}

void printCrossReferenceTable(std::map<std::string, WordData> &words, int lineNum) {
    std::stringstream buffer;

    int spaceLen = std::to_string(lineNum).length();

    buffer << std::setw(21) << std::left << "Word" << "\t" << std::right;
    for (int i = 1; i < lineNum; i++) {
        buffer << std::setw(spaceLen) << i << " ";
    }
    buffer << "\n";

    for (auto word : words) {
        if (word.second.count > 1) {
            buffer << std::setw(21) << std::left << word.first << "\t";
            int currentNumber = 0;
            for (auto number : word.second.containingLines) {
                int numberOfSpaces = number - currentNumber;
                buffer << std::string(numberOfSpaces*(spaceLen+1)-2, ' ') << "* ";
                currentNumber = number;
            }
            buffer << "\n";
        }
    }

    std::ofstream table("cross_reference.txt");
    table << buffer.rdbuf();
    table.close();
}

void printUrls(std::vector<std::string> &urls) {
    std::stringstream buffer;

    buffer << "Urls:\n";
    for (auto url : urls) {
        buffer << url << "\n";
    }

    std::ofstream table("urls.txt");
    table << buffer.rdbuf();
    table.close();
}

int main() {
    std::map<std::string, WordData> words;
    std::vector<std::string> urls;

    std::string fileName;
    std::cout << "Irasykite failo pavadinima: ";
    std::cin >> fileName;

    std::stringstream buffer;

    std::ifstream inputFile(fileName);
    if (inputFile) {
        buffer << inputFile.rdbuf();
        inputFile.close();
    } else {
        std::cout << "Nurodytas failas (" << fileName << ") nerastas." << std::endl;
        return 0;
    }

    bool lowerCase = yesNoQuestion("Keisti raides i mazasias? ");

    std::string line;
    int lineNumber = 1;

    while (getline(buffer, line)) {
        std::string word;
        std::stringstream ss(line);

        while (ss >> word) {
            if (isURL(word)) {
                urls.push_back(word);
            } else {
                if (lowerCase)
                    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){return std::tolower(c);});
                insertWord(cleanWord(word), words, lineNumber);
            }
        }
        lineNumber++;
    }

    printWordTable(words);
    printCrossReferenceTable(words, lineNumber);
    printUrls(urls);
}