#include <iostream>
#include <string>

using namespace std;

void q1() {
    int opr, num1, num2;
    cout << "Choose your operation:" << endl;
    cout << "1: Addition " << "\n" << "2: Subtraction" << "\n" << "3: Multiply" << "\n" << "4: Divide" << "\n"
         << "5: Modulus" << endl;
    cin >> opr;
    cout << "Enter 2 numbers: ";
    cin >> num1 >> num2;

    switch (opr) {
        case 1:
            cout << num1 + num2;
            break;
        case 2:
            cout << num1 - num2;
            break;
        case 3:
            cout << num1 * num2;
            break;
        case 4:
            cout << num1 / num2;
            break;
        case 5:
            cout << num1 % num2;
            break;
    }


}

void q2() {
    int a = 1000;
    while (a <= 2000) {
        if (a % 8 == 0 && a % 5 == 0) {
            cout << a << endl;
        }
        a++;
    }
}

void q3() {
    string s;
    int i;

    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        cout << s[s.length() - 1 - i];
    }
}

void q4() {
    int guess = rand() % 10;
    int ug;

    while (ug != guess) {
        cout << "guess a no.: ";
        cin >> ug;
    }

}

void q5() {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << "\n";
    }
    for (int i = 4; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << "\n";
    }
}

void q7() {
    int r, c;
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << i * j;
        }
        cout << endl;
    }
}

void q8() {
    string text;
    cin>>text;
    int d = 0, l = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] > '0' && text[i] < '9') {
            d++;
        } else if (text[i] > 'a' && text[i] < 'z') {
            l++;
        } else if (text[i] == '\0') {
            break;
        }
    }
    cout << "digits: " << d << endl;
    cout << "letters: " << l << endl;
}

//void q9() {
//    string pass;
//    int check;
//    cin >> pass;
//    int l, n, c;
//    for (int i =0; i<pass.length(); i++){
//        if(pass[i]>'a' && pass[i]<'z'){
//            l++;
//        } else if(pass[i]=='')
//    }
//    if (pass.length() < 1) {
//        cout << "Not a Valid Password" << endl;
//    } else if(pass.length()>16){
//        cout << "Not a Valid Password" << endl;
//    } else if()
//}

void q10() {
    int i = 100;
    while (i != 400) {
        int a;
        a = i / 10;
        if ((i / 100) % 2 == 0 && i % 2 == 0 && a % 2 == 0) {
            cout << i << ",";
        }
        i++;
    }
}

void q12() {
    int a, b;
    cin >> a >> b;
    int sum = a + b;
    if (sum >= 105 && sum <= 200) {
        cout << 200;
    } else { cout << sum; }
}

void q11() {
    string month;
    cout << "enter month: ";
    cin >> month;
    if (month == "jan" || month == "march" || month == "may" || month == "july" || month == "august" ||
        month == "oct" || month == "dec") {
        cout << 31;
    } else if (month == "april" || month == "june" || month == "sept" || month == "nov") {
        cout << 30;
    } else { cout << 28; }
}

void q13() {
    for (int i = 9; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << i;
        }
        cout << endl;
    }
}

int main() {
    q3();
    return 0;
}