#ifndef PREDICTOR_HPP
#define PREDICTOR_HPP
#include<cstdint>
#include<utility>
class Predictor{
public:
    std::pair<bool,uint32_t> get(int expc){return std::make_pair(false,0);}
    void feed(uint32_t frompc,uint32_t topc){//true: jumped
    }
};


class PredictPC{
    uint32_t pc[4]={0},pcset=0;
    bool pause=false;
public:
    void set(uint32_t spc){pcset=spc;}
    void set(/*bool branch,*/Predictor &pd){
        auto pred=pd.get(pc[0]);
        if(pred.first){pcset=pred.second;}
        else pcset=pc[0]+4;
    }
    void hold(){pause=true;}
    void step(){
        if(pause){
            pause=false;return;
        }
        for(int i=3;i>0;i--)pc[i]=pc[i-1];
        pc[0]=pcset;
    }
    uint32_t get(int offset){
        return pc[offset];
    }
};

#endif