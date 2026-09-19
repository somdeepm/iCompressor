#include <bits/stdc++.h>

#include "Trie_class.hpp"

#include <sys/stat.h>

using namespace std;
struct stat results;
int initial_size = 0;
class LevelOneCompressor
{
public:
    Trie myTrie;
    vector<string> vs;
    char *inpStr, *ansStr;
    long long charLen;

    void insertDictionary()
    {
        string myText;
        long long d = 0;
        ifstream myDict("dictionary.txt");
        while (myDict.eof() == 0)
        {
            myDict >> myText;
            if (myText[myText.size() - 1] == ')')
                myText[myText.size() - 1] = ' ';
            myTrie.insert(myText, d);
            d++;
        }
        myDict.close();
    }
    void vectorString()
    {
        string myText;
        ifstream myDict("key.txt");
        while (myDict.eof() == 0)
        {
            myDict >> myText;
            vs.push_back(myText);
        }
        myDict.close();
    }

    void readToString(char *fileName)
    {
        if (stat(fileName, &results) == 0)
            initial_size = charLen = results.st_size;
        ifstream myFile1(fileName, ios::in | ios::binary);
        inpStr = new char[charLen];
        myFile1.read(inpStr, charLen);
        myFile1.close();
    }

    void compress(char *fileName)
    {
        insertDictionary();
        vectorString();
        readToString(fileName);
        string buffStr = "", ans = "";
        for (long long i = 0; i < charLen; ++i)
        {
            long long flag = 0, lastPos, key, index;
            string searc = "";
            if (inpStr[i] == '\n')
                continue;
            if (inpStr[i] >= 'a' && inpStr[i] <= 'z' || (inpStr[i] >= 'A' && inpStr[i] <= 'Z'))
            {
                for (long long j = i, k = 0; k < 15 && j < charLen; ++j, ++k)
                {
                    if (inpStr[j] >= 'a' && inpStr[j] <= 'z' || (inpStr[j] >= 'A' && inpStr[j] <= 'Z') || inpStr[j] == ' ')
                    {
                        searc += inpStr[j];
                        key = myTrie.search(searc);
                        if (key != -1)
                        {
                            flag = 1;
                            lastPos = j;
                            index = key;
                        }
                    }
                    else
                        break;
                }
                if (flag == 1)
                {
                    if (buffStr.size() > 0)
                    {
                        if (buffStr.size() < 10)
                        {
                            ans += '0' + buffStr.size();
                        }
                        else
                        {
                            unsigned char c = (int)0;
                            ans += '0';
                            c += 22 + buffStr.size();
                            ans += c;
                        }
                        ans += buffStr;
                        buffStr = "";
                    }
                    ans += vs[index];
                    i = lastPos;
                }
                else
                {
                    if (buffStr.size() != 0 || (inpStr[i] >= 'a' && inpStr[i] <= 'z'))
                        buffStr += inpStr[i];
                    else
                        ans += inpStr[i];
                }
            }
            else
            {
                if (buffStr.size() == 0 && (inpStr[i] < '0' || inpStr[i] > '9'))
                {
                    ans += inpStr[i];
                }
                else
                {
                    buffStr += inpStr[i];
                }
            }
            if (buffStr.size() > 90)
            {
                if (buffStr.size() > 0)
                {
                    if (buffStr.size() < 10)
                    {
                        ans += '0' + buffStr.size();
                    }
                    else
                    {
                        unsigned char c = (int)0;
                        ans += '0';
                        c += 22 + buffStr.size();
                        ans += c;
                    }
                    ans += buffStr;
                    buffStr = "";
                }
            }
        }
        if (buffStr.size() > 0)
        {
            if (buffStr.size() < 10)
            {
                ans += '0' + buffStr.size();
            }
            else
            {
                unsigned char c = (int)0;
                ans += '0';
                c += 22 + buffStr.size();
                ans += c;
            }
            ans += buffStr;
        }
        ansStr = new char[ans.size()];
        for (int i = 0; i < ans.size(); ++i)
        {
            ansStr[i] = ans[i];
        }
        ofstream myFile("coutput1.bin", ios::out | ios::binary);
        myFile.write(ansStr, ans.size());
        myFile.close();
    }
};

class LevelOneDecompressor
{
public:
    Trie myTrie;
    struct stat results;
    long long charLen;
    vector<string> vs;
    char *outStr, *ansStr;
    void insertDictionary()
    {
        string myText;
        long long d = 0;
        ifstream myDict("key.txt");
        while (myDict.eof() == 0)
        {
            myDict >> myText;
            myTrie.insert(myText, d);
            d++;
        }
        myDict.close();
    }
    void readToString()
    {
        if (stat("doutput1.bin", &results) == 0)
            charLen = results.st_size;
        ifstream myFile1("doutput1.bin", ios::in | ios::binary);
        outStr = new char[charLen];
        myFile1.read(outStr, charLen);
        myFile1.close();
    }
    void vectorString()
    {
        string myText;
        ifstream myDict("dictionary.txt");
        while (myDict.eof() == 0)
        {
            myDict >> myText;
            if (myText[myText.size() - 1] == ')')
                myText[myText.size() - 1] = ' ';
            vs.push_back(myText);
        }
        myDict.close();
    }
    void decompressor(char *fileName)
    {
        insertDictionary();
        vectorString();
        readToString();
        string ans = "", temp = "";
        for (int i = 0; i < charLen; ++i)
        {
            if (outStr[i] == '\n')
                continue;
            if (*(outStr + i) >= '0' && *(outStr + i) <= '9')
            {
                if (*(outStr + i) == '0')
                {
                    int temp = (int)outStr[i + 1] - 22;
                    for (int j = i + 2, k = 0; k < temp; ++j, ++k)
                    {
                        ans += *(outStr + j);
                        i = j;
                    }
                }
                else
                {
                    int temp = outStr[i] - '0';
                    for (int j = i + 1, k = 0; k < temp; ++j, ++k)
                    {
                        ans += *(outStr + j);
                        i = j;
                    }
                }
            }
            else
            {
                if (!(outStr[i] >= 'a' && outStr[i] <= 'z'))
                {
                    ans += outStr[i];
                }
                else
                {
                    temp += outStr[i];
                    if (outStr[i] <= 'k')
                    {
                        ans += vs[myTrie.search(temp)];
                        temp = "";
                    }
                    else
                    {
                    }
                }
            }
        }
        ansStr = new char[ans.size()];
        for (int i = 0; i < ans.size(); ++i)
        {
            ansStr[i] = ans[i];
        }
        for (int j = strlen(fileName) - 1, k = 0; k < 14; j--, k++)
            fileName[j] = '\0';
        strcat(fileName, "decompressed.txt");
        ofstream myFile(fileName, ios::out | ios::binary);
        myFile.write(ansStr, ans.size());
        myFile.close();
        cout << "\n\tFile Decompressed Succesfully\n\tFile Name: " << fileName << endl;
    }
};
class LevelTwo
{
public:
    string lvl1 = "";
    string decompressed = "";
    int char_count = 0;
    unsigned char *tempans,
        *realans;
    char *char_ans,
        *out_ans;
    int power[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

    void readToString(char name[])
    {
        lvl1 = "";
        int charLen;
        char *inpStr;
        if (stat(name, &results) == 0)
            char_count = charLen = results.st_size;
        ifstream myFile1(name, ios::in | ios::binary);
        inpStr = new char[charLen];
        myFile1.read(inpStr, charLen);
        for (int i = 0; i < charLen; i++)
            lvl1 += inpStr[i];
        myFile1.close();
    }

    void writeToFile(char name[], char *ptr, int size)
    {
        ofstream myFile(name, ios::out | ios::binary);
        myFile.write(ptr, size);
        myFile.close();
    }

    void string_flush(string &ptr, int &ind, int flag = 0)
    {
        int size = ptr.size();
        string temp1 = "";
        for (int i = 0; size - i >= 8 + flag; i += 8)
        {
            int temp = 0;
            for (int j = i, k = 0, t; k < 8; ++k, ++j)
            {
                t = power[7 - k];
                temp += t * (ptr[j] - '0');
            }
            char_count++;
            tempans[ind++] = temp;
        }
        for (int i = 0, j = size - 1; i < size % 8; i++)
            temp1 += ptr[j--];
        reverse(temp1.begin(), temp1.end());
        ptr = temp1;
        return;
    }

    int valid(char a)
    {
        if ((a >= 'a' && a <= 'z'))
            return (int)a - 'a' + 1;
        if (a == ' ')
            return 27;
        if (a == ',')
            return 28;
        if (a == '.')
            return 29;
        if (a == '-')
            return 30;
        return -1;
    }

    char revmap(int n)
    {
        if (n > 0 && n <= 26)
            return 'a' + n - 1;
        if (n == 27)
            return ' ';
        if (n == 28)
            return ',';
        if (n == 29)
            return '.';
        return '-';
    }

    string binaryConversion(int temp1, int n)
    {
        string temp = "";
        for (int i = 0; i < n; i++, temp1 /= 2)
        {
            temp += (temp1 % 2) + '0';
        }
        reverse(temp.begin(), temp.end());
        return temp;
    }

    string getchars(int n)
    {
        string retval = "";
        if (n % 30 == 0)
        {
            retval += revmap((n / 30) - 1);
            retval += revmap(30);
            return retval;
        }
        retval += revmap(n / 30);
        retval += revmap(n % 30);
        return retval;
    }

    void compress(string lvl1)
    {
        string ans = "";
        int temp1, temp2, ind = 0;
        int size = lvl1.size();
        for (int i = 0, j = 0; i < size; ++i, ++j)
        {
            if (lvl1[i + 1] == size)
            {
                ans += '0';
                ans += binaryConversion((int)(unsigned char)lvl1[i], 8);
            }
            else if ((valid(lvl1[i]) != -1) && valid(lvl1[i + 1]) != -1)
            {
                ans += '1';
                temp1 = valid(lvl1[i]) * 30;
                temp2 = valid(lvl1[i + 1]);
                temp1 += temp2;
                ans += binaryConversion(temp1, 10);
                i++;
            }
            else
            {
                ans += '0';
                ans += binaryConversion((int)(unsigned char)lvl1[i], 8);
            }
            // if(i!=0&&j>10000){string_flush(ans,ind,4);j=0;}
        }

        size = ans.size() % 8;
        if (size != 0)
        {
            for (int j = 0; j < 8 - size; ++j)
                ans += '0';
        }
        string_flush(ans, ind);
        tempans[ind++] = '\0';
    }

    void decompressor(string &ans, int flag = 3)
    {
        int size = ans.size(), end_ind = 0;
        for (int i = 0; size - i >= 9 + flag; i++)
        {
            int temp = 0;
            if (ans[i] == '1')
            {
                for (int j = i + 1, k = 0, t; k < 10; ++k, ++j)
                {
                    t = power[9 - k];
                    temp += t * (ans[j] - '0');
                }
                decompressed += getchars(temp);
                i += 10;
            }
            else
            {
                for (int j = i + 1, k = 0, t; k < 8; ++k, ++j)
                {
                    t = power[7 - k];
                    temp += t * (ans[j] - '0');
                }
                decompressed += (unsigned char)temp;
                i += 8;
            }
            end_ind = i + 1;
        }
        string tmp_str = "";
        for (int i = end_ind; i < size; i++)
            tmp_str += ans[i];
        ans = tmp_str;
    }

    void decomp_reader(unsigned char *ptr)
    {
        string ans = "";
        for (int i = 0, j = 0; i < char_count; ++i, j++)
        {
            ans += binaryConversion(*(ptr + i), 8);
            if (j > 500000)
            {
                decompressor(ans);
                j = 0;
            }
        }
        decompressor(ans, 0);
    }
    void levelTwoMainD(char *fileName)
    {
        char_count = 0;
        readToString(fileName);
        realans = new unsigned char[char_count];
        for (int i = 0; i < char_count; i++)
            realans[i] = lvl1[i];
        decomp_reader(realans);
        out_ans = new char[decompressed.size()];
        for (int i = 0; i < decompressed.size(); i++)
            out_ans[i] = decompressed[i];
        cout << endl;
        ofstream myFile("doutput1.bin", ios::out | ios::binary);
        myFile.write(out_ans, decompressed.size());
        myFile.close();
    }

    void levelTwoMainC(char *fileName)
    {
        char outputBinFileName[] = "coutput1.bin";
        readToString(outputBinFileName);
        tempans = new unsigned char[2 * lvl1.size()];
        char_count = 0;
        compress(lvl1);
        int size = lvl1.size();
        char_ans = new char[char_count];
        realans = new unsigned char[char_count];
        for (int i = 0; i < char_count; i++)
            char_ans[i] = tempans[i];
        for (int j = strlen(fileName) - 1, k = 0; k <= 3; j--, k++)
            fileName[j] = '\0';
        strcat(fileName, "_compressed.bin");
        writeToFile(fileName, char_ans, char_count);
        cout << "\n\tFile Compressed Succesfully\n\tFile Path: " << fileName << endl;
        cout << "\tText compressed by: " << 100 - ((double)char_count * 100 / initial_size) << "%\n";
    }
};
int main()
{
    system("CLS");
    string t1;
    ifstream t("Logo.txt");
    stringstream buffer;
    buffer << t.rdbuf();
    cout << buffer.str() << endl;
    t.close();
    LevelOneCompressor f;
    LevelOneDecompressor fd;
    LevelTwo d;
    LevelTwo d1;
    int ch;
    while (1)
    {
        cout << "\n\t**==Welcome to iCompresser==**\n";
        cout << "\tPress '1' to compress your file\n\tPress '2' to decompress your file\n\tPress '3' to exit...\n\n\t";
        if (!(cin >> ch))
        {
            // Non-numeric input put cin into a fail state. Recover so the
            // loop does not spin forever printing "Invalid Choice".
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Choice\n";
            continue;
        }
        // Discard the rest of the line (spaces, leftover chars)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        char fileName[100];
        string fileNameStr;
        switch (ch)
        {
        case 1:
            cout << "\tEnter your file path or file name to compress: ";
            getline(cin, fileNameStr);
            strncpy(fileName, fileNameStr.c_str(), sizeof(fileName) - 1);
            fileName[sizeof(fileName) - 1] = '\0';
            f.compress(fileName);
            d.levelTwoMainC(fileName);
            break;
        case 2:
            cout << "\tEnter your file path or file name to decompress: ";
            getline(cin, fileNameStr);
         strncpy(fileName, fileNameStr.c_str(), sizeof(fileName) - 1);
            fileName[sizeof(fileName) - 1] = '\0';
            d1.levelTwoMainD(fileName);
            fd.decompressor(fileName);
            break;
        case 3:
            cout << "\n\tExiting....";
            return 0;
        default:
            cout << "Invalid Choice\n";
        }
    }
}