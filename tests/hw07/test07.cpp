/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#include <limits>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

// if you activate this, doctest won't swallow exceptions
// #define DOCTEST_CONFIG_NO_EXCEPTIONS

#include <doctest/doctest.h>

#ifndef DOCTEST_REQUIRE_NOTHROW
#define DOCTEST_REQUIRE_NOTHROW(x) do { x; } while (0)
#endif


#include "hw07.h"

// require at least c++20
static_assert(__cplusplus >= 202002L);


std::string str_repeat(int n, std::string_view what) {
    std::ostringstream os;
    for(int i = 0; i < n; i++)
        os << what;
    return std::move(os).str();
}


TEST_CASE("FileContent") {
    REQUIRE_NOTHROW(FileContent{});

    // we need to allocate a big buffer.
    // otherwise the string will the data "locally" (on the stack)
    // and then it's copied although we move the string.
    std::string buf = str_repeat(5000, "1234567890");

    SUBCASE("copy_init") {
        // copy the content
        FileContent fc{buf};
        // content should now be equal
        CHECK_EQ(*fc.get(), buf);
        // pointers will be different
        CHECK_NE(fc.get()->data(), buf.data());
    }

    SUBCASE("move_init") {
        // remember the ptr
        const std::string::value_type* bufptr = buf.data();

        // move the content
        FileContent fc{std::move(buf)};

        // pointers will be the same
        CHECK_EQ(fc.get()->data(), bufptr);
    }

    SUBCASE("size") {
        std::string bla = "gschichten";
        FileContent fc{std::move(bla)};
        CHECK_EQ(fc.get_size(), 10);
    }

    SUBCASE("chararray_init") {
        const char* stuff = "legacysoftware";
        FileContent fc{stuff};
        CHECK_EQ(fc.get_size(), 14);
        CHECK_EQ(*fc.get(), stuff);
    }

    SUBCASE("copy_init") {
        // because of doctest magic, buf is reinitialized for each subcase!

        FileContent fc1{std::move(buf)};
        FileContent fc2{fc1};

        // content should now be equal
        CHECK_EQ(*fc1.get(), *fc2.get());
        // pointers will be the same
        CHECK_EQ(fc1.get()->data(), fc2.get()->data());
    }

    SUBCASE("move_init") {
        // because of doctest magic, buf is reinitialized for each subcase!

        // first copy buf into a new file content, then move the file content
        FileContent fc1{buf};
        const std::string::value_type* fc1ptr = fc1.get()->data();

        FileContent fc2{std::move(fc1)};

        // content should now be equal
        CHECK_EQ(*fc2.get(), buf);
        // fc2 & buf pointers will be different
        CHECK_NE(fc2.get()->data(), buf.data());
        // the pointer fc1 had should be the same that fc2 now has
        CHECK_EQ(fc2.get()->data(), fc1ptr);

        // fc1 is now "empty" since we moved from it
        CHECK_EQ(fc1.get(), nullptr);
    }
}


TEST_CASE("Audio") {
    SUBCASE("type") {
        Audio file{};
        CHECK_EQ(file.get_type(), "AUD");
    }

    SUBCASE("rename") {
        Audio file{};
        // should be false by default
        CHECK_EQ(file.rename(""), false);
        CHECK_EQ(file.rename("rolf"), false);
    }

    SUBCASE("construction_1") {
        Audio file{FileContent{"magic audio file"}, 20};

        CHECK_EQ(file.get_type(), "AUD");
        CHECK_EQ(file.get_duration(), 20);
        CHECK_EQ(file.get_size(), 16);
        CHECK_EQ(*file.get_content().get(), "magic audio file");
        CHECK_EQ(file.get_raw_size(), 3840000);
    }

    SUBCASE("construction_2") {
        Audio file{FileContent{"great audio file"}, 25};

        CHECK_EQ(file.get_type(), "AUD");
        CHECK_EQ(file.get_duration(), 25);
        CHECK_EQ(file.get_size(), 16);
        CHECK_EQ(*file.get_content().get(), "great audio file");
        CHECK_EQ(file.get_raw_size(), 4800000);
    }

    SUBCASE("construction_3") {
        Audio file{FileContent{"impressive audio file"}, 415};

        CHECK_EQ(file.get_type(), "AUD");
        CHECK_EQ(file.get_duration(), 415);
        CHECK_EQ(file.get_size(), 21);
        CHECK_EQ(*file.get_content().get(), "impressive audio file");
        CHECK_EQ(file.get_raw_size(), 79680000);
    }

    SUBCASE("update_1") {
        Audio file{FileContent{"impressive audio file"}, 415};
        file.update(FileContent{"upgrayedd"}, 100);

        CHECK_EQ(file.get_type(), "AUD");
        CHECK_EQ(file.get_duration(), 100);
        CHECK_EQ(file.get_size(), 9);
        CHECK_EQ(*file.get_content().get(), "upgrayedd");
        CHECK_EQ(file.get_raw_size(), 19200000);
    }

    SUBCASE("update_2") {
        Audio file{FileContent{"random audio file"}, 4};
        file.update(FileContent{"ulrd omoeiaf niad"}, 59);

        CHECK_EQ(file.get_type(), "AUD");
        CHECK_EQ(file.get_duration(), 59);
        CHECK_EQ(file.get_size(), 17);
        CHECK_EQ(*file.get_content().get(), "ulrd omoeiaf niad");
        CHECK_EQ(file.get_raw_size(), 11328000);
    }

    SUBCASE("update_move") {
        std::string buf = str_repeat(5000, "1234567890");

        Audio file{FileContent{"innocent audio file"}, 9001};
        FileContent massive_content{buf};
        const std::string::value_type* dataptr = massive_content.get()->data();
        file.update(std::move(massive_content), 9001);

        // the data pointer in the file should be the same as the content had before updating
        CHECK_EQ(file.get_content().get()->data(), dataptr);

        CHECK_EQ(file.get_type(), "AUD");
        CHECK_EQ(file.get_duration(), 9001);
        CHECK_EQ(file.get_size(), 50000);
        CHECK_EQ(*file.get_content().get(), buf);
        CHECK_EQ(file.get_raw_size(), 1728192000);
    }
}


TEST_CASE("Document") {
    SUBCASE("type") {
        Document file{};
        CHECK_EQ(file.get_type(), "DOC");
    }

    SUBCASE("rename") {
        Document file{};
        // should be false by default
        CHECK_EQ(file.rename(""), false);
        CHECK_EQ(file.rename("rolf"), false);
    }

    SUBCASE("construction_1") {
        Document file{FileContent{"magic document file"}};

        CHECK_EQ(file.get_type(), "DOC");
        CHECK_EQ(file.get_character_count(), 17);
        CHECK_EQ(file.get_size(), 19);
        CHECK_EQ(*file.get_content().get(), "magic document file");
        CHECK_EQ(file.get_raw_size(), 19);
    }

    SUBCASE("construction_2") {
        Document file{FileContent{"great document file"}};

        CHECK_EQ(file.get_type(), "DOC");
        CHECK_EQ(file.get_character_count(), 17);
        CHECK_EQ(file.get_size(), 19);
        CHECK_EQ(*file.get_content().get(), "great document file");
        CHECK_EQ(file.get_raw_size(), 19);
    }

    SUBCASE("construction_3") {
        Document file{FileContent{"impressive document file"}};

        CHECK_EQ(file.get_type(), "DOC");
        CHECK_EQ(file.get_character_count(), 22);
        CHECK_EQ(file.get_size(), 24);
        CHECK_EQ(*file.get_content().get(), "impressive document file");
        CHECK_EQ(file.get_raw_size(), 24);
    }

    SUBCASE("update_1") {
        Document file{FileContent{"impressive document file"}};
        file.update(FileContent{"upgrayedd"});

        CHECK_EQ(file.get_type(), "DOC");
        CHECK_EQ(file.get_character_count(), 9);
        CHECK_EQ(file.get_size(), 9);
        CHECK_EQ(*file.get_content().get(), "upgrayedd");
        CHECK_EQ(file.get_raw_size(), 9);
    }

    SUBCASE("update_2") {
        Document file{FileContent{"random document file"}};
        file.update(FileContent{"fu elntrom icmdeodna"});

        CHECK_EQ(file.get_type(), "DOC");
        CHECK_EQ(file.get_character_count(), 18);
        CHECK_EQ(file.get_size(), 20);
        CHECK_EQ(*file.get_content().get(), "fu elntrom icmdeodna");
        CHECK_EQ(file.get_raw_size(), 20);
    }

    SUBCASE("update_move") {
        std::string buf = str_repeat(5000, "123456789 ");

        Document file{FileContent{"innocent document file"}};
        FileContent massive_content{buf};
        const std::string::value_type* dataptr = massive_content.get()->data();
        file.update(std::move(massive_content));

        // the data pointer in the file should be the same as the content had before updating
        CHECK_EQ(file.get_content().get()->data(), dataptr);

        CHECK_EQ(file.get_type(), "DOC");
        CHECK_EQ(file.get_character_count(), 45000);
        CHECK_EQ(file.get_size(), 50000);
        CHECK_EQ(*file.get_content().get(), buf);
        CHECK_EQ(file.get_raw_size(), 50000);
    }
}


TEST_CASE("Image") {
    SUBCASE("type") {
        Image file{};
        CHECK_EQ(file.get_type(), "IMG");
    }

    SUBCASE("rename") {
        Image file{};
        // should be false by default
        CHECK_EQ(file.rename(""), false);
        CHECK_EQ(file.rename("rolf"), false);
    }

    SUBCASE("construction_1") {
        Image file{FileContent{"magic image file"}, {1920, 1080}};

        CHECK_EQ(file.get_type(), "IMG");
        CHECK_EQ(file.get_resolution(), Image::resolution_t{1920, 1080});
        CHECK_EQ(file.get_size(), 16);
        CHECK_EQ(*file.get_content().get(), "magic image file");
        CHECK_EQ(file.get_raw_size(), 8294400);
    }

    SUBCASE("construction_2") {
        Image file{FileContent{"great image file"}, {800, 600}};

        CHECK_EQ(file.get_type(), "IMG");
        CHECK_EQ(file.get_resolution(), Image::resolution_t{800, 600});
        CHECK_EQ(*file.get_content().get(), "great image file");
        CHECK_EQ(file.get_raw_size(), 1920000);
    }

    SUBCASE("construction_3") {
        Image file{FileContent{"impressive image file"}, {3840, 2160}};

        CHECK_EQ(file.get_type(), "IMG");
        CHECK_EQ(file.get_resolution(), Image::resolution_t{3840, 2160});
        CHECK_EQ(file.get_size(), 21);
        CHECK_EQ(*file.get_content().get(), "impressive image file");
        CHECK_EQ(file.get_raw_size(), 33177600);
    }

    SUBCASE("update_1") {
        Image file{FileContent{"impressive image file"}, {640, 480}};
        file.update(FileContent{"upgrayedd"}, {1920, 1080});

        CHECK_EQ(file.get_type(), "IMG");
        CHECK_EQ(file.get_resolution(), Image::resolution_t{1920, 1080});
        CHECK_EQ(file.get_size(), 9);
        CHECK_EQ(*file.get_content().get(), "upgrayedd");
        CHECK_EQ(file.get_raw_size(), 8294400);
    }

    SUBCASE("update_2") {
        Image file{FileContent{"random image file"}, {20, 20}};
        file.update(FileContent{"nm ro failemediag"}, {50, 50});

        CHECK_EQ(file.get_type(), "IMG");
        CHECK_EQ(file.get_resolution(), Image::resolution_t{50, 50});
        CHECK_EQ(file.get_size(), 17);
        CHECK_EQ(*file.get_content().get(), "nm ro failemediag");
        CHECK_EQ(file.get_raw_size(), 10000);
    }

    SUBCASE("update_move") {
        std::string buf = str_repeat(5000, "1234567890");

        Image file{FileContent{"innocent image file"}, {800, 600}};
        FileContent massive_content{buf};
        const std::string::value_type* dataptr = massive_content.get()->data();
        file.update(std::move(massive_content), {1920, 1080});

        // the data pointer in the file should be the same as the content had before updating
        CHECK_EQ(file.get_content().get()->data(), dataptr);

        CHECK_EQ(file.get_type(), "IMG");
        CHECK_EQ(file.get_resolution(), Image::resolution_t{1920, 1080});
        CHECK_EQ(file.get_size(), 50000);
        CHECK_EQ(*file.get_content().get(), buf);
        CHECK_EQ(file.get_raw_size(), 8294400);
    }

    SUBCASE("content_owning") {
        std::string buf = str_repeat(5000, "lol");
        std::shared_ptr<const std::string> access;
        {
            // copy the file content string
            Image file{FileContent{buf}, {800, 600}};
            access = file.get_content().get();

            // now there have to be two owners: the image file, and our content pointer here.
            CHECK_EQ(access.use_count(), 2);
            CHECK_EQ(*access, buf);
            // image is deallocated, therefore the filecontent is freed
        }
        // now only the pointer in this function owns the data, since image is gone.
        CHECK_EQ(access.use_count(), 1);
        CHECK_EQ(*access, buf);
    }
}


TEST_CASE("Video") {
    SUBCASE("type") {
        Video file{};
        CHECK_EQ(file.get_type(), "VID");
    }

    SUBCASE("rename") {
        Video file{};
        // should be false by default
        CHECK_EQ(file.rename(""), false);
        CHECK_EQ(file.rename("rolf"), false);
    }

    SUBCASE("construction_1") {
        Video file{FileContent{"magic video file"}, {1920, 1080}, 600.5};

        CHECK_EQ(file.get_type(), "VID");
        CHECK_EQ(file.get_duration(), doctest::Approx(600.5));
        CHECK_EQ(file.get_resolution(), Video::resolution_t{1920, 1080});
        CHECK_EQ(file.get_size(), 16);
        CHECK_EQ(*file.get_content().get(), "magic video file");
        CHECK_EQ(file.get_raw_size(), 112067712000);
    }

    SUBCASE("construction_2") {
        Video file{FileContent{"great video file"}, {800, 600}, 40.25};

        CHECK_EQ(file.get_type(), "VID");
        CHECK_EQ(file.get_duration(), doctest::Approx(40.25));
        CHECK_EQ(file.get_resolution(), Video::resolution_t{800, 600});
        CHECK_EQ(*file.get_content().get(), "great video file");
        CHECK_EQ(file.get_raw_size(), 1738080000);
    }

    SUBCASE("construction_3") {
        Video file{FileContent{"impressive video file"}, {3840, 2160}, 60.0 * 60.0 * 2.2};

        CHECK_EQ(file.get_type(), "VID");
        CHECK_EQ(file.get_duration(), doctest::Approx(60.0 * 60.0 * 2.2));
        CHECK_EQ(file.get_resolution(), Video::resolution_t{3840, 2160});
        CHECK_EQ(file.get_size(), 21);
        CHECK_EQ(*file.get_content().get(), "impressive video file");
        CHECK_EQ(file.get_raw_size(), 5912248320000);
    }

    SUBCASE("update_1") {
        Video file{FileContent{"impressive video file"}, {640, 480}, 180.1};
        file.update(FileContent{"upgrayedd"}, {1920, 1080}, 100);

        CHECK_EQ(file.get_type(), "VID");
        CHECK_EQ(file.get_duration(), doctest::Approx(100));
        CHECK_EQ(file.get_resolution(), Video::resolution_t{1920, 1080});
        CHECK_EQ(file.get_size(), 9);
        CHECK_EQ(*file.get_content().get(), "upgrayedd");
        CHECK_EQ(file.get_raw_size(), 18662400000);
    }

    SUBCASE("update_2") {
        Video file{FileContent{"random video file"}, {20, 20}, 25.8};
        file.update(FileContent{"e arm dioleovdinf"}, {50, 50}, 50.50);

        CHECK_EQ(file.get_type(), "VID");
        CHECK_EQ(file.get_duration(), doctest::Approx(50.50));
        CHECK_EQ(file.get_resolution(), Video::resolution_t{50, 50});
        CHECK_EQ(file.get_size(), 17);
        CHECK_EQ(*file.get_content().get(), "e arm dioleovdinf");
        CHECK_EQ(file.get_raw_size(), 11362500);
    }

    SUBCASE("update_move") {
        std::string buf = str_repeat(5000, "1234567890");

        Video file{FileContent{"innocent video file"}, {800, 600}, 10.5};
        FileContent massive_content{buf};
        const std::string::value_type* dataptr = massive_content.get()->data();
        file.update(std::move(massive_content), {1920, 1080}, 9001.12);

        // the data pointer in the file should be the same as the content had before updating
        CHECK_EQ(file.get_content().get()->data(), dataptr);

        CHECK_EQ(file.get_type(), "VID");
        CHECK_EQ(file.get_duration(), doctest::Approx(9001.12));
        CHECK_EQ(file.get_resolution(), Video::resolution_t{1920, 1080});
        CHECK_EQ(file.get_size(), 50000);
        CHECK_EQ(*file.get_content().get(), buf);
        CHECK_EQ(file.get_raw_size(), 1679821286400);
    }
}


TEST_CASE("Filesystem") {
    auto fs = std::make_shared<Filesystem>();
    // just the pointer in this function should keep the fs alive
    CHECK_EQ(fs.use_count(), 1);

    CHECK_EQ(fs->register_file("movie_script.org", std::make_shared<Document>("great plot")), true);
    CHECK_EQ(fs->register_file("movie.av1", std::make_shared<Video>("awesome content", Video::resolution_t{1920, 1080}, 1200.0)), true);
    CHECK_EQ(fs->register_file("landscape.avif", std::make_shared<Image>("best picture", Image::resolution_t{1920, 1080})), true);
    CHECK_EQ(fs->register_file("music.opus", std::make_shared<Audio>("relaxing music", 420)), true);

    CHECK_EQ(fs->register_file("secret_diary.doc", std::make_shared<Document>("bad plot")), true);
    CHECK_EQ(fs->register_file("bad_movie.hevc", std::make_shared<Video>("boring content", Video::resolution_t{640, 480}, 1600.0)), true);
    CHECK_EQ(fs->register_file("football.wmf", std::make_shared<Image>("indecipherable image", Image::resolution_t{433, 512})), true);
    CHECK_EQ(fs->register_file("vacuum.wma", std::make_shared<Audio>("annoying music", 80)), true);

    // just the pointer in this function should keep the fs alive
    // if this check fails, something else is keeping fs alive, too.
    CHECK_EQ(fs.use_count(), 1);

    SUBCASE("register") {
        auto fs2 = std::make_shared<Filesystem>();
        // empty name not allowed
        CHECK_EQ(fs2->register_file("", std::make_shared<Audio>("nope", 0)), false);
        // empty file pointer not allowed
        CHECK_EQ(fs2->register_file("great", nullptr), false);

        CHECK_EQ(fs->get_file("music.opus")->get_name(), "music.opus");
        CHECK_EQ(fs->get_file("vacuum.wma")->get_name(), "vacuum.wma");
        CHECK_EQ(fs.use_count(), 1);
    }

    SUBCASE("reregister") {
        auto fs2 = std::make_shared<Filesystem>();

        // file already registered in other filesystem
        CHECK_EQ(fs2->register_file("rolf.opus", fs->get_file("music.opus")), false);
        CHECK_EQ(fs->get_file("music.opus")->get_name(), "music.opus");
    }

    SUBCASE("get_file") {
        CHECK_EQ(fs->get_file_count(), 8);
        CHECK_EQ(fs->in_use(), 107);

        auto&& file1 = fs->get_file("football.wmf");
        CHECK_NE(file1, nullptr);
        CHECK_EQ(*file1->get_content().get(), "indecipherable image");

        auto&& file2 = fs->get_file("movie.av1");
        CHECK_NE(file2, nullptr);
        CHECK_EQ(*file2->get_content().get(), "awesome content");

        CHECK_EQ(fs->get_file_count(), 8);
    }

    SUBCASE("remove_file") {
        CHECK_EQ(fs->get_file_count(), 8);

        CHECK_EQ(fs->remove_file("nonexistant"), false);
        CHECK_EQ(fs->remove_file("football.wmf"), true);
        CHECK_EQ(fs->get_file_count(), 7);
        CHECK_EQ(fs->in_use(), 87);

        {
            auto&& file = fs->get_file("football.wmf");
            CHECK_EQ(file, nullptr);
            CHECK_EQ(fs->remove_file("football.wmf"), false);
        }
        {
            auto&& file = fs->get_file("movie.av1");
            CHECK_NE(file, nullptr);
            CHECK_EQ(*file->get_content().get(), "awesome content");
            CHECK_EQ(fs->remove_file("movie.av1"), true);
            auto&& file2 = fs->get_file("movie.av1");
            CHECK_EQ(file2, nullptr);
            CHECK_EQ(fs->get_file_count(), 6);
        }
    }

    SUBCASE("rename_file") {
        CHECK_EQ(fs->get_file_count(), 8);
        CHECK_EQ(fs->in_use(), 107);
        CHECK_EQ(fs->rename_file("what.opus", "notthere.opus"), false);

        {
            // check content
            auto&& file = fs->get_file("music.opus");
            CHECK_NE(file, nullptr);
            CHECK_EQ(*file->get_content().get(), "relaxing music");
        }

        CHECK_EQ(fs->rename_file("music.opus", "relaxing.opus"), true);

        {
            // check content
            auto&& file = fs->get_file("relaxing.opus");
            CHECK_NE(file, nullptr);
            CHECK_EQ(*file->get_content().get(), "relaxing music");
            // old file must be gone now
            auto&& file2 = fs->get_file("music.opus");
            CHECK_EQ(file2, nullptr);
        }

        CHECK_EQ(fs->get_file_count(), 8);
        CHECK_EQ(fs->in_use(), 107);
        CHECK_EQ(fs->remove_file("relaxing.opus"), true);

        {
            auto&& file = fs->get_file("relaxing.opus");
            CHECK_EQ(file, nullptr);
        }

        CHECK_EQ(fs->get_file_count(), 7);
        CHECK_EQ(fs->in_use(), 93);
    }

    SUBCASE("files_in_size_range") {
        CHECK_EQ(fs->files_in_size_range(0, 0).size(), 0);
        CHECK_EQ(fs->files_in_size_range(std::numeric_limits<size_t>::max(), 0).size(), 8);
        CHECK_EQ(fs->files_in_size_range(std::numeric_limits<size_t>::max(),
                                         std::numeric_limits<size_t>::max()).size(), 0);
        CHECK_EQ(fs->files_in_size_range(10).size(), 2);
        {
            auto files = fs->files_in_size_range(12);
            CHECK_EQ(files.size(), 3);
            std::vector<std::string> expected{"secret_diary.doc", "landscape.avif", "movie_script.org"};
            size_t found = 0;
            for (auto&& exp : expected) {
                for (auto&& result : files) {
                    if (result->get_name() == exp) {
                        found += 1;
                        // check if the content was not copied
                        CHECK_EQ(fs->get_file(exp)->get_content().get(), result->get_content().get());
                    }
                }
            }
            CHECK_EQ(found, 3);
        }
        {
            auto files = fs->files_in_size_range(14, 10);
            CHECK_EQ(files.size(), 5);
            std::vector<std::string> expected{"vacuum.wma", "bad_movie.hevc",
                                              "music.opus", "landscape.avif",
                                              "movie_script.org"};
            size_t found = 0;
            for (auto&& exp : expected) {
                for (auto&& result : files) {
                    if (result->get_name() == exp) {
                        found += 1;
                        CHECK_EQ(fs->get_file(exp)->get_content().get(), result->get_content().get());
                    }
                }
            }
            CHECK_EQ(found, 5);
        }
    }

    // still, nothing but this function should keep the filesystem pointer alive.
    CHECK_EQ(fs.use_count(), 1);
}


TEST_CASE("File_rename") {
    auto fs = std::make_shared<Filesystem>();
    fs->register_file("thesis.org", std::make_shared<Document>("very science"));
    fs->register_file("samples.av1", std::make_shared<Video>("brains", Video::resolution_t{1920, 1080}, 100.0));
    fs->register_file("funny_cats.mpg", std::make_shared<Video>("cute", Video::resolution_t{640, 480}, 60.0));

    {
        auto&& file = fs->get_file("samples.av1");
        CHECK_NE(file, nullptr);
        CHECK_EQ(file->get_name(), "samples.av1");
        CHECK_EQ(file->rename("brains.av1"), true);
        CHECK_EQ(file->get_name(), "brains.av1");

        // name already occupied in fs
        CHECK_EQ(file->rename("brains.av1"), false);

        // fs must now point to the same file
        CHECK_EQ(fs->get_file("brains.av1"), file);
    }
    {
        auto&& file = fs->get_file("thesis.org");
        CHECK_NE(file, nullptr);
        CHECK_EQ(file->get_name(), "thesis.org");
        CHECK_EQ(file->rename("tothemoon.org"), true);
        CHECK_EQ(file->get_name(), "tothemoon.org");

        // fs must now point to the same file
        CHECK_EQ(fs->get_file("tothemoon.org"), file);
    }
    {
        auto&& file = fs->get_file("funny_cats.mpg");
        CHECK_NE(file, nullptr);
        CHECK_EQ(file->get_name(), "funny_cats.mpg");
        CHECK_EQ(file->rename("funniest_cats.mpg"), true);
        CHECK_EQ(fs->rename_file("funniest_cats.mpg", "mediocre_cats.mpg"), true);
        CHECK_EQ(file->get_name(), "mediocre_cats.mpg");
        CHECK_EQ(file->rename("fun_cats.mpg"), true);
        CHECK_EQ(file->get_name(), "fun_cats.mpg");
        CHECK_EQ(fs->get_file("fun_cats.mpg"), file);
    }

    // just the pointer in this function should keep the fs alive
    CHECK_EQ(fs.use_count(), 1);

    {
        std::shared_ptr<File> longliving;
        {
            auto fs2 = std::make_shared<Filesystem>();
            fs2->register_file("paper.org", std::make_shared<Document>("much research"));
            longliving = fs2->get_file("paper.org");
            CHECK_NE(longliving, nullptr);
            CHECK_EQ(fs2.use_count(), 1);
        }

        // here, fs2 was deallocated, but the file is still living
        // since the filesystem is gone, renaming must no longer work.
        CHECK_EQ(longliving->rename("best_paper.org"), false);
    }
}

