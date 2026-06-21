#include <string>
#include <iostream>
#include <variant>
#include <optional>
#include <vector>

struct Logger {
    void info(const std::string& msg) {
        std::cout << "[INFO] " << msg << '\n';
    }

    void error(const std::string& msg) {
        std::cout << "[ERR ] " << msg << '\n';
    }
};

struct CardPayment {
    std::string cardId;
};

struct BankTransfer {
    std::string iban;
};

using PaymentMethod = std::variant<CardPayment, BankTransfer>;

struct Order {
    int id;
    double total;
    PaymentMethod payment;
};

class PaymentGateway {
public:
    bool charge(const Order& order) {
        if (order.total <= 0)
            return false;

        return true;
    }
};

class OrderService {
public:
    OrderService(Logger* log, PaymentGateway* gateway)
        : log(log), gateway(gateway) { //no checks for nullptr
    }

    bool process(Order order) {
        try {
            if (order.total == 0)
                order.total = loadDefaultTotal();

            if (!gateway->charge(order)) {
                log->error("Payment failed for order " + std::to_string(order.id));
                return false;
            }

            processedIds.push_back(order.id);
            lastProcessed = order.id;
            log->info("Processed order " + std::to_string(order.id));
            return true;
        }
        catch (...) { // bad practice
            return false; //no error logging
        }
    }

    std::optional<int> getLastProcessed() const {
        return lastProcessed;
    }

private:
    double loadDefaultTotal() const {
        return 49.99;
    }

    Logger* log; //Logger&
    PaymentGateway* gateway; //PaymentGateway&

    std::vector<int> processedIds;
    std::optional<int> lastProcessed;
};

int main() {
    Logger logger;
    PaymentGateway gateway;
    OrderService service(&logger, &gateway);

    Order o1{ 1, 0, CardPayment{"card-123"} };
    Order o2{ 2, -5, BankTransfer{"BG00TEST0000000000"} };

    service.process(o1);
    service.process(o2);

    //if (service.getLastProcessed())
    std::cout << "last=" << *service.getLastProcessed() << '\n';
}