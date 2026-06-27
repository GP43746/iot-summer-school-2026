import os

def count_ino_files():
    ino_count = 0
    # Walk through all directories and files from the root level down
    for root, dirs, files in os.walk('.'):
        # Correctly isolate folder names to skip actual hidden ones like .git or .github
        # Modifying dirs in-place prevents os.walk from diving into them
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        
        for file in files:
            if file.endswith('.ino'):
                ino_count += 1
                print(f"Found Arduino Sketch: {os.path.join(root, file)}")
                
    print("\n" + "="*30)
    print(f"TOTAL ARDUINO (.ino) FILES DETECTED: {ino_count}")
    print("="*30)

if __name__ == "__main__":
    count_ino_files()