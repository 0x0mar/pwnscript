# Code style

## Primary coding goals
* Terse
    * Yay for variables like `e` (element), `i` (iterator), `t` (temp) and `r` (result). Try to avoid noncommittal names `x` and `y` though, unless they're describing an xy coordinate system or something.
    * Yay for one line if statements! `if(!x) return NULL;`
* Readable
    * Terseness shouldn't be taken too far.
    * Tertiary operators are hard to quickly read. Use proper if statements instead.

## Comments
Use `//` for comments (and add one space afterwards). I `/*` and `*/` looks busy, and sometimes has weird bugs in C.

```c
// multi line comments go like this
// just throw a new `//` at the beginning of every new line
// there shouldn't really be any areas that require this much commenting anyway :P
```

```c
// TODO: a task
// FIXME: a bug
// HACK: a hack to cleanup
```

I have a habit of commenting structs like this:

```
struct x {
    int a; // some value a that holds things
    int b; // a value b that holds more things
    int c; // a value c that doesn't do anything.
};
```

It's more important to comment and explain a data structure than code that uses it. It's easier to infer the reasons for code than it is for data.

## Formatter
* Install `astyle` (I think it's in the brew repository, and it's definitely in the Arch repo)
* Run `astyle --style=attach -xW --break-blocks -p -U -xe -k3 -n *.c *.h` to format code with a consistant style.

## Naming/interface conventions
* C doesn't have classes, so prefix functions with the name (or first letter of the name) of the file. (i.e. `node.h` would have functions called `node_new`, `node_del`, etc).
* Structs should be typedefed and post-fixed with `_t`.
    * ```
      typedef struct {
        char *name;
      } node_t;
      ```
* Functions that operate on a struct should accept the struct as the first argument
    * `node_find(node_t *root, type_t type)`
    * `node_generate(node_t *node, int id)`
* Static functions don't have to be prefixed with the name of the file.
