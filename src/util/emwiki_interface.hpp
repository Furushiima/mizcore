#pragma once

#include <memory>

namespace mizcore {

class ASTBlock;
class SymbolTable;
class TokenTable;
class ErrorTable;

class EmwikiInterface
{
  public:
    EmwikiInterface(const char* vctpath);
    virtual ~EmwikiInterface() = default;
    EmwikiInterface(EmwikiInterface const&) = delete;
    EmwikiInterface(EmwikiInterface&&) = delete;
    EmwikiInterface& operator=(EmwikiInterface const&) = delete;
    EmwikiInterface& operator=(EmwikiInterface&&) = delete;

    void Exec(const char* mizpath);
    std::shared_ptr<TokenTable> GetTokenTable() const { return token_table_; }
    std::shared_ptr<ASTBlock> GetASTRoot() const { return ast_root_; }
    std::shared_ptr<ErrorTable> GetErrorTable() const { return error_table_; }
    //以下消す
    std::string GetDoc() const { return doc_; }

  private:
    std::shared_ptr<SymbolTable> symbol_table_;
    std::shared_ptr<TokenTable> token_table_;
    std::shared_ptr<ASTBlock> ast_root_;
    std::shared_ptr<ErrorTable> error_table_;
    //以下消す
    std::string doc_;
};

} // namespace mizcore
