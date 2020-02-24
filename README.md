# roman-numbers
Roman numbers converter

```bash
# compile
$ gcc -o r2i roman-numbers.c

# interactive
$ ./r2i
lxviv
69
mmdxxlvii
2537
^C

# batch
$ cat afile
xiv
mccliii
mmmdxxlvii
$ ./r2i <afile
14
1253
3537

# no trailing newline
$ echo -n xii | ./r2i
12
```
