# Script helpful for windows users, to copy the libmysql.dll file 
# to the build directory after creating build project.

import os
import shutil

def copy_libmysql_dll(source_path, destination_path):
    try:
        # Ensure the source file exists
        if not os.path.isfile(source_path):
            print(f"Error: Source file does not exist at {source_path}")
            return

        # Ensure the destination directory exists; if not, create it
        if not os.path.exists(destination_path):
            os.makedirs(destination_path)
            print(f"Created destination directory: {destination_path}")

        # Copy the file to the destination
        shutil.copy(source_path, destination_path)
        print(f"File copied successfully to {destination_path}")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    # Source and destination paths
    source_file = r"C:\Program Files\MySQL\MySQL Server 8.0\lib\libmysql.dll"
    destination_dir = r".\build\bin"

    copy_libmysql_dll(source_file, destination_dir)