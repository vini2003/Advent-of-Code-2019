# Day V - what does topaz_ actually mean?

Your input is a series of instructions (_opcodes_). It is separated by `,` (_commas_), and looks like:

```
    3,225,1,225,6,6,1100,1,238,225,104,0,1101...
```

Your parser must now be able to interpretate five instructions, and two parameter modes. What is a parameter mode, you may ask?

A paremeter mode can be:

- `position` - use the value stored at the specified position.
- `immediate` - use the value of the parameter itself.

An instruction can be:

- `1` - appears as `BA01,X,Y,Z`, where `B` and `A` specify, respectively, the parameter modes of `X` and `Y`. The instruction dictates you must sum `X` and `Y`'s values and store the result in `Z`.

- `2` - appears as `BA01,X,Y,Z`, where `B` and `A` specify, respectively, the parameter modes of `X` and `Y`. The instruction dictates you must multiply `X` and `Y`'s values and store the result in `Z`.

- `3` - appears as `3,X`. The instruction dictates you must get a value from the user and store it at position `X`.

- `4` - appears as `4,X`. The instruction dictates you must show the value stored at position `X` to the user.

- `99` - appears as `99`. The instruction dictates the interpreter should stop.

Parameters themselves are stored from *right* to *left*, and the _instruction_ itself is located at the last two digits of the input, meaning, given the input `0101,2,4,6`, the _instruction_ is `01` (`1`), parameter `2` is in mode `1` (`immediate`), and parameter `4` is in mode `0` (`position`).