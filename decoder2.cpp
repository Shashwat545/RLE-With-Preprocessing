// SHASHWAT SINGH
// 20ME02039

// Command to compile file - "/usr/bin/g++ -fdiagnostics-color=always -std=c++17 -g decoder.cpp -o decoder -ldivsufsort"

#include <bits/stdc++.h>

using namespace std;

string inverseDynamicByteRemapping(const string& remapped, const map<char, string>& byteMap) {
    string original;
    string currentByte;
    for (char bit : remapped) {
        currentByte += bit;
        for (const auto& entry : byteMap) {
            if (entry.second == currentByte) {
                original += entry.first;
                currentByte = "";
                break;
            }
        }
    }
    return original;
}

string inverseRunLengthEncoding(const vector<int>& rle) {
    string verticalString = "";
    for (int i=0; i<rle.size(); i++) {
        for(int j=0; j<rle[i]; j++) {
            verticalString += to_string((i%2));
        }
    }
    return verticalString;
}

string horizontalByteReading(const vector<string>& bitStrings) {
    string remapped;
    for (size_t i = 0; i < bitStrings[0].size(); ++i) {
        for (const string& str : bitStrings) {
            remapped += str[i];
        }
    }
    return remapped;
}

string inverseBurrowsWheelerScottTransform(const string& bwt) {
    string input = bwt;
    vector<pair<string, int>> sortedSuffixes(input.size());
    for (int i = 0; i < input.size(); ++i) {
        sortedSuffixes[i] = {input.substr(i) + input.substr(0, i), i};
    }
    sort(sortedSuffixes.begin(), sortedSuffixes.end());

    string original;
    for (const auto& suffix : sortedSuffixes) {
        original += suffix.first.back();
    }
    return original;
}

int main() {
    ifstream encodedFile("encoded.txt");
    ifstream remappingFile("remapping.txt");

    if (!encodedFile.is_open() || !remappingFile.is_open()) {
        cerr << "Unable to open encoded.txt or remapping.txt!" << endl;
        return 1;
    }

    vector<int> rle;
    int run;
    while (encodedFile >> run) {
        rle.push_back(run);
    }
    encodedFile.close();

    map<char, string> byteMap;
    char byte;
    string mapping;
    while (remappingFile >> byte >> mapping) {
        byteMap[byte] = mapping;
    }
    remappingFile.close();

    string verticalString = inverseRunLengthEncoding(rle);
    vector<string> bitStrings(8, "");
    for (size_t i = 0; i < verticalString.size(); ++i) {
        bitStrings[i % 8] += verticalString[i];
    }

    string remapped = horizontalByteReading(bitStrings);
    string original = inverseDynamicByteRemapping(remapped, byteMap);
    string decoded = inverseBurrowsWheelerScottTransform(original);

    cout << "Decoded string: " << decoded << endl;

    return 0;
}
