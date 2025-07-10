# miniGit

`miniGit` is a simplified Git-like version control system written in C++. It supports basic commands such as `init`, `add`, `commit`, `log`, `status`, and `restore`. Designed for learning and experimentation, `miniGit` demonstrates how real Git works internally by using a custom object store and SHA-1 hashing.

## Features

* `init`: Initializes a `.miniGit/` directory
* `add <file>`: Stages a file by saving its SHA-1 hash
* `commit <message>`: Saves a snapshot of staged files
* `log`: Displays commit history
* `status`: Lists currently staged files
* `restore <file>`: Restores a file from the index

## Building

Make sure you have OpenSSL development headers installed (`libssl-dev` on Linux). Then build using:

```bash
g++ -std=c++17 -lssl -lcrypto -Iinclude src/*.cpp -o miniGit
```

## Usage

Run the following commands inside any directory you'd like to turn into a `miniGit` repository:

```bash
./minigit init
./minigit add file.txt
./minigit commit "initial commit"
./minigit status
./minigit log
./minigit restore file.txt
./minigit restore --staged
./minigit restore --commit commit-id
./minigit checkout commit-id
```