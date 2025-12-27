# Quiz Game in C

## Project Description
This project is a **console-based Quiz Game** developed in **C programming language**.  
The game allows users to answer multiple-choice questions from different subjects and difficulty levels, track their scores, and view past performance.

The project demonstrates the use of **structures, file handling, arrays, and user input validation** in C. It is suitable for **beginners and academic learning purposes**.

---

## Features
- User name input and personalized gameplay
- Multiple subjects:
  - Math
  - Science
  - History
- Three difficulty levels:
  - Easy
  - Medium
  - Hard
- Multiple-choice questions (MCQs)
- Score calculation and display
- Score saving using file handling
- Viewing previous scores
- Input validation for better user experience

---

## How the Game Works
1. The user enters their name
2. The user selects:
   - A subject
   - A difficulty level
3. The quiz starts with 10 questions
4. The user answers each question by choosing options (1–4)
5. The final score is displayed
6. Scores are saved automatically and can be viewed later

---

## Technologies Used
- Programming Language: **C**
  
- Concepts Used:
  - Structures (`struct`)
  - File Handling (`fopen`, `fprintf`, `fscanf`)
  - Arrays and Strings
  - Conditional statements and loops
  - Input validation

---

## File Handling
- `questions.txt`  
  Stores quiz questions, options, subject, and difficulty level  
- `scores.txt`  
  Stores user names and their scores (created automatically)

> Note: These files are handled automatically by the program.

---

## How to Compile and Run

### Compile the program
```bash
gcc quiz_game.c -o quiz_game
```

### Run the program
```bash
./quiz_game
```

> Make sure `questions.txt` is present in the same directory before running.

---

## Menu Options
- Play Quiz
- View Scores
- Exit

---

## Notes
- Each quiz contains **10 questions**
- Input validation prevents invalid choices
- This is a **console-based application**
- Designed for **learning and academic purposes**

---

## Author
- Student Project

---

## License
This project is intended for **educational use only**.
