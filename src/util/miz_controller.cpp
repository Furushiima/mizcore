#include <filesystem>
#include <fstream>
#include <iostream>

#include "ast_block.hpp"
#include "ast_token.hpp"
#include "error_table.hpp"
#include "miz_block_parser.hpp"
#include "miz_controller.hpp"
#include "miz_lexer_handler.hpp"
#include "spdlog/spdlog.h"
#include "symbol.hpp"
#include "symbol_table.hpp"
#include "token_table.hpp"
#include "vct_lexer_handler.hpp"

using mizcore::ErrorTable;
using mizcore::MizBlockParser;
using mizcore::MizController;
using mizcore::MizLexerHandler;
using mizcore::VctLexerHandler;

void
MizController::ExecImpl(std::istream& ifs_miz, const char* vctpath)
{
    std::ifstream ifs_vct(vctpath);
    if (!ifs_vct) {
        spdlog::error("Failed to open vct file. The specified path: \"{}\"",
                      vctpath);
    }
    VctLexerHandler vct_handler(&ifs_vct);
    vct_handler.yylex();
    symbol_table_ = vct_handler.GetSymbolTable();
    MizLexerHandler miz_handler(&ifs_miz, symbol_table_);
    miz_handler.yylex();
    token_table_ = miz_handler.GetTokenTable();
    error_table_ = std::make_shared<ErrorTable>();
    MizBlockParser miz_block_parser(token_table_, error_table_);
    miz_block_parser.Parse();
    ast_root_ = miz_block_parser.GetASTRoot();
}

void
MizController::ExecFile(const char* mizpath, const char* vctpath)
{
    std::ifstream ifs_miz(mizpath);
    if (!ifs_miz) {
        spdlog::error("Failed to open miz file. The specified path: \"{}\"",
                      mizpath);
    }
    MizController::ExecImpl(ifs_miz, vctpath);
}

void
MizController::ExecBuffer(const char* buffer, const char* vctpath)
{
    std::string str_text = std::string(buffer);
    std::stringbuf str_buf(str_text);
    std::istream ifs_miz(&str_buf);
    MizController::ExecImpl(ifs_miz, vctpath);
}
