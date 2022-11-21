/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <iterator>
#include <sstream>


#include "hw04.h"

// require at least c++20
static_assert(__cplusplus >= 202002L);

// unfortunately it's necessary that we write
//   const auto& result = ...
//   const auto& topstack = std::get<0>(result);
//   const auto& output_string = std::get<1>(result);
// instead of
//   const auto& [topstack, output_string] = ...
// because clang13.0.1 can't pass that local binding as reference
// to capture into the lambda doctest creates for CHECK_EQ.
// => "reference to local binding 'topstack' declared in enclosing function 'DOCTEST_ANON_FUNC_...'"



TEST_CASE("vm_direct_return") {
    SUBCASE("return_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 123\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);

        CHECK_EQ(topstack, 123);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("return_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST -98123\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, -98123);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("return_3") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 456\n"
                                 "EXIT\n"
                                 "LOAD_CONST 789\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);

        CHECK_EQ(topstack, 456);
        CHECK_EQ(output_string, "");
    }
}


TEST_CASE("vm_pop") {
    vm::vm_state state = vm::create_vm();
    auto code = vm::assemble(state,
                             "LOAD_CONST 456\n"
                             "LOAD_CONST 123\n"
                             "POP\n"
                             "EXIT\n");
    const auto& result = vm::run(state, code);
    const auto& topstack = std::get<0>(result);
    const auto& output_string = std::get<1>(result);
    CHECK_EQ(topstack, 456);
    CHECK_EQ(output_string, "");
}


TEST_CASE("vm_add") {
    SUBCASE("add_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 3521\n"
                                 "LOAD_CONST 5652\n"
                                 "ADD\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 9173);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("add_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 3215\n"
                                 "LOAD_CONST 664\n"
                                 "ADD\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 3879);
        CHECK_EQ(output_string, "");
    }
}


TEST_CASE("vm_div") {
    SUBCASE("div_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 346375\n"
                                 "LOAD_CONST 815\n"
                                 "DIV\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 425);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("div_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 22272\n"
                                 "LOAD_CONST 232\n"
                                 "DIV\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 96);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("div_zero") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 4212\n"
                                 "LOAD_CONST 0\n"
                                 "DIV\n"
                                 "EXIT\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::div_by_zero);
    }
}


TEST_CASE("vm_eq") {
    SUBCASE("eq_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 90\n"
                                 "LOAD_CONST 90\n"
                                 "EQ\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 1);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("eq_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 90\n"
                                 "LOAD_CONST 91\n"
                                 "EQ\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 0);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("eq_3") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST -52\n"
                                 "LOAD_CONST -52\n"
                                 "EQ\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 1);
        CHECK_EQ(output_string, "");
    }
}

TEST_CASE("vm_neq") {
    SUBCASE("neq_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 1234\n"
                                 "LOAD_CONST 1234\n"
                                 "NEQ\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 0);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("neq_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 1337\n"
                                 "LOAD_CONST -1338\n"
                                 "NEQ\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 1);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("neq_3") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST -9001\n"
                                 "LOAD_CONST -9001\n"
                                 "NEQ\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 0);
        CHECK_EQ(output_string, "");
    }
}


TEST_CASE("vm_dup") {
    SUBCASE("dup_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 7451\n"
                                 "DUP\n"
                                 "ADD\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 14902);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("dup_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 10\n"
                                 "DUP\n"
                                 "ADD\n"
                                 "DUP\n"
                                 "DIV\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 1);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("dup_3") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 5\n"
                                 "LOAD_CONST 10\n"
                                 "DUP\n"
                                 "ADD\n"
                                 "DUP\n"
                                 "ADD\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 40);
        CHECK_EQ(output_string, "");
    }
}


TEST_CASE("vm_write") {
    SUBCASE("write_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 60601\n"
                                 "WRITE\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 60601);
        CHECK_EQ(output_string, "60601");
    }
    SUBCASE("write_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 10\n"
                                 "LOAD_CONST 20\n"
                                 "WRITE\n"
                                 "POP\n"
                                 "WRITE\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 10);
        CHECK_EQ(output_string, "2010");
    }
}


TEST_CASE("vm_write_char") {
    SUBCASE("write_char_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 33\n"
                                 "LOAD_CONST 105\n"
                                 "LOAD_CONST 72\n"
                                 "WRITE_CHAR\n"
                                 "POP\n"
                                 "WRITE_CHAR\n"
                                 "POP\n"
                                 "WRITE_CHAR\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 33);
        CHECK_EQ(output_string, "Hi!");
    }
    SUBCASE("write_char_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 36\n"
                                 "LOAD_CONST 1337\n"
                                 "LOAD_CONST 101\n"
                                 "WRITE_CHAR\n"
                                 "POP\n"
                                 "WRITE\n"
                                 "POP\n"
                                 "WRITE_CHAR\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 36);
        CHECK_EQ(output_string, "e1337$");
    }
}


TEST_CASE("vm_jmp") {
    SUBCASE("jmp_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 13\n"
                                 "LOAD_CONST 37\n"
                                 "JMP 4\n"
                                 "POP\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 37);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("jmp_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 701\n"
                                 "JMP 3\n"
                                 "LOAD_CONST 601\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 701);
        CHECK_EQ(output_string, "");
    }
    SUBCASE("jmp_3") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "JMP 5\n"
                                 "LOAD_CONST 123\n"
                                 "LOAD_CONST 912\n"
                                 "JMP 7\n"
                                 "LOAD_CONST 852\n"
                                 "JMP 2\n"
                                 "LOAD_CONST 601\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 912);
        CHECK_EQ(output_string, "");
    }
}


TEST_CASE("vm_jmpz") {
    // test if jump works and tos is consumed
    SUBCASE("jmpz_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 13\n"
                                 "LOAD_CONST 37\n"
                                 "LOAD_CONST 0\n"
                                 "JMPZ 5\n"
                                 "POP\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 37);
        CHECK_EQ(output_string, "");
    }
    // test if comparisons, jumping and return value works
    SUBCASE("jmpz_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 701\n"
                                 "LOAD_CONST 20\n"
                                 "EQ\n"
                                 "JMPZ 6\n"
                                 "LOAD_CONST 8001\n"
                                 "JMP 7\n"
                                 "LOAD_CONST 6231\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 6231);
        CHECK_EQ(output_string, "");
    }
    // same, just the other branch
    SUBCASE("jmpz_3") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 701\n"
                                 "LOAD_CONST 701\n"
                                 "EQ\n"
                                 "JMPZ 6\n"
                                 "LOAD_CONST 8001\n"
                                 "JMP 7\n"
                                 "LOAD_CONST 6231\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 8001);
        CHECK_EQ(output_string, "");
    }
    // test if TOS is consumed on non-zero
    SUBCASE("jmpz_4") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 5\n"
                                 "LOAD_CONST 1\n"
                                 "JMPZ 4\n"
                                 "EXIT\n"
                                 "LOAD_CONST 10\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 5);
        CHECK_EQ(output_string, "");
    }
    // test if TOS is consumed on zero
    SUBCASE("jmpz_5") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 5\n"
                                 "LOAD_CONST 0\n"
                                 "JMPZ 3\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 5);
        CHECK_EQ(output_string, "");
    }
}


TEST_CASE("vm_illegal_instruction") {
    SUBCASE("unknown_mul_instruction") {
        vm::vm_state state = vm::create_vm();
        REQUIRE_THROWS_AS(
            vm::assemble(state,
                         "LOAD_CONST 9001\n"
                         "LOAD_CONST 6\n"
                         "MUL\n"
                         "EXIT\n"),
            vm::invalid_instruction);
    }
    SUBCASE("too_many_args") {
        vm::vm_state state = vm::create_vm();
        REQUIRE_THROWS_AS(
            vm::assemble(state,
                         "LOAD_CONST 13 37\n"
                         "\n"
                         "EXIT\n"),
            vm::invalid_instruction);
    }
}


TEST_CASE("vm_custom_instructions") {
    SUBCASE("mul_instruction") {
        vm::vm_state state = vm::create_vm();

        register_instruction(state, "MUL", [](vm::vm_state& vmstate, const vm::item_t arg) {
            vm::item_t a = vmstate.stack.top();
            vmstate.stack.pop();
            vm::item_t b = vmstate.stack.top();
            vmstate.stack.pop();

            vmstate.stack.push(a * b);
            return true;
        });

        auto code = vm::assemble(state,
                                 "LOAD_CONST 9001\n"
                                 "LOAD_CONST 6\n"
                                 "MUL\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 54006);
        CHECK_EQ(output_string, "");
    }

    SUBCASE("mod_instruction") {
        vm::vm_state state = vm::create_vm();

        register_instruction(state, "MOD", [](vm::vm_state& vmstate, const vm::item_t arg) {
            vm::item_t a = vmstate.stack.top();
            vmstate.stack.pop();
            vm::item_t b = vmstate.stack.top();
            vmstate.stack.pop();

            vmstate.stack.push(b % a);
            return true;
        });

        auto code = vm::assemble(state,
                                 "LOAD_CONST 53\n"
                                 "LOAD_CONST 5\n"
                                 "MOD\n"
                                 "EXIT\n");
        const auto& result = vm::run(state, code);
        const auto& topstack = std::get<0>(result);
        const auto& output_string = std::get<1>(result);
        CHECK_EQ(topstack, 3);
        CHECK_EQ(output_string, "");
    }
}


TEST_CASE("vm_stack_failure") {
    SUBCASE("exit") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "EXIT\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("add_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "ADD\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("add_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST -52\n"
                                 "ADD\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("pop") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "POP\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("div_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "DIV\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("div_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 123\n"
                                 "DIV\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("eq_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "EQ\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("eq_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 1455\n"
                                 "EQ\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("neq_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "NEQ\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("neq_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 1215\n"
                                 "NEQ\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("dup") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "DUP\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("jmpz") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "JMPZ 9001\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("write") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "WRITE\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
    SUBCASE("write_char") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state, "WRITE_CHAR\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_stackfail);
    }
}


TEST_CASE("vm_segfault") {
    SUBCASE("jump_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "JMP 2\n"
                                 "EXIT\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_segfault);
    }
    SUBCASE("jump_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "JMP -5\n"
                                 "EXIT\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_segfault);
    }
    SUBCASE("jumpz_1") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 0\n"
                                 "JMPZ 3\n"
                                 "EXIT\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_segfault);
    }
    SUBCASE("jumpz_2") {
        vm::vm_state state = vm::create_vm();
        auto code = vm::assemble(state,
                                 "LOAD_CONST 0\n"
                                 "JMPZ -40\n"
                                 "EXIT\n");
        REQUIRE_THROWS_AS(vm::run(state, code), vm::vm_segfault);
    }
}
