#pragma once

#include <cstdint>
#include <functional>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <utility>

namespace vm {

///////////////////////////////////////////////////////////////////////////////
// definition of the internal types
// these are vm internals - you may change here whatever you think is best!

/**
 * type used for storing data in one slot on the stack.
 */
using item_t = int64_t;

/**
 * type used for identifying assembled opcodes.
 */
using op_id_t = size_t;


/** single instruction with its argument */
using op_t = std::pair<op_id_t, item_t>;


// forward declaration
struct vm_state;

/**
 * if an instruction is executed, what should be done?
 *
 * function args: the vmstate and the operation argument.
 * return value: true if the VM should keep running on after the instruction.
 */
using op_action_t = std::function<bool(vm_state&, const item_t)>;


/** stores all the assembled instructions, i.e. this is our running program */
using code_t = std::vector<op_t>;


/** all vm execution state information is stored in here */
struct vm_state {
    /**
     * where in the program code are we?
     */
    size_t pc = 0;

    /**
     * stores which id is given the next instruction that is registered.
     */
    size_t next_op_id = 0;

    /**
     * the main execution state stack.
     */
    std::stack<item_t> stack;

    /**
     * mapping of instruction name to operation id.
     */
    std::unordered_map<std::string, op_id_t> instruction_ids;

    /**
     * mapping of operation ids back to instruction names.
     * used for debugging -> so we can resolve an op_id back to a name.
     */
    std::unordered_map<op_id_t, std::string> instruction_names;

    /**
     * mapping of operation id to action.
     */
    std::unordered_map<op_id_t, op_action_t> instruction_actions;

    /**
     * activate vm debugging.
     */
    bool debug = false;

    // if you need to store more vm state, add it here!
};


///////////////////////////////////////////////////////////////////////////////
// definition of the VM API
// we test for the correct behavior of these functions,
// thus we expect these method signatures.


/**
 * create a fresh vm with all available instructions registered.
 *
 * instructions are registered with `register_instruction` in here.
 *
 * @param debug: enable debug output for when running the VM.
 * @return a new vm state with attached instructions
 */
vm_state create_vm(bool debug = false);


/**
 * convert the given instruction string to executable vm code.
 *
 * the code is just a list of instructions.
 * after assembling, the code is given to the `run` function to execute.
 *
 * @param vm: which vm to use for assembling instructions
 * @param input_program: the program text to convert to executable instructions
 *
 * @return the executable code
 */
code_t assemble(const vm_state& vm, std::string_view input_program);


/**
 * register a new instruction to a vm.
 *
 * @param vm: which vm to register the instruction to
 * @param name: the textual identifier of the newly created instruction
 * @param action: the function to run when this instruction is encountered in a program
 */
void register_instruction(vm_state& vm, std::string_view name,
                          const op_action_t &action);


/**
 * execute the given vm instructions.
 *
 * @return the execution results: {last TOS item, result string from WRITE instructions}
 */
std::tuple<item_t, std::string> run(vm_state& vm, const code_t &code);


//// exception types, thrown in various error situations.

/**
 * exception thrown when the VM attempts to divide by zero.
 */
struct div_by_zero : std::runtime_error {
    using std::runtime_error::runtime_error;
};


/**
 * exception thrown when an invalid memory address is requested.
 */
struct vm_segfault : std::runtime_error {
    using std::runtime_error::runtime_error;
};


/**
 * exception thrown when the stack content is not as expected.
 */
struct vm_stackfail : std::runtime_error {
    using std::runtime_error::runtime_error;
};


/**
 * exception thrown when a instruction could not be decoded.
 */
struct invalid_instruction : std::runtime_error {
    using std::runtime_error::runtime_error;
};


} // namespace vm
