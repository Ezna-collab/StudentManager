# Student Manager

A simple command-line application written in C to manage a list of students.
It allows you to add, search, display, and delete students, and to save or
load the student list from a text file.

## Features

- Add a student (ID, firstname, lastname, GPA)
- Search a student by ID
- Display all students
- Delete a student by ID
- Save the student list to a file
- Load the student list from a file at startup
- Input validation (no empty input, no invalid menu choice, no crash on
  non-numeric input)
- Asks to save on exit only if there are unsaved changes (like Word)

## Project structure

```
StudentManager/
├── README.md
├── data/
│   └── students.txt      # Saved student data
├── include/
│   └── student.h         # Struct definition and function prototypes
├── scripts/
│   └── build.sh          # Build script
└── src/
    ├── main.c            # Menu and user interaction
    └── student.c         # Student management functions
```

## Requirements

- GCC (or any C compiler compatible with C99/C11)
- A Unix-like environment (Linux, macOS, or WSL on Windows) to run the
  build script

## Build

From the project root, run:

```bash
./scripts/build.sh
```

This will compile the project and produce an executable named `main` at
the project root.

Alternatively, you can compile manually:

```bash
gcc src/main.c src/student.c -Iinclude -o main
```

## Run

```bash
./main
```

## Usage

On launch, the program automatically loads existing students from
`data/students.txt` (if the file exists).

You will see a menu:

```
================STUDENT MANAGER===================
1. Add student.
2. Search a student.
3. Show all the students.
4. Delete a student.
5. save.
0. exit.
```

Enter the number corresponding to the action you want to perform. Invalid
input (letters, empty input, or numbers outside the menu range) will be
rejected and you will be asked to try again.

When exiting (option `0`), if you have unsaved changes, you will be asked
whether you want to save before quitting.

## Data file format

Students are saved in `data/students.txt` using a simple format:

```
<number_of_students>
<id>;<firstname>;<lastname>;<gpa>
<id>;<firstname>;<lastname>;<gpa>
...
```

## Notes

- Maximum number of students and maximum name length are defined in
  `include/student.h` (`MAX_STUDENTS` and `SIZE_NAME`).
- Make sure the `data/` directory exists before running the program, since
  saving requires write access to `data/students.txt`.