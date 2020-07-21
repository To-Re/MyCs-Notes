#ifndef _STRBLOBPTR_H_
#define _STRBLOBPTR_H_

#include "StrBlob.h"

class StrBlobPtr {
public:
    StrBlobPtr(): curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0):
        wptr(a.data), curr(sz) {}
    string &deref() const; // 解引用
    StrBlobPtr& incr(); // 递增
private:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

#endif