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
    Command(double const& value) : value(value) {
    }
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
    std::queue<std::unique_ptr<Command> > commands;

  public:
    void addCommand(std::unique_ptr<Command> command) {
      commands.push(std::move(command));
    }

    double executeCommands(double arg) {
      while (!commands.empty()) {
        arg = commands.front()->execute(arg);
        commands.pop();
      }
      return arg;
    }

    void revCommands(int n) {
      for (int i = 0; i < n && !commands.empty(); i++) {
        commands.pop();
      }
    }
};

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
  } else {
    throw std::invalid_argument("Invalid command");
  }
  return istrm;
}

int main() {
  Calculator calculator;
  Command* command;
  std::string commandType;
  double value;
  while (std::cin >> commandType >> value) {
    if (commandType == "ADD") {
      command = new AddCommand(value);
    } else if (commandType == "SUB") {
      command = new SubCommand(value);
    } else if (commandType == "MUL") {
      command = new MulCommand(value);
    } else if (commandType == "DIV") {
      command = new DivCommand(value);
    } else {
      //std::cin.setstate(std::ios_base::failbit)
    }
    calculator.addCommand(std::unique_ptr<Command>(command));
  }

}
