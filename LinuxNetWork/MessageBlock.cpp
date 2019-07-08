#include "MessageBlock.h"
#include "DataBlock.h"
MessageBlock::MessageBlock(){
}

MessageBlock::~MessageBlock(){
}

int MessageBlock::add(char* data, long len){
	if (last_==nullptr){
		auto tmpBlock = new DataBlock();
		tmpBlock->add(data, len);
		first_ = last_ = tmpBlock;
	}
	else{
		auto tmpBlock = last_;
		auto tmpSpace = last_->space();
		
		if (len > tmpSpace){
			tmpBlock->add(data, tmpSpace);
			len -= tmpSpace;
			data += tmpSpace;
			auto newBuffer = new DataBlock();
			newBuffer->add(data, len);
			tmpBlock->next(newBuffer);
			
		}else{
			last_->add(data, len);
		}		
	}
}

int MessageBlock::remove(char* buffer, long len){
	if (last_ == nullptr)
		return 0;
	auto tmpFirst = first_;
	while (tmpFirst&& len>0){
		auto tmpSpace = tmpFirst->space();
		if(tmpSpace>len){
			tmpFirst->remove(buffer, len);
			buffer += len;
			len -= len;
		}
		else{
			tmpFirst->remove(buffer, tmpFirst->getDataLen());
			buffer += tmpFirst->getDataLen();
			len -= tmpFirst->getDataLen();
		}
		tmpFirst = tmpFirst->next();
	}
	return 0;
}

void MessageBlock::expand(){

}
