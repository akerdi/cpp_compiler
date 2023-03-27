# CPP_Compiler

Implement `Input String` to `AStruct*`.

## Usage

```cpp
string input;
input = "if (+ x y) { * 890909 9 } { / 9 3 }";
AStruct& program = AKCompiler::compiler(input);
    program.print();
    program.deleteNode();
    cout << endl << endl;
}
```

More test see `foo.cpp`

## Environment

force compiler to be a library:

`CMake Option: COMPILER_LIB_MODE`

    ON: Library Mode
    OFF: Test Mode

## TODO

- [ ] Letter match regex enable
- [ ] Number match regex enable
- [ ] Load the file separated by \n, not by 4096 bytes
- [x] Error type return

## Other Language

[JavaScript & Doc](https://github.com/akerdi/jslispy)

[Golang](https://github.com/akerdi/the-super-tiny-compiler)