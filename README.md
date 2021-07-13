# This WIP, testing ground, unfinished.

do not use (yet)

## Some build / config notes.

In `build`, generate `compile_commands.json`:

```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=YES ..
```

Then symlink, in project root execute:

```bash
ln -s ~/git/CScratch/astrocal/build/Debug/compile_commands.json .
```
