import sys
import os
import re

def main():
    depth_path_dict = {}
    if(len(sys.argv) != 2):
        print("please put the file as an argument:)")
        exit(1)
        
    input_file = sys.argv[1]
    if(not os.path.exists(input_file)):
        print("file does not exist")
        exit(1)

    with open(input_file, "r") as input_file:
        content = input_file.read()
    
    regex_pattern = "(?<=\$ )(?:cd (.*?)[\n\r])|(?:ls[\r\n](.*?)(?:(?=\$)|(?:$(?![\r\n]))))"

    matches = re.findall(regex_pattern, content, re.MULTILINE | re.IGNORECASE | re.DOTALL)
    cur_dir = []
    for match in matches:
        print(match)
    
    print("-------------------------------")
    # exit(1)
    for match in matches:
        dir_dirtrav, file_or_dir = match
        #if it is a directory or directory traversal
        if(dir_dirtrav):
            # three cases:
            # a Directory Traversal Backwards 
            if(dir_dirtrav == ".."):
                cur_dir.pop()
            # b. Go to root
            elif(dir_dirtrav[0] == "/"):
                if(len(dir_dirtrav) == 1):
                    cur_dir = []
                else:
                    cur_dir = []
                    dir_list = dir_dirtrav.split("/")[1:]
                    for dir in dir_list: 
                        cur_dir.append(dir + "/")
            # c. Directory
            else:
                if(len(dir_dirtrav) == 1):
                    cur_dir.append(dir_dirtrav + "/")
                else:
                    dir_list = dir_dirtrav.split("/")
                    for dir in dir_list:
                        cur_dir.append(dir + "/")
        else:
            file_dir_list = file_or_dir.strip().split("\n")
            for file_dir in file_dir_list:
                file_dir = file_dir.split(" ")
                typing = file_dir[0]
                if(not (typing == "dir")):
                    # print("cur_dir : {0}".format(cur_dir))
                    #We know it is a file
                    file_name = file_dir[1]
                    file_path = "/" + "".join(cur_dir) + file_name
                    depth_path_dict.setdefault(len(cur_dir) + 1, set()).add(file_path)

    # Initialize variables
    total_files = 0
    total_depth = 0

    # Find the deepest depth
    deepest = max(depth_path_dict)

    # Get the path at the deepest level
    deepest_file = next(iter(depth_path_dict[deepest]))

    # Calculate total files and total depth
    for depth, paths in depth_path_dict.items():
        num_files_at_depth = len(paths)
        total_files += num_files_at_depth
        total_depth += num_files_at_depth * depth

    # Calculate average depth
    avg_depth = total_depth / total_files

    print("{0},\"{1}\",{2}".format(total_files, deepest_file, avg_depth))

if __name__ == "__main__":
    main()

