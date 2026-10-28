//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include <chrono>
//#include <Windows.h> // Необходмо для корректного ввода кириллицы в консоли Windows
//
//// ==========================================
//// СЕРВИСНЫЕ ИНСТРУМЕНТЫ (Работа Руководителя)
//// ==========================================
//
//// Класс-инструмент для генерации случайных данных карт
//class CardGenerator
//{
//public:
//    // 1) Генератор случайного 16-значного номера карты
//    static std::string GenerateCardNumber()
//    {
//        std::string number = "";
//        for (int i = 0; i < 16; i++)
//        {
//            number += std::to_string(rand() % 10);
//        }
//        return number;
//    }
//
//    // 2) Генератор трехзначного номера - CVC-кода
//    static std::string GenerateCVC()
//    {
//        std::string cvc = "";
//        for (int i = 0; i < 3; i++)
//        {
//            cvc += std::to_string(rand() % 10);
//        }
//        return cvc;
//    }
//};
//
//// Принцип АБСТРАКЦИИ: базовый абстрактный класс для всех пластиковых карт в системе
//class BasePlasticCard
//{
//protected:
//    std::string cardNumber; // Сюда также может записываться ID пропуска
//    std::string holderName;  // ФИО владельца
//
//public:
//    BasePlasticCard(std::string name, std::string number)
//    {
//        holderName = name;
//        cardNumber = number;
//    }
//
//    virtual ~BasePlasticCard() {} // Виртуальный деструктор для корректного удаления наследников
//};
//
//
//// ==========================================
//// ВАРИАНТ 1: БАНКОВСКИЕ КАРТЫ
//// ==========================================
//
//// Базовый класс банковских карт
//class BaseBankingCard : public BasePlasticCard
//{
//protected:
//    // Принцип ИНКАПСУЛЯЦИИ: Скрываем данные, чтобы защитить их от прямого изменения извне
//    std::string cvc;
//    std::string pinCode;
//    float deposit;
//
//public:
//    BaseBankingCard(std::string name, std::string number, std::string cardCvc, std::string pin, float initialDeposit)
//        : BasePlasticCard(name, number)
//    {
//        cvc = cardCvc;
//        pinCode = pin;
//
//        // Логика защиты: депозит не может быть установлен на значение меньше нуля
//        if (initialDeposit < 0)
//        {
//            deposit = 0;
//        }
//        else
//        {
//            deposit = initialDeposit;
//        }
//    }
//
//    // Геттеры для безопасного вывода данных на консоль без нарушения инкапсуляции
//    float GetDeposit() { return deposit; }
//    std::string GetHolderName() { return holderName; }
//    std::string GetNumber() { return cardNumber; }
//};
//
//
//// ==========================================
//// ВАРИАНТ 2: ДЕБЕТОВАЯ И КРЕДИТНАЯ КАРТЫ
//// ==========================================
//
//// Класс Дебетовой карты
//class DebitCard : public BaseBankingCard
//{
//public:
//    // Конструктор использует статический класс-генератор и устанавливает начальный депозит 10000р.
//    DebitCard(std::string name)
//        : BaseBankingCard(name, CardGenerator::GenerateCardNumber(), CardGenerator::GenerateCVC(), "0000", 10000.0f) {
//    }
//};
//
//// Класс Кредитной карты
//class CreditCard : public BaseBankingCard
//{
//public:
//    // Конструктор создаёт новую карту с начальным депозитом в 100000р.
//    CreditCard(std::string name)
//        : BaseBankingCard(name, CardGenerator::GenerateCardNumber(), CardGenerator::GenerateCVC(), "1111", 100000.0f) {
//    }
//
//    // Функция снятия процента за обслуживание
//    void Service()
//    {
//        float serviceFee = 500.0f; // Сумма платы за обслуживание
//        deposit -= serviceFee;
//        std::cout << "Плата за обслуживание (" << serviceFee << "р.) списана с карты: " << cardNumber << std::endl;
//    }
//};
//
//
//// ==========================================
//// ВАРИАНТ 3: БАЗОВЫЙ КЛАСС ПРОПУСКОВ
//// ==========================================
//
//class BasePassKey : public BasePlasticCard
//{
//protected:
//    std::string organization; // Наименование организации
//
//public:
//    // Передаем персональный идентификатор владельца (id) в качестве номера карты базового класса
//    BasePassKey(std::string name, std::string id, std::string org)
//        : BasePlasticCard(name, id)
//    {
//        organization = org;
//    }
//
//    // Виртуальная функция-заготовка для использования пропуска
//    virtual void Pass()
//    {
//        std::cout << "Пропуск проверен в организации: " << organization << std::endl;
//    }
//};
//
//
//// ==========================================
//// ВАРИАНТ 4: КЛЮЧ ДОСТУПА И БИЛЕТ
//// ==========================================
//
//// Класс Ключа доступа
//class AccessKey : public BasePassKey
//{
//public:
//    AccessKey(std::string name, std::string id, std::string org)
//        : BasePassKey(name, id, org) {
//    }
//
//    // Принцип ПОЛИМОРФИЗМА: переопределяем функцию Pass с фиксацией времени
//    void Pass() override
//    {
//        auto time = std::chrono::system_clock::now(); // Фиксирует текущее время
//        std::time_t convertedTime = std::chrono::system_clock::to_time_t(time);
//
//        std::cout << "Сотрудник " << holderName << " совершил вход в " << organization << std::endl;
//
//        char timeString[26];
//        ctime_s(timeString, sizeof(timeString), &convertedTime);
//        std::cout << "Passed at: " << timeString;
//    }
//};
//
//// Класс Билета
//class Ticket : public BasePassKey
//{
//private:
//    float deposit; // Переменная-депозит для поездок/единиц
//
//public:
//    Ticket(std::string name, std::string id, std::string org, float initialDeposit)
//        : BasePassKey(name, id, org)
//    {
//        deposit = initialDeposit;
//    }
//
//    // Принцип ПОЛИМОРФИЗМА: при вызове Pass с депозита списывается 75 единиц
//    void Pass() override
//    {
//        if (deposit >= 75.0f)
//        {
//            deposit -= 75.0f;
//            std::cout << "Билет [" << cardNumber << "]. Проход выполнен. Списано 75 ед. Остаток: " << deposit << std::endl;
//        }
//        else
//        {
//            std::cout << "Билет [" << cardNumber << "]. Отказ в проходе! Недостаточно средств. Баланс: " << deposit << std::endl;
//        }
//    }
//};
//
//
//// ==========================================
//// ТОЧКА ВХОДА СИСТЕМЫ (ГЛАВНЫЙ ФАЙЛ)
//// ==========================================
//
//int main()
//{
//    // Настройка кодировки для корректного ввода и вывода кириллицы в консоли Windows
//    SetConsoleCP(1251);
//    SetConsoleOutputCP(1251);
//    srand(static_cast<unsigned int>(std::time(nullptr)));
//
//    std::string userFullName;
//    std::cout << "Введите имя и фамилию владельца карт: ";
//    std::getline(std::cin, userFullName); // Считываем всю строку (включая пробел между именем и фамилией)
//    std::cout << std::endl;
//
//    std::cout << "====== ПРОВЕРКА РАБОТЫ БАНКОВСКИХ КАРТ ======" << std::endl;
//
//    // Тестируем дебетовую карту с введенным именем
//    DebitCard myDebit(userFullName);
//    std::cout << "Дебетовая карта владельца: " << myDebit.GetHolderName() << std::endl;
//    std::cout << "Номер: " << myDebit.GetNumber() << " | Баланс: " << myDebit.GetDeposit() << "р." << std::endl;
//    std::cout << "---------------------------------------------" << std::endl;
//
//    // Тестируем кредитную карту с введенным именем
//    CreditCard myCredit(userFullName);
//    std::cout << "Кредитная карта владельца: " << myCredit.GetHolderName() << std::endl;
//    std::cout << "Баланс до обслуживания: " << myCredit.GetDeposit() << "р." << std::endl;
//    myCredit.Service();
//    std::cout << "Баланс после обслуживания: " << myCredit.GetDeposit() << "р." << std::endl;
//    std::cout << std::endl;
//
//
//    std::cout << "====== ПРОВЕРКА РАБОТЫ ПРОПУСКОВ (ПОЛИМОРФИЗМ) ======" << std::endl;
//
//    // Создаем объекты ключа доступа и билета, используя введенное пользователем имя
//    AccessKey officePass(userFullName, "ID-77291", "ЛИМЭ");
//    Ticket metroTicket("Единый Билет (" + userFullName + ")", "TCK-5541", "МосМетро", 150.0f);
//
//    // Демонстрируем полиморфизм при помощи массива указателей на базовый класс BasePassKey
//    BasePassKey* turnstileCheckpoints[2];
//    turnstileCheckpoints[0] = &officePass;
//    turnstileCheckpoints[1] = &metroTicket;
//
//    // Циклом имитируем проход через турникет для разных типов пропусков
//    for (int i = 0; i < 2; i++)
//    {
//        turnstileCheckpoints[i]->Pass(); // Вызывается переопределенный метод конкретного класса
//        std::cout << "---------------------------------------------" << std::endl;
//    }
//
//    // Проверяем реакцию билета на нехватку баланса
//    std::cout << "Повторный проход по билету:" << std::endl;
//    metroTicket.Pass(); // Баланс станет 0
//    std::cout << "Попытка прохода с нулевым балансом:" << std::endl;
//    metroTicket.Pass(); // Должен сработать отказ
//    std::cout << "---------------------------------------------" << std::endl;
//
//    return 0;
//}
