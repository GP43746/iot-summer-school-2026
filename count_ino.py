import os

def count_ino_files():
    ino_count = 0
    for root, dirs, files in os.walk('.'):
        if any(part.startswith('.') for part in root.split(os.sep)):
            continue
        for file in files:
            if file.endswith('.ino'):
                ino_count += 1
                print(f"Found Arduino Sketch: {os.path.join(root, file)}")
                
    print("\n" + "="*30)
    print(f"TOTAL ARDUINO (.ino) FILES DETECTED: {ino_count}")
    print("="*30)

if __name__ == "__main__":
    count_ino_files()