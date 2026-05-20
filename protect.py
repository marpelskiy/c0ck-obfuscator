import sys

def protect_file(input_file, key=0xAA):
    magic_header = b'C0CK' # 
    
    try:
        with open(input_file, 'rb') as f:
            data = f.read()
        
        
        encrypted = magic_header + bytes([b ^ key for b in data])
        
        output_file = input_file.rsplit('.', 1)[0] + '.c0ck'
        
        with open(output_file, 'wb') as f:
            f.write(encrypted)
        print(f"[+] Файл '{input_file}' запакован в '{output_file}'")
    except Exception as e:
        print(f"[-] Ошибка: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Использование: python protect.py <файл>")
    else:
        protect_file(sys.argv[1])
