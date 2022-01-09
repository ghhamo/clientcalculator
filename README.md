From any folder in terminal
1. Generate build tree with `cmake -B build -S /path/to/source/root`
2. Build target calculator with `make all -C build`
3. Create a file for input
4. Fill input file with expressions. You can write multiple expressions, each on one a separate line.
5. Call calculator client by passing path to input as argument `./build/clientcalculator /path/to/input.txt`
6. Check results from output.txt in current directory