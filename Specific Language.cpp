/**
* Езикът на планетата Абецедея се състои от думи, които се образуват според следните правила:
* Празният низ е дума от езика;
* Ако <w> е дума от езика, то AA<w>B също е дума от езика;
* Ако <w> е дума от езика, то <w>C<w> също е дума от езика;
* Ако <w1> и <w2> са две различни думи от езика, то <w1>C<w2> също е дума от езика;
* Ако <w> e дума от езика, то <w>D<w> също е дума от езика;
* Ако <w> се състои от повече от 64 символа, то <w> не е дума от езика.
* Абецедейците са много любопитни и всеки път когато видят някаква последователност от символи се чудят дали
* това е дума от техния език. Помогнете им като напишете функция с име isWord(), която получава като параметър низ и
* проверява дали той е дума от гореописания език. Напишете функция main(), в която от стандартния вход се въвежда
* цяло число n, следвано от n реда, на всеки от който има по един низ (празният низ се задава с празен ред). Програмата
* трябва да извежда на стандартния изход n реда, всеки от които съдържа по една цифра: 1, ако подадената на входа дума е
* дума от езика, или 0 - в противен случай.
*
* Пример
 * Вход
10
AAAABB
AACB
CCCC
CCDCCCAAB
AABAAB
CAABDAAB
AABCDAAB

CXC
AABAAAABB

 * Изход
1
1
1
1
0
1
0
1
0
0


*/


#include <iostream>

int wordLength;

char *inputStr(int size) {
    char *a = new char[size];
    std::cin.getline(a, size);

    return a;
}

int size(char *str) {
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        counter++;
    }
    return counter;
}


bool isValidStr(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'A' || str[i] == 'B' || str[i] == 'C' || str[i] == 'D' || str[i] == '\n') {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

bool isWordValid(char *word, int start, int end) {
    if (end <= start) {
        return true;
    }

    int currentLength = end - start + 1;
    int mid = currentLength / 2 + start;

    if (currentLength % 2 != 0) {
        if (word[mid] == 'C') {
            if (isWordValid(word, start, mid - 1)) {
                return isWordValid(word, mid + 1, end);
            }
            else
                return false;
        }
        else if (word[mid] == 'D') {
            int start1 = start;
            int start2 = mid + 1;

            while (start1<mid && start2 <= end) {
                if (word[start1] != word[start2]) {
                    return false;
                }
                start1++;
                start2++;
            }
            //as both words are equal, it does not matter which one we check
            return isWordValid(word, start, mid - 1);
        }
        else if (word[start] == 'A' && word[start + 1] == 'A' && word[end] == 'B' && end == start + 2) {
            return true;
        }
        else
            return false;
    }
    else {     // if currSize%2==0
        if (word[start] == 'C') {
            return isWordValid(word, start + 1, end);
        }
        else if (word[start] == 'A' && word[start + 1] == 'A' && word[end] == 'B') {
            return isWordValid(word, start + 2, end - 1);
        }
        else return false;
    }
}

int main() {
    int n;
    std::cin >> n;

    while (std::cin.fail())  //while the data type declared doesn't match data type entered
    {
        std::cout << "Invalid number.  Select again: ";  //error msg
        std::cin.clear();   //clear istream
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');  //repair istream
        std::cin >> n; //get user input again
    }

    int input = n + 1;
    int *result = new int[n];
    int i = 0;
    while (input--) {
        char *str = inputStr(100);
        wordLength = size(str);

        if (isValidStr(str)) {
            if (isWordValid(str, 0, wordLength - 1)) {
                result[i] = 1;
            }
            else {
                result[i] = 0;
            }
            i++;
        }
    }

    for (int j = 1; j < i; j++) {
        std::cout << result[j] << std::endl;
    }

    return 0;
}