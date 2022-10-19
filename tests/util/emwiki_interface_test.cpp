#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "ast_block.hpp"
#include "doctest/doctest.h"
#include "emwiki_interface.hpp"
#include "file_handling_tools.hpp"
#include "spdlog/spdlog.h"

using mizcore::EmwikiInterface;
namespace fs = std::filesystem;

namespace {

const fs::path&
TEST_DIR()
{
    static fs::path test_dir = fs::path(__FILE__).parent_path();
    return test_dir;
}

} // namespace

TEST_CASE("test emwiki_interface")
{
    auto mizpath = TEST_DIR() / "data" / "numerals.miz";
    auto vctpath = TEST_DIR().parent_path() / "parser" / "data" / "mml.vct";
    mizcore::EmwikiInterface emwiki_interface(vctpath.string().c_str());
    std::ifstream ifs_miz(mizpath);
    CHECK(ifs_miz.good());
    // ifs_mizをcharに変換(生の定理) https://www.miraclelinux.com/tech-blog/1n4hgx
    emwiki_interface.Exec(std::string((std::istreambuf_iterator<char>(ifs_miz)),
                                      std::istreambuf_iterator<char>())
                            .c_str());

    if (!fs::exists(TEST_DIR() / "result")) {
        fs::create_directory(TEST_DIR() / "result");
    }
    fs::path result_file_path = TEST_DIR() / "result" / "numerals_blocks.json";
    nlohmann::json json;
    auto ast_root = emwiki_interface.GetASTRoot();
    ast_root->ToJson(json);
    mizcore::write_json_file(json, result_file_path);
    fs::path expected_file_path =
      TEST_DIR() / "expected" / "numerals_blocks.json";

    auto json_diff =
      mizcore::json_file_diff(result_file_path, expected_file_path);

    CHECK(json_diff.empty());
    if (!json_diff.empty()) {
        fs::path diff_file_path =
          TEST_DIR() / "result" / "numerals_blocks_diff.json";
        mizcore::write_json_file(json_diff, diff_file_path);
    } else {
        remove(result_file_path.string().c_str());
    }
}
