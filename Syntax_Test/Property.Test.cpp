#include "pch.h"

/*
 ���� Property װ���� �Ƿ��ܹ���������
*/

class PropertyTest : public ::testing::Test {
protected:
    int _p1;
    int _rop2;
    Property<int> p1 = Property<int>(_p1);          // һ������
    ROProperty<int> rop2 = ROProperty<int>(_rop2);  // ֻ������

    void SetUp() override {}
    void TearDown() override {}
};

/*
 �������Ե� get �� set ����
*/
TEST_F(PropertyTest, GetSet) {
    p1.Set(2);
    EXPECT_EQ(p1.Get(), 2);
}