# LectureCode
>JAVA in IDEAProject & C++ in VisualStudio

##My algorithm home work
###1.Closet Point Pair
###2.Convex Hull
###3.Cut-Vertex
###4.is Bipartiteness
###5.Red Black Tree
A program to mantain a tree that meet the RBT's conditions.
###6.Dynamic Hash Table
A Hash Table using pointer to a Bucket pointer array.When insertion happend and table need split,double expand table but new extension only have points to old part.It avoid high cost on contributiing a hash table. This new insertion will be inserted in new extension and the corresponding bucket's data will be taken out and reinsert again.  
###7.Optimal Binary Search Tree

###8.Longest Common Subsequents
###9.Akari puzzle
这个比较难，想了一种关灯的搜索方法。主要规则是：
得到满足所有黑色有数字方块的一个带有未照亮的块的可能解集。
解集大小为 4~（3号块数量+1号块数量）+6~（2号块数量）—灯互相照射到的解的集合。集合中的灯为黄色。

1.直接给所有白色块，放置棕色灯，棕色灯可能被其他棕色灯互相照射，当棕色灯被黄色灯照射到的时候，自动变成空白块，记录每个棕色灯被几个棕色灯照亮，每个白色块被几个灯照亮。
开始剪枝：
2如果有块未被照亮，本解为不可行解
3找出数值为0的棕色块，变为黄色。
4.找出数值为1的白色快，如果该白色块是被棕色灯照亮，把棕色灯变成黄色
5.对所有的拐角点进行分支，去掉拐角后形成新分支，去掉拐角照到的两个点形成新的分支。
6.出掉所有拐角后，对共线的棕色灯进行处理。逐个熄灭棕色灯，当熄灭某个棕色灯并且导致出现空白块时，把该灯改为黄色（其他棕色灯被黄色照射变成空白块）。然后若出现空白块，则本树失败。考虑第五步的下一课树。


