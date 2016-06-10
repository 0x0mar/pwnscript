# pwnscript
a scripting language designed specifically for security analysis and capture the flag competitions

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
* Pointers with pointer math (somehow mark as unsafe, but this is definitely needed)
* Compile to C (I *think* C is a pretty great IR) ...
* ... or compile to executable (I like compiled languages)

# Examples
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
