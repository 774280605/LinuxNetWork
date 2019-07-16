#include "pch.h"
#include "../LinuxNetWork/MessageBlock.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(MessageBlock,DataBlock){
	MessageBlock mb;
	mb.add("zhangxiaofei", 12);

}