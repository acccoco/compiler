#include "pch.h"

/*
  TokenReader �Ĳ���
 */

class TokenReaderTest : public ::testing::Test {
protected:
    TokenReader* reader = nullptr;
    /*
     ����һ��Reader����
    */
    void SetUp() override {
        auto tokens = ConstructTokens();
        reader = new TokenReader(tokens);
    }
    void TearDown() override {
        delete reader;
    }

    /* 
     tokens �����ݼ���
     10��10�У����ǹؼ��� "acc row, column"
    */
    vector<vector<shared_ptr<Token>>> ConstructTokens() {
        vector<vector<shared_ptr<Token>>> tokens;
        for (int i = 0; i < 10; ++i) {
            vector<shared_ptr<Token>> tokensRow;
            for (int j = 0; j < 10; ++j) {
                char temp[256];
                string strValue = "acc ";
                _itoa_s(i + 1, temp, 10);
                strValue += temp;
                strValue += ", ";
                _itoa_s(j + 1, temp, 10);
                strValue += temp;
                tokensRow.emplace_back(new Token(TokenTypeEnum::IDENTIFIER, strValue));
            }
            tokens.push_back(tokensRow);
        }
        return tokens;
    }
};

/*
 ����Index���ԵĶ�д�Ƿ�����
*/
TEST_F(TokenReaderTest, Index) {
    EXPECT_EQ(reader->Index.Get(), 0);     // ��ʼindexΪ0
    reader->RecoveryIndex(1);
    EXPECT_EQ(reader->Index.Get(), 1);
}

/*
 ����TokenCount����
*/
TEST_F(TokenReaderTest, TokenCount) {
    EXPECT_EQ(reader->TokenCount.Get(), 100);
}

/*
 ����SeekToken
 SeekToken����ı� index��count������
 SeekToken����������ȡֵ
*/
TEST_F(TokenReaderTest, SeekToken) {
    EXPECT_EQ(reader->SeekToken()->StrValue.Get(), "acc 1, 1");
    EXPECT_EQ(reader->Index.Get(), 0);
    EXPECT_EQ(reader->TokenCount.Get(), 100);
}
/*
 ����GetToken
 GetTokenӦ�û�ı�index
*/
TEST_F(TokenReaderTest, GetToken) {
    // ����һ�ζ���
    reader->RecoveryIndex(26);
    auto token = reader->GetToken();
    EXPECT_EQ(token->StrValue.Get(), "acc 3, 7");
    EXPECT_EQ(token->LineNum.Get(), 3);
    EXPECT_EQ(reader->Index.Get(), 27);
    EXPECT_EQ(reader->GetLastLineNum(), 3);
    EXPECT_EQ(reader->GetCurLineNum(), 3);
}
/*
 ���Ա߽�
 �ߵ��߽�󣬾��޷�������
*/
TEST_F(TokenReaderTest, Boder) {
    for (int i = 0; i < 99; ++i) {
        reader->GetToken();
        EXPECT_EQ(reader->Index.Get(), 1 + i);
        EXPECT_EQ(reader->IsEnd(), false);
    }
    auto token = reader->GetToken();
    EXPECT_EQ(token->StrValue.Get(), "acc 10, 10");
    EXPECT_EQ(reader->IsEnd(), true);
    EXPECT_EQ(reader->SeekToken(), nullptr);
    EXPECT_EQ(reader->GetCurLineNum(), 0);
    EXPECT_EQ(reader->GetLastLineNum(), 10);
    EXPECT_EQ(reader->Index.Get(), 100);
}