#include <iostream>

#include <fstream>
#include <utility>
#include <vector>

#include "matrix.h"

class Register {
public:
    Register(std::string name, Matrix &matrix) : matrix(matrix), name_(std::move(name)) {

    }

    Matrix &get_matrix() const {
        return matrix;
    }

    std::string get_name() const {
        return name_;
    }

private:
    std::string name_;
    Matrix &matrix;
};


Register &find_register(std::vector<Register> registers, const std::string &name) {
    for (auto &reg: registers) {
        if (reg.get_name() == name) {
            return reg;
        }
    }
}

int main() {
    std::vector<Register> registers;
    std::string command;
    std::cin >> command;
    while (true) {
        if (command == "load") {
            std::string registered;
            std::string filename;
            std::cin >> registered;
            std::cin >> filename;
            std::ifstream in_matrix_file(filename);
            int cols = 0;
            int rows = 0;
            in_matrix_file >> rows;
            in_matrix_file >> cols;
            auto *matrix = new Matrix(rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int value;
                    in_matrix_file >> value;
                    matrix->set(i, j, value);
                }
            }
            std::string symbol = registered.substr(0, 1);
            std::string register_name = registered.substr(1);
            if (symbol == "$") {
                //TODO
            }
            registers.emplace_back(register_name, *matrix);
        } else if (command == "print") {
            std::string registered;
            std::cin >> registered;
            std::string register_name = registered.substr(1);
            Register &reg = find_register(registers, register_name);
            for (int i = 0; i < reg.get_matrix().get_rows(); i++) {
                for (int j = 0; j < reg.get_matrix().get_cols(); j++) {
                    std::cout << reg.get_matrix().get(i, j) << ((j != reg.get_matrix().get_cols()-1) ? " " : "");
                }
                std::cout << std::endl;
            }


        } else if (command == "add") {
            std::string registered1;
            std::cin >> registered1;
            std::string register_name1 = registered1.substr(1);
            std::string registered2;
            std::cin >> registered2;
            std::string register_name2 = registered2.substr(1);
            Register register1 = find_register(registers, register_name1);
            Register register2 = find_register(registers, register_name2);
            try {
                register1.get_matrix() += register2.get_matrix();
            } catch (MatrixException &exception) {
                std::cout << exception.what() << std::endl;
            }
        } else if (command == "mul") {
            std::string registered1;
            std::cin >> registered1;
            std::string register_name1 = registered1.substr(1);
            std::string registered2;
            std::cin >> registered2;
            std::string register_name2 = registered2.substr(1);
            Register register1 = find_register(registers, register_name1);
            Register register2 = find_register(registers, register_name2);
            try {
                register1.get_matrix() *= register2.get_matrix();
            } catch (MatrixException &exception) {
                std::cout << exception.what() << std::endl;
            }
        } else if (command == "elem") {
            std::string registered;
            std::cin >> registered;
            std::string register_name = registered.substr(1);
            Register &reg = find_register(registers, register_name);
            int i, j;
            std::cin >> i >> j;
            try {
                std::cout << reg.get_matrix().get(i, j) << std::endl;
            }
            catch (MatrixException &exception) {
                std::cout << exception.what() << std::endl;
            }
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "sorry, we don't know this command, please enter correct command" << std::endl;
        }
        std::cin >> command;
    }
    return 0;
}
