#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ast_block.hpp"
#include "ast_token.hpp"
#include "emwiki_interface.hpp"
#include "error_table.hpp"
#include "miz_block_parser.hpp"
#include "miz_lexer_handler.hpp"
#include "spdlog/spdlog.h"
#include "symbol.hpp"
#include "symbol_table.hpp"
#include "token_table.hpp"
#include "vct_lexer_handler.hpp"

using mizcore::EmwikiInterface;
using mizcore::ErrorTable;
using mizcore::MizBlockParser;
using mizcore::MizLexerHandler;
using mizcore::VctLexerHandler;

EmwikiInterface::EmwikiInterface(const char* vctpath)
{
    std::ifstream ifs_vct(vctpath);
    if (!ifs_vct) {
        spdlog::error("Failed to open vct file. The specified path: \"{}\"",
                      vctpath);
    }
    VctLexerHandler vct_handler(&ifs_vct);
    vct_handler.yylex();
    symbol_table_ = vct_handler.GetSymbolTable();
}

void
EmwikiInterface::Exec(const char* doc)
{
    // 一旦std::stringbufへ変換し, istreamへ変換（直接は変換できない為
    // std::string str_doc = std::string(doc);
    // std::string str_doc = "theorem Th2: for X being non empty TopStruct, g being Function of X,R^1,B being Subset of X,";
    // std::istringstream iss_miz(str_doc);
    // std::ifstream ifs_miz(str_doc.c_str());
    // std::stringbuf strBuf(str_doc);
    // std::istream ifs_miz( &strBuf );
    // std::ifstream ifs_miz = static_cast<std::ifstream>(istream);

    // 定理を受け取る版
    std::string str_doc = std::string(doc);
    std::stringbuf strBuf(str_doc);
    std::istream ifs_miz( &strBuf );


    // パスを受け取る版(こっちでは上手くいく)
    // std::string path = "/home/g063ff/mizcore/jgraph_4.abs";
    // auto mizpath = path.c_str();
    // std::ifstream ifs_miz(mizpath);

    MizLexerHandler miz_handler(&ifs_miz, symbol_table_);
    miz_handler.yylex();
    token_table_ = miz_handler.GetTokenTable();
    error_table_ = std::make_shared<ErrorTable>();
    MizBlockParser miz_block_parser(token_table_, error_table_);
    // ここでセグメンテーションエラー
    miz_block_parser.Parse();
    // doc_.assign(str_doc);
    ast_root_ = miz_block_parser.GetASTRoot();
}
