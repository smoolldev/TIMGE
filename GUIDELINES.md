# Styling Guidelines

## If Statements

### Single Statement Blocks

```cpp
if (expression) {
    // Code
}
```

### Compound Statements

```cpp
if (expression)
{
    // Code
}
```

## Switch Statements

```cpp
switch (expression)
{
    case 1:
        // Code, try to keep it small (call a function, or call max 3 instructions)
        break;
    case 2:
        // Code, try to keep it small (call a function, or call max 3 instructions)
        break;
    default:
        break;
}
```

## Classes

```cpp
class ClassName
{
    public:
        // Code
    protected:
        // Code
    private:
        // Code
};
```

### Member Variables

```cpp
class ClassName
{
    private:
        void mFunctionName();

        int mVariableName;

        // Code
};
```

## Functions

### Declarations

```cpp
void FunctionName(parameters);
```

### Definitions

```cpp
void FunctionName(parameters)
{
    // Code
}
```

## Temporary Variables

```cpp
int variableName;
```

## Global Variables

```cpp
int gVariableName;
```

## Constant Variables

Do not do:

```cpp
#define CONSTANT_VARIABLE_NAME value
```

Instead do:

```cpp
constexpr int CONSTANT_VARIABLE_NAME = value;
```

## Templates

```cpp
template<typename Type_T>
void FunctionName(Type_T name);
```

## Function Parameters

```cpp
void FunctionName(int parameterName);
```

## Includes
Including goes in this order:
- Your own headers
- C++ headers
- Other libraries' headers

Example:

```cpp
#include "TIMGE/TIMGE.hpp" // Your own libraries first

#include <iostream> // C++ libraries second

#include <glfw/glfw3.h> // Other libraries third
```
