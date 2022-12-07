from typing import Tuple, Dict, Union, List
from enum import Enum

FILENAME = 'input.txt'


class FileType(Enum):
    Dir = 'dir'
    File = 'file'


class Operation(Enum):
    Cd = 'cd'
    Ls = 'ls'


class Directory:
    # files: Dict[str, int]
    # directories: Dict[str, 'Directory']
    # parent: 
    # name: str
    # size: int

    def __init__(self, name: str = '/', parent = None):
        self.files = {}
        self.directories = {}
        self.name = name
        self.parent = parent
        self.size = 0
    
    def add_file(self, name: str, size: int):
        if name in self.files and self.files[name] == size:
            return

        self.files[name] = size
        self.size += size

    def add_dir(self, name: str) -> 'Directory':
        if name in self.directories:
            return self.directories[name]

        new_dir = Directory(name, self)
        self.directories[name] = new_dir
        return new_dir

    def get_parent(self) -> 'Directory':
        return self.parent
    
    def get_size(self) -> int:
        size_sum = self.size
        for d in self.directories.values():
            size_sum += d.get_size()
        return size_sum

    def __str__(self) -> str:
        return f'''
                <Dir
                    name={self.name}
                    files={self.files.items()}
                    directories={self.directories.items()}
                    parent={None if self.get_parent() is None else self.get_parent().name}
                />
                '''


def parseOperations():
    root_dir = None
    with open(FILENAME, 'r') as f:
        prev_op = None
        curr_dir: Directory = None
        for line in f:
            line = line.strip().split(' ')
            if line[0] == '$':
                # operation
                prev_op = Operation(line[1])
                if prev_op == Operation.Cd:
                    dirname = line[2]
                    if dirname == '..':
                        curr_dir = curr_dir.get_parent()
                    else:
                        if root_dir == None:
                            root_dir = Directory(dirname)
                            curr_dir = root_dir
                        else:
                            curr_dir = curr_dir.add_dir(dirname)
            elif prev_op == Operation.Ls:
                # ls operation
                try:
                    file_type = FileType(line[0])
                    name = line[1]
                    if file_type == FileType.Dir:
                        curr_dir.add_dir(name)
                except:
                    file_type = FileType.File
                    size = int(line[0])
                    if file_type == FileType.File:
                        curr_dir.add_file(name, size)
            else:
                raise 'what the hell'
    return root_dir


def part1():
    root_dir = parseOperations()
    size_sum = 0
    dirs = [root_dir]

    while len(dirs) > 0:
        curr_dir = dirs.pop()
        c_size = curr_dir.get_size()
        if c_size <= 100000:
            size_sum += c_size
        if len(curr_dir.directories) > 0:
            dirs += curr_dir.directories.values()

    return size_sum

SYS_AVAILABLE = 70000000
REQUIRED_SPACE = 30000000

def part2():
    root_dir = parseOperations()
    dirs = [root_dir]
    dir_sizes = []
    
    SPACE_AVAILABLE = SYS_AVAILABLE - root_dir.get_size()

    while len(dirs) > 0:
        curr_dir = dirs.pop()
        dir_sizes.append(curr_dir.get_size())
        if len(curr_dir.directories) > 0:
            dirs += curr_dir.directories.values()

    enough_space = list(filter(lambda x: SPACE_AVAILABLE + x >= REQUIRED_SPACE, dir_sizes))
    enough_space.sort() # min first
    return enough_space[0]

if __name__ == '__main__':
    print(f'part 1 = {part1()}')
    print(f'part 2 = {part2()}')