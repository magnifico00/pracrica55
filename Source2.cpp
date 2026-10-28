#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// === ГЕНЕРАТОР ДАННЫХ ===
class CardDataGenerator {
public:
    static std::string generateCardNumber() {
        std::string num = "";
        for (int i = 0; i < 16; ++i) num += std::to_string(rand() % 10);
        return num;
    }
    static std::string generateCVC() {
        std::string cvc = "";
        for (int i = 0; i < 3; ++i) cvc += std::to_string(rand() % 10);
        return cvc;
    }
};

// === БАНКОВСКИЕ КАРТЫ ===
class BasePlasticCard {
protected:
    std::string ownerName;
public:
    BasePlasticCard(std::string name) : ownerName(name) {}
};

class BaseBankingCard : public BasePlasticCard {
public:
    std::string cardNumber, cvc, pinCode;
    double deposit;

    BaseBankingCard(std::string name, std::string pin, double startDeposit)
        : BasePlasticCard(name), pinCode(pin) {
        cardNumber = CardDataGenerator::generateCardNumber();
        cvc = CardDataGenerator::generateCVC();
        deposit = (startDeposit < 0) ? 0 : startDeposit; // проверка на < 0
    }
};

class DebitCard : public BaseBankingCard {
public:
    DebitCard(std::string name, std::string pin) : BaseBankingCard(name, pin, 10000.0) {}

    void setDeposit(double amount) {
        if (amount >= 0) deposit = amount;
        else std::cout << "Ошибка: Баланс не может быть меньше нуля!\n";
    }
};

class CreditCard : public BaseBankingCard {
public:
    CreditCard(std::string name, std::string pin) : BaseBankingCard(name, pin, 100000.0) {}

    void Service() {
        double fee = deposit * 0.01;
        deposit -= fee;
        std::cout << "Снято за обслуживание: " << fee << "р. Баланс: " << deposit << "р.\n";
    }
};

// === ПРОПУСКИ И БИЛЕТЫ ===
class BasePassKey {
protected:
    std::string id, ownerName, organization;
public:
    BasePassKey(std::string passId, std::string name, std::string org)
        : id(passId), ownerName(name), organization(org) {
    }

    virtual void Pass() {
        std::cout << "Обработка прохода: " << ownerName << "...\n";
    }
};

class AccessKey : public BasePassKey {
public:
    AccessKey(std::string passId, std::string name, std::string org) : BasePassKey(passId, name, org) {}

    void Pass() override {
        std::cout << "Сотрудник " << ownerName << " (" << organization << ") запросил доступ.\n";
        std::time_t now = std::time(nullptr);
        std::cout << "Passed at: " << std::ctime(&now); // вывод текущего времени
    }
};

class Ticket : public BasePassKey {
private:
    double ticketDeposit;
public:
    Ticket(std::string passId, std::string name, std::string org, double money)
        : BasePassKey(passId, name, org), ticketDeposit(money) {
    }

    void Pass() override {
        if (ticketDeposit >= 75) {
            ticketDeposit -= 75;
            std::cout << "Проход разрешен. Списано 75 ед. Остаток: " << ticketDeposit << "\n";
        }
        else {
            std::cout << "Отказ! Недостаточно средств. Баланс: " << ticketDeposit << "\n";
        }
    }
};

// === ПРОВЕРКА РАБОТЫ ===
int main() {
    std::setlocale(LC_ALL, "Russian");
    std::srand(std::time(0));

    std::cout << "--- БАНКОВСКИЕ КАРТЫ ---\n";
    DebitCard debit("Иванов И.И.", "1234");
    std::cout << "Дебетка создана. Номер: " << debit.cardNumber << " | Баланс: " << debit.deposit << "р.\n";

    CreditCard credit("Петров П.П.", "0000");
    credit.Service();

    std::cout << "\n--- ПРОПУСКИ ---\n";
    AccessKey pass("ID-99", "Алексеев А.А.", "ТехноПром");
    pass.Pass();

    std::cout << "\n--- БИЛЕТЫ ---\n";
    Ticket ticket("T-1", "Пассажир", "Метро", 150.0);
    ticket.Pass(); // -75
    ticket.Pass(); // -75
    ticket.Pass(); // Отказ
}
