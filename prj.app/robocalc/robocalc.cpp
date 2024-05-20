//
// Created by Егор Федюнин on 13.05.2024.
//
#include <queue>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <memory>

class Command {
  public:
    double value;
    Command(double const& value) : value(value) {}
    virtual ~Command() = default;
    virtual double execute(double arg) = 0;
    std::istream& readFrom(std::istream& istrm) noexcept;
};

class AddCommand : public Command {
  public:
    AddCommand(const double& value) : Command(value) {
    }
    double execute(double arg) override {
      return arg + value;
    }
};

class SubCommand : public Command {
  public:
    SubCommand(double value) : Command(value) {
    }
    double execute(double arg) override {
      return arg - value;
    }
};

class MulCommand : public Command {
  public:
    MulCommand(double value) : Command(value) {
    }
    double execute(double arg) override {
      return arg * value;
    }
};

class DivCommand : public Command {
  public:
    DivCommand(double value) : Command(value) {
    }
    double execute(double arg) override {
      if (value != 0) {
        return arg / value;
      } else {
        throw std::invalid_argument("Division by zero");
      }
    }
};

class Calculator {
  private:
  std::vector<std::unique_ptr<Command>> commands;

  public:
  void addCommand(std::unique_ptr<Command> command) {
    commands.push_back(std::move(command));
  }

  double executeCommands(double arg) {
    for (auto& command : commands) {
      arg = command->execute(arg);
    }
    commands.clear(); // Clear the commands after executing them
    return arg;
  }

  void revCommands(int n) {
    if (n <= commands.size()) {
      commands.erase(commands.end() - n, commands.end());
    } else {
      throw std::invalid_argument("Not enough commands to reverse");
    }
  }
};

/*
std::istream& Command::readFrom(std::istream& istrm) noexcept {
  std::string command;
  std::string value;
  istrm >> command >> value;
  if (command == "add") {
    *this =  AddCommand(std::stod(value));
  } else if (command == "sub") {
    *this = SubCommand(std::stod(value));
  } else if (command == "mul") {
    *this = MulCommand(std::stod(value));
  } else if (command == "div") {
    *this = DivCommand(std::stod(value));
  }
  else {
    throw std::invalid_argument("Invalid command");
  }
  return istrm;
}*/

int main() {
  Calculator calculator;
  std::string commandType;
  double value;
  while (std::cin >> commandType) {
    if (commandType == "ADD") {
      std::cin >> value;
      calculator.addCommand(std::make_unique<AddCommand>(value));
    } else if (commandType == "SUB") {
      std::cin >> value;
      calculator.addCommand(std::make_unique<SubCommand>(value));
    } else if (commandType == "MUL") {
      std::cin >> value;
      calculator.addCommand(std::make_unique<MulCommand>(value));
    } else if (commandType == "DIV") {
      std::cin >> value;
      calculator.addCommand(std::make_unique<DivCommand>(value));
    } else if (commandType == "REV") {
      std::cin >> value;
      calculator.revCommands(static_cast<int>(value));
    } else if (commandType == "OUT") {
      std::cin >> value;
      std::cout << calculator.executeCommands(value) << std::endl;
    } else {
      std::cout << "INCORRECT INPUT" << std::endl;
      std::cin.setstate(std::ios_base::failbit);
    }
  }
}
