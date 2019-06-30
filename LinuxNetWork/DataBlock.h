#pragma once

class DataBlock
{
public:
	DataBlock();
	virtual ~DataBlock();






private:
	char*buffer_{nullptr};

	int totalSize_{};
	DataBlock*prev_{nullptr};
	DataBlock*next_{nullptr};
};
