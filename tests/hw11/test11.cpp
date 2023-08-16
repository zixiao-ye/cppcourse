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

#include "hw11.h"
#include <string>

struct my_key {
    // implicit char[]->my_key conversions :)
    constexpr my_key(const char *key_) : key{key_} {}

    constexpr bool operator ==(const my_key& other) const {
        return std::string_view{this->key} == other.key;
    }
    const char *key;
};

struct my_value {
    const int value;
};



TEST_CASE("constexprmap_test") {
		{
		auto map = create_cexpr_map<my_key, my_value>();

		static_assert(std::is_same_v<decltype(map)::key_type, my_key>);
		static_assert(std::is_same_v<decltype(map)::value_type, my_value>);
	}

	static_assert(create_cexpr_map<int, int>(std::make_pair(0, 42)).size() == 1,
	              "wrong size");
	static_assert(create_cexpr_map<int, int>(std::make_pair(0, 42),
	                                         std::make_pair(13, 37)).size() == 2,
	              "wrong size");

	static_assert(not create_cexpr_map<int, int>().contains(9001),
	              "empty map doesn't contain anything");
	static_assert(create_cexpr_map<int, int>(std::make_pair(42, 0),
	                                         std::make_pair(13, 37)).contains(42),
	              "contained element missing");
	static_assert(create_cexpr_map<int, int>(std::make_pair(42, 0),
	                                         std::make_pair(13, 37)).contains(13),
	              "contained element missing");
	static_assert(not create_cexpr_map<int, int>(std::make_pair(42, 0),
	                                             std::make_pair(13, 37)).contains(9001),
	              "uncontained element seems to be contained.");

	static_assert(create_cexpr_map<int, int>(std::make_pair(42, 9001),
	                                         std::make_pair(13, 37)).get(42) == 9001,
	              "fetched wrong value");
	static_assert(create_cexpr_map<int, int>(std::make_pair(42, 9001),
	                                         std::make_pair(13, 37)).get(13) == 37,
	              "fetched wrong value");

	static_assert(create_cexpr_map<int, int>(std::make_pair(42, 9001),
	                                         std::make_pair(13, 37)).get(13) == 37,
	              "fetched wrong value");

	{
		// oh dear c++
		constexpr auto map = create_cexpr_map<my_key, int>(
			std::pair(my_key{"stuff"}, 9001),
			std::pair("gschicht", 37));

		static_assert(map.get("stuff") == 9001,
		              "fetched wrong value");
		static_assert(map.size() == 2,
		              "fetched wrong value");
	}

	{
		// type deduction check
		// and mix compile and runtime
		constexpr CexprMap cmap {
			std::pair(0, 0),
			std::pair(13, 37),
			std::pair(42, 9001)
		};

		// runtime
		CHECK_EQ(cmap.contains(0), true);
		CHECK_EQ(cmap.contains(18), false);

		CHECK_EQ(cmap.size(), 3);
		CHECK_EQ(cmap.get(13), 37);
		CHECK_EQ(cmap.get(42), 9001);
		CHECK_EQ(cmap[42], 9001);

		CHECK_EQ(cmap.contains(13), true);
		CHECK_EQ(cmap.contains(9001), false);
		CHECK_THROWS_AS(cmap.get(9001), std::out_of_range);
		CHECK_THROWS_AS(cmap[235], std::out_of_range);

		// compiletime
		static_assert(cmap.get(13) == 37, "fetched wrong value");
		static_assert(cmap[13] == 37, "fetched wrong value");
	}

	{
		// unfortunately I didn't figure out a way
		// (except preprocessor?) to test the duplicate key detection
		// at compiletime without breaking the whole program...
		CHECK_THROWS_AS(CexprMap(std::pair(13, 37), std::pair(13, 42)),
		                std::invalid_argument);
	}
}
