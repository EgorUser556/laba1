#include<iostream>
#include<locale>
#include<string>
#include<conio.h>
#include<fstream>
#include <Windows.h>
#include<iomanip> 
#include <cstdlib>

using namespace std;

void enterWelcomeText();

void copyFileContent(const string& sourceFile, const string& destinationFile) {
    ifstream inputFile(sourceFile);
    ofstream outputFile(destinationFile, ios::app);

    if (!inputFile.is_open()) {
        cout << "Ошибка открытия исходного файла!" << endl;
        return;
    }
    if (!outputFile.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        outputFile << line << " 0" << endl;
    }

    inputFile.close();
    outputFile.close();
    ofstream file("adminFiles.txt", ios::trunc);
    file.close();
}

void displayRequests() {
    ifstream file("adminFiles.txt");

    cout << "Заявки на регистрацию:" << endl;
    cout << left << setw(20) << "Логин" << setw(30) << "Пароль" << endl;
    cout << string(50, '-') << endl;

    string login, password;
    while (file >> login >> password) {
        cout << setw(20) << login << setw(30) << password << endl;
    }

    file.close();

    int acceptRequests;
    cout << "\nВыберите действие:\n\n1 - принять все\n\n2 - отклонить все";
    cin >> acceptRequests;
    while (acceptRequests != 1 && acceptRequests != 2) {
        cout << "\nПожалуйста, повторите попытку\n";
        cin >> acceptRequests;
    }
    switch (acceptRequests) {
    case 1:
        copyFileContent("adminFiles.txt", "users.txt");
        break;
    case 2:
        ofstream file("adminFiles.txt", ios::trunc);
        file.close();
        break;
    }
}

struct User {
    string login;
    string password;
    int role; // 1 - админ, 0 - пользователь
};

void displayUsers() {
    ifstream file("users.txt");
    setlocale(LC_ALL, "Russian");

    cout << "Все пользователи:" << endl;
    cout << left << setw(20) << "Логин" << setw(30) << "Пароль" << setw(20) << "Роль" << endl;
    cout << string(70, '-') << endl;

    User allUsers;
    while (file >> allUsers.login >> allUsers.password >> allUsers.role) {
        cout << setw(20) << allUsers.login << setw(30) << allUsers.password << setw(20) << allUsers.role << endl;
    }

    file.close();

}

struct Product {
    string name;
    string brand;
    double weight;  // Вес товара (в килограммах или граммах)
    string flavor;
    double price;   // Цена товара в BYN
};

// Функция для отображения списка товаров
void displayProducts() {

    ifstream file("goods.txt");
    setlocale(LC_ALL, "");

    // Выводим заголовки для таблицы
    cout << left << setw(30) << "Название" << setw(20) << "Бренд" << setw(10) << "Вес (кг)"
        << setw(15) << "Вкус" << setw(10) << "Цена (BYN)" << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;

    // Считываем товары и выводим их в таблицу
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



void adminPanel() {
    system("cls");
    int adminChoise;
    cout << "Добро пожаловать, администратор!\n Доступны следующие действия: \n";
    cout << "\n\n1 - Просмотреть список зарегистрированных пользователей";
    cout << "\n\n2 - Просмотреть заявки на регистрацию";
    cout << "\n\n3 - Перейти к списку товаров";
    cout << "\n\n4 - Выход\n";

    cin >> adminChoise;
    while (adminChoise < 1 || adminChoise > 4) {
        cout << "\nНекорректный запрос. Повторите попытку";
        cin >> adminChoise;
    }

    switch (adminChoise) {
    case 1:
        displayUsers();
        break;
    case 2:
        displayRequests();
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
    int userChoise;
    cout << "Добро пожаловать, пользователь!\n Доступны следующие действия: \n";
    cout << "\n\n1 - Поиск определенного товара по имени";
    cout << "\n\n2 - Поиск определенного товара по бренду";
    cout << "\n\n3 - Помощь с выбором товара по целям";
    cout << "\n\n4 - Выход\n";

    cin >> userChoise;
    while (userChoise < 1 || userChoise > 4) {
        cout << "\nНекорректный запрос. Повторите попытку";
        cin >> userChoise;
    }

    switch (userChoise) {
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:
        system("cls");

        break;
    }

}

void addToAdminFiles(const string& login, const string& password) {
    ofstream file("adminFiles.txt", ios::app); // Открываем файл в режиме добавления
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    file << login << " " << password << endl;
    file.close();
}

//string login, password;

void registration() {
    User userReg;
    string login, password, password_check;
    system("cls");
    cout << "Отлично! Необходимо ввести данные, необходимые для регистрации";
    cout << "\nВаш логин: "; cin >> login;
    cout << "\nВаш пароль: "; cin >> password;
    cout << "\nПовтор пароля: "; cin >> password_check;
    while (password != password_check) {
        cout << "\nВведенные пароли не совпадают.\nПожалуйста, попробуйте снова";
        cout << "\nВаш пароль: "; cin >> password;
        cout << "\nПовтор пароля: "; cin >> password_check;
    }

    addToAdminFiles(login, password);
    cout << "Заявка на авторизацию отправлена.\nОжидайте одобрения администратора";
    Sleep(2000);
    //тут надо намутить, чтобы администратору в отдельный файлик отправлялась вся эта лабуда
    enterWelcomeText();
}

void enterWelcomeText() {
    system("cls");
    string text = "Электронный магазин спортивного питания";
    int width = text.length() + 6;

    cout << string(width, '#') << endl;
    cout << "  " << text << endl;
    cout << string(width, '#') << endl << endl << endl << endl;
    int choise;
    cout << "Введите число в зависимости от действия" << endl;
    cout << "    1 - Впервые на сайте? Регистрация" << endl;
    cout << "    2 - Авторизация" << endl;
    cin >> choise;
    while (choise != 1 && choise != 2) {
        cout << "Некорректный ответ. Попробуйте еще";
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
        cout << "\nЛогин: ";
        cin >> currentUser.login;

        cout << "\nПароль: ";
        getHiddenInput(currentUser.password);

        cout << "\nРоль (1 - админ, 0 - пользователь): ";
        cin >> currentUser.role;

        // Проверка корректности роли
        while (currentUser.role != 1 && currentUser.role != 0) {
            cout << "Некорректный ответ. Попробуйте еще";
            cout << "\nРоль (1 - админ, 0 - пользователь): ";
            cin >> currentUser.role;
        }

        // Проверка авторизации
        if (authorizationCheck(currentUser)) {

            // Переходим в панель в зависимости от роли
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
            cout << "Пожалуйста, попробуйте снова";
            authorization();
        }
    }
}


void main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    enterWelcomeText();
    authorization();
}