#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sys/ptrace.h>
#include <stdlib.h>

void anti_debug() { if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) exit(0); }

int main(int argc, char* argv[]) {
    anti_debug();

    if (argc < 2) {
        std::cout << "Использование: ./fortress_engine <файл.c0ck>" << std::endl;
        return 1;
    }

    std::string input_filename = argv[1];
    std::ifstream file(input_filename, std::ios::binary);
    if (!file) {
        std::cerr << "[-] Файл не найден!" << std::endl;
        return 1;
    }

    
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)), 
                                       std::istreambuf_iterator<char>());

    
    if (buffer.size() < 4 || buffer[0] != 'C' || buffer[1] != '0' || buffer[2] != 'C' || buffer[3] != 'K') {
        std::cerr << "[-] Ошибка: Файл поврежден или это не .c0ck" << std::endl;
        return 1;
    }

    
    unsigned char key = 0xAA;
    for (size_t i = 4; i < buffer.size(); i++) {
        buffer[i] ^= key;
    }

    
    std::string output_filename = "decrypted_" + input_filename.substr(0, input_filename.find_last_of('.'));
    std::ofstream outfile(output_filename, std::ios::binary);
    
    if (outfile.is_open()) {
        outfile.write(reinterpret_cast<char*>(&buffer[4]), buffer.size() - 4);
        outfile.close();
        std::cout << "[+] Файл расшифрован успешно!" << std::endl;
        std::cout << "[+] Создан файл: " << output_filename << std::endl;
    } else {
        std::cerr << "[-] Ошибка при создании файла." << std::endl;
    }

    return 0;
}
