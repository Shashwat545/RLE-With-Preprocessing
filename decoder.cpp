// SHASHWAT SINGH
// 20ME02039

// Command to compile file - "/usr/bin/g++ -fdiagnostics-color=always -std=c++17 -g decoder.cpp -o decoder -ldivsufsort"

#include <bits/stdc++.h>
#include <divsufsort.h>

using namespace std;

string inverseBurrowsWheelerTransform(const string& bwt) {
    int n = bwt.length();
    vector<pair<char, int>> indexed_bwt(n);

    for (int i = 0; i < n; i++) {
        indexed_bwt[i] = {bwt[i], i};
    }

    sort(indexed_bwt.begin(), indexed_bwt.end());

    string original_string;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        idx = indexed_bwt[idx].second;
        original_string += indexed_bwt[idx].first;
    }

    return original_string;
}

string reverseDynamicByteRemapping(const string& encoded, const map<char, string>& byteMap) {
    string original = "";
    string currentByte = "";
    
    for (char bit : encoded) {
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

string reverseVerticalByteReading(const vector<string>& bitStrings) {
    string original = "";
    int size = bitStrings[0].size();

    for (int i = 0; i < size; ++i) {
        for (const string& bits : bitStrings) {
            original += bits[i];
        }
    }
    
    return original;
}

string reverseRunLengthEncoding(const vector<int>& rle) {
    string original = "";
    
    for (size_t i = 0; i < rle.size(); ++i) {
        char bit = (i % 2 == 0) ? '0' : '1';
        for (int j = 0; j < rle[i]; ++j) {
            original += bit;
        }
    }
    
    return original;
}

int main() {
    ifstream encodedFile("encoded.txt");
    ifstream remappingFile("remapping.txt");

    if (!encodedFile.is_open() || !remappingFile.is_open()) {
        cerr << "Unable to open input files!" << endl;
        return 1;
    }

    vector<int> rle;
    int run;
    while (encodedFile >> run) {
        rle.push_back(run);
    }

    map<char, string> byteMap;
    char c;
    string bits;
    while (remappingFile >> c >> bits) {
        byteMap[c] = bits;
    }

    encodedFile.close();
    remappingFile.close();

    string verticalString = reverseRunLengthEncoding(rle);

    vector<string> bitStrings;
    for (int i = 0; i < 8; ++i) {
        bitStrings.push_back(verticalString.substr(i * verticalString.size() / 8, verticalString.size() / 8));
    }

    string remapped = reverseVerticalByteReading(bitStrings);
    string original = reverseDynamicByteRemapping(remapped, byteMap);
    string inverseBWST = inverseBurrowsWheelerTransform(original);

    cout << "Decoded original string: " << inverseBWST << endl;

    return 0;
}
