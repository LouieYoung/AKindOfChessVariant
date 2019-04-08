#ifndef STONE_H
#define STONE_H

#include <QString>
class Stone
{
public:
    Stone();

    enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG,NO};


    int _row;
    int _col;
    int _id;
    bool _dead;
    bool _red;
    bool _qi;
    bool _select;
    TYPE _type;


    void init(int id)
    {
        struct
        {
            int row,col;
            Stone::TYPE type;
        }pos[16] =
        {
        {0,0,Stone::CHE},
        {0,8,Stone::CHE},
        {0,1,Stone::MA},
        {0,7,Stone::MA},
        {0,2,Stone::XIANG},
        {0,6,Stone::XIANG},
        {0,3,Stone::SHI},
        {0,5,Stone::SHI},
        {0,4,Stone::PAO},
        {1,4,Stone::PAO},

        {2,0,Stone::BING},
        {2,2,Stone::BING},
        {2,4,Stone::BING},
        {2,6,Stone::BING},
        {2,8,Stone::BING},

        {3,4,Stone::JIANG},
        };

        _id = id;
        _dead = false;
        _select = false;
        _red = id<16;
        _qi = true;

        if(id<16)
        {
            _row=pos[id].row;
            _col=pos[id].col;
            _type=pos[id].type;
        }
        else
        {

            _row=8-pos[id-16].row;
            _col=8-pos[id-16].col;

            _type=pos[id-16].type;
        }
    }


    QString getText()
    {
        switch(this->_type)
        {
            case CHE:
                if(this->_red)
                    return QString::fromLocal8Bit("车");
                else
                    return QString::fromLocal8Bit("車");
            case MA:
                if(this->_red)
                    return QString::fromLocal8Bit("马");
                else
                    return QString::fromLocal8Bit("馬");
            case PAO:
                if(this->_red)
                    return QString::fromLocal8Bit("砲");
                else
                    return QString::fromLocal8Bit("炮");
            case BING:
                if(this->_red)
                    return QString::fromLocal8Bit("兵");
                else
                    return QString::fromLocal8Bit("卒");
            case JIANG:
                if(this->_red)
                    return QString::fromLocal8Bit("帅");
                else
                    return QString::fromLocal8Bit("将");
            case SHI:
                if(this->_red)
                    return QString::fromLocal8Bit("仕");
                else
                    return QString::fromLocal8Bit("士");
            case XIANG:
                if(this->_red)
                    return QString::fromLocal8Bit("相");
                else
                    return QString::fromLocal8Bit("象");
            case NO:
                return QString::fromLocal8Bit("无");
        }
        return QString::fromLocal8Bit("棋子类型错误");
    }





};

#endif // STONE_H
