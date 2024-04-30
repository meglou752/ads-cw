#include "Include/sudoku.h"

// App entry point, interface handles from here (recursion loop may be a problem in future).
int main() {
    init_stacks(); // Initialise stacks for use
    interface();
    return 0;
}