# printf
This is a library that contains a recreation of the printf funciton in C. It also contains all functions from the libft project.

This printf function ```ft_printf()``` handles the conversions ```cspdiux``` and the flags ```- 0```. Field width is also handled along with precision with the ```.``` flag.

The only allowed external functions were malloc, free, write, va_start, va_arg, va_copy, and va_end.

----
### Conversions
|Specifier  |Description                                                 |
|:---------:|------------------------------------------------------------|
|%c         |Character argument is printed.                              |
|%s         |String argument is printed.                                 |
|%p         |Address of pointer argument is printed.                     |
|%d %i      |Integer argument is printed.                                |
|%u         |Unsigned integer arguments is printed.                      |
|%x         |Argument is printed as a hexadecimal with lowercase letters.|

### flags
|flag       |Description                                                                                                                          |
|:---------:|-------------------------------------------------------------------------------------------------------------------------------------|
|Field width|A number or asterisk can be added before the conversion specifier letter in order to dictate the total width of the output. If the width is longer than the output string, it will be blank padded unless specified otherwise with another flag.                                                                     |
|.          |Indicates presicion. A number or asterisk can be added after a period to indicate the maximum number of characters to ouput from the argument conversion. (for %d and %i, 0 will pad the output.)                                                                                                                   |
|-          |padding will be added to the right of the output instead of the left.                                                                |
|(space)    |Puts a space in front of a positive signed integer output.                                                                           |
|0          |puts '0' padding instead of ' ' padding.                                                                                             |

#### Example
ft_printf("Hello %13s.\n", "world");
```bash
Hello         world.
```
ft_printf("%.*d minutes.\n", 10, 525600);
```bash 
0000525600 minutes.
```

### Installation
```bash
git clone https://github.com/unstoppa61e/printf.git
```

## Usage
```bash
make - compiles library libftprintf.a
make clean - removes all .o files
make fclean - removes all .o files and library
make re - removes all .o files and library before recompiling library
```
