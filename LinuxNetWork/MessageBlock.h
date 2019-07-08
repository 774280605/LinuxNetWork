#pragma once
class DataBlock;
class MessageBlock
{
public:
	MessageBlock();
	virtual ~MessageBlock();

	int add(char* data, long len);
	int remove(char*buffer,long len);
private:
	void expand();

private:
	DataBlock*first_{nullptr};
	DataBlock*last_{nullptr};
	
	long totalLen_{};
};
