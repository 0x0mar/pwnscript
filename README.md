# pwnscript
a scripting language designed specifically for security analysis and capture the flag competitions

# What's currently implemented
* Tokenizer
* Basic parser

## Build the project
* You need to install `flex`, `bison`, a C compiler, and `make`
* Run `make`
* `./pwn`
* Enter your program. For instance:

    + (1,2)

* Hit `Ctrl-D`
* See the glorious AST dump.

```
FN {
   ARGS {
   }
   BLOCK {
      FNCALL {
         CALLERS {
            ID { + }
         }
         CALLEES {
            FN {
               ARGS {
               }
               BLOCK {
                  NUM { 1 }
                  NUM { 2 }
               }
            }
         }
      }
   }
}
```

# Goals

* Lightweight and embeddable (like Lua)
* Fast
* Easy to integrate with C stuff - needed for binary exploit type stuff
* Out of the box support for analysis (image/video manipulation, etc)
* Out of the box support for assembly/disassembly
* Out of the box support for networking stuff
* Out of the box support for crypto
* Out of the box support for gdb
* Basically, steal every feature from pwntools :)

# Design
* Prototypical (screw OOP)
* Syntax is mostly a ripoff of Ruby, Python, Lua and JavaScript. (go ahead and add more examples below)
* Pointers with pointer math (somehow mark as unsafe, but this is definitely needed for security stuff)
* Compiled. Because interpreted languages are too dependent.

# (possible) Examples
The following are some examples of what the language could possibly look like. (add more examples if you want some specific feature)

## Binary exploits
Simple buffer overflow example that could be piped to `nc`
```
p 'a' * 32 // print 'a' 32 times to fill up buffer
p 0x03a3fed.to_s // print location for return address
```

... or in a pwntools kinda way ...

```
ARCH='i386'
OS='linux'
s = socket 'exploit.somethingsomething.com'
s.connect! // functions with side effects require '!'
some_shellcode.to_asm | s // send shellcode through socket
// could also be written: s.send(some_shellcode.to_asm)
```

## Boring things

```
// prototypical like lua or javascript
s = {
    f = fn(y) {
        p y
    }
}

s.f(3) // prints 3
```

Creating libraries:

* create file with name of library.
* create library module.
* i.e. a library named `thing` would be in `thing.pwn`:

```
thing = {
    libfunc = fn() {
        // ... something here
    }
}
```

... then in a file that uses it:

```
thing = load 'thing'
thing.libfunc()
```

# Code
Yup. I'm insane. I went with C for a compiler *again*. Oh well :P

But this time, I've got a secret weapon! [QBE](http://c9x.me/compile/)! (the bit the generates assembly)

----

Here's how a compiler works:

### Stage 1: Lexing
The first stage is lexing. It converts the code into a series of tokens that get sent to the parser.

* Lexing is done with `flex`
* The lexfile is `pwn.l` - use this file for defining new tokens (which shouldn't really ever have to happen - most operators won't be tokens - they'll be functions).
* `flex` uses `pwn.l` to generates `lexer.c`, which should **never** be manually edited.

### Stage 2: Parsing
Next, the tokens are used to build a tree (called the abstract syntax tree - AST). The parser describes the grammar for the langueage and does static syntax checks.

* Parsing is done with `bison`
* The parser file is `pwn.y` - this is where the syntax is defined.
* `bison` uses `pwn.y` to generate `parser.c`, which also should **never** be manually edited.

### Stage 3: Code generation
Finally, traverse the AST and generate assembly.

This is where QBE comes in, since all we have to do is output a very simple intermediate langauge (IR) that gets converted to machine code. It does a lot of cool optimizations and stuff too.

Read QBE's docs for more info on this.

### In conclusion

The whole pipeline looks like this:

```
flex pwn.l -> bison pwn.y -> pwn.c (traverses AST and generates QBE IR) -> QBE -> executable
```

## Examples/References
* http://gnuu.org/2009/09/18/writing-your-own-toy-compiler/3/
