# 🚗 Parking Management System (IAED Project)

This repository contains a parking management system implemented in C, designed as part of the **IAED 2024** coursework. The goal of this project was to develop a memory-efficient, modular, and standards-compliant command-line tool for registering, managing, and calculating fees for cars entering and exiting multiple parking lots.

## 📌 Project Highlights

- Modular C architecture (split across `project.c`, `parque.c`, `carros.c`, `registo.c`, `lib.c`)
- Supports commands to:
  - Create and list parking lots
  - Register vehicle entries and exits
  - Validate vehicle data (license plate, date, time)
  - Calculate fees with tiered logic
  - Generate revenue reports
- Developed according to strict academic guidelines, including:
  - `gcc -Wall -Wextra -Werror -Wno-unused-result` compliance
  - Memory safety (`valgrind`, `fsanitize`, `cppcheck` tested)
  - Consistent Doxygen-style documentation

## 🛠️ Compilation & Execution

To compile the project:

```bash
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj1 *.c
```

Run a specific test:

```bash
./proj1 < tests/test01.in
```

Compare with expected output:

```bash
diff myoutput.out tests/test01.out
```

## ✅ Sample Commands

- `p "Parque Centro" 100 0.50 1.00 15.00` — Create a parking lot  
- `e "Parque Centro" AA-00-BB 01-01-2024 08:00` — Register car entry  
- `s "Parque Centro" AA-00-BB 01-01-2024 09:45` — Register car exit and calculate fee  
- `v AA-00-BB` — View all parkings a car has used  
- `f "Parque Centro"` — View total revenue per day  

## 🧠 Learning Outcomes

- Efficient linked list usage for dynamic memory operations  
- Defensive programming and input validation  
- Structuring C code for readability and modularity  
- Experience with debugging tools and performance analyzers  

## 🧪 Tools Used

- GCC 12.3.0  
- Valgrind  
- cppcheck  
- icdiff  
- Make

## 📝 Notes

- This project follows strict submission guidelines and was evaluated via an automatic testing system.  
- Refer to `debugging.md` and `guidelines.md` for insights into code quality, memory safety, and testing workflow.
