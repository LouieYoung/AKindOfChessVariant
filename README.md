﻿# 基于 Qt5 的 C++ 中宫象棋实现
这是一个基于 Qt5 的 C++ 中宫象棋实现，完美实现了该种象棋变体的基本规则，适合棋类爱好者尝鲜。

点击“中宫象棋规则说明.jpg”了解该种象棋变体的具体规则

下载“C++ 实现中宫象棋.exe”实际体验对弈的乐趣

      中宫象棋规则说明

      1、棋具为中国象棋棋子完整一副，棋盘 9x9线格正方形，没有河界，双方也没有各自的九宫。
      2、只有一个共用的中心九宫，只有将帅受九宫限制，不能出宫。
      3、棋子的基本走法吃法同中国象棋，只是士、象可走全盘有效位置、兵卒起步就可以横移走或吃，
      重要的是这里将帅没有"飞将"规则，是可以照面的。
      4、虽然取胜方法还是吃掉对方的将或帅，但是一定要"白吃"才算胜利，即：吃掉敌方将或帅的棋
      不能随即就被敌方吃掉，因为吃掉对方刚吃掉将或帅的棋也为胜。就是说，当自己的棋看住自己
      的将帅时，敌方是不能吃的，此情况下叫杀将帅可称之为"牵将"，不属于"将军"，被"牵将"时
      可以不应将，但此时不能全部撤离被"牵将"保护棋。只有在要杀无保护的将帅时，才算"将军"，
      解将的方式多了一项"看护"，此时若无法解将为输棋。
      5、围困敌将或帅四面皆为死路敌方又无法随即打通时也为胜：将或帅周围横竖四个紧邻点不能没
      有空位，该空位称作"气点"，"气点"不限中宫 内外，将帅即使不动也必须有自己的"气点"才行，
      无论这个气点能不能走，被围堵无气点的将或帅为被"困将"，被困方必须随即解困，无法解困时为输。
      不能主动给自己的将或帅造成无"气点"局面，自困为输。
      6、中宫象棋关于兵（卒）进到对方底线的规则：
              五枚底线兵为胜。
              四枚底线兵可兑掉敌人一枚车。
              三枚底线兵可对掉敌人一匹马。
              两枚底线兵可对掉敌人一枚炮。
              一枚底线兵可兑掉敌人一枚卒。
              兑掉 等同走棋。
              
 开发者の微博：@如意羊Louie  2018年12月31日

