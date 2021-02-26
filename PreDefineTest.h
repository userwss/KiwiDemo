#ifndef PREDEFINE_H
#define PREDEFINE_H

namespace preDefine {
    class Test {
    public:
        float getTest();
    };
}
#endif  //PREDEFINE_H

#ifdef PRE_DEFINE_H
#ifndef PRE_DEFINE_H_
#define PRE_DEFINE_H_

float preDefine::Test::getTest() {
    return 1.f;
}

#endif  //PRE_DEFINE_H_
#endif  //PRE_DEFINE_H
