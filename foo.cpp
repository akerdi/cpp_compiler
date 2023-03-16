#include <iostream>

using namespace std;

#include "compiler.h"

void doWork(string& input) {
    cout << input << ": " << endl;
    AStruct* program = compiler(input);
    program->print(0);
    program->deleteNode();
    cout << endl << endl;
}

int main() {
    string input;
    input = "if (+ x y) { * 890909 9 } { / 9 3 }";
    doWork(input);
    input = "(add 2 (subtract 4 2))";
    doWork(input);
    input = "+ 1 2";
    doWork(input);
    input = "/";
    doWork(input);
    input = "(- 100)";
    doWork(input);
    input = "(/ ())";
    doWork(input);
    input = "list 1 2 3 4";
    doWork(input);
    input = "{head (list 1 2 3 4)}";
    doWork(input);
    input = "eval {head (list 1 2 3 4)}";
    doWork(input);
    input = "tail {tail tail tail}";
    doWork(input);
    input = "eval (tail {tail tail {5 6 7}})";
    doWork(input);
    input = "eval (head {(+ 1 2) (+ 10 20)})";
    doWork(input);
    input = "def {x} 100";
    doWork(input);
    input = "x";
    doWork(input);
    input = "def {a b} 5 6";
    doWork(input);
    input = "def {arglist} {a b x y}";
    doWork(input);
    input = "def {add-mul} (\\ {x y} {+ x (* x y)})";
    doWork(input);
    input = "def {fun} (\\ {args body} {def (head args) (\\ (tail args) body)})";
    doWork(input);
    input = "fun {add-together x y} {+ x y}";
    doWork(input);
    input = "fun {unpack f xs} {eval (join (list f) xs)}";
    doWork(input);
    input = "fun {pack f & xs} {f xs}";
    doWork(input);
    input = "def {uncurry} pack";
    doWork(input);
    input = "print \"Hello World!\"";
    doWork(input);
}