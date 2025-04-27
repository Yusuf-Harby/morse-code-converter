#include <iostream>
#include <string>
using namespace std;

class MorseCode {
private:
    string alpha[26] = {
            "._", "_...", "_._.",
            "_..", ".", ".._.",
            "__.", "....", "..",
            ".___", "_._", "._..",
            "__", "_.", "___",
            ".__.", "__._", "._.",
            "...", "_", ".._",
            "..._", ".__", "_.._",
            "_.__", "__.."
    };

    string digitToMorse(int digit) {
        string morse = "";
        if (digit < 5)
            morse.append(digit, '.').append(5 - digit, '_');
        else
            morse.append(digit - 5, '_').append(10 - digit, '.');
        return morse;
    }

    char morseToDigit(string morse) {
        int i = 0, j = 0;
        while (morse[i] == '.')
            i++;
        j = i;
        while (morse[j] == '_')
            j++;
        j -= i;
        if (j + i == 5)
            return char(i + '0');

        i = 0, j = 0;
        while (morse[i] == '_')
            i++;
        j = i;
        while (morse[j] == '.')
            j++;
        j -= i;
        if (j + i == 5)
            return char(i + 5 + '0');
        return '#';
    }

    char morseToLetter(string morse) {
        for (int i = 0; i < 26; i++)
            if (morse == alpha[i])
                return char(i + 'a');
        return '!';
    }

    string trim(string str) {
        int start = 0;
        while (start < str.size() && str[start] == ' ') start++;
        int end = str.size() - 1;
        while (end >= 0 && str[end] == ' ') end--;
        return str.substr(start, end - start + 1);
    }

    void processMorseToken(string &m, string &en) {
        if (m.size() == 5)
            en += morseToDigit(m);
        else if (m.size() < 5)
            en += morseToLetter(m);
        else
            en += " -Invalid Morse Code- ";
        m = "";
    }

public:
    MorseCode() {}

    string englishToMorse(string text) {
        text = trim(text);
        string morse = "";

        for (size_t i = 0; i < text.size(); ++i) {
            if (text[i] == ' ') {
                morse += "/ ";
                while (i + 1 < text.size() && text[i + 1] == ' ') i++;
                continue;
            }
            else if (isdigit(text[i]))
                morse += digitToMorse(text[i] - '0');
            else if (isalpha(text[i]))
                morse += alpha[tolower(text[i]) - 'a'];
            else
                morse += "Invalid character";

            morse += ' ';
        }
        return morse;
    }

    string morseToEnglish(string morse) {
        string m = "", en = "";
        morse += " ";

        for (size_t i = 0; i < morse.size(); ++i) {
            if (morse[i] == '.' || morse[i] == '_')
                m += morse[i];

            else if (morse[i] == ' ') {
                if (!m.empty())
                    processMorseToken(m, en);
                while (i + 1 < morse.size() && morse[i + 1] == ' ') i++;
            }

            else if (morse[i] == '/') {
                if (!m.empty())
                    processMorseToken(m, en);
                en += ' ';
                while (i + 1 < morse.size() && (morse[i + 1] == '/' || morse[i + 1] == ' ')) i++;
            }

            else {
                en += " -Invalid Morse Code- ";
                m = "";
            }
        }
        return en;
    }
};

int main() {
    MorseCode converter;

    string input, choice;

    while (true) {
        cout << "\n-----------------------------\n";
        cout << "1) Text to Morse code\n";
        cout << "2) Morse code to Text\n";
        cout << "3) Exit\n";
        cout << "Choose an option: ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Enter your text: ";
            getline(cin, input);
            cout << "Morse code: " << converter.englishToMorse(input) << '\n';
        }
        else if (choice == "2") {
            cout << "Enter Morse code: ";
            getline(cin, input);
            cout << "English Text: " << converter.morseToEnglish(input) << '\n';
        }
        else if (choice == "3") {
            break;
        }
        else {
            cout << "Invalid choice, please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}
