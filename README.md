# Math Expression Parser

## Overview

This project is a comprehensive Math Expression Parser implemented in C/C++ using the Lex (Flex) lexical analyzer. It demonstrates various parsing techniques, including lexical analysis, recursive descent parsing, infix-to-postfix conversion, and expression tree construction. The project serves as a tool for understanding compiler design concepts, particularly in the context of mathematical expression evaluation.

## What Does It Do?

The Math Expression Parser can:

1. **Lexical Analysis**: Tokenize input strings containing mathematical expressions, operators, functions, and variables using regular expressions defined in `Parser.l`.

2. **Parsing Multiple Grammars**:
   - Mathematical expressions (E → E+F | E-F | F, etc.)
   - Circle and ellipse equations (e.g., x² + y² = r²)
   - Alternating 'a' and 'b' strings (simple grammar demonstration)
   - SQL SELECT statements (basic parsing)

3. **Infix to Postfix Conversion**: Convert infix mathematical expressions to postfix notation using the Shunting-yard algorithm.

4. **Expression Tree Construction**: Build a binary expression tree from postfix notation, representing the hierarchical structure of mathematical operations.

5. **Tree Traversal and Printing**: Perform inorder traversal to display the constructed expression tree.

## How Does It Work?

### Architecture

The project consists of several key components:

1. **Lexer (`Parser.l`)**: 
   - Uses Flex to generate a lexical analyzer
   - Defines regular expressions for tokens (numbers, operators, functions, variables, etc.)
   - Implements a custom stack-based undo mechanism for backtracking during parsing

2. **Parsers**:
   - **MathExpParser.c**: Recursive descent parser for mathematical expressions
   - **Equations.c**: Specialized parser for geometric equations
   - **Alternate_a_b.c**: Parser for alternating 'a' and 'b' sequences
   - **SqlSelectParserCFG.c**: Basic SQL SELECT statement parser

3. **Data Structures**:
   - **MexprTree**: C++ class hierarchy for expression trees
   - **Dtypes**: Classes for different data types (INT, DOUBLE, STRING, BOOL)
   - **Operators**: Classes for mathematical and logical operators

4. **Conversion and Evaluation**:
   - Infix to postfix conversion algorithm
   - Expression tree construction from postfix notation

### Workflow

1. **Input Processing**: User inputs a mathematical expression as a string
2. **Lexical Analysis**: The lexer tokenizes the input using defined patterns
3. **Parsing**: Recursive descent parser validates the expression grammar
4. **Conversion**: Infix expression is converted to postfix notation
5. **Tree Building**: Postfix tokens are used to construct a binary expression tree
6. **Output**: The expression tree is traversed and printed in inorder fashion


## Framework and Technologies

- **Language**: C/C++ hybrid
- **Lexer Generator**: Flex (Lex)
- **Build System**: Manual compilation via shell script
- **Data Structures**: Custom stack implementations, linked trees
- **Paradigm**: Object-oriented design for tree nodes and operators

## How to Execute

### Prerequisites

- GCC/G++ compiler
- Flex (Lex) installed on the system

### Build Instructions

1. Navigate to the project directory:
   ```bash
   cd /path/to/MathExpressionParser
   ```

2. Run the build script:
   ```bash
   ./run.sh
   ```

   This script performs the following:
   - Generates lexer code from `Parser.l` using `lex`
   - Compiles all C/C++ source files
   - Links them into an executable named `exe`

### Running the Parser

1. Execute the compiled program:
   ```bash
   ./exe
   ```

2. Input mathematical expressions when prompted:
   ```
   Input-> 2 + 3 * 4
   ```

3. The program will:
   - Parse the expression
   - Convert it to postfix
   - Build and display the expression tree

### Example Usage

```
Input-> 5 + 3 * 2
E : Accepted
Print the postfix array : 5 3 2 * +
Constructing Expression Tree
Printing MexprTree : 5 + 3 * 2
```

## Detailed Execution Example

Let's examine how the parser processes the expression `2 + (3*4) / (5+(6-1))` step by step. Note that the current implementation has some limitations with whitespace handling and may reject complex expressions or crash due to unhandled token types in operator precedence. Below is a conceptual breakdown of the parsing process:

### Step 1: Lexical Analysis
The lexer tokenizes the input string into tokens:
- `2` → MATH_CPP_INT
- `+` → MATH_CPP_PLUS
- `(` → MATH_CPP_BRACKET_START
- `3` → MATH_CPP_INT
- `*` → MATH_CPP_MUL
- `4` → MATH_CPP_INT
- `)` → MATH_CPP_BRACKET_END
- `/` → MATH_CPP_DIV
- `(` → MATH_CPP_BRACKET_START
- `5` → MATH_CPP_INT
- `+` → MATH_CPP_PLUS
- `(` → MATH_CPP_BRACKET_START
- `6` → MATH_CPP_INT
- `-` → MATH_CPP_MINUS
- `1` → MATH_CPP_INT
- `)` → MATH_CPP_BRACKET_END
- `)` → MATH_CPP_BRACKET_END

### Step 2: Parsing
The recursive descent parser validates the expression against the grammar:
- E (Expression) → F E'
- F (Factor) → T F'
- T (Term) → (E) | number | variable | function(E,E) | unary_function(E)
- E' → + F E' | - F E' | ε
- F' → * T F' | / T F' | ε

The parser builds a parse tree by recursively applying these rules.

### Step 3: Infix to Postfix Conversion
Using the Shunting-yard algorithm, the infix expression is converted to postfix notation:
`2 + (3*4) / (5+(6-1))` → `2 3 4 * 5 6 1 - + / +`

### Step 4: Expression Tree Construction
The postfix tokens are processed with a stack to build a binary tree:
- Operands (numbers) become leaf nodes
- Operators become internal nodes with appropriate children
- The tree represents the hierarchical structure of operations

### Step 5: Tree Traversal
An inorder traversal prints the expression: `2 + 3 * 4 / 5 + 6 - 1`

### Actual Execution Output
When running the expression, the current implementation may produce output like:
```
Input-> 2 + (3*4) /(5+(6-1))
E : Rejected (due to whitespace handling issues)
```
Or potentially crash with an assertion failure if unhandled tokens are encountered.

This example demonstrates the theoretical parsing pipeline. The project could be improved by:
- Modifying the lexer to skip whitespaces instead of pushing them
- Fixing the parser to properly handle whitespace tokens
- Ensuring all token types are handled in operator precedence functions
- Correcting the acceptance check logic

## What Can We Learn from This Project?

### Compiler Design Concepts

1. **Lexical Analysis**: Understanding how source code is broken into tokens using regular expressions and finite automata.

2. **Parsing Techniques**: 
   - Recursive descent parsing
   - Grammar design and left-recursion elimination
   - Error handling and backtracking

3. **Expression Evaluation**:
   - Infix, prefix, and postfix notations
   - Operator precedence and associativity
   - Stack-based evaluation algorithms

4. **Data Structures for Compilers**:
   - Abstract Syntax Trees (AST)
   - Symbol tables
   - Parse trees vs. expression trees

### Software Engineering Principles

1. **Modular Design**: Separation of lexer, parser, and evaluator components
2. **Object-Oriented Programming**: Class hierarchies for different node types
3. **Error Handling**: Checkpoint and restore mechanisms for parsing failures
4. **Memory Management**: Proper allocation and deallocation in C/C++

### Advanced Topics

1. **Language Processing**: Building interpreters and compilers
2. **Algorithm Design**: Stack-based algorithms for expression processing
3. **Type Systems**: Handling different data types in expressions
4. **Optimization**: Potential for constant folding, dead code elimination

### Practical Applications

- Calculator implementations
- Formula evaluators in spreadsheets
- Mathematical software libraries
- Domain-specific language (DSL) development
- Compiler front-end design

This project provides a solid foundation for understanding the core principles of programming language processing and can be extended to support more complex grammars, additional operators, and even code generation for different target platforms.
