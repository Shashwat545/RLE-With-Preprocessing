// SHASHWAT SINGH
// 20ME02039

// Command to compile file - "/usr/bin/g++ -fdiagnostics-color=always -std=c++17 -g encoder.cpp -o encoder -ldivsufsort"

#include <bits/stdc++.h>
#include <divsufsort.h>

using namespace std;

string burrowsWheelerScottTransform(const string& input) {
    int n = input.length();
    vector<int> sa(n), bwt(n);

    divsufsort((const unsigned char *)input.c_str(), &sa[0], n);

    for (int i = 0; i < n; i++) {
        bwt[i] = (sa[i] == 0) ? n - 1 : sa[i] - 1;
    }

    string bwt_string;
    for (int i = 0; i < n; i++) {
        bwt_string += input[bwt[i]];
    }

    return bwt_string;
}

pair<string, map<char, string>> dynamicByteRemapping(const string& input) {
    string remapped="";
    map<char, string> byteMap;
    map<char, int> byteCount;

    for (char c : input) {
        byteCount[c]++;
    }

    vector<pair<char, int>> byteFreq(byteCount.begin(), byteCount.end());
    sort(byteFreq.begin(), byteFreq.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    string mapping = "00000000";
    for (const auto& pair : byteFreq) {
        byteMap[pair.first] = mapping;
        mapping = bitset<8>(bitset<8>(mapping).to_ulong() + 1).to_string();
    }

    for (char c : input) {
        remapped += byteMap[c];
    }

    pair<string, map<char, string>> ans;
    ans.first = remapped;
    ans.second = byteMap;

    return ans;
}

vector<string> verticalByteReading(const string& input) {
    vector<string> bitStrings(8, "");
    int chunkSize = 8;

    for (size_t i = 0; i < input.size(); i += chunkSize) {
        string chunk = input.substr(i, chunkSize);
        
        for (int j = 0; j < chunkSize; ++j) {
            bitStrings[j] += chunk[j];
        }
    }
    
    return bitStrings;
}


vector<int> runLengthEncoding(const string& input) {
    vector<int> rle;
    int count = 1;
    char currentBit = input[0];

    for (size_t i = 1; i < input.size(); ++i) {
        if (input[i] == currentBit) {
            count++;
        } else {
            rle.push_back(count);
            count = 1;
            currentBit = input[i];
        }
    }
    rle.push_back(count);

    return rle;
}

int main() {
    string original;
    cout<<"Enter a string to encode: ";
    cin>>original;

    string transformed = burrowsWheelerScottTransform(original);
    cout<<transformed<<endl;

    pair<string, map<char, string>> remappedData = dynamicByteRemapping(transformed);
    string remapped = remappedData.first;
    map<char, string> byteMap = remappedData.second;

    vector<string> bitStrings = verticalByteReading(remapped);

    string verticalString = "";
    for(int i=0; i<8; i++) {
        verticalString+=bitStrings[i];
    }

    vector<int> rle = runLengthEncoding(verticalString);

    ofstream outputFile("encoded.txt");
    if (outputFile.is_open()) {
        for (int run : rle) {
            outputFile << run << " ";
        }
        outputFile.close();
        cout << "RLE encoded data has been written to encoded.txt" << endl;
    } else {
        cerr << "Unable to open file encoded.txt for writing!" << endl;
        return 1;
    }

    ofstream remappingOutputFile("remapping.txt");
    if (remappingOutputFile.is_open()) {
        for (const auto& entry : byteMap) {
            remappingOutputFile << entry.first << " " << entry.second << endl;
        }
        remappingOutputFile.close();
        cout << "Byte remapping has been written to remapping.txt" << endl;
    } else {
        cerr << "Unable to open file remapping.txt for writing!" << endl;
        return 1;
    }

    return 0;
}
