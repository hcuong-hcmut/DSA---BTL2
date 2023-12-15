#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<list>
#include <utility> 
#include <algorithm>

using namespace std;
bool compare(const std::vector<std::pair<char, int>>& a, const std::vector<std::pair<char, int>>& b);
void print(const std::vector<std::pair<char, int>>& a, const std::vector<std::pair<char, int>>& b);

using CharFreqPair = std::pair<char, int>;

char caesarCipher(char ch, int shift) {
    if (isalpha(ch)) {
        char offset = isupper(ch) ? 'A' : 'a';
        return (char)((ch - offset + shift) % 26 + offset);
    }
    return ch;
}

// Function to process the string
vector<pair<char, int>> string_Processing(string& name) {
    vector<pair<char, int>> freq_prev;
    // Step 1: Count character frequency and maintain the order of appearance
    for (char& ch : name) {
        auto it = find_if(freq_prev.begin(), freq_prev.end(),
                               [ch](const pair<char, int>& p) { return p.first == ch; });
        if (it != freq_prev.end()) {
            it->second++;
        } else {
            freq_prev.push_back(make_pair(ch, 1));
        }
    }
    
    // Step 2: Apply Caesar cipher to name and update freq_prev
    string updated_name;
    for (char& ch : name) {
        auto it = find_if(freq_prev.begin(), freq_prev.end(),
                               [ch](const pair<char, int>& p) { return p.first == ch; });
        if (it != freq_prev.end()) {
            char ciphered_char = caesarCipher(ch, it->second);
            updated_name.push_back(ciphered_char);
        }
    }

    freq_prev.clear();
    for (char& ch : updated_name) {
        auto it = find_if(freq_prev.begin(), freq_prev.end(),
                               [ch](const pair<char, int>& p) { return p.first == ch; });
        if (it != freq_prev.end()) {
            it->second++;
        } else {
            freq_prev.push_back(make_pair(ch, 1));
        }
    }

    name = updated_name;

    // Step 3: Merge frequencies of the same characters
    vector<pair<char, int>> freq;
    for (auto& p : freq_prev) {
        auto it = find_if(freq.begin(), freq.end(), [p](const pair<char, int>& elem) {
            return elem.first == p.first;
        });

        if (it != freq.end()) {
            // Character found, add to the frequency
            it->second += p.second;
        } else {
            // Character not found, add a new pair
            freq.push_back(p);
        }
    }

    // Step 4: Sort the frequency vector
    sort(freq.begin(), freq.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        else{
            if (islower(a.first) && islower(b.first)) {
            return a.first > b.first; // Lowercase characters in descending order
        } else if (isupper(a.first) && isupper(b.first)) {
            return a.first > b.first; // Uppercase characters in descending order
        } else {
            return (bool)(isupper(a.first)); // Uppercase characters take precedence over lowercase
        }
        }
        
    });

    return freq;
}


int main()
{
    //! test 1: kiểm tra bước 1 bước 2
    string name = "aaa";
    cout << "test 1 - name = " << name << " : ";
    string nameResult = "ddd";
    std::vector<std::pair<char, int>> result = {{'d', 3}};
    std::vector<std::pair<char, int>> you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 2: kiểm tra bước 1 bước 2
    name = "zzz";
    cout << "test 2 - name = " << name << " : ";
    nameResult = "ccc";
    result = {{'c', 3}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }


    //! test 3: kiểm tra bước 3 và 4
    name = "aAzzAB";
    cout << "test 3 - name = " << name << " : ";
    nameResult = "bCbbCC";
    result = {{'C', 3}, {'b', 3}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }



    //! test 4: kiểm tra bước 3 và 4
    name = "azdbc";
    cout << "test 4 - name = " << name << " : ";
    nameResult = "baecd";
    result = {{'e',1}, {'d', 1}, {'c', 1}, {'b',1}, {'a', 1}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }


    //! test 5: 
    name = "aAcc";
    cout << "test 5 - name = " << name << " : ";
    nameResult = "bBee";
    result = {{'e',2}, {'B', 1}, {'b', 1}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 6: 
    name = "cac";
    cout << "test 6 - name = " << name << " : ";
    nameResult = "ebe";
    result = {{'e',2},  {'b', 1}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }


    //! test 7: 
    name = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
    cout << "test 7 - name = " << name << " : ";
    nameResult = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
    result = {{'a',26}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 8: 
    name = "aaaaaaaaaaaaaaaaaaaaaaaaab";
    cout << "test 8 - name = " << name << " : ";
    nameResult = "zzzzzzzzzzzzzzzzzzzzzzzzzc";
    result = {{'z',25}, {'c',1}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    
}

void print(const std::vector<std::pair<char, int>>& a, const std::vector<std::pair<char, int>>& b){
    cout << "solution     : ";
    for (auto i : a) cout << "{" << i.first << ":" << i.second << "} -> ";
    cout << "\nsolution_you : ";
    for (auto i : b) cout << "{" << i.first << ":" << i.second << "} -> ";
    cout << "\n";
}

bool compare(const std::vector<std::pair<char, int>>& a, const std::vector<std::pair<char, int>>& b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}



