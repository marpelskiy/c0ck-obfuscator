л#!/bin/bash

echo "[*] Компиляция движка fortress_engine..."
g++ -O3 -s -fno-stack-protector -o fortress_engine fortress.cpp

if [ $? -eq 0 ]; then
    echo "[+] Движок успешно собран!"
    echo "------------------------------------------"
    echo "Закиньте файл в папку и введите название файла:"
    read filename

    if [ -f "$filename" ]; then
        echo "обфусцирую..."
        python3 protect.py "$filename"
        echo "готов!"
        echo "[!] Файл готов к использованию: ${filename%.*}.c0ck"
    else
        echo "[-] Ошибка: Файл '$filename' не найден в текущей папке!"
    fi
else
    echo "[-] Ошибка компиляции!"
fi
