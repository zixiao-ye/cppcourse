#include "hw04.h"
#include "vm.h"

#include <iostream>


namespace vm {

/**
 * simple test code for invoking the VM.
 */
void test_vm() {
    std::string program = (
        "LOAD_CONST 432\n"
        "LOAD_CONST 905\n"
        "ADD\n"
        "PRINT\n"
        "EXIT\n");

    std::cout << "initializing vm..." << std::endl;
    // create it in debug-mode!
    vm_state state = create_vm(true);

    try {
        std::cout << "assembling..." << std::endl;
        code_t code = assemble(state, program);

        std::cout << "running..." << std::endl;
        const auto& [exit_state, return_text] = run(state, code);

        std::cout << "done! vm result: " << exit_state << std::endl;
        if (return_text.size()) {
            std::cout << return_text << std::endl;
        }
    }
    catch (vm_stackfail &err) {
        std::cout << "vm stack access failes! " << err.what() << std::endl;
        std::cout << "stack status (newest at top, size="
                  << state.stack.size()
                  << "):" << std::endl;

        while (not state.stack.empty()) {
            std::cout << " " << state.stack.top() << std::endl;
            state.stack.pop();
        }
    }
    catch (vm_segfault &err) {
        std::cout << "vm segfaulted! " << err.what() << std::endl;
        std::cout << "tried to access invalid program memory at pc="
                  << state.pc << std::endl;

    }
    catch (div_by_zero &err) {
        std::cout << "vm divided by zero! " << err.what() << std::endl;
    }
}

} // namespace vm


int main() {
    vm::test_vm();
    return 0;
}
