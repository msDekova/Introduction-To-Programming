/**
*Да се напише програма, която приема вход от потребителя във формат: <<op X1 X2>>, където op е една от целочислените
* аритметични операции [+, -, *], a Х1 и Х2  са цели десетични числа с максимален размер 100 цифри. Програмата да
* извежда на екрана резултата от аритметичната операция.
*Забележка: Числата може да са както положителни, така и отрицателни.

*/


#include<iostream>

const int MAX = 100;
int length1;
int length2;

bool isValidStr(char str[]) {
    if (str == nullptr)
        return false;

    int i = 0;
    if (str[0] == '-')
        i += 1;
    for (i; str[i] != '\0'; i++) {
        if (str[i] < 48 || str[i]>57) {
            return false;
        }
    }
    return true;
}

int length(char str[]) {
    int size = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        size++;
    }
    return size;
}

void print(int arr[], int size) {
    int i = 0;
    while (arr[i] == 0) {
        i++;
    }

    for (i; i<size; i++) {
        std::cout << arr[i];
    }
}
void charIntoInt1(char str[], int arr[], int length1) {
    int i = 0;
    if (str[0] == '-') {
        arr[0] = 0;
        i = 1;
    }

    for (i; i < length1; i++) {
        arr[i] = str[i] - '0';
    }
}
void charIntoInt2(char str[], int arr[], int length2) {
    int i = 0;
    if (str[0] == '-') {
        i = 1;
        arr[0] = 0;
    }

    for (i; i < length2; i++) {
        arr[i] = str[i] - '0';
    }
}


void _multiply(int arr1[], int arr2[]) {
    int returnedArr[MAX];
    for (int i = 0; i < MAX; i++) {
        returnedArr[i] = 0;
    }

    ////array of the second number
    ////every element of the second array is multiplied with every element of the first array
    for (int j = 0; j < length2; j++) {
        int num = arr2[j];

        //// currArray stores multiplication of element arr2[i] with arr1
        int currArr[MAX];
        for (int i = 0; i < MAX; i++) {
            currArr[i] = 0;
        }

        for (int i = length1 - 1; i >= 0; i--) {

            currArr[i] = num * arr1[i];
        }

        for (int i = length1 - 1; i >= 0; i--) {
            if (currArr[i] > 9 && i - 1 >= 0) {
                currArr[i - 1] += currArr[i] / 10;
                currArr[i] = currArr[i] % 10;
            }

        }


        for (int k = j; k < length1 + length2; k++) {
            returnedArr[k] += currArr[k - j];
        }

        for (int i = length1 + length2; i >= 0; i--) {
            if (returnedArr[i] > 9 && i - 1 >= 0) {
                returnedArr[i - 1] += returnedArr[i] / 10;
                returnedArr[i] = returnedArr[i] % 10;
            }

        }
    }

    print(returnedArr, length1 + length2 - 1);
}

int bigger(int arr1[], int arr2[]) {
    if (length1 > length2) {
        return 1; ////for first word
    }
    else if (length1 < length2) {
        return 2; ////for second word
    }
    else if (length1 == length2) {
        for (int i = 0; i < length1; i++) {
            if (arr1[i] > arr2[i]) {
                return 1;
            }
            else if (arr1[i] < arr2[i]) {
                return 2;
            }
        }
    }
    return 0;
}

void substraction(int arr1[], int arr2[], int size) {
    int borrow = 0;
    int newSize = size;
    int *newArr = new int[newSize];

    for (int i = 0; i < newSize; i++) {
        newArr[i] = 0;
    }

    int smallerLength = length1 < length2 ? length1 : length2;

    int *currArr = new int[size];
    int k = 0;
    for (int i = 0; i < size; i++) {
        if (i < size - smallerLength) {
            currArr[i] = 0;
        }
        else {
            currArr[i] = arr2[k];
            k++;
        }
    }

    for (int i = newSize - 1; i > 0; i--) {
        if (arr1[i] < currArr[i]) {
            borrow = 10 + arr1[i];
            newArr[i] = borrow - currArr[i];
            arr1[i - 1] -= 1;
        }
        else {
            newArr[i] = arr1[i] - currArr[i];
        }
    }
    newArr[0] = arr1[0];

    print(newArr, newSize);
}

void addition(int arr1[], int arr2[]) {
    int newSize = length2;
    if (length1 > length2) {
        newSize = length1;
    }
    int *newArr = new int[newSize];
    for (int i = 0; i < newSize; i++) {
        newArr[i] = 0;
    }
    int sum = 0;
    int add = 0;

    for (int i = newSize - 1; i >= 0; i--) {
        sum = 0;
        int num1 = arr1[length1 - 1];
        int num2 = arr2[length2 - 1];

        if (length1 <= 0) {
            num1 = 0;
        }
        if (length2 <= 0) {
            num2 = 0;
        }

        sum = num1 + num2 + add;
        if (i == 0) {
            newArr[i] = sum;
            break;
        }
        if (sum >= 0 && sum < 10) {
            newArr[i] = sum;
            add = 0;
        }
        else if (sum > 9) {
            newArr[i] = sum % 10;
            sum = sum / 10;
            add = sum;
        }
        length1--;
        length2--;
    }
    print(newArr, newSize);
}

int main() {
    char symbol;
    std::cout << "Insert an operating symbol (+/-/*): ";
    std::cin >> symbol;
    if (symbol == '+' || symbol == '-' || symbol == '*') {

        char str1[MAX];
        char str2[MAX];
        std::cout << "Insert two numbers: ";
        std::cin >> str1 >> str2;

        if (!(isValidStr(str1)) || !isValidStr(str2)) {
            std::cout << "Invalid numbers.\n";
            system("pause");
            return 0;
        }


        length1 = length(str1);
        length2 = length(str2);

        int *arr1 = new int[length1];
        int *arr2 = new int[length2];

        charIntoInt1(str1, arr1, length1);
        charIntoInt2(str2, arr2, length2);

        if (symbol == '+') {
            if ((str1[0] != '-' && str2[0] != '-')) {
                addition(arr1, arr2);
            }
            else if (str1[0] == '-' && str2[0] == '-') {
                std::cout << "-";
                addition(arr1, arr2);
            }
            else {
                int checkBigger = bigger(arr1, arr2);

                if (checkBigger == 0) {
                    std::cout << "0\n";
                }
                else if ((checkBigger == 1 && str1[0] == '-') && str2[0] != '-') {
                    std::cout << "-";
                    substraction(arr1, arr2, length1);
                }
                else if ((checkBigger == 2 && str2[0] == '-') && str1[0] != '-') {
                    std::cout << "-";
                    substraction(arr2, arr1, length2);
                }
                else if (checkBigger == 2 && str1[0] == '-') {
                    substraction(arr2, arr1, length2);
                }
                else {
                    substraction(arr1, arr2, length1);
                }
            }
        }

        if (symbol == '-') {
            int checkBigger = bigger(arr1, arr2);
            if (checkBigger == 0) {
                std::cout << "0\n";
            }
            else if (checkBigger == 1) {
                if (str1[0] != '-') {
                    if (str2[0] == '-') {
                        addition(arr1, arr2);
                    }
                    else {
                        substraction(arr1, arr2, length1);
                    }
                }
                else {
                    if (str2[0] == '-') {
                        std::cout << "-";
                        substraction(arr1, arr2, length1);
                    }
                    else {
                        std::cout << "-";
                        addition(arr1, arr2);
                    }
                }
            }
            else if (checkBigger == 2) {
                if (str1[0] != '-') {
                    if (str2[0] == '-') {
                        addition(arr1, arr2);
                    }
                    else {
                        std::cout << "-";
                        substraction(arr2, arr1, length2);
                    }
                }
                else {
                    if (str2[0] == '-') {
                        substraction(arr2, arr1, length2);
                    }
                    else {
                        std::cout << "-";
                        addition(arr1, arr2);
                    }
                }
            }
        }

        if (symbol == '*') {
            if ((str1[0] == '-' && str2[0] == '-') || (str1[0] != '-' && str2[0] != '-')) {
                _multiply(arr1, arr2);
            }
            else if (str1[0] == '-' || str2[0] == '-') {
                std::cout << "-";
                _multiply(arr1, arr2);
            }
        }
    }
    else {
        return 0;
    }

    std::cout << std::endl;

    return 0;
}