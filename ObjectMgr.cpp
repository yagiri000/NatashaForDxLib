#include "ObjectMgr.h"
#include "Func.h"
#include "Draw.h"

ObjectMgr& obj = ObjectMgr::get();

ObjectMgr& ObjectMgr::get(){
	static ObjectMgr inst;
	return inst;
}

void ObjectMgr::init(){
}

ObjectMgr::ObjectMgr()
{
};


