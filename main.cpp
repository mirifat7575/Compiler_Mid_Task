#include <iostream>
#include <fstream>
using namespace std;

bool isKeyword(char word[]) {
    char keywords[17][15] = {
        "int", "float", "double", "char", "void",
        "if", "else", "while", "for", "return",
        "using", "namespace", "include", "const",
        "bool", "true", "false"
    };

    for (int i = 0; i < 17; i++) {
        int j = 0;

        while (word[j] == keywords[i][j] &&
               word[j] != '\0') {
            j++;
        }

        if (word[j] == '\0' && keywords[i][j] == '\0')
            return true;
    }

    return false;
}

void analyze() {
    ifstream file("hello.txt");
    ofstream outFile("output.txt");

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    if (!outFile) {
        cout << "Error opening output file!" << endl;
        return;
    }

    char ch;
    char word[100];
    int i;

    while (file.get(ch)) {

        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') || ch == '_') {

            i = 0;
            word[i++] = ch;

            while (file.peek() != EOF) {
                char next = file.peek();

                if ((next >= 'A' && next <= 'Z') ||
                    (next >= 'a' && next <= 'z') ||
                    (next >= '0' && next <= '9') ||
                    next == '_') {
                    file.get(ch);
                    word[i++] = ch;
                }
                else {
                    break;
                }
            }

            word[i] = '\0';

            if (isKeyword(word)) {
                cout << word << " : Keyword" << endl;
                outFile << word << " : Keyword" << endl;
            }
            else {
                cout << word << " : Identifier" << endl;
                outFile << word << " : Identifier" << endl;
            }
        }

        else if (ch >= '0' && ch <= '9') {
            cout << ch << " : Constant" << endl;
            outFile << ch << " : Constant" << endl;
        }

        else if (ch == '+' || ch == '-' || ch == '*' ||
                 ch == '/' || ch == '=' || ch == '<' ||
                 ch == '>' || ch == '%') {
            cout << ch << " : Operator" << endl;
            outFile << ch << " : Operator" << endl;
        }

        else if (ch != ' ' && ch != '\n' &&
                 ch != '\t' && ch != '\r') {
            cout << ch << " : Punctuation" << endl;
            outFile << ch << " : Punctuation" << endl;
        }
    }

    file.close();
    outFile.close();
}

int main() {
    analyze();
    return 0;
}
