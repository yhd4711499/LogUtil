//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_PTR_H
#define WNSLOGHELPER_PTR_H

struct delete_ptr {
    template<class T>
    void operator()(T *p) {
        delete p;
    }
};

#define delete_v(X) std::for_each(X.begin(), X.end(), delete_ptr())

#endif //WNSLOGHELPER_PTR_H
