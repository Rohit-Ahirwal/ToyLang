<h1 align="center" id="title">ToyLang</h1>

<p align="center"><img src="https://socialify.git.ci/Rohit-Ahirwal/ToyLang/image?description=1&font=KoHo&forks=1&language=1&name=1&owner=1&pattern=Solid&stargazers=1&theme=Auto" alt="project-image"></p>

<p align="center">This is the official repository for <b>Toy Language.</b></p>

Welcome to the **ToyLang**! This is a simple, fun programming language designed for learning and experimentation. It includes essential programming constructs and is a perfect project for those wanting to understand the fundamentals of building a custom language. 

This language features core constructs like variable assignment, condition management, loops, console logging, and basic arithmetic operations.

> **Note:** This is a **toy language** for practice and educational purposes, not a fully functional language like Python, C, or C++. It’s designed to help you understand the basics of creating a programming language from scratch.

---

## Features 🚀

ToyLang covers all the basic features of a programming language which are sufficient to understand and build a programming language from scratch.

- **Variable Assignment**: Support for basic variable assignments (`a = 10;`).
- **Condition Management**: `if`, `else`, and `elif` statements to handle conditional logic.
- **Loops**: `while` and `for` loops to create repetitive tasks.
- **Console Logging**: Built-in `log()` function to output to the console.
- **Arithmetic Operations**: Addition, subtraction, multiplication, and division.
  
---

## How It Works 💻

This language is interpreted, meaning it’s parsed and evaluated line-by-line. The interpreter reads the code, creates an Abstract Syntax Tree (AST), and evaluates the nodes according to the logic defined in the evaluator.

---

## Download

You can simply download **ToyLang** from our [website](https://toylang-docs.vercel.app/).

## Usage

After downloading it if you are using vscode make sure you have installed [ToyLang Extension in Vscode](https://marketplace.visualstudio.com/items?itemName=RohitAhirwal.toylang), This extension will enable the syntax highlights and auto completion for **ToyLang** in vscode.

This is how it looks with the extension

### Before
![simple code](https://github.com/user-attachments/assets/46b77997-7f4a-4de1-b188-ee0a123f2e71)

### After
![highlighted code](https://github.com/user-attachments/assets/e4f0fa81-27c0-417d-a7a9-c709e70eca2e)

## Documentation

ToyLang is a dynamically typed programming language, designed for practice and educational use, and implemented in C++.

### Variables
Easily assign values to variables with statements like.

```
a = 10;
```

### Types
ToyLang supports Number, String and Boolean etc. all these like other language.

```
a = 10;
b = "Hello World!";
c = true;
```

### Built-ins
You can use built-in log keyword to print anything to console.

```
log("Hello World!");
```

### Conditionals
ToyLang supports a simple if-elif-else construct to handle conditional logic. The if block executes when the condition is true, while the elif blocks can be used to check additional conditions in sequence. If none of the above conditions are true, the else block will execute, providing a default action when all conditions fail. This allows for clear and easy branching of program logic based on different conditions.

```
if (a > b) {
  log("a is greater than a");
} elif (a < b) {
  log("b is greater than a");
} else {
  log("b is equal to a");
}
```

### For Loop
ToyLang provides a for loop for iterating over a specified range of values. It is ideal for situations where the number of iterations is known beforehand. You can define the start, condition, and step of the loop, making it easy to run repetitive tasks a set number of times.

```
for (i = 0; i < 10; i++) {
  log(i);
}
```

### While Loop
The while loop in ToyLang runs as long as a given condition is true. This loop is useful for situations where the number of iterations is not predetermined and the loop continues until a specific condition becomes false. It provides flexibility for running tasks based on dynamic conditions.

```
while (i < 10) {
  log(i);
  i = i + 1;
}
```