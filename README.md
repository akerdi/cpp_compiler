# CPP_Compiler

Implement `Input String` to `AStruct*`.

## Usage

```cpp
string input;
input = "if (+ x y) { * 890909 9 } { / 9 3 }";
AStruct* program = compiler(input);
if (Ast_Type_Error == program.type) {
    program.print();
    program.deleteNode();
    continue;
}
program->print();
program->deleteNode();
```

More test see `foo.cpp`

## Environment

`CMake Option: USE_MY_COMPILER`

    ON: Library Mode
    OFF: Test Mode

## TODO

- [ ] Letter match regex enable
- [ ] Number match regex enable
- [x] Error type return

## Other Language

[JavaScript & Doc](https://github.com/akerdi/jslispy)

[Golang](https://github.com/akerdi/the-super-tiny-compiler)