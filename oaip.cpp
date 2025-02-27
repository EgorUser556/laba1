#include<iostream>
#include<locale>
#include<string>
#include<conio.h>
#include<fstream>
#include <Windows.h>
#include<iomanip> 
#include <cstdlib>;

using namespace std;

void enterWelcomeText();

void displayRegistrationRequests() {
    ifstream file("adminFiles.txt");
    if (!file.is_open()) {
        cout << "������ �������� ����� � ��������!" << endl;
        return;
    }

    cout << "������ �� �����������:" << endl;
    cout << left << setw(20) << "�����" << setw(30) << "������" << endl;
    cout << string(50, '-') << endl;

    string login, password;
    while (file >> login >> password) {
        cout << setw(20) << login << setw(30) << password << endl;
    }

    file.close();
}

void workWithUsers() {

}

struct Product {
    string name;
    string brand;
    double weight;  // ��� ������ (� ����������� ��� �������)
    string flavor;
    double price;   // ���� ������ � BYN
};

// ������� ��� ����������� ������ �������
void displayProducts() {

    ifstream file("goods.txt");
    setlocale(LC_ALL, "");
    if (!file.is_open()) {
        cout << "������ �������� ����� � ��������!" << endl;
        return;
    }

    // ������� ��������� ��� �������
    cout << left << setw(30) << "��������" << setw(20) << "�����" << setw(10) << "��� (��)"
        << setw(15) << "����" << setw(10) << "���� (BYN)" << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;

    // ��������� ������ � ������� �� � �������
    Product product;
    while (file >> product.name >> product.brand >> product.weight >> product.flavor >> product.price) {
        cout << left << setw(30) << product.name
            << setw(20) << product.brand
            << setw(10) << product.weight
            << setw(15) << product.flavor
            << setw(10) << fixed << setprecision(2) << product.price << endl;
    }

    file.close();
}

struct User {
    string login;
    string password;
    int role; // 1 - �����, 0 - ������������
};

void adminPanel() {
    system("cls");
    int adminChoise;
    cout << "����� ����������, �������������!\n �������� ��������� ��������: \n";
    cout << "\n\n1 - ����������� ������ ������������������ �������������";
    cout << "\n\n2 - ����������� ������ �� �����������";
    cout << "\n\n3 - ������� � ������ �������";
    cout << "\n\n4 - �����\n";

    cin >> adminChoise;
    while (adminChoise != 1 && adminChoise != 2 && adminChoise != 3 && adminChoise != 4) {
        cout << "\n������������ ������. ��������� �������";
        cin >> adminChoise;
    }

    switch (adminChoise) {
    case 1:
        break;
    case 2:
        displayRegistrationRequests();
        break;
    case 3:
        displayProducts();
        break;

    case 4:
        system("cls");
        enterWelcomeText();
        break;
    }
}

void userPanel() {

    system("cls");
    cout << "����� ����������, ������������!\n �������� ��������� ��������: \n";
    cout << "\n\n1 - ����� ������������� ������ �� �����";
    cout << "\n\n2 - ����� ������������� ������ �� ������";
    cout << "\n\n3 - ������ � ������� ������ �� �����";

}

void addToAdminFiles() {
    ofstream file("adminFiles.txt");

}

string login, password;
int role;

void registration() {
    User userReg;
    string login, password, password_check;
    system("cls");
    cout << "�������! ���������� ������ ������, ����������� ��� �����������";
    cout << "\n��� �����: "; cin >> login;
    cout << "\n��� ������: "; cin >> password;
    cout << "\n������ ������: "; cin >> password_check;
    while (password != password_check) {
        cout << "\n��������� ������ �� ���������.\n����������, ���������� �����";
        cout << "\n��� ������: "; cin >> password;
        cout << "\n������ ������: "; cin >> password_check;
    }

    addToAdminFiles();
    cout << "������ �� ����������� ����������.\n�������� ��������� ��������������";
    Sleep(2000);
    //��� ���� ��������, ����� �������������� � ��������� ������ ������������ ��� ��� ������
    enterWelcomeText();
}

void enterWelcomeText() {
    system("cls");
    string text = "����������� ������� ����������� �������";
    int width = text.length() + 6;

    cout << string(width, '#') << endl;
    cout << "  " << text << endl;
    cout << string(width, '#') << endl << endl << endl << endl;
    int choise;
    cout << "������� ����� � ����������� �� ��������" << endl;
    cout << "    1 - ������� �� �����? �����������" << endl;
    cout << "    2 - �����������" << endl;
    cin >> choise;
    while (choise != 1 && choise != 2) {
        cout << "������������ �����. ���������� ���";
        cin >> choise;
    }
    if (choise == 1) {
        registration();
    }
}

void getHiddenInput(string& input) {
    char ch;
    int length = 0;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (length > 0) {
                input[length - 1] = '\0';
                length--;
                cout << "\b \b";
            }
        }
        else {
            input += ' ';
            input[length] = ch;
            length++;
            cout << '*';
        }
    }
    cout << endl;
}

bool authorizationCheck(const User& currentUser) {
    ifstream file("users.txt");

    /*if (!file.is_open()) {
        cout << "������ �������� ����� users.txt" << endl;
        return false;
    }*/

    User user;

    while (file >> user.login >> user.password >> user.role) {

        if (user.login == currentUser.login &&
            user.password == currentUser.password &&
            user.role == currentUser.role) {

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void authorization() {
    User currentUser;

    while (true) {
        cout << "\n�����: ";
        cin >> currentUser.login;

        cout << "\n������: ";
        getHiddenInput(currentUser.password);

        cout << "\n���� (1 - �����, 0 - ������������): ";
        cin >> currentUser.role;

        // �������� ������������ ����
        while (currentUser.role != 1 && currentUser.role != 0) {
            cout << "������������ �����. ���������� ���";
            cout << "\n���� (1 - �����, 0 - ������������): ";
            cin >> currentUser.role;
        }

        // �������� �����������
        if (authorizationCheck(currentUser)) {

            // ��������� � ������ � ����������� �� ����
            if (currentUser.role == 1) {
                adminPanel();
                break;
            }
            else {
                userPanel();
                break;
            }
        }
        else {
            cout << "����������, ���������� �����";
            authorization();
        }
    }
}


void main() {
    setlocale(LC_ALL, "Russian");
    enterWelcomeText();
    authorization();
}